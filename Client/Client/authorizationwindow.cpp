#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "registerwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::on_pushButtonLogIn_clicked()
{
    QRegularExpression rx("^[a-zA-Z0-9_^-]+$");
    if (ui->lineEdit_login->text().size() > 20) {
        QMessageBox::critical(this, "Log in error", "Login has length more that 20!");
    }
    else if (ui->lineEdit_login->text().size() == 0) {
        QMessageBox::critical(this, "Log in error", "Login is empty!");
    }
    else if (!rx.match(ui->lineEdit_login->text()).hasMatch())
    {
        QMessageBox::critical(this, "Log in error", "Login has forbidden symbols! Only digits, latin letters of any case, _,^,- allowed");
    }
    else if (ui->lineEdit_password->text().size() > 20) {
        QMessageBox::critical(this, "Log in error", "Password has length more that 20!");
    }
    else if (ui->lineEdit_password->text().size() == 0) {
        QMessageBox::critical(this, "Log in error", "Password is empty!");
    }
    else if (!rx.match(ui->lineEdit_password->text()).hasMatch())
    {
        QMessageBox::critical(this, "Log in error", "Password has forbidden symbols! Only digits, latin letters of any case, _,^,- allowed");
    }
}


void AuthorizationWindow::on_pushButton_register_clicked()
{
    RegisterWindow* register_window  = new RegisterWindow(ui->lineEdit_login->text(), ui->lineEdit_password->text(), this);
    register_window->show();
}

