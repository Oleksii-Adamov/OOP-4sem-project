#include "studentassignmentsessionswindow.h"
#include "ui_studentassignmentsessionswindow.h"
#include "font.h"
#include "teacherassignmentcheckingwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonfile.h"
#include "client.h"

StudentAssignmentSessionsWindow::StudentAssignmentSessionsWindow(const AssignmentSessionInfo& assignment_session_info, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(), ui(new Ui::StudentAssignmentSessionsWindow),
    assignment_session_info_(assignment_session_info)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Student assignments for " + QString::fromStdString(assignment_session_info.assignment.getAssignmentName()));

    student_assignments_list_model.reset(new StudentAssignmentSessionsForTeacherListModel(assignment_session_info_.assignment.getAssignmentMaxScore()));

    ui->label_assignment_name->setFont(Font::BigFont());
    ui->label_deadline->setFont(Font::RegularListViewFont());
    ui->label_student_assignments->setFont(Font::BigFont());

    ui->student_assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->student_assignments_list_view->setFont(Font::RegularListViewFont());
    ui->student_assignments_list_view->setModel(student_assignments_list_model.data());

    connect(ui->student_assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnStudentAssignmentClicked(QModelIndex)));

    ui->label_assignment_name->setText(QString::fromStdString(assignment_session_info_.assignment.getAssignmentName()));
    ui->label_deadline->setText("Deadline: " + QString::fromStdString(assignment_session_info_.assignment_session.getAssignmentSessionEndDate()));
    student_assignments_list_model->PushBack(StudentAssignmentSessionInfoForTeacher(StudentAssignmentSession(1,1,StudentAssignmentSessionStatus::submitted, "", 0, "19.06.2022 23:21"), User(1,"login", "student name")));
//    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(2, StudentAssignmentSessionStatus::checked, "17:59 18.06.2022", "User name2", 3));
//    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(3, StudentAssignmentSessionStatus::not_submitted, "17:59 18.06.2022", "User name3"));
    //GetData();
}

void StudentAssignmentSessionsWindow::GetData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS;
    message << assignment_session_info_.assignment_session.getAssignmentSessionId();
    Client::GetInstance()->Send(message);
}

void StudentAssignmentSessionsWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::RETURN_ALL_STUDENT_ASSIGNMENT_SESSION_ANSWERS)
    {
        //student_assignments_list_model->Clear();
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonArray student_assignment_session_infos =  json_doc_obj.take("StudentAssignmentSessionInfosForTeacher").toArray();
        for (int i = 0; i < student_assignment_session_infos.size(); i++)
        {
            QJsonObject student_assignment_session_info_object = student_assignment_session_infos.at(i).toObject();
            QJsonObject student_assignment_session_object = student_assignment_session_info_object.take("StudentAssignmentSession").toObject();
            QString student_assignment_session_status_string = student_assignment_session_object.take("student_assignment_session_status").toString();
            StudentAssignmentSessionStatus student_assignment_session_status = StudentAssignmentSessionStatus::not_submitted;
            if (student_assignment_session_status_string == "not_submitted")
            {
                student_assignment_session_status = StudentAssignmentSessionStatus::not_submitted;
            }
            else if (student_assignment_session_status_string == "submitted")
            {
                student_assignment_session_status = StudentAssignmentSessionStatus::submitted;
            }
            else if (student_assignment_session_status_string == "checked")
            {
                student_assignment_session_status = StudentAssignmentSessionStatus::checked;
            }
            StudentAssignmentSession student_assignment_session(
                        student_assignment_session_object.take("student_user_id").toInteger(),
                        student_assignment_session_object.take("assignment_session_id").toInteger(),
                        student_assignment_session_status, "",
                        student_assignment_session_object.take("student_assignment_session_score").toInt(),
                        student_assignment_session_object.take("student_assignment_session_finish_date").toString().toStdString());
            QJsonObject student_object = student_assignment_session_info_object.take("User").toObject();
            User student(student_object.take("user_id").toInteger(),
                         student_object.take("login").toString().toStdString(),
                         student_object.take("user_name").toString().toStdString());
            student_assignments_list_model->PushBack(StudentAssignmentSessionInfoForTeacher(student_assignment_session, student));
        }
    }
}

void StudentAssignmentSessionsWindow::OnStudentAssignmentClicked(const QModelIndex& student_assignment)
{
    TeacherAssignmentCheckingWindow* new_window = new TeacherAssignmentCheckingWindow(student_assignments_list_model->GetData(student_assignment),
                                                                                      assignment_session_info_.assignment, this);
    new_window->show();
}

StudentAssignmentSessionsWindow::~StudentAssignmentSessionsWindow()
{
    delete ui;
}
