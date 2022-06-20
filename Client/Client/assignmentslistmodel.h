#ifndef ASSIGNMENTSLISTMODEL_H
#define ASSIGNMENTSLISTMODEL_H

#include <QAbstractListModel>
#include "assignmentsessioninfo.h"

class AssignmentsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AssignmentsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool PushBack(const Assignment &value, int role = Qt::EditRole);

    Assignment GetData(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void Clear();

protected:
    std::vector<Assignment> list_;
};

#endif // ASSIGNMENTSLISTMODEL_H
