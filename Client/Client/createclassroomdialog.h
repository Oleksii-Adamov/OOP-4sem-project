#ifndef CREATECLASSROOMDIALOG_H
#define CREATECLASSROOMDIALOG_H

#include <QDialog>

namespace Ui {
class CreateClassroomDialog;
}

class CreateClassroomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateClassroomDialog(QWidget *parent = nullptr);
    ~CreateClassroomDialog();

private slots:
    void on_pushButton_create_clicked();

private:
    Ui::CreateClassroomDialog *ui;
};

#endif // CREATECLASSROOMDIALOG_H
