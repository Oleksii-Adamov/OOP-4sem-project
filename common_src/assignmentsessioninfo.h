#ifndef ASSIGNMENTSESSIONINFO_H
#define ASSIGNMENTSESSIONINFO_H

#include "Entities/AssignmentSession.h"
#include "Entities/Assignment.h"

struct AssignmentSessionInfo
{
    AssignmentSession assignment_session;
    Assignment assignment;
    AssignmentSessionInfo() {}
    AssignmentSessionInfo(const AssignmentSession& assignment_session, const Assignment& assignment)
        : assignment_session(assignment_session), assignment(assignment)
    {}
};

#endif // ASSIGNMENTSESSIONINFO_H
