#include "studentassignmentwindow.h"
#include "ui_studentassignmentwindow.h"
#include "font.h"
#include <QScrollArea>
#include "assignmentguidirector.h"
#include "jsonfile.h"

StudentAssignmentWindow::StudentAssignmentWindow(const StudentAssignmentSessionInfo& student_assignment_session_info, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(),
    ui(new Ui::StudentAssignmentWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_deadline->setFont(Font::RegularListViewFont());
    this->setWindowTitle(QString::fromStdString(student_assignment_session_info.assignment.getAssignmentName()));
    ui->label_deadline->setText("Deadline: " + QString::fromStdString(student_assignment_session_info.assignment_session.getAssignmentSessionEndDate()));

    QVBoxLayout* layout = new QVBoxLayout(ui->assignment_widget);

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    QWidget* assignment_container = new QWidget(this);
    scrollArea->setWidget(assignment_container);

    QVBoxLayout* assignment_layout = new QVBoxLayout(assignment_container);

    AssignmentGUIBuilder assignment_GUI_builder;
    bool is_editable = false;
    if (student_assignment_session_info.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::not_submitted) {
        is_editable = true;
    }
    assignment_GUI_builder.Set(assignment_layout, assignment_container, is_editable);
    AssignmentGUIDirector assignment_GUI_director;
    assignment_GUI_director.set_builder(&assignment_GUI_builder);
    assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_server_to_student.json"));
}

void StudentAssignmentWindow::Update(net::message<CustomMsgTypes> msg)
{

}

StudentAssignmentWindow::~StudentAssignmentWindow()
{
    delete ui;
}

void StudentAssignmentWindow::GetData()
{

}
