#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

private slots:
    void on_pushButton_classrooms_clicked();

    void on_pushButton_send_assignment_clicked();

    void on_pushButton_created_assignments_clicked();

private:
    Ui::MainMenuWindow *ui;
};

#endif // MAINMENUWINDOW_H
