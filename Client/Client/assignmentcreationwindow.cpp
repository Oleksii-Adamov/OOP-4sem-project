#include "assignmentcreationwindow.h"
#include "ui_assignmentcreationwindow.h"

AssignmentCreationWindow::AssignmentCreationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssignmentCreationWindow)
{
    ui->setupUi(this);
}

AssignmentCreationWindow::~AssignmentCreationWindow()
{
    delete ui;
}
