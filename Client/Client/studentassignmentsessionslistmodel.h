#ifndef STUDENTASSIGNMENTSESSIONSLISTMODEL_H
#define STUDENTASSIGNMENTSESSIONSLISTMODEL_H

#include <QAbstractListModel>
#include "studentassignmentsessioninfo.h"

class StudentAssignmentSessionsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit StudentAssignmentSessionsListModel(long long max_score, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Push data to beggining
    bool PushBack(const StudentAssignmentSessionInfo &value, int role = Qt::EditRole);

    unsigned long long GetId(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    std::vector<StudentAssignmentSessionInfo> list_;
    long long max_score_ = 0;
};

#endif // STUDENTASSIGNMENTSESSIONSLISTMODEL_H
