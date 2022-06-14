#ifndef CLASSROOMWINDOWSTRATEGY_H
#define CLASSROOMWINDOWSTRATEGY_H


class ClassroomWindowStrategy
{
public:
    ClassroomWindowStrategy();
    virtual void OnAssignmentClicked(unsigned long long id) = 0;
};

#endif // CLASSROOMWINDOWSTRATEGY_H
