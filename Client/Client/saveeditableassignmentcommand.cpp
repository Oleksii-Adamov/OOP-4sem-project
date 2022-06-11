#include "saveeditableassignmentcommand.h"
#include "jsonfile.h"

SaveEditableAssignmentCommand::SaveEditableAssignmentCommand(const QJsonDocument& json_doc)
    :json_doc_(json_doc)
{

}
bool SaveEditableAssignmentCommand::execute()
{
    writeJsonFile(json_doc_, "assinment_json_from_teacher_to_server.json");
    return false;
}
