#include "enterassignmentnamedialog.h"
#include "ui_enterassignmentnamedialog.h"
#include <QRegularExpression>
#include <QValidator>
#include <QFile>
#include <QMessageBox>
#include "filepath.h"
#include "font.h"

EnterAssignmentNameDialog::EnterAssignmentNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterAssignmentNameDialog)
{
    ui->setupUi(this);
    QRegularExpression rx("^[a-zA-ZА-Яа-я0-9ЁёІЇІЇҐґ_ -]+$");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_name->setValidator(validator);
    ui->lineEdit_name->setMaxLength(40);

    ui->lineEdit_name->setFont(Font::RegularFont());
    ui->label_name->setFont(Font::RegularFont());
    ui->label_max_score->setFont(Font::RegularFont());
    ui->pushButton_Save->setFont(Font::RegularFont());
    ui->pushButton_Cancel->setFont(Font::RegularFont());
    ui->spinBox_max_score->setFont(Font::RegularFont());
}

EnterAssignmentNameDialog::~EnterAssignmentNameDialog()
{
    delete ui;
}

void EnterAssignmentNameDialog::on_pushButton_Save_clicked()
{
    QFile file(QString::fromStdString(GetAssignmentPath(ui->lineEdit_name->text().toStdString())));
    if (file.exists()) {
        QMessageBox::critical(this, "Error", "Assignment with this name already exists!");
        return;
    }
    emit NameChanged(ui->lineEdit_name->text());
    this->close();
}


void EnterAssignmentNameDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

