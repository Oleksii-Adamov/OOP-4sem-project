#ifndef JOINCLASSROOMDIALOG_H
#define JOINCLASSROOMDIALOG_H

#include <QDialog>
#include "clientsubscriber.h"

namespace Ui {
class JoinClassroomDialog;
}

class JoinClassroomDialog : public QDialog, ClientSubscriber
{
    Q_OBJECT

public:
    explicit JoinClassroomDialog(QWidget *parent = nullptr);
    ~JoinClassroomDialog();
    void Update(net::message<CustomMsgTypes>& msg) override;

private slots:
    void on_pushButton_join_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::JoinClassroomDialog *ui;
};

#endif // JOINCLASSROOMDIALOG_H
