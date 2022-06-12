#ifndef ENTERASSIGNMENTNAMEDIALOG_H
#define ENTERASSIGNMENTNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class EnterAssignmentNameDialog;
}

class EnterAssignmentNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnterAssignmentNameDialog(QWidget *parent = nullptr);
    ~EnterAssignmentNameDialog();

signals:
   void NameChanged(const QString& name);

private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::EnterAssignmentNameDialog *ui;

};

#endif // ENTERASSIGNMENTNAMEDIALOG_H
