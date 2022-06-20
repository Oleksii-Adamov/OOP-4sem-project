#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H

#include "../../common_src/Entities/Entities.h"
#include "../../common_src/studentassignmentsessioninfo.h"
#include "../../common_src/studentassignmentsessioninfoforteacher.h"
#include <string>
#include <vector>

class Database
{
public:
    //! Initializes the database (creates if it doesn't exist)
    static void init();

    //! Returns all the User's Classrooms in which he is a teacher
    static std::pair<bool, std::vector<Classroom>> selectAllClassroomsWhereUserIsTeacher(ID UserId);

    //!
    //

    //!
    //

    //! Returns all Assignments created by the User
    static std::pair<bool, std::vector<Assignment>> selectAllAssignmentUserCreated(ID UserId);

    //! Joins User to Classroom as a student
    static bool joinUserToClassroom(ID UserId, ID ClassroomId);

    //! Creates a new Classroom with a specific name
    static bool createNewClassroom(ID TeacherUserId, const std::string& ClassroomName);

    //! Returns Student's answer to the Assignment Session
    static std::pair<bool, std::string> getStudentAssignmentSessionAnswer(ID StudentUserId, ID AssignmentSessionId);

    //! Returns all Student's answers to the specific Assignment Session
    static std::pair<bool, std::vector<StudentAssignmentSessionInfoForTeacher>> getAllStudentAssignmentSessionAnswers(ID AssignmentSessionId);
};


#endif