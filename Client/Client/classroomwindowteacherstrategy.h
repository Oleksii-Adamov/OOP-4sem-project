#ifndef CLASSROOMWINDOWTEACHERSTRATEGY_H
#define CLASSROOMWINDOWTEACHERSTRATEGY_H

#include "classroomwindowstrategy.h"

class ClassroomWindowTeacherStrategy : public ClassroomWindowStrategy
{
public:
    ClassroomWindowTeacherStrategy();
    void OnAssignmentClicked(unsigned long long id) override;
};

#endif // CLASSROOMWINDOWTEACHERSTRATEGY_H
