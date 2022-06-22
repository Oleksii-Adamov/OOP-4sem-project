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
    QJsonObject json_doc_obj = json_doc.object();
    QJsonObject assignment_obj =  json_doc_obj.take("Assignment").toObject();
    return Assignment(assignment_obj.take("assignment_id").toString().toULongLong(), assignment_obj.take("teacher_user_id").toString().toUInt(),
                      assignment_obj.take("assignment_name").toString().toStdString(),
                      assignment_obj.take("assignment_creation_date").toString().toStdString(),
                      assignment_obj.take("assignment_data").toString().toStdString(),
                      assignment_obj.take("assignment_max_score").toString().toULongLong());
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
