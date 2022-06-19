#include "DatabaseAssignmentSessionType.h"


void DatabaseAssignmentSessionType::setAssignmentSessionId(const ID& assignment_session_id)
{
    assignment_session_id_ = assignment_session_id;
}

void DatabaseAssignmentSessionType::setAssignmentId(const ID& assignment_id)
{
    assignment_id_ = assignment_id;
}

void DatabaseAssignmentSessionType::setAssignmentSessionStartDate(const DATETIME& assignment_session_start_date)
{
    assignment_session_start_date_ = assignment_session_start_date;
}

void DatabaseAssignmentSessionType::setAssignmentSessionEndDate(const DATETIME& assignment_session_end_date)
{
    assignment_session_end_date_ = assignment_session_end_date;
}

ID DatabaseAssignmentSessionType::getAssignmentSessionId() const
{
    return assignment_session_id_;
}

ID DatabaseAssignmentSessionType::getAssignmentId() const
{
    return assignment_id_;
}

DATETIME DatabaseAssignmentSessionType::getAssignmentSessionStartDate() const
{
    return assignment_session_start_date_;
}

DATETIME DatabaseAssignmentSessionType::getAssignmentSessionEndDate() const
{
    return assignment_session_end_date_;
}