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
    {
        delete db;
        return false;
    }
    auto commandResFull = db->getLastTableID("User", "UserID");
    if(!commandResFull.first)
    {
        delete db;
        return false;
    }
    flag = db->execInsert("Authorization", {"UserID", "Password"},
                          {std::to_string(commandResFull.second), password});
    delete db;
    if(!flag)
        return false;
    return true;
}

std::pair<bool, User> Database::checkLogIn(const std::string& login, const std::string& password)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script1 = "SELECT User.UserID, User.Login, User.UserName\n"
                          "FROM 'User'\n"
                          "WHERE (User.Login = '" + login + "');";
    auto commandResFull1 = db->execSelect(script1, 3);
    delete db;
    if(!commandResFull1.first)
        return {false, User()};
    if(commandResFull1.second[0].empty())
        return {true, User{0,"",""}};

    db = new SQLiteAdapter();
    std::string script2 = "SELECT Password\n"
                          "FROM 'Authorization'\n"
                          "WHERE (Authorization.UserID = '" + commandResFull1.second[0][0] + "');";
    auto commandResFull2 = db->execSelect(script2, 1);
    delete db;
    if(!commandResFull2.first || commandResFull2.second[0].empty())
        return {false, User()};

    if(password == commandResFull2.second[0][0])
    {
        User result;
        result.setUserId(std::stoull(commandResFull1.second[0][0]));
        result.setLogin(commandResFull1.second[0][1]);
        result.setUserName(commandResFull1.second[0][2]);
        return {true, result};
    }
    return {true, User{0,"",""}};
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
        currRes.setClassroomId(std::stoull(commandRes[0][i]));
        currRes.setTeacherUserId(std::stoull(commandRes[1][i]));
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
        currRes.setAssignmentId(std::stoull(commandRes[0][i]));
        currRes.setTeacherUserId(std::stoull(commandRes[1][i]));
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
                               {std::to_string(TeacherUserId), ClassroomName});
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
        currUser.setUserId(std::stoull(commandRes[0][i]));
        currUser.setLogin(commandRes[1][i]);
        currUser.setUserName(commandRes[2][i]);

        currStudentAssignmentSession.setStudentUserId(std::stoull(commandRes[3][i]));
        currStudentAssignmentSession.setAssignmentSessionId(std::stoull(commandRes[4][i]));
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

std::pair<bool, Assignment> Database::getAssignmentWithoutData(ID AssignmentId)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT Assignment.AssignmentID, Assignment.TeacherUserID, Assignment.AssignmentName, "
                         "Assignment.AssignmentCreationDate, Assignment.AssignmentMaxScore\n"
                         "FROM 'Assignment'\n"
                         "WHERE (Assignment.AssignmentID = '" + std::to_string(AssignmentId) + "');";
    auto commandResFull = db->execSelect(script, 5);
    delete db;
    if(!commandResFull.first)
        return {false, Assignment()};
    const auto& commandRes = commandResFull.second;

    if(!commandRes[0].empty())
    {
        Assignment result;
        result.setAssignmentId(std::stoull(commandRes[0][0]));
        result.setTeacherUserId(std::stoull(commandRes[1][0]));
        result.setAssignmentName(commandRes[2][0]);
        result.setAssignmentCreationDate(commandRes[3][0]);
        result.setAssignmentMaxScore(std::stoi(commandRes[4][0]));
        return {true, result};
    }
    return {false, Assignment()};
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

std::pair<bool, Assignment> Database::createNewAssignment(const Assignment& NewAssignment)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->execInsert("Assignment", {"TeacherUserID", "AssignmentName", "AssignmentData", "AssignmentMaxScore"},
                               {std::to_string(NewAssignment.getTeacherUserId()), NewAssignment.getAssignmentName(),
                                NewAssignment.getAssignmentData(), std::to_string(NewAssignment.getAssignmentMaxScore())});
    auto lastIdResult = db->getLastTableID("Assignment", "AssignmentID");
    delete db;

    if(!flag || !lastIdResult.first)
        return {false, Assignment()};
    return Database::getAssignmentWithoutData(lastIdResult.second);
}

bool Database::submitStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->exec("UPDATE Student_AssignmentSession SET "
                         "StudentAssignmentSessionStatus = '1', \n"
                         "StudentAssignmentSessionAnswer = '" + UpdatedInfo.getStudentAssignmentSessionAnswer() +"', \n"
                         "StudentAssignmentSessionFinishDate = datetime('now')\n"
                         "WHERE Student_AssignmentSession.StudentUserID = " + std::to_string(UpdatedInfo.getStudentUserId())
                         + " and Student_AssignmentSession.AssignmentSessionID = " + std::to_string(UpdatedInfo.getAssignmentSessionId()) + ");");
    delete db;
    if(!flag)
        return false;
    return true;
}

bool Database::evaluateStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->execUpdate("Student_AssignmentSession",
                               {"StudentAssignmentSessionStatus", "StudentAssignmentSessionScore"},
                               {"2", std::to_string(UpdatedInfo.getStudentAssignmentSessionScore())},
                               "Student_AssignmentSession.StudentUserID = " + std::to_string(UpdatedInfo.getStudentUserId())
                               + " and Student_AssignmentSession.AssignmentSessionID = " + std::to_string(UpdatedInfo.getAssignmentSessionId()) + ");");
    delete db;
    if(!flag)
        return false;
    return true;
}

std::pair<bool, Assignment> Database::updateAssignment(const Assignment& UpdatedInfo)
{
    DatabaseOperation* db = new SQLiteAdapter();
    std::string script = "SELECT Assignment.AssignmentID\n"
                         "FROM 'Assignment' INNER JOIN 'AssignmentSession' ON (Assignment.AssignmentID = AssignmentSession.AssignmentID)\n"
                         "WHERE (Assignment.AssignmentID = '" + std::to_string(UpdatedInfo.getAssignmentId()) + "');";
    auto commandResFull = db->execSelect(script, 1);
    if(!commandResFull.first)
    {
        delete db;
        return {false, Assignment()};
    }

    Assignment result;
    if(commandResFull.second[0].empty())
    {
        // No assignment sessions, can be updated
        auto flag = db->execUpdate("Assignment",
                                   {"AssignmentName", "AssignmentData", "AssignmentMaxScore"},
                                   {UpdatedInfo.getAssignmentName(), UpdatedInfo.getAssignmentData(),
                                    std::to_string(UpdatedInfo.getAssignmentMaxScore())},
                                   "Assignment.AssignmentID = '" + std::to_string(UpdatedInfo.getAssignmentId()) + "';");
        delete db;
        return {flag, result};
    }
    // There are assignment sessions, can't be updated - cloning
    return Database::createNewAssignment(UpdatedInfo);
}

bool Database::sendAssignmentToClassroom(ID AssignmentId, ID ClassroomId, const std::string& EndDate)
{
    DatabaseOperation* db = new SQLiteAdapter();
    auto flag = db->execInsert("AssignmentSession", {"ClassroomID", "AssignmentID", "AssignmentSessionFinishDate"},
                               {std::to_string(ClassroomId), std::to_string(AssignmentId), EndDate});
    auto lastIdResult = db->getLastTableID("AssignmentSession", "AssignmentSessionID");
    if(!flag || !lastIdResult.first)
    {
        delete db;
        return false;
    }
    std::string script = "SELECT StudentUserID\n"
                         "FROM 'Student_Classroom'\n"
                         "WHERE (Student_Classroom.ClassroomID = '" + std::to_string(ClassroomId) + "');";
    auto commandResFull = db->execSelect(script, 1);
    if(!commandResFull.first)
    {
        delete db;
        return false;
    }
    const auto& commandRes = commandResFull.second;
    for(auto& student : commandRes[0])
    {
        if(!db->execInsert("Student_AssignmentSession", {"StudentUserID", "AssignmentSessionID", "StudentAssignmentSessionStatus",
                                     "StudentAssignmentSessionAnswer", "StudentAssignmentSessionScore", "StudentAssignmentSessionFinishDate"},
                           {student, std::to_string(lastIdResult.second), "0", "", "0", "0"}))
        {
            delete db;
            return false;
        }
    }
    delete db;
    return true;
}