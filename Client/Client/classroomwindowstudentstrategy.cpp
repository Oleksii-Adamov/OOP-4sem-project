#include "classroomwindowstudentstrategy.h"
#include "studentassignmentsessionslistmodel.h"

ClassroomWindowStudentStrategy::ClassroomWindowStudentStrategy()
{

}

void ClassroomWindowStudentStrategy::OnAssignmentClicked(unsigned long long id)
{
    // get info about assignment from server, Instanciate window, give it layout to AssignmentGUIDirector with json
}

void ClassroomWindowStudentStrategy::SetModel(QSharedPointer<QAbstractListModel>& model)
{
    model.reset(new StudentAssignmentSessionsListModel());
}

void ClassroomWindowStudentStrategy::Update(net::message<CustomMsgTypes>& msg, QSharedPointer<QAbstractListModel>& model)
{
    StudentAssignmentSessionsListModel* student_assignment_sessions_model = qobject_cast<StudentAssignmentSessionsListModel*>(model.data());
    //QSharedPointer<StudentAssignmentSessionsListModel> student_assignment_sessions_model = qobject_cast<QSharedPointer<StudentAssignmentSessionsListModel>>(model);
    student_assignment_sessions_model->PushBack(StudentAssignmentSessionInfo(StudentAssignmentSession(1,1,StudentAssignmentSessionStatus::not_submitted, "", 0, ""),
                                                                             AssignmentSession(1,1,"19.06.2022 21:42","19.06.2022 21:42"), Assignment(1,1,"name","","",5)));
}
