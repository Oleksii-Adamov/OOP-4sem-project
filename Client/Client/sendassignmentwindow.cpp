#include "sendassignmentwindow.h"
#include "ui_sendassignmentwindow.h"
#include "font.h"

SendAssignmentWindow::SendAssignmentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendAssignmentWindow)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowMaximized);

    assignments_list_model.reset(new AssignmentsNameListModel());
    classrooms_list_model.reset(new ClassroomsNameListModel());

    ui->label_assignment->setFont(Font::RegularFont());
    ui->label_classroom->setFont(Font::RegularFont());

    ui->pushButton_cancel->setFont(Font::RegularFont());
    ui->pushButton_send->setFont(Font::RegularFont());

    ui->comboBox_assignment->setFont(Font::RegularFont());
    ui->comboBox_assignment->setModel(assignments_list_model.data());

    ui->comboBox_classroom->setFont(Font::RegularFont());
    ui->comboBox_classroom->setModel(classrooms_list_model.data());

    assignments_list_model->Push(AssignmentInfo(1, "A1", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(2, "A2", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "12:01 14.06.2022"));
}

SendAssignmentWindow::~SendAssignmentWindow()
{
    delete ui;
}
