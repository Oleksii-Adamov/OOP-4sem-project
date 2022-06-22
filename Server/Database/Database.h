#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H

#include "../../common_src/Entities/Entities.h"
#include "../../common_src/studentassignmentsessioninfo.h"
#include "../../common_src/studentassignmentsessioninfoforteacher.h"
#include "../../common_src/assignmentsessioninfo.h"
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
    static std::pair<bool, User> checkLogIn(const std::string& login, const std::string& password);

    //! Returns all the User's Classrooms in which he is a teacher
    static std::pair<bool, std::vector<Classroom>> selectAllClassroomsWhereUserIsTeacher(ID UserId);

    /*!
     * Returns all Assignments (without Assignment data), Assignment Sessions, Student Assignment Sessions
     * (without student assignment session answer) information of student in the Classroom
     */
    static std::pair<bool, std::vector<StudentAssignmentSessionInfo>> selectAllAssignmentsOfClassroomStudentInfo(ID StudentUserId, ID ClassroomId);

    /*!
     * Returns all Assignments (without Assignment data), Assignment Sessions information of teacher in the Classroom
     */
    static std::pair<bool, std::vector<AssignmentSessionInfo>> selectAllAssignmentsOfClassroomTeacherInfo(ID TeacherUserId, ID ClassroomId);

    //! Returns all Assignments created by the User
    static std::pair<bool, std::vector<Assignment>> selectAllAssignmentUserCreated(ID UserId);

    //! Joins User to Classroom as a student
    static std::pair<bool, bool> joinUserToClassroom(ID UserId, ID ClassroomId);

    //! Creates a new Classroom with a specific name
    static bool createNewClassroom(ID TeacherUserId, const std::string& ClassroomName);

    //! Returns Student's answer to the Assignment Session
    static std::pair<bool, std::string> getStudentAssignmentSessionAnswer(ID StudentUserId, ID AssignmentSessionId);

    //! Returns all Student's answers to the Assignment Session
    static std::pair<bool, std::vector<StudentAssignmentSessionInfoForTeacher>> getAllStudentAssignmentSessionAnswers(ID AssignmentSessionId);

    //! Returns Assignment without assignment_data_ (equals "")
    static std::pair<bool, Assignment> getAssignmentWithoutData(ID AssignmentId);

    //! Returns assignment_data_ of the Assignment
    static std::pair<bool, std::string> getAssignmentData(ID AssignmentId);

    /*!
     * \brief Creates a new Assignment
     *
     * Returns inserted Assignment without assignment_data_ (equals "") as the second parameter of pair
     */
    static std::pair<bool, Assignment> createNewAssignment(const Assignment& NewAssignment);

    /*!
     * \brief Submit Student's Assignment Session
     *
     * \param UpdatedInfo New information of StudentAssignmentSession to update. Its fields student_user_id_ and assignment_session_id_
     * are used to determine a specific record to update (not changeable!)
     *
     * Updates the following fields: student_assignment_session_status_, student_assignment_session_answer_, student_assignment_session_finish_date_
     */
    static bool submitStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo);

    /*!
     * \brief Evaluate Student's Assignment Session information
     *
     * \param UpdatedInfo New information of StudentAssignmentSession to update. Its fields student_user_id_ and assignment_session_id_
     * are used to determine a specific record to update (not changeable!)
     *
     * Updates the following fields: student_assignment_session_status_, student_assignment_session_score_
     */
    static bool evaluateStudentAssignmentSession(const StudentAssignmentSession& UpdatedInfo);

    /*!
     * \brief Updates Assignment's information
     *
     * If there are already Assignment Sessions of this Assignment, the new Assignment will be created instead of updating of existing
     *
     * \param UpdatedInfo New information of Assignment to update. Its field assignment_id_
     * are used to determine a specific record to update (not changeable!).
     *
     * Returns inserted Assignment without assignment_data_ (equals "") as the second parameter of pair
     */
    static std::pair<bool, Assignment> updateAssignment(const Assignment& UpdatedInfo);

    //! Sends Assignment to the Classroom
    static bool sendAssignmentToClassroom(ID AssignmentId, ID ClassroomId, const std::string& EndDate);
};


#endif