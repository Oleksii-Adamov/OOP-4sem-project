#ifndef CLASSROOMINFO_H
#define CLASSROOMINFO_H

#include "Entities/Classroom.h"
#include "Entities/User.h"

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
