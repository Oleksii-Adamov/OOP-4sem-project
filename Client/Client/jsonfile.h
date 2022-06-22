/*! \file jsonfile.h
    \brief Functions that parse JSON.
*/
#ifndef JSONFILE_H
#define JSONFILE_H

#include<QJsonDocument>
#include <string>
#include "net.h"
#include "messagetypes.h"
#include <QString>
#include "Assignment.h"
#include <QJsonObject>
#include "AssignmentSession.h"
#include "StudentAssignmentSession.h"

QJsonDocument QJsonDocumentFromServerMessage(net::message<CustomMsgTypes>& msg);
QJsonDocument QJsonDocumentFromJsonFile(const std::string& file_path);
void writeJsonFile(const QJsonDocument& json_doc, const std::string& file_path);
void WriteJsonToMsg(const QJsonDocument& json_doc, net::message<CustomMsgTypes>& message);
void WriteQStringToMsg(const QString& q_string, net::message<CustomMsgTypes>& message);
Assignment GetAssignmentFromJson(QJsonDocument json_doc);
Assignment GetAssignmentFromJson(QJsonObject& json_obj);
AssignmentSession GetAssignmentSessionFromJson(QJsonObject& json_obj);
std::string GetStringFromMsg(net::message<CustomMsgTypes>& message);
StudentAssignmentSession GetStudentAssignmentSessionFromJson(QJsonObject& json_obj);

#endif // JSONFILE_H
