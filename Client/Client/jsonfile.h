/*! \file jsonfile.h
    \brief Functions that parse JSON.
*/
#ifndef JSONFILE_H
#define JSONFILE_H

#include<QJsonDocument>
#include <string>
#include "net.h"
#include "messagetypes.h"

QJsonDocument QJsonDocumentFromServerMessage(net::message<CustomMsgTypes>& msg);
QJsonDocument QJsonDocumentFromJsonFile(const std::string& file_path);
void writeJsonFile(const QJsonDocument& json_doc, const std::string& file_path);
void sendJsonFile(const QJsonDocument& json_doc);

#endif // JSONFILE_H
