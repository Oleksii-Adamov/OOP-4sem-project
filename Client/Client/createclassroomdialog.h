#ifndef CREATECLASSROOMDIALOG_H
#define CREATECLASSROOMDIALOG_H

#include <QDialog>
#include "clientsubscriber.h"

namespace Ui {
class CreateClassroomDialog;
}

class CreateClassroomDialog : public QDialog, ClientSubscriber
{
    Q_OBJECT

public:
    explicit CreateClassroomDialog(QWidget *parent = nullptr);
    ~CreateClassroomDialog();
    void Update(net::message<CustomMsgTypes> msg) override;

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::CreateClassroomDialog *ui;
};

#endif // CREATECLASSROOMDIALOG_H
