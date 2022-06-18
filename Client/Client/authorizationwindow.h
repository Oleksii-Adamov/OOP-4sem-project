#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();
    void closeEvent (QCloseEvent *event) override;

private slots:
    void on_pushButtonLogIn_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::AuthorizationWindow *ui;
    bool is_succesuful_ = false;
};

#endif // AUTHORIZATIONWINDOW_H
