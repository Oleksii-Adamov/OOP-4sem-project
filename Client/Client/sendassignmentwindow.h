#ifndef SENDASSIGNMENTWINDOW_H
#define SENDASSIGNMENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class SendAssignmentWindow;
}

class SendAssignmentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SendAssignmentWindow(QWidget *parent = nullptr);
    ~SendAssignmentWindow();

private:
    Ui::SendAssignmentWindow *ui;
};

#endif // SENDASSIGNMENTWINDOW_H
