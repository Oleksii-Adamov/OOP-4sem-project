#ifndef ASSIGNMENTSESSION_H
#define ASSIGNMENTSESSION_H

#include "Entity.h"

class AssignmentSession : Entity
{
    ID assignment_session_id_;
    ID assignment_id_;
    DATETIME assignment_session_start_date_;
    DATETIME assignment_session_end_date_;
public:
    AssignmentSession(const ID& assignment_session_id, const ID& assignment_id,
                      const DATETIME& assignment_session_start_date, const DATETIME& assignment_session_end_date) :
                                  assignment_session_id_(assignment_session_id), assignment_id_(assignment_id),
                                  assignment_session_start_date_(assignment_session_start_date), assignment_session_end_date_(assignment_session_end_date) {};
    void setAssignmentSessionId(const ID& assignment_session_id);
    void setAssignmentId(const ID& assignment_id);
    void setAssignmentSessionStartDate(const DATETIME& assignment_session_start_date);
    void setAssignmentSessionEndDate(const DATETIME& assignment_session_end_date);
    ID getAssignmentSessionId() const;
    ID getAssignmentId() const;
    DATETIME getAssignmentSessionStartDate() const;
    DATETIME getAssignmentSessionEndDate() const;
};


#endif