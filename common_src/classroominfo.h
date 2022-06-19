#ifndef CLASSROOMINFO_H
#define CLASSROOMINFO_H

#include "Classroom.h"
#include "User.h"

struct ClassroomInfo
{
    Classroom classroom;
    User teacher;
    ClassroomInfo() {}
    ClassroomInfo(const Classroom& classroom, const User& teacher)
        : classroom(classroom), teacher(teacher)
    {}
};

#endif // CLASSROOMINFO_H
