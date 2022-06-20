#include "Database.h"
#include "DatabaseService.h"
#include "SQLite/SQLiteAdapter.h"


void Database::init()
{
    DatabaseService::initDatabase();
}

std::pair<bool, std::vector<Classroom>> Database::selectAllClassroomsWhereUserIsTeacher(ID UserId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT ClassroomID, TeacherUserID, ClassroomName\n"
                         "FROM 'Classroom' INNER JOIN 'User' ON (TeacherUserID = UserID)\n"
                         "WHERE (User.UserID = " + std::to_string(UserId) + ");";
    auto commandResFull = db->execSelect(script, 3);
    delete db;
    if(!commandResFull.first)
        return {false, {}};
    const auto& commandRes = commandResFull.second;

    std::vector<Classroom> res;
    Classroom currRes;
    for(size_t i=0; i<commandRes[0].size(); i++)
    {
        currRes.setClassroomId(std::stoi(commandRes[0][i]));
        currRes.setTeacherUserId(std::stoi(commandRes[1][i]));
        currRes.setName(commandRes[2][i]);
        res.push_back(currRes);
    }
    return {true, res};
}

std::pair<bool, std::vector<Assignment>> Database::selectAllAssignmentUserCreated(ID UserId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT Assignment.AssignmentID, Assignment.TeacherUserID, "
                         "Assignment.AssignmentName, Assignment.AssignmentCreationDate, Assignment.AssignmentMaxScore\n"
                         "FROM 'Assignment' INNER JOIN 'User' ON (TeacherUserID = UserID)\n"
                         "WHERE (User.UserID = " + std::to_string(UserId) + ");";
    auto commandResFull = db->execSelect(script, 5);
    delete db;
    if(!commandResFull.first)
        return {false, {}};
    const auto& commandRes = commandResFull.second;

    std::vector<Assignment> res;
    Assignment currRes;
    for(size_t i=0; i<commandRes[0].size(); i++)
    {
        currRes.setAssignmentId(std::stoi(commandRes[0][i]));
        currRes.setTeacherUserId(std::stoi(commandRes[1][i]));
        currRes.setAssignmentName(commandRes[2][i]);
        currRes.setAssignmentCreationDate(commandRes[3][i]);
        currRes.setAssignmentMaxScore(std::stoi(commandRes[4][i]));
        res.push_back(currRes);
    }
    return {true, res};
}

bool Database::joinUserToClassroom(ID UserId, ID ClassroomId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->execInsert("Student_Classroom", {"ClassroomID", "StudentUserID"},
                                         {std::to_string(ClassroomId), std::to_string(UserId)});
    delete db;
    if(!flag)
        return false;
    return true;
}

bool Database::createNewClassroom(ID TeacherUserId, const std::string& ClassroomName)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->execInsert("Classroom", {"TeacherUserID", "ClassroomName"},
                               {std::to_string(TeacherUserId), '"'+ClassroomName+'"'});
    delete db;
    if(!flag)
        return false;
    return true;
}