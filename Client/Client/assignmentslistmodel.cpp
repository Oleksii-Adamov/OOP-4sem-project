#include "assignmentslistmodel.h"
/*
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

    return list_.size();
}

QVariant AssignmentsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(QString::fromStdString(list_[std::size_t(index.row())].getName() +
                        "\n Published :" + list_[std::size_t(index.row())].getStartDateTime() +
                "\n Deadline :" + list_[std::size_t(index.row())].getDeadlineDateTime()));
    return QVariant();
}

bool AssignmentsListModel::Push(const AssignmentSessionInfo &value, int role)
{
    if (role == Qt::EditRole) {
        beginInsertRows(QModelIndex(), 0, 0);
        list_.insert(list_.begin(), value);
        endInsertRows();
        return true;
    }
    else {
        return false;
    }
}

unsigned long long AssignmentsListModel::GetId(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return 0;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return list_[std::size_t(index.row())].getId();
    return 0;
}
*/
