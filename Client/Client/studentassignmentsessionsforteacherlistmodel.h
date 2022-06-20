#ifndef STUDENTASSIGNMENTSESSIONSFORTEACHERLISTMODEL_H
#define STUDENTASSIGNMENTSESSIONSFORTEACHERLISTMODEL_H

#include <QAbstractListModel>
#include "studentassignmentsessioninfoforteacher.h"

class StudentAssignmentSessionsForTeacherListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit StudentAssignmentSessionsForTeacherListModel(int max_score, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Push data to beggining
    bool PushBack(const StudentAssignmentSessionInfoForTeacher &value, int role = Qt::EditRole);

    StudentAssignmentSessionInfoForTeacher GetData(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    std::vector<StudentAssignmentSessionInfoForTeacher> list_;
    int max_score_;

private:
};

#endif // STUDENTASSIGNMENTSESSIONSFORTEACHERLISTMODEL_H
