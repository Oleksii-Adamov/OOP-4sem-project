#include "studentassignmentsessionsforteacherlistmodel.h"

StudentAssignmentSessionsForTeacherListModel::StudentAssignmentSessionsForTeacherListModel(int max_score, QObject *parent)
    : QAbstractListModel(parent), max_score_(max_score)
{
}

int StudentAssignmentSessionsForTeacherListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return list_.size();
}

QVariant StudentAssignmentSessionsForTeacherListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        StudentAssignmentSessionInfoForTeacher student_assignment = list_[std::size_t(index.row())];
        QString display = QString::fromStdString(student_assignment.student.getUserName() + "\n");

        if (student_assignment.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::not_submitted)
        {
            display += "Not submitted";
        }
        else {
            display += "Submitted: " + QString::fromStdString(student_assignment.student_assignment_session.getStudentAssignmentSessionFinishDate()) + "\nScore: ";
            if (student_assignment.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::checked)
            {
                display += QString::number(student_assignment.student_assignment_session.getStudentAssignmentSessionScore());
            }
            else {
                display += "-";
            }
            display += "/" + QString::number(max_score_) + "\n";
        }
        return display;
    }
    return QVariant();
}

bool StudentAssignmentSessionsForTeacherListModel::PushBack(const StudentAssignmentSessionInfoForTeacher &value, int role)
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

StudentAssignmentSessionInfoForTeacher StudentAssignmentSessionsForTeacherListModel::GetData(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= list_.size())
        return StudentAssignmentSessionInfoForTeacher();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return list_[std::size_t(index.row())];
    return StudentAssignmentSessionInfoForTeacher();
}
