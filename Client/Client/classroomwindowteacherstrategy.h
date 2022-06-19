#ifndef CLASSROOMWINDOWTEACHERSTRATEGY_H
#define CLASSROOMWINDOWTEACHERSTRATEGY_H

#include "classroomwindowstrategy.h"

class ClassroomWindowTeacherStrategy : public ClassroomWindowStrategy
{
public:
    ClassroomWindowTeacherStrategy();
    void OnAssignmentClicked(unsigned long long id) override;
    void SetModel(QSharedPointer<QAbstractListModel>& model) override;
    void Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model) override;
};

#endif // CLASSROOMWINDOWTEACHERSTRATEGY_H
