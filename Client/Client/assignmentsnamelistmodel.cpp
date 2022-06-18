#include "assignmentsnamelistmodel.h"

AssignmentsNameListModel::AssignmentsNameListModel(QObject *parent)
    : AssignmentsListModel(parent)
{

}

QVariant AssignmentsNameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= assignments_list_.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(QString::fromStdString(assignments_list_[std::size_t(index.row())].getName()));
    return QVariant();
}