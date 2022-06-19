#ifndef CLASSROOMWINDOWSTRATEGY_H
#define CLASSROOMWINDOWSTRATEGY_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "net.h"
#include "messagetypes.h"

class ClassroomWindowStrategy
{
public:
    virtual void SetModel(QSharedPointer<QAbstractListModel>& model) = 0;
    virtual void OnAssignmentClicked(const QModelIndex& index, QSharedPointer<QAbstractListModel>& model, QWidget* parent = nullptr) = 0;
    virtual void Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model) = 0;
};

#endif // CLASSROOMWINDOWSTRATEGY_H
