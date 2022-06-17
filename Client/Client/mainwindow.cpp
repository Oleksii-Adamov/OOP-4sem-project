#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "assignmentguibuilder.h"
#include "assignmentguidirector.h"
#include "jsonfile.h"
#include "editablelabel.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout(ui->centralwidget);

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
    //assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_server_to_student.json"));
    //assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("assinment_json_from_student_to_server.json"));
    assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("assinment_json_from_student_to_server.json"),
                                          QJsonDocumentFromJsonFile("Assignments/from_teacher_to_server.json"));

    //assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_server_to_student_example.json"));
    //assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_teacher_to_server.json"));
    //assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_student_to_server.json"));
    //assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_student_to_server.json"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

