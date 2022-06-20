#include "studentassignmentsessionslistmodel.h"

StudentAssignmentSessionsListModel::StudentAssignmentSessionsListModel(QObject *parent)
    : QAbstractListModel(parent)
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
        QString display = QString::fromStdString(student_assignment.assignment.getAssignmentName() +
                "\nPublished: " + student_assignment.assignment_session.getAssignmentSessionStartDate() +
                "\nDeadline: " + student_assignment.assignment_session.getAssignmentSessionEndDate() + "\n");

        if (student_assignment.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::not_submitted)
        {
            display += "Not submitted";
        }
        else {
            display += "Submitted: " + QString::fromStdString(student_assignment.student_assignment_session.getStudentAssignmentSessionFinishDate()) + "\n";
            if (student_assignment.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::checked)
            {
                display += QString::number(student_assignment.student_assignment_session.getStudentAssignmentSessionScore());
            }
            else {
                display += "-";
            }
            display += "/" + QString::number(student_assignment.assignment.getAssignmentMaxScore()) + "\n";
        }
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

StudentAssignmentSessionInfo StudentAssignmentSessionsListModel::GetData(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return StudentAssignmentSessionInfo();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return list_[std::size_t(index.row())];
    return StudentAssignmentSessionInfo();
}

void StudentAssignmentSessionsListModel::Clear()
{
    list_.clear();
}
