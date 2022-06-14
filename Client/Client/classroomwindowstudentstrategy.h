#ifndef CLASSROOMWINDOWSTUDENTSTRATEGY_H
#define CLASSROOMWINDOWSTUDENTSTRATEGY_H

#include "classroomwindowstrategy.h"

class ClassroomWindowStudentStrategy : public ClassroomWindowStrategy
{
public:
    ClassroomWindowStudentStrategy();
    void OnAssignmentClicked(unsigned long long id) override;
};

#endif // CLASSROOMWINDOWSTUDENTSTRATEGY_H
