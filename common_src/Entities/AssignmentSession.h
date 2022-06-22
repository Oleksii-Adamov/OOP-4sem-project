#ifndef ASSIGNMENTSESSION_H
#define ASSIGNMENTSESSION_H

#include "Entity.h"

class AssignmentSession : Entity
{
    ID assignment_session_id_ = 0;
    ID classroom_id_ = 0;
    ID assignment_id_ = 0;
    DATETIME assignment_session_start_date_ = "";
    DATETIME assignment_session_end_date_ = "";
public:
    AssignmentSession(){};
    AssignmentSession(const ID& assignment_session_id, const ID& classroom_id, const ID& assignment_id,
                      const DATETIME& assignment_session_start_date, const DATETIME& assignment_session_end_date) :
                                  assignment_session_id_(assignment_session_id), classroom_id_(classroom_id), assignment_id_(assignment_id),
                                  assignment_session_start_date_(assignment_session_start_date), assignment_session_end_date_(assignment_session_end_date) {};
    void setAssignmentSessionId(const ID& assignment_session_id)
    {
        assignment_session_id_ = assignment_session_id;
    }

    void setClassroomId(const ID& classroom_id)
    {
        classroom_id_ = classroom_id;
    }

    void setAssignmentId(const ID& assignment_id)
    {
        assignment_id_ = assignment_id;
    }

    void setAssignmentSessionStartDate(const DATETIME& assignment_session_start_date)
    {
        assignment_session_start_date_ = assignment_session_start_date;
    }

    void setAssignmentSessionEndDate(const DATETIME& assignment_session_end_date)
    {
        assignment_session_end_date_ = assignment_session_end_date;
    }

    ID getAssignmentSessionId() const
    {
        return assignment_session_id_;
    }

    ID getClassroomId() const
    {
        return classroom_id_;
    }

    ID getAssignmentId() const
    {
        return assignment_id_;
    }

    DATETIME getAssignmentSessionStartDate() const
    {
        return assignment_session_start_date_;
    }

    DATETIME getAssignmentSessionEndDate() const
    {
        return assignment_session_end_date_;
    }
};


#endif
