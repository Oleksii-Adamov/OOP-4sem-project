#include "teacherassignmentcheckingwindow.h"
#include "ui_teacherassignmentcheckingwindow.h"
#include "font.h"
#include "checkassignment.h"
#include "jsonfile.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "assignmentguibuilder.h"
#include "assignmentguidirector.h"
#include <QMessageBox>
#include "client.h"


TeacherAssignmentCheckingWindow::TeacherAssignmentCheckingWindow(const StudentAssignmentSessionInfoForTeacher& student_assignment_session_info_for_teacher, const Assignment& assignment, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(), student_assignment_session_info_for_teacher_(student_assignment_session_info_for_teacher),
    ui(new Ui::TeacherAssignmentCheckingWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_auto_score->setFont(Font::RegularListViewFont());
    ui->label_max_score->setFont(Font::RegularListViewFont());
    ui->label_final_score->setFont(Font::RegularListViewFont());
    ui->spinBox_final_score->setFont(Font::RegularListViewFont());
    ui->pushButton_rate->setFont(Font::RegularFont());
    ui->spinBox_final_score->setMaximum(assignment.getAssignmentMaxScore());
    ui->label_max_score->setText("Max score: " + QString::number(assignment.getAssignmentMaxScore()));
    this->setWindowTitle(QString::fromStdString(student_assignment_session_info_for_teacher.student.getUserName()) + " " +
                         QString::fromStdString(assignment.getAssignmentName()));
}

void TeacherAssignmentCheckingWindow::Update(net::message<CustomMsgTypes> msg)
{  
    if (msg.header.id == CustomMsgTypes::SUCCESS_EVALUATE_STUDENT_ASSIGNMENT) {
        QMessageBox::information(this, "Evaluation info", "Successfully rated!");
        this->close();
    }
    if (msg.header.id == CustomMsgTypes::RETURN_STUDENT_ASSIGNMENT_SESSION_ANSWER)
    {
        student_data_ready = true;
        student_json_doc =  QJsonDocumentFromServerMessage(msg);
        if (student_data_ready && teacher_data_ready) {
            FromJSON(student_json_doc, teacher_json_doc);
        }
    }
    if (msg.header.id == CustomMsgTypes::RETURN_CREATED_ASSIGNMENT)
    {
        teacher_data_ready = true;
        teacher_json_doc =  QJsonDocumentFromServerMessage(msg);
        if (student_data_ready && teacher_data_ready) {
            FromJSON(student_json_doc, teacher_json_doc);
        }
    }
}

TeacherAssignmentCheckingWindow::~TeacherAssignmentCheckingWindow()
{
    delete ui;
}

void TeacherAssignmentCheckingWindow::on_pushButton_rate_clicked()
{
    net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::EVALUATE_STUDENT_ASSIGNMENT;
    msg << (int32_t) ui->spinBox_final_score->value() << student_assignment_session_info_for_teacher_.student_assignment_session.getAssignmentSessionId() << student_assignment_session_info_for_teacher_.student.getUserId();
}

void TeacherAssignmentCheckingWindow::GetStudentAnswer()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_STUDENT_ASSIGNMENT_SESSION_ANSWER;
    message << (ID) student_assignment_session_info_for_teacher_.student_assignment_session.getAssignmentSessionId() << (ID) student_assignment_session_info_for_teacher_.student.getUserId();
    Client::GetInstance()->Send(message);
}
void TeacherAssignmentCheckingWindow::GetAssignmentAnswer()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_CREATED_ASSIGNMENT;
    //message << assignment_.getAssignmentId();
    //CustomMsgTypes::Get
}

void TeacherAssignmentCheckingWindow::FromJSON(const QJsonDocument& student_json_doc, const QJsonDocument& teacher_json_doc)
{
    CheckAssignment assignment_checker;

    AutoScore auto_score = assignment_checker.GetScore(student_json_doc,
                                                      teacher_json_doc);
    ui->label_auto_score->setText(ui->label_auto_score->text() +
                                  QString::number(auto_score.score) + "/" + QString::number(auto_score.max_score));

    QVBoxLayout* layout = new QVBoxLayout(ui->assignment_widget);

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    QWidget* assignment_container = new QWidget(this);
    scrollArea->setWidget(assignment_container);

    QVBoxLayout* assignment_layout = new QVBoxLayout(assignment_container);

    AssignmentGUIBuilder assignment_GUI_builder;
    assignment_GUI_builder.Set(assignment_layout, assignment_container, false);
    AssignmentGUIDirector assignment_GUI_director;
    assignment_GUI_director.set_builder(&assignment_GUI_builder);
    assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("assinment_json_from_student_to_server.json"),
                                          QJsonDocumentFromJsonFile("Assignments/from_teacher_to_server.json"));
}
