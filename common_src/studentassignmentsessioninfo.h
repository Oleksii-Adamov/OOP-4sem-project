#ifndef STUDENTASSIGNMENTSESSIONINFO_H
#define STUDENTASSIGNMENTSESSIONINFO_H

#include "StudentAssignmentSession.h"
#include "AssignmentSession.h"
#include "Assignment.h"

struct StudentAssignmentSessionInfo
{
    StudentAssignmentSession student_assignment_session;
    AssignmentSession assignment_session;
    Assignment assignment;
    StudentAssignmentSessionInfo() {}
    StudentAssignmentSessionInfo(const StudentAssignmentSession& student_assignment_session,
                                 const AssignmentSession& assignment_session, const Assignment& assignment)
        : student_assignment_session(student_assignment_session), assignment_session(assignment_session), assignment(assignment)
    {}
};

#endif // STUDENTASSIGNMENTSESSIONINFO_H
