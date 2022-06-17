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

    return classrooms_list_.size();
}

QVariant ClassroomsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= classrooms_list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(QString::fromStdString(classrooms_list_[std::size_t(index.row())].getName() + "\n" +
                classrooms_list_[std::size_t(index.row())].getTeachersName()+ "\n"));
    return QVariant();
}

bool ClassroomsListModel::PushBack(const ClassroomInfo &value, int role)
{
    if (role == Qt::EditRole) {
        beginInsertRows(QModelIndex(), 0, 0);
        classrooms_list_.push_back(value);
        endInsertRows();
        return true;
    }
    else {
        return false;
    }
}

unsigned long long ClassroomsListModel::GetId(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= classrooms_list_.size())
        return 0;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return classrooms_list_[std::size_t(index.row())].getId();
    return 0;
}
