#include "classroomwindowstudentstrategy.h"
#include "studentassignmentsessionslistmodel.h"
#include "studentassignmentwindow.h"
#include "jsonfile.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "client.h"

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
    if (msg.header.id == CustomMsgTypes::RETURN_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO) {
    StudentAssignmentSessionsListModel* student_assignment_sessions_model = qobject_cast<StudentAssignmentSessionsListModel*>(model.data());
    //student_assignment_sessions_model->PushBack(StudentAssignmentSessionInfo(StudentAssignmentSession(1,1,StudentAssignmentSessionStatus::not_submitted, "", 0, ""),
     student_assignment_sessions_model->Clear();
     QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
     QJsonObject json_doc_obj = json_doc.object();
     QJsonArray infos =  json_doc_obj.take("StudentAssignmentSessionInfos").toArray();
     for (int i = 0; i < infos.size(); i++)
     {
         QJsonObject info_object = infos.at(i).toObject();
         QJsonObject student_assignment_session_object = info_object.take("StudentAssignmentSession").toObject();
         QJsonObject assignment_session_obj = info_object.take("AssignmentSession").toObject();
         QJsonObject assignment_obj = info_object.take("Assignment").toObject();
         Assignment assignment = GetAssignmentFromJson(assignment_obj);
         AssignmentSession assignment_session = GetAssignmentSessionFromJson(assignment_session_obj);
         StudentAssignmentSession student_assignment_session = GetStudentAssignmentSessionFromJson(student_assignment_session_object);
        student_assignment_sessions_model->PushBack(StudentAssignmentSessionInfo(student_assignment_session,assignment_session, assignment));
     }
    }
}

void ClassroomWindowStudentStrategy::GetData(const ClassroomInfo& classroom_info)
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_ALL_ASSIGNMENTS_OF_CLASSROOM_STUDENT_INFO;
    message << classroom_info.classroom.getClassroomId() << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}
