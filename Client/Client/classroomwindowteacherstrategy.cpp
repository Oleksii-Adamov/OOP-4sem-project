#include "classroomwindowteacherstrategy.h"
#include "assignmentsessionslistmodel.h"

ClassroomWindowTeacherStrategy::ClassroomWindowTeacherStrategy()
{

}

void ClassroomWindowTeacherStrategy::OnAssignmentClicked(unsigned long long id)
{

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
