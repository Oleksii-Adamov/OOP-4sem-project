#ifndef ASSIGNMENTSLISTMODEL_H
#define ASSIGNMENTSLISTMODEL_H

#include <QAbstractListModel>
#include "assignmentinfo.h"

class AssignmentsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AssignmentsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Push data to beggining
    bool Push(int row, const QVariant &value, int role = Qt::EditRole);

    long long GetId(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    std::vector<AssignmentInfo> assignments_list_;
};

#endif // ASSIGNMENTSLISTMODEL_H
