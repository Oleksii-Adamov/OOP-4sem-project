#include "studentassignmentwindow.h"
#include "ui_studentassignmentwindow.h"
#include "font.h"
#include <QScrollArea>
#include "assignmentguidirector.h"
#include "jsonfile.h"
#include "client.h"

StudentAssignmentWindow::StudentAssignmentWindow(const StudentAssignmentSessionInfo& student_assignment_session_info, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(),
    ui(new Ui::StudentAssignmentWindow), student_assignment_session_info_(student_assignment_session_info)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_deadline->setFont(Font::RegularListViewFont());
    this->setWindowTitle(QString::fromStdString(student_assignment_session_info.assignment.getAssignmentName()));
    ui->label_deadline->setText("Deadline: " + QString::fromStdString(student_assignment_session_info.assignment_session.getAssignmentSessionEndDate()));
    GetData();
    FromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_server_to_student.json"));
}

void StudentAssignmentWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::RETURN_STUDENT_ASSIGNMENT_SESSION_ANSWER)
    {
        FromJSON(QJsonDocumentFromServerMessage(msg));
    }
}

StudentAssignmentWindow::~StudentAssignmentWindow()
{
    delete ui;
}

void StudentAssignmentWindow::GetData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_STUDENT_ASSIGNMENT_SESSION_ANSWER;
    message << student_assignment_session_info_.student_assignment_session.getAssignmentSessionId() << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}

void StudentAssignmentWindow::FromJSON(const QJsonDocument& json_doc)
{
    QVBoxLayout* layout = new QVBoxLayout(ui->assignment_widget);

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    QWidget* assignment_container = new QWidget(this);
    scrollArea->setWidget(assignment_container);

    QVBoxLayout* assignment_layout = new QVBoxLayout(assignment_container);

    AssignmentGUIBuilder assignment_GUI_builder;
    bool is_editable = false;
    if (student_assignment_session_info_.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::not_submitted) {
        is_editable = true;
    }
    assignment_GUI_builder.Set(assignment_layout, assignment_container, is_editable);
    AssignmentGUIDirector assignment_GUI_director;
    assignment_GUI_director.set_builder(&assignment_GUI_builder);
    assignment_GUI_director.BuildFromJSON(json_doc);
}

void StudentAssignmentWindow::on_actionUpdate_triggered()
{
    GetData();
}

