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

bool AssignmentsListModel::Push(const AssignmentInfo &value, int role)
{
    if (role == Qt::EditRole) {
        beginInsertRows(QModelIndex(), 0, 0);
        assignments_list_.insert(assignments_list_.begin(), value);
        endInsertRows();
        return true;
    }
    else {
        return false;
    }
}

unsigned long long AssignmentsListModel::GetId(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= assignments_list_.size())
        return -1;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return assignments_list_[std::size_t(index.row())].getId();
    return -1;
}

