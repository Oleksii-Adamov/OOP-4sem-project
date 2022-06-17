#include "sendassignmentwindow.h"
#include "ui_sendassignmentwindow.h"

SendAssignmentWindow::SendAssignmentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendAssignmentWindow)
{
    ui->setupUi(this);
}

SendAssignmentWindow::~SendAssignmentWindow()
{
    delete ui;
}
