#ifndef SAVEEDITABLEASSIGNMENTCOMMAND_H
#define SAVEEDITABLEASSIGNMENTCOMMAND_H


#include "command.h"
#include <QJsonDocument>

/*!
 * \brief Save assignment created by teacher as JSON file locally (Command pattern - concrete command)
 */
class SaveEditableAssignmentCommand : public Command
{
private:
    const QJsonDocument& json_doc_;
    const QString assignment_name_;
public:
    SaveEditableAssignmentCommand(const QJsonDocument& json_doc, const QString& assignment_name);
    bool execute() override;
};

#endif // SAVEEDITABLEASSIGNMENTCOMMAND_H
