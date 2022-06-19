#include "teacherassignmentcheckingwindow.h"
#include "ui_teacherassignmentcheckingwindow.h"
#include "font.h"
#include "checkassignment.h"
#include "jsonfile.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "assignmentguibuilder.h"
#include "assignmentguidirector.h"


TeacherAssignmentCheckingWindow::TeacherAssignmentCheckingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherAssignmentCheckingWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_auto_score->setFont(Font::RegularListViewFont());
    ui->label_max_score->setFont(Font::RegularListViewFont());
    ui->label_final_score->setFont(Font::RegularListViewFont());
    ui->spinBox_final_score->setFont(Font::RegularListViewFont());
    //ui->spinBox_final_score->setMaximum(max_score);
    // set title according to name

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

TeacherAssignmentCheckingWindow::~TeacherAssignmentCheckingWindow()
{
    delete ui;
}