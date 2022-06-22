#ifndef CLASSROOMWINDOWSTUDENTSTRATEGY_H
#define CLASSROOMWINDOWSTUDENTSTRATEGY_H

#include "classroomwindowstrategy.h"

class ClassroomWindowStudentStrategy : public ClassroomWindowStrategy
{
public:
    ClassroomWindowStudentStrategy();
    void OnAssignmentClicked(const QModelIndex& index, QSharedPointer<QAbstractListModel>& model, QWidget* parent = nullptr) override;
    void SetModel(QSharedPointer<QAbstractListModel>& model) override;
    void Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model) override;
    void GetData() override;
};

#endif // CLASSROOMWINDOWSTUDENTSTRATEGY_H
