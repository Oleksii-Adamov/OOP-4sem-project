#include "teacherassignmentcheckingwindow.h"
#include "ui_teacherassignmentcheckingwindow.h"
#include "font.h"
#include "checkassignment.h"
#include "jsonfile.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "assignmentguibuilder.h"
#include "assignmentguidirector.h"


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

    CheckAssignment assignment_checker;

    AutoScore auto_score = assignment_checker.GetScore(QJsonDocumentFromJsonFile("assinment_json_from_student_to_server.json"),
                                                       QJsonDocumentFromJsonFile("Assignments/from_teacher_to_server.json"));
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

void TeacherAssignmentCheckingWindow::Update(net::message<CustomMsgTypes> msg)
{  

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

