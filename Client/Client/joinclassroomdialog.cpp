#include "joinclassroomdialog.h"
#include "ui_joinclassroomdialog.h"
#include "font.h"
#include <QMessageBox>
#include <QRegularExpression>

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

        this->close();
    }
}


void JoinClassroomDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

