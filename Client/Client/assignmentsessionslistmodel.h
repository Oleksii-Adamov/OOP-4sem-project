#ifndef ASSIGNMENTSESSIONSLISTMODEL_H
#define ASSIGNMENTSESSIONSLISTMODEL_H

#include <QAbstractListModel>
#include "assignmentsessioninfo.h"

class AssignmentSessionsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AssignmentSessionsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Push data to beggining
    bool PushBack(const AssignmentSessionInfo &value, int role = Qt::EditRole);

    AssignmentSessionInfo GetData(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    std::vector<AssignmentSessionInfo> list_;

private:
};

#endif // ASSIGNMENTSESSIONSLISTMODEL_H
