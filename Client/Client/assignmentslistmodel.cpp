#include "assignmentslistmodel.h"

AssignmentsListModel::AssignmentsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int AssignmentsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return assignments_list_.size();
}

QVariant AssignmentsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= assignments_list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(QString::fromStdString(assignments_list_[std::size_t(index.row())].getName() + "\n" +
                assignments_list_[std::size_t(index.row())].getDateTime()));
    return QVariant();
}

bool AssignmentsListModel::Push(int row, const QVariant &value, int role)
{
    beginInsertRows(QModelIndex(), row, row);
    assignments_list_.insert(assignments_list_.begin(), value.value<AssignmentInfo>());
    endInsertRows();
    return true;
}

long long AssignmentsListModel::GetId(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= assignments_list_.size())
        return -1;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return assignments_list_[std::size_t(index.row())].getId();
    return -1;
}

/*
bool AssignmentsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole && data(index, role) != value) {
        assignments_list_[std::size_t(index.row())] = value.value<AssignmentInfo>();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags AssignmentsListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool AssignmentsListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    assignments_list_.insert(assignments_list_.begin() + row, count, ToDoListData());
    endInsertRows();
    return true;
}
*/

