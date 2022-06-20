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