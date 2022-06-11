#ifndef SAVEEDITABLEASSIGNMENTCOMMAND_H
#define SAVEEDITABLEASSIGNMENTCOMMAND_H


#include "command.h"
#include <QJsonDocument>

class SaveEditableAssignmentCommand : public Command
{
private:
    const QJsonDocument& json_doc_;
public:
    SaveEditableAssignmentCommand(const QJsonDocument& json_doc);
    bool execute() override;
};

#endif // SAVEEDITABLEASSIGNMENTCOMMAND_H
