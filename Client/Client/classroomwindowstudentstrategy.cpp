#include "classroomwindowstudentstrategy.h"
#include "studentassignmentsessionslistmodel.h"
#include "studentassignmentwindow.h"

ClassroomWindowStudentStrategy::ClassroomWindowStudentStrategy()
{

}

void ClassroomWindowStudentStrategy::OnAssignmentClicked(const QModelIndex& index, QSharedPointer<QAbstractListModel>& model, QWidget* parent)
{
    StudentAssignmentSessionsListModel* student_assignment_sessions_model = qobject_cast<StudentAssignmentSessionsListModel*>(model.data());
    StudentAssignmentWindow* new_window = new StudentAssignmentWindow(student_assignment_sessions_model->GetData(index), parent);
    new_window->show();
}

void ClassroomWindowStudentStrategy::SetModel(QSharedPointer<QAbstractListModel>& model)
{
    model.reset(new StudentAssignmentSessionsListModel());
}

void ClassroomWindowStudentStrategy::Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model)
{
    StudentAssignmentSessionsListModel* student_assignment_sessions_model = qobject_cast<StudentAssignmentSessionsListModel*>(model.data());
    student_assignment_sessions_model->PushBack(StudentAssignmentSessionInfo(StudentAssignmentSession(1,1,StudentAssignmentSessionStatus::not_submitted, "", 0, ""),
                                                                             AssignmentSession(1,1,"19.06.2022 21:42","19.06.2022 21:42"), Assignment(1,1,"name","","",5)));
}
