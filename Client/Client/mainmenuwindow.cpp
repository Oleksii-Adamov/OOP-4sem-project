#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "font.h"
#include "authorizationwindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    ui->pushButton_classrooms->setFont(Font::BigFont());
    ui->pushButton_assignments->setFont(Font::BigFont());
    ui->pushButton_send_assignment->setFont(Font::BigFont());

    AuthorizationWindow* new_window  = new AuthorizationWindow(this);
    new_window->setWindowModality(Qt::WindowModal);
    new_window->show();
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}
