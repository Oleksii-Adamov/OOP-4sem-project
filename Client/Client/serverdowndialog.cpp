#include "serverdowndialog.h"
#include "ui_serverdowndialog.h"

ServerDownDialog::ServerDownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDownDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Classrooms");
}

ServerDownDialog::~ServerDownDialog()
{
    exit(0);
    delete ui;
}

void ServerDownDialog::on_pushButtonOK_clicked()
{
    this->close();
}

