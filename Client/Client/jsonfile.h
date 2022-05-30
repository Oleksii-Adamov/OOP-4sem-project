#ifndef JSONFILE_H
#define JSONFILE_H

#include<QJsonDocument>
#include <string>

QJsonDocument QJsonDocumentFromJsonFile(const std::string& file_path);

#endif // JSONFILE_H
