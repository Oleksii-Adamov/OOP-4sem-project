#include "createclassroomdialog.h"
#include "ui_createclassroomdialog.h"
#include <QRegularExpression>
#include <QMessageBox>
#include "font.h"

CreateClassroomDialog::CreateClassroomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateClassroomDialog)
{
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
        QMessageBox::critical(this, "Log in error", "Clasroom name has forbidden symbols!");
    }
    else {
        this->close();
    }
}

void CreateClassroomDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

