#include "createdassignmentswindow.h"
#include "ui_createdassignmentswindow.h"

CreatedAssignmentsWindow::CreatedAssignmentsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatedAssignmentsWindow)
{
    ui->setupUi(this);
}

CreatedAssignmentsWindow::~CreatedAssignmentsWindow()
{
    delete ui;
}
