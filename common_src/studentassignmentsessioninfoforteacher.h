#ifndef STUDENTASSIGNMENTSESSIONINFOFORTEACHER_H
#define STUDENTASSIGNMENTSESSIONINFOFORTEACHER_H

#include "Entities/StudentAssignmentSession.h"
#include "Entities/User.h"

struct StudentAssignmentSessionInfoForTeacher
{
    StudentAssignmentSession student_assignment_session;
    User student;
    StudentAssignmentSessionInfoForTeacher() {}
    StudentAssignmentSessionInfoForTeacher(const StudentAssignmentSession& student_assignment_session,
                                 const User& student)
        : student_assignment_session(student_assignment_session), student(student)
    {}
};

#endif // STUDENTASSIGNMENTSESSIONINFOFORTEACHER_H
