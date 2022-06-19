#include "studentassignmentsessionslistmodel.h"

StudentAssignmentSessionsListModel::StudentAssignmentSessionsListModel(long long max_score, QObject *parent)
    : QAbstractListModel(parent), max_score_(max_score)
{
}

int StudentAssignmentSessionsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return list_.size();
}

QVariant StudentAssignmentSessionsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        StudentAssignmentSessionInfo student_assignment = list_[std::size_t(index.row())];
        QString display = QString::fromStdString(student_assignment.getStudentUserName()) + "  ";
        if (student_assignment.getStatus() != StudentAssignmentSessionStatus::checked)
        {
            display += QString::number(student_assignment.getScore());
        }
        else {
            display += "-";
        }
        display += "/" + QString::number(max_score_) + "\n";
        if (student_assignment.getStatus() == StudentAssignmentSessionStatus::not_submitted)
        {
            display += "Not submitted";
        }
        else {
            display += "Submitted: " + QString::fromStdString(student_assignment.getFinishDateTime());
        }
        display += "\n";
        return display;
    }
    return QVariant();
}

bool StudentAssignmentSessionsListModel::PushBack(const StudentAssignmentSessionInfo &value, int role)
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

unsigned long long StudentAssignmentSessionsListModel::GetId(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return 0;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return list_[std::size_t(index.row())].getId();
    return 0;
}
