#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "registerwindow.h"
#include "font.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "jsonfile.h"
#include "client.h"


AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    //this->setWindowState(Qt::WindowMaximized);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    ui->label_login->setFont(Font::RegularFont());
    ui->label_password->setFont(Font::RegularFont());
    ui->lineEdit_login->setFont(Font::RegularFont());
    ui->lineEdit_password->setFont(Font::RegularFont());
    ui->pushButtonLogIn->setFont(Font::RegularFont());
    ui->pushButton_register->setFont(Font::RegularFont());
    this->setWindowTitle("Log In");
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
    else {
        is_succesuful_ = true;
        this->close();
    }
}

void AuthorizationWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::SUCCESS_CREATE_CLASSROOM)
    {
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonObject user_object = json_doc_obj.take("User").toObject();
        User user(user_object.take("user_id").toInteger(),
                     user_object.take("login").toString().toStdString(),
                     user_object.take("user_name").toString().toStdString());
        Client::GetInstance()->SetUser(user);
        is_succesuful_ = true;
        this->close();
    }
    if (msg.header.id == CustomMsgTypes::FAILURE_CREATE_CLASSROOM)
    {
        QMessageBox::critical(this, "Registraion error", "Failed to register. User with this login already exists!");
    }
}

void AuthorizationWindow::LogInRequest()
{
    net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::JOIN_CLASSROOM_REQUEST;

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


void AuthorizationWindow::on_pushButton_register_clicked()
{
    RegisterWindow* register_window  = new RegisterWindow(ui->lineEdit_login->text(), ui->lineEdit_password->text(), this);
    register_window->show();
}

void AuthorizationWindow::closeEvent (QCloseEvent *event)
{
    if (is_succesuful_) {
        event->accept();
    }
    else {
        exit(0);
    }
}
