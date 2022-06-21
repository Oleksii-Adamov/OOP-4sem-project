#ifndef CLASSROOMSNAMELISTMODEL_H
#define CLASSROOMSNAMELISTMODEL_H

#include <QAbstractListModel>
#include "Classroom.h"

class ClassroomsNameListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ClassroomsNameListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Get displayed data
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Pushes data to end
    bool PushBack(const Classroom &value, int role = Qt::EditRole);

    void Clear();

    Classroom GetClassroom(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    std::vector<Classroom> list_;
};

#endif // CLASSROOMSNAMELISTMODEL_H
