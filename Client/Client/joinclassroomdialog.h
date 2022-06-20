#ifndef JOINCLASSROOMDIALOG_H
#define JOINCLASSROOMDIALOG_H

#include <QDialog>

namespace Ui {
class JoinClassroomDialog;
}

class JoinClassroomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JoinClassroomDialog(QWidget *parent = nullptr);
    ~JoinClassroomDialog();

private slots:
    void on_pushButton_join_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::JoinClassroomDialog *ui;
};

#endif // JOINCLASSROOMDIALOG_H
