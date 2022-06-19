#include "StudentAssignmentSession.h"


void StudentAssignmentSession::setStudentUserId(const ID& student_user_id)
{
    student_user_id_ = student_user_id;
}

void StudentAssignmentSession::setAssignmentSessionId(const ID& assignment_session_id)
{
    assignment_session_id_ = assignment_session_id;
}

void StudentAssignmentSession::setStudentAssignmentSessionStatus(int student_assignment_session_status)
{
    student_assignment_session_status_ = student_assignment_session_status;
}

void StudentAssignmentSession::setStudentAssignmentSessionAnswer(DATA* student_assignment_session_answer)
{
    student_assignment_session_answer_ = student_assignment_session_answer;
}

void StudentAssignmentSession::setStudentAssignmentSessionScore(int student_assignment_session_score)
{
    student_assignment_session_score_ = student_assignment_session_score;
}

void StudentAssignmentSession::setStudentAssignmentSessionFinishDate(const DATETIME& student_assignment_session_finish_date)
{
    student_assignment_session_finish_date_ = student_assignment_session_finish_date;
}

ID StudentAssignmentSession::getStudentUserId() const
{
    return student_user_id_;
}

ID StudentAssignmentSession::getAssignmentSessionId() const
{
    return assignment_session_id_;
}

int StudentAssignmentSession::getStudentAssignmentSessionStatus() const
{
    return student_assignment_session_status_;
}

DATA* StudentAssignmentSession::getStudentAssignmentSessionAnswer() const
{
    return student_assignment_session_answer_;
}

int StudentAssignmentSession::getStudentAssignmentSessionScore() const
{
    return student_assignment_session_score_;
}

DATETIME StudentAssignmentSession::getStudentAssignmentSessionFinishDate() const
{
    return student_assignment_session_finish_date_;
}