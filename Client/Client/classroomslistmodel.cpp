#include "classroomslistmodel.h"

ClassroomsListModel::ClassroomsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ClassroomsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return list_.size();
}

QVariant ClassroomsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(QString::fromStdString(list_[std::size_t(index.row())].classroom.getName() + "\n" +
                list_[std::size_t(index.row())].teacher.getUserName()+ "\n"));
    return QVariant();
}

bool ClassroomsListModel::PushBack(const ClassroomInfo &value, int role)
{
    if (role == Qt::EditRole) {
        beginInsertRows(QModelIndex(), 0, 0);
        list_.push_back(value);
        endInsertRows();
        return true;
    }
    else {
        return false;
    }
}


ClassroomInfo ClassroomsListModel::GetClassroomInfo(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return ClassroomInfo();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return list_[std::size_t(index.row())];
    return ClassroomInfo();
}
