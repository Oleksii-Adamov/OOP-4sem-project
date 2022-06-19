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
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Pushes data to end
    bool PushBack(const ClassroomInfo &value, int role = Qt::EditRole);

    ClassroomInfo GetClassroomInfo(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    std::vector<ClassroomInfo> list_;
};

#endif // CLASSROOMSLISTMODEL_H
