#ifndef CLASSROOMWINDOWTEACHERSTRATEGY_H
#define CLASSROOMWINDOWTEACHERSTRATEGY_H

#include "classroomwindowstrategy.h"

class ClassroomWindowTeacherStrategy : public ClassroomWindowStrategy
{
public:
    ClassroomWindowTeacherStrategy();
    void OnAssignmentClicked(const QModelIndex& index, QSharedPointer<QAbstractListModel>& model, QWidget* parent = nullptr) override;
    void SetModel(QSharedPointer<QAbstractListModel>& model) override;
    void Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model) override;
    void GetData() override;
};

#endif // CLASSROOMWINDOWTEACHERSTRATEGY_H
