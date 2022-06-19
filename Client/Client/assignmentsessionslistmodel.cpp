#include "assignmentsessionslistmodel.h"

AssignmentSessionsListModel::AssignmentSessionsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int AssignmentSessionsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return list_.size();
}

QVariant AssignmentSessionsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        AssignmentSessionInfo student_assignment = list_[std::size_t(index.row())];
        QString display = QString::fromStdString(student_assignment.assignment.getAssignmentName() +
                "\nPublished: " + student_assignment.assignment_session.getAssignmentSessionStartDate() +
                "\nDeadline: " + student_assignment.assignment_session.getAssignmentSessionEndDate() + "\n");
        return display;
    }
    return QVariant();
}

bool AssignmentSessionsListModel::PushBack(const AssignmentSessionInfo &value, int role)
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

AssignmentSessionInfo AssignmentSessionsListModel::GetData(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return AssignmentSessionInfo();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return list_[std::size_t(index.row())];
    return AssignmentSessionInfo();
}
