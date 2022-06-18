#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "font.h"
#include "authorizationwindow.h"
#include "classroomslistwindow.h"
#include "sendassignmentwindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Main menu");
    ui->pushButton_classrooms->setFont(Font::BigFont());
    ui->pushButton_created_assignments->setFont(Font::BigFont());
    ui->pushButton_send_assignment->setFont(Font::BigFont());

    AuthorizationWindow* new_window  = new AuthorizationWindow(this);
    new_window->setWindowModality(Qt::WindowModal);
    new_window->show();
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::on_pushButton_classrooms_clicked()
{
    ClassroomsListWindow* new_window  = new ClassroomsListWindow(this);
    new_window->show();
}


void MainMenuWindow::on_pushButton_send_assignment_clicked()
{
    SendAssignmentWindow* new_window  = new SendAssignmentWindow(this);
    new_window->show();
}

