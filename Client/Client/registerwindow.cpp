#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

RegisterWindow::RegisterWindow(const QString& login, const QString& password, QWidget *parent) :
    RegisterWindow(parent)
{
    ui->lineEdit_login->setText(login);
    ui->lineEdit_password->setText(password);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_register_clicked()
{
    QRegularExpression rx("^[a-zA-Z0-9_^-]+$");
    if (ui->lineEdit_login->text().size() > 20) {
        QMessageBox::critical(this, "Registraion error", "Login has length more that 20!");
    }
    else if (ui->lineEdit_login->text().size() == 0) {
        QMessageBox::critical(this, "Registraion error", "Login is empty!");
    }
    else if (!rx.match(ui->lineEdit_login->text()).hasMatch())
    {
        QMessageBox::critical(this, "Registraion error", "Login has forbidden symbols! Only digits, latin letters of any case, _,^,- allowed");
    }
    else if (ui->lineEdit_user_name->text().size() > 20) {
        QMessageBox::critical(this, "Registraion error", "User name has length more that 20!");
    }
    else if (ui->lineEdit_user_name->text().size() == 0) {
        QMessageBox::critical(this, "Registraion error", "User name is empty!");
    }
    else if (!rx.match(ui->lineEdit_user_name->text()).hasMatch())
    {
        QMessageBox::critical(this, "Registraion error", "User name has forbidden symbols! Only digits, latin letters of any case, _,^,- allowed");
    }
    else if (ui->lineEdit_password->text().size() > 20) {
        QMessageBox::critical(this, "Registraion error", "Password has length more that 20!");
    }
    else if (ui->lineEdit_password->text().size() == 0) {
        QMessageBox::critical(this, "Registraion error", "Password is empty!");
    }
    else if (!rx.match(ui->lineEdit_password->text()).hasMatch())
    {
        QMessageBox::critical(this, "Registraion error", "Password has forbidden symbols! Only digits, latin letters of any case, _,^,- allowed");
    }
}

