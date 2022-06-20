#include "jsonfile.h"
#include <QFile>
#include "client.h"
#include <cstdint>

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
    qDebug() << json_string;
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
    qDebug() << "File:\n" + json_string + "\n";
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

void sendJsonFile(const QJsonDocument& json_doc)
{
    QString json_string = json_doc.toJson();
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::ServerMessage;
    std::string json_std_str = json_string.toStdString();
    uint32_t json_c_str_size = uint32_t(json_string.size());
    for (uint32_t i = 0; i < json_c_str_size; i++) {
        message << json_std_str[i];
    }
    message << uint32_t(json_string.size());
    Client::GetInstance()->Send(message);
}
