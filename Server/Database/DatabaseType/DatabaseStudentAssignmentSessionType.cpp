#include "DatabaseStudentAssignmentSessionType.h"


void DatabaseStudentAssignmentSessionType::setStudentUserId(const ID& student_user_id)
{
    student_user_id_ = student_user_id;
}

void DatabaseStudentAssignmentSessionType::setAssignmentSessionId(const ID& assignment_session_id)
{
    assignment_session_id_ = assignment_session_id;
}

void DatabaseStudentAssignmentSessionType::setStudentAssignmentSessionStatus(int student_assignment_session_status)
{
    student_assignment_session_status_ = student_assignment_session_status;
}

void DatabaseStudentAssignmentSessionType::setStudentAssignmentSessionAnswer(DATA* student_assignment_session_answer)
{
    student_assignment_session_answer_ = student_assignment_session_answer;
}

void DatabaseStudentAssignmentSessionType::setStudentAssignmentSessionScore(int student_assignment_session_score)
{
    student_assignment_session_score_ = student_assignment_session_score;
}

void DatabaseStudentAssignmentSessionType::setStudentAssignmentSessionFinishDate(const DATETIME& student_assignment_session_finish_date)
{
    student_assignment_session_finish_date_ = student_assignment_session_finish_date;
}

ID DatabaseStudentAssignmentSessionType::getStudentUserId() const
{
    return student_user_id_;
}

ID DatabaseStudentAssignmentSessionType::getAssignmentSessionId() const
{
    return assignment_session_id_;
}

int DatabaseStudentAssignmentSessionType::getStudentAssignmentSessionStatus() const
{
    return student_assignment_session_status_;
}

DATA* DatabaseStudentAssignmentSessionType::getStudentAssignmentSessionAnswer() const
{
    return student_assignment_session_answer_;
}

int DatabaseStudentAssignmentSessionType::getStudentAssignmentSessionScore() const
{
    return student_assignment_session_score_;
}

DATETIME DatabaseStudentAssignmentSessionType::getStudentAssignmentSessionFinishDate() const
{
    return student_assignment_session_finish_date_;
}