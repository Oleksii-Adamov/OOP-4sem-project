#include "joinclassroomdialog.h"
#include "ui_joinclassroomdialog.h"
#include "font.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "client.h"

JoinClassroomDialog::JoinClassroomDialog(QWidget *parent) :
    QDialog(parent), ClientSubscriber(),
    ui(new Ui::JoinClassroomDialog)
{
    ui->setupUi(this);
    ui->label_classroom_id->setFont(Font::RegularListViewFont());
    ui->lineEdit_classroom_id->setFont(Font::RegularListViewFont());
    ui->pushButton_join->setFont(Font::RegularFont());
    ui->pushButton_cancel->setFont(Font::RegularFont());
    ui->lineEdit_classroom_id->setMaxLength(19);
}

JoinClassroomDialog::~JoinClassroomDialog()
{
    delete ui;
}

void JoinClassroomDialog::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::SUCCESS_JOIN_CLASSROOM)
    {
        this->close();
    }
    if (msg.header.id == CustomMsgTypes::FAILURE_JOIN_CLASSROOM)
    {
        QMessageBox::critical(this, "Classroom join error", "Failed to join classroom, check the id");
    }
}

void JoinClassroomDialog::on_pushButton_join_clicked()
{
    QRegularExpression rx("^[0-9]+$");
    if (ui->lineEdit_classroom_id->text().size() == 0) {
        QMessageBox::critical(this, "Classroom join error", "Id is empty!");
    }
    if (!rx.match(ui->lineEdit_classroom_id->text()).hasMatch())
    {
        QMessageBox::critical(this, "Classroom join error", "Id is not a positive integer!");
    }
    else {
        JoinRequest();
    }
}


void JoinClassroomDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

void JoinClassroomDialog::JoinRequest()
{
    net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::JOIN_CLASSROOM_REQUEST;
    msg << ui->lineEdit_classroom_id->text().toInt() << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(msg);
}

