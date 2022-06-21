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

    //! Checks if the login of User is unique
    static std::pair<bool, bool> checkUniqueLogin(const std::string& login);

    //! Creates a new User
    static bool createNewUser(const User& NewUser, const std::string& password);

    //! Checks if login and password are correct
    static std::pair<bool, bool> checkLogIn(const std::string& login, const std::string& password);

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

    //! Returns all Student's answers to the Assignment Session
    static std::pair<bool, std::vector<StudentAssignmentSessionInfoForTeacher>> getAllStudentAssignmentSessionAnswers(ID AssignmentSessionId);

    //! Returns data of the Assignment
    static std::pair<bool, std::string> getAssignmentData(ID AssignmentId);

    /*!
     * \brief Updates Student's Assignment Session information
     * \param UpdatedInfo New information of StudentAssignmentSession to update. Its fields student_user_id_ and assignment_session_id_
     * are used to determine a specific record to update (not changeable!)
     */
    static bool updateStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo);

    /*!
     * \brief Updates Assignment's information
     *
     * If there are already Assignment Sessions of this Assignment, the new Assignment will be created instead of updating the existing
     *
     * \param UpdatedInfo New information of Assignment to update. Its field assignment_id_
     * are used to determine a specific record to update (not changeable!).
     */
    static bool updateAssignment(const Assignment& UpdatedInfo);
};


#endif