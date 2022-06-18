#include "teacherassignmentcheckingwindow.h"
#include "ui_teacherassignmentcheckingwindow.h"
#include "font.h"

TeacherAssignmentCheckingWindow::TeacherAssignmentCheckingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherAssignmentCheckingWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_tests_score->setFont(Font::RegularListViewFont());
}

TeacherAssignmentCheckingWindow::~TeacherAssignmentCheckingWindow()
{
    delete ui;
}
