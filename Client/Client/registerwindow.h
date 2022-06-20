#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include "clientsubscriber.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    explicit RegisterWindow(const QString& login, const QString& password, QWidget *parent = nullptr);
    ~RegisterWindow();
    void Update(net::message<CustomMsgTypes>& msg) override;
private slots:
    void on_pushButton_register_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
