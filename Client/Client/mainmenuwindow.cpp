#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "font.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    ui->pushButton_classrooms->setFont(Font::BigFont());
    ui->pushButton_assignments->setFont(Font::BigFont());
    ui->pushButton_send_assignment->setFont(Font::BigFont());
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}
