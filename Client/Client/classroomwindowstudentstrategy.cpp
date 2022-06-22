#include "classroomwindowstudentstrategy.h"
#include "studentassignmentsessionslistmodel.h"
#include "studentassignmentwindow.h"
#include "jsonfile.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
    if (1) {
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
     }
    }
}

void ClassroomWindowStudentStrategy::GetData()
{

}
