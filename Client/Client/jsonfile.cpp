#include "jsonfile.h"
#include <QFile>

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
