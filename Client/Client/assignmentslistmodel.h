#ifndef ASSIGNMENTSLISTMODEL_H
#define ASSIGNMENTSLISTMODEL_H

#include <QAbstractListModel>

class AssignmentsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AssignmentsListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<AssignmentInfo> assignments_list_;
};

#endif // ASSIGNMENTSLISTMODEL_H
