#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "clientsubscriber.h"

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();
    void closeEvent (QCloseEvent *event) override;
    void Update(net::message<CustomMsgTypes> msg) override;
private slots:
    void on_pushButtonLogIn_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::AuthorizationWindow *ui;
    bool is_succesuful_ = false;
};

#endif // AUTHORIZATIONWINDOW_H
