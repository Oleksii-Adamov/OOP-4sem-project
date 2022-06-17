#include "classroomsnamelistmodel.h"

ClassroomsNameListModel::ClassroomsNameListModel(QObject *parent)
    : ClassroomsListModel(parent)
{
}

QVariant ClassroomsNameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= classrooms_list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(QString::fromStdString(classrooms_list_[std::size_t(index.row())].getName()));
    return QVariant();
}
