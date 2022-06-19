#include "classroomwindowteacherstrategy.h"
#include "assignmentsessionslistmodel.h"
#include "studentassignmentsessionswindow.h"

ClassroomWindowTeacherStrategy::ClassroomWindowTeacherStrategy()
{

}

void ClassroomWindowTeacherStrategy::OnAssignmentClicked(const QModelIndex& index, QSharedPointer<QAbstractListModel>& model, QWidget* parent)
{
    AssignmentSessionsListModel* student_assignment_sessions_model = qobject_cast<AssignmentSessionsListModel*>(model.data());
    StudentAssignmentSessionsWindow* new_window = new StudentAssignmentSessionsWindow(student_assignment_sessions_model->GetData(index), parent);
    new_window->show();
}

void ClassroomWindowTeacherStrategy::SetModel(QSharedPointer<QAbstractListModel>& model)
{
    model.reset(new AssignmentSessionsListModel());
}

void ClassroomWindowTeacherStrategy::Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model)
{
    AssignmentSessionsListModel* student_assignment_sessions_model = qobject_cast<AssignmentSessionsListModel*>(model.data());
    student_assignment_sessions_model->PushBack(AssignmentSessionInfo(AssignmentSession(1,1,"19.06.2022 21:42","19.06.2022 21:42"), Assignment(1,1,"name","","",5)));
}
