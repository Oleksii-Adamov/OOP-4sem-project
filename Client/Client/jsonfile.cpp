#include "jsonfile.h"
#include <QFile>
#include "client.h"
#include <cstdint>
#include "net.h"
#include "messagetypes.h"
#include <QJsonObject>

QJsonDocument QJsonDocumentFromServerMessage(net::message<CustomMsgTypes>& message)
{
    uint64_t size;
    message >> size;
    QString json_string = "";
    for (uint64_t i = 0; i < size; i++) {
      char c;
      message >> c;
      json_string = c + json_string;
    }
    //qDebug() << json_string;
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()) {
        throw std::runtime_error(std::string("JSON doc is null"));
    }
    if (!json_doc.isObject()) {
        throw std::runtime_error(std::string("JSON is not an object "));
    }

    return json_doc;
}

QJsonDocument QJsonDocumentFromJsonFile(const std::string& file_path)
{
    QFile file_obj(QString::fromStdString(file_path));
    if (!file_obj.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(std::string("Failed to open ") + file_path);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    //qDebug() << "File:\n" + json_string + "\n";
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()) {
        throw std::runtime_error(std::string("Failed to create JSON doc ") + file_path);
    }
    if (!json_doc.isObject()) {
        throw std::runtime_error(std::string("JSON is not an object ") + file_path);
    }

    return json_doc;
}

void writeJsonFile(const QJsonDocument& json_doc, const std::string& file_path)
{
    QString json_string = json_doc.toJson();
    QFile save_file(QString::fromStdString(file_path));
    if (!save_file.open(QIODevice::WriteOnly)) {
        throw std::runtime_error(std::string("failed to open save file") + file_path);
    }
    save_file.write(json_string.toLocal8Bit());
    save_file.close();
}


void WriteQStringToMsg(const QString& q_string, net::message<CustomMsgTypes>& message)
{
    std::string std_str = q_string.toStdString();
    uint64_t c_str_size = uint64_t(std_str.size());
    for (uint64_t i = 0; i < c_str_size; i++) {
        message << (char) std_str[i];
    }
    message << c_str_size;
}

void WriteJsonToMsg(const QJsonDocument& json_doc, net::message<CustomMsgTypes>& message)
{
    WriteQStringToMsg(json_doc.toJson(), message);
}

Assignment GetAssignmentFromJson(const QJsonDocument& json_doc)
{
   GetAssignmentFromJson(json_doc.object());
}

Assignment GetAssignmentFromJson(QJsonObject& json_obj)
{
    QJsonObject assignment_obj =  json_obj.take("Assignment").toObject();
    return Assignment(assignment_obj.take("assignment_id").toString().toULongLong(), assignment_obj.take("teacher_user_id").toString().toULongLong(),
                      assignment_obj.take("assignment_name").toString().toStdString(),
                      assignment_obj.take("assignment_creation_date").toString().toStdString(),
                      assignment_obj.take("assignment_data").toString().toStdString(),
                      assignment_obj.take("assignment_max_score").toString().toULongLong());
}

AssignmentSession GetAssignmentSessionFromJson(QJsonObject& json_obj)
{
    QJsonObject assignment_obj =  json_obj.take("AssignmentSession").toObject();
    return AssignmentSession(assignment_obj.take("assignment_session_id").toString().toULongLong(), assignment_obj.take("classroom_id").toString().toULongLong(),
                      assignment_obj.take("assignment_id").toString().toStdString().toULongLong(),
                      assignment_obj.take("assignment_session_start_date").toString().toStdString(),
                      assignment_obj.take("assignment_session_end_date").toString().toStdString());
}

StudentAssignmentSession GetStudentAssignmentSessionFromJson(QJsonObject& json_obj)
{
    QJsonObject student_assignment_session_object = json_obj.take("StudentAssignmentSession").toObject();
    QString student_assignment_session_status_string = student_assignment_session_object.take("student_assignment_session_status").toString();
    StudentAssignmentSessionStatus student_assignment_session_status = StudentAssignmentSessionStatus::not_submitted;
    if (student_assignment_session_status_string == "not_submitted")
    {
        student_assignment_session_status = StudentAssignmentSessionStatus::not_submitted;
    }
    else if (student_assignment_session_status_string == "submitted")
    {
        student_assignment_session_status = StudentAssignmentSessionStatus::submitted;
    }
    else if (student_assignment_session_status_string == "checked")
    {
        student_assignment_session_status = StudentAssignmentSessionStatus::checked;
    }
    StudentAssignmentSession student_assignment_session(
                student_assignment_session_object.take("student_user_id").toString().toULongLong(),
                student_assignment_session_object.take("assignment_session_id").toString().toULongLong(),
                student_assignment_session_status, "",
                student_assignment_session_object.take("student_assignment_session_score").toString().toInt(),
                student_assignment_session_object.take("student_assignment_session_finish_date").toString().toStdString());
    return student_assignment_session;
}

std::string GetStringFromMsg(net::message<CustomMsgTypes>& message)
{
    std::string ret = "";
    uint64_t size;
    message >> size;
    for (uint64_t i = 0; i < size; i++)
    {
        char c;
        message >> c;
        ret = c + ret;
    }
    return ret;
}
