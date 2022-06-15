#ifndef CLASSROOMSLISTMODEL_H
#define CLASSROOMSLISTMODEL_H

#include <QAbstractListModel>
#include "classroominfo.h"

class ClassroomsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ClassroomsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Pushes data to end
    bool PushBack(const ClassroomInfo &value, int role = Qt::EditRole);

    unsigned long long GetId(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    std::vector<ClassroomInfo> classrooms_list_;

private:
};

#endif // CLASSROOMSLISTMODEL_H
