#ifndef STUDENTASSIGNMENTSESSIONSLISTMODEL_H
#define STUDENTASSIGNMENTSESSIONSLISTMODEL_H

#include <QAbstractListModel>
#include "studentassignmentsessioninfo.h"

class StudentAssignmentSessionsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit StudentAssignmentSessionsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Push data to beggining
    bool PushBack(const StudentAssignmentSessionInfo &value, int role = Qt::EditRole);

    StudentAssignmentSessionInfo GetData(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    std::vector<StudentAssignmentSessionInfo> list_;
};

#endif // STUDENTASSIGNMENTSESSIONSLISTMODEL_H
