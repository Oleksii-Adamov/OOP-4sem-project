#include "createclassroomdialog.h"
#include "ui_createclassroomdialog.h"
#include <QRegularExpression>
#include <QMessageBox>
#include "font.h"
#include "client.h"

CreateClassroomDialog::CreateClassroomDialog(QWidget *parent) :
    QDialog(parent), ClientSubscriber(),
    ui(new Ui::CreateClassroomDialog)
{
    //comment
    ui->setupUi(this);
    ui->label_classroom_name->setFont(Font::RegularListViewFont());
    ui->lineEdit_classroom_name->setFont(Font::RegularListViewFont());
    ui->pushButton_create->setFont(Font::RegularFont());
    ui->pushButton_cancel->setFont(Font::RegularFont());
}

CreateClassroomDialog::~CreateClassroomDialog()
{
    delete ui;
}

void CreateClassroomDialog::on_pushButton_create_clicked()
{
    QRegularExpression rx("^[a-zA-ZА-Яа-я0-9ЁёІЇІЇҐґ_ -():]+$");
    if (ui->lineEdit_classroom_name->text().size() > 40) {
        QMessageBox::critical(this, "Create classrom error", "Clasroom name has length more that 40!");
    }
    else if (ui->lineEdit_classroom_name->text().size() == 0) {
        QMessageBox::critical(this, "Create classrom error", "Clasroom name is empty!");
    }
    else if (!rx.match(ui->lineEdit_classroom_name->text()).hasMatch())
    {
        QMessageBox::critical(this, "Create classrom error", "Clasroom name has forbidden symbols!");
    }
    else {
        CreateRequest();
    }
}

void CreateClassroomDialog::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::SUCCESS_CREATE_CLASSROOM)
    {
        this->close();
    }
    if (msg.header.id == CustomMsgTypes::FAILURE_CREATE_CLASSROOM)
    {
        QMessageBox::critical(this, "Create classrom error", "Failed to create classroom");
    }
}

void CreateClassroomDialog::CreateRequest()
{
    net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::CREATE_CLASSROOM_REQUEST;
    for (int i = 0; i < ui->lineEdit_classroom_name->text().size(); i++)
    {
        msg << ui->lineEdit_classroom_name->text()[i];
    }
    msg << ui->lineEdit_classroom_name->text().size() << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(msg);
}

void CreateClassroomDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

