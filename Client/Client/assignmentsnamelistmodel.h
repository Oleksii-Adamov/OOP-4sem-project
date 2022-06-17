#ifndef ASSIGNMENTSNAMELISTMODEL_H
#define ASSIGNMENTSNAMELISTMODEL_H

#include<assignmentslistmodel.h>

class AssignmentsNameListModel : public AssignmentsListModel
{
    Q_OBJECT
public:
    explicit AssignmentsNameListModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // ASSIGNMENTSNAMELISTMODEL_H
