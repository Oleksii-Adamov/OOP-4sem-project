#ifndef CLASSROOMINFO_H
#define CLASSROOMINFO_H

#include "Entities/Classroom.h"
#include "Entities/User.h"

struct ClassroomInfo
{
    Classroom classroom = Classroom();
    User teacher = User();
};

#endif // CLASSROOMINFO_H
