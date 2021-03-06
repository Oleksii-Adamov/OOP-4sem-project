#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "font.h"
#include "client.h"

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    //this->setWindowState(Qt::WindowMaximized);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    ui->label_login->setFont(Font::RegularFont());
    ui->label_password->setFont(Font::RegularFont());
    ui->label_user_name->setFont(Font::RegularFont());
    ui->lineEdit_login->setFont(Font::RegularFont());
    ui->lineEdit_password->setFont(Font::RegularFont());
    ui->lineEdit_user_name->setFont(Font::RegularFont());
    ui->pushButton_register->setFont(Font::RegularFont());
    this->setWindowTitle("Register");
}

RegisterWindow::RegisterWindow(const QString& login, const QString& password, QWidget *parent) :
    RegisterWindow(parent)
{
    ui->lineEdit_login->setText(login);
    ui->lineEdit_password->setText(password);
}


void RegisterWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::SUCCESS_CREATE_CLASSROOM)
    {
        QMessageBox::information(this, "Registraion info", "Registraion is successful!");
        this->close();
    }
    if (msg.header.id == CustomMsgTypes::FAILURE_CREATE_CLASSROOM)
    {
        QMessageBox::critical(this, "Registraion error", "Failed to register. User with this login already exists!");
    }
}

void RegisterWindow::RegisterRequest()
{
    net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::JOIN_CLASSROOM_REQUEST;

    QString user_name = ui->lineEdit_user_name->text();
    for (int i = 0; i < user_name.size(); i++)
    {
        msg << user_name[i];
    }
    msg << user_name.size();

    QString password = ui->lineEdit_password->text();
    for (int i = 0; i < password.size(); i++)
    {
        msg << password[i];
    }
    msg << password.size();

    QString login = ui->lineEdit_login->text();
    for (int i = 0; i < login.size(); i++)
    {
        msg << login[i];
    }
    msg << login.size();

    Client::GetInstance()->Send(msg);
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
    else {
        this->close();
    }
}

