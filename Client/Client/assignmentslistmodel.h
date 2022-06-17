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
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Push data to beggining
    bool Push(const AssignmentInfo &value, int role = Qt::EditRole);

    unsigned long long GetId(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    std::vector<AssignmentInfo> assignments_list_;
};

#endif // ASSIGNMENTSLISTMODEL_H
