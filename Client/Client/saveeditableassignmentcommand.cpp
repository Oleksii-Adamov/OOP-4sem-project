#include "saveeditableassignmentcommand.h"
#include "jsonfile.h"
#include "filepath.h"

SaveEditableAssignmentCommand::SaveEditableAssignmentCommand(const QJsonDocument& json_doc, const QString& assignment_name)
    :json_doc_(json_doc), assignment_name_(assignment_name)
{

}
bool SaveEditableAssignmentCommand::execute()
{
    writeJsonFile(json_doc_, GetAssignmentPath(assignment_name_));
    return false;
}
