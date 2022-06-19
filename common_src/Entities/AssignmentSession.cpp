#include "AssignmentSession.h"


void AssignmentSession::setAssignmentSessionId(const ID& assignment_session_id)
{
    assignment_session_id_ = assignment_session_id;
}

void AssignmentSession::setAssignmentId(const ID& assignment_id)
{
    assignment_id_ = assignment_id;
}

void AssignmentSession::setAssignmentSessionStartDate(const DATETIME& assignment_session_start_date)
{
    assignment_session_start_date_ = assignment_session_start_date;
}

void AssignmentSession::setAssignmentSessionEndDate(const DATETIME& assignment_session_end_date)
{
    assignment_session_end_date_ = assignment_session_end_date;
}

ID AssignmentSession::getAssignmentSessionId() const
{
    return assignment_session_id_;
}

ID AssignmentSession::getAssignmentId() const
{
    return assignment_id_;
}

DATETIME AssignmentSession::getAssignmentSessionStartDate() const
{
    return assignment_session_start_date_;
}

DATETIME AssignmentSession::getAssignmentSessionEndDate() const
{
    return assignment_session_end_date_;
}