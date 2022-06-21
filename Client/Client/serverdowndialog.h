#ifndef SERVERDOWNDIALOG_H
#define SERVERDOWNDIALOG_H

#include <QDialog>

namespace Ui {
class ServerDownDialog;
}

class ServerDownDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDownDialog(QWidget *parent = nullptr);
    ~ServerDownDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ServerDownDialog *ui;
};

#endif // SERVERDOWNDIALOG_H
