#ifndef CLASSROOMSNAMELISTMODEL_H
#define CLASSROOMSNAMELISTMODEL_H

#include "classroomslistmodel.h"

class ClassroomsNameListModel : public ClassroomsListModel
{
    Q_OBJECT
public:
    explicit ClassroomsNameListModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // CLASSROOMSNAMELISTMODEL_H
