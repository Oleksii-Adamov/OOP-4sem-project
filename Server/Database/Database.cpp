#include "Database.h"
#include "DatabaseLog.h"
#include "SQLite/SQLiteAdapter.h"


void Database::init()
{
    DatabaseOperation* db = new SQLiteAdapter();
    if(db->initDatabase())
        DatabaseLog::out("Started!");
    else
        DatabaseLog::error("Failed to start database!");
}

std::pair<bool, bool> Database::checkUniqueLogin(const std::string& login)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto commandResFull = db->checkUniqueRecord("User", "Login", login);
    delete db;
    return commandResFull;
}

bool Database::createNewUser(const User& NewUser, const std::string& password)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->execInsert("User", {"Login", "UserName"},
                               {NewUser.getLogin(), NewUser.getUserName()});
    if(!flag)
        return false;
    auto commandResFull = db->getLastTableID("User", "UserID");
    if(!commandResFull.first)
        return false;
    flag = db->execInsert("Authorization", {"UserID", "Password"},
                          {std::to_string(commandResFull.second), password});
    delete db;
    if(!flag)
        return false;
    return true;
}

std::pair<bool, bool> Database::checkLogIn(const std::string& login, const std::string& password)
{
    DatabaseOperation* db = new SQLiteAdapter();

    std::string script1 = "SELECT UserID\n"
                          "FROM 'User'\n"
                          "WHERE (User.Login = '" + login + "');";
    auto commandResFull1 = db->execSelect(script1, 1);
    if(!commandResFull1.first)
        return {false, false};
    if(commandResFull1.second[0].empty())
        return {true, false};

    std::string script2 = "SELECT Password\n"
                          "FROM 'Authorization'\n"
                          "WHERE (Authorization.UserID = '" + commandResFull1.second[0][0] + "');";
    auto commandResFull2 = db->execSelect(script2, 1);
    if(!commandResFull2.first || commandResFull2.second[0].empty())
        return {false, false};
    delete db;

    return {true, password == commandResFull2.second[0][0]};
}

std::pair<bool, std::vector<Classroom>> Database::selectAllClassroomsWhereUserIsTeacher(ID UserId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT ClassroomID, TeacherUserID, ClassroomName\n"
                         "FROM 'Classroom' INNER JOIN 'User' ON (TeacherUserID = UserID)\n"
                         "WHERE (User.UserID = '" + std::to_string(UserId) + "');";
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
                         "WHERE (User.UserID = '" + std::to_string(UserId) + "');";
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

std::pair<bool, std::string> Database::getStudentAssignmentSessionAnswer(ID StudentUserId, ID AssignmentSessionId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT Student_AssignmentSession.StudentAssignmentSessionAnswer\n"
                         "FROM 'Student_AssignmentSession'\n"
                         "WHERE (Student_AssignmentSession.StudentUserID = '" + std::to_string(StudentUserId)
                         + "' and Student_AssignmentSession.AssignmentSessionId = '" + std::to_string(AssignmentSessionId) + "');";
    auto commandResFull = db->execSelect(script, 1);
    delete db;
    if(!commandResFull.first)
        return {false, ""};
    const auto& commandRes = commandResFull.second;

    if(!commandRes[0].empty())
        return {true, commandRes[0][0]};
    else
        return {false, ""};
}

std::pair<bool, std::vector<StudentAssignmentSessionInfoForTeacher>> Database::getAllStudentAssignmentSessionAnswers(ID AssignmentSessionId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT *\n"
                         "FROM ('User' INNER JOIN 'Student_AssignmentSession' ON (Student_AssignmentSession.StudentUserID = User.UserID))\n"
                         "INNER JOIN 'AssignmentSession' ON (Student_AssignmentSession.AssignmentSessionID = AssignmentSession.AssignmentSessionID)\n"
                         "WHERE (AssignmentSession.AssignmentSessionId = '" + std::to_string(AssignmentSessionId) + "');";
    auto commandResFull = db->execSelect(script, 13);
    delete db;
    if(!commandResFull.first)
        return {false, {}};
    const auto& commandRes = commandResFull.second;

    std::vector<StudentAssignmentSessionInfoForTeacher> res;
    User currUser;
    StudentAssignmentSession currStudentAssignmentSession;
    for(size_t i=0; i<commandRes[0].size(); i++)
    {
        currUser.setUserId(std::stoi(commandRes[0][i]));
        currUser.setLogin(commandRes[1][i]);
        currUser.setUserName(commandRes[2][i]);

        currStudentAssignmentSession.setStudentUserId(std::stoi(commandRes[3][i]));
        currStudentAssignmentSession.setAssignmentSessionId(std::stoi(commandRes[4][i]));
        switch(std::stoi(commandRes[5][i]))
        {
            case 0: currStudentAssignmentSession.setStudentAssignmentSessionStatus(StudentAssignmentSessionStatus::not_submitted);
                break;
            case 1: currStudentAssignmentSession.setStudentAssignmentSessionStatus(StudentAssignmentSessionStatus::submitted);
                break;
            case 2: currStudentAssignmentSession.setStudentAssignmentSessionStatus(StudentAssignmentSessionStatus::checked);
                break;
        }
        currStudentAssignmentSession.setStudentAssignmentSessionScore(std::stoi(commandRes[7][i]));
        currStudentAssignmentSession.setStudentAssignmentSessionFinishDate(commandRes[8][i]);
        res.emplace_back(currStudentAssignmentSession, currUser);
    }
    return {true, res};
}

std::pair<bool, std::string> Database::getAssignmentData(ID AssignmentId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT Assignment.AssignmentData\n"
                         "FROM 'Assignment'\n"
                         "WHERE (Assignment.AssignmentID = '" + std::to_string(AssignmentId) + "');";
    auto commandResFull = db->execSelect(script, 1);
    delete db;
    if(!commandResFull.first)
        return {false, ""};
    const auto& commandRes = commandResFull.second;

    if(!commandRes[0].empty())
        return {true, commandRes[0][0]};
    else
        return {false, ""};
}

bool Database::updateStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo)
{
    DatabaseOperation* db = new SQLiteAdapter();
    int status;
    switch(UpdatedInfo.getStudentAssignmentSessionStatus())
    {
        case StudentAssignmentSessionStatus::not_submitted: status = 0;
            break;
        case StudentAssignmentSessionStatus::submitted: status = 1;
            break;
        case StudentAssignmentSessionStatus::checked: status = 2;
            break;
    }

    auto flag = db->execUpdate("Student_AssignmentSession",
                               {"StudentAssignmentSessionStatus", "StudentAssignmentSessionAnswer", "StudentAssignmentSessionScore",
                                "StudentAssignmentSessionFinishDate"},
                               {std::to_string(status), UpdatedInfo.getStudentAssignmentSessionAnswer(),
                                std::to_string(UpdatedInfo.getStudentAssignmentSessionScore()), UpdatedInfo.getStudentAssignmentSessionFinishDate()},
                               "Student_AssignmentSession.StudentUserID = " + std::to_string(UpdatedInfo.getStudentUserId())
                               + " and Student_AssignmentSession.AssignmentSessionID = " + std::to_string(UpdatedInfo.getAssignmentSessionId()) + ");");
    delete db;
    if(!flag)
        return false;
    return true;
}