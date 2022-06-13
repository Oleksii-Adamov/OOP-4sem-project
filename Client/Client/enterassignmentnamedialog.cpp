#include "enterassignmentnamedialog.h"
#include "ui_enterassignmentnamedialog.h"
#include <QRegularExpression>
#include <QValidator>
#include <QFile>
#include <QMessageBox>
#include "filepath.h"

EnterAssignmentNameDialog::EnterAssignmentNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterAssignmentNameDialog)
{
    ui->setupUi(this);
    QRegularExpression rx("^[a-zA-ZА-Яа-я0-9ЁёІЇІЇҐґ_ -]+$");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setMaxLength(24);
}

EnterAssignmentNameDialog::~EnterAssignmentNameDialog()
{
    delete ui;
}

void EnterAssignmentNameDialog::on_pushButton_Save_clicked()
{
    QFile file(QString::fromStdString(GetAssignmentPath(ui->lineEdit->text().toStdString())));
    if (file.exists()) {
        QMessageBox::critical(this, "Error", "Assignment with this name already exists!");
        return;
    }
    emit NameChanged(ui->lineEdit->text());
    this->close();
}


void EnterAssignmentNameDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

