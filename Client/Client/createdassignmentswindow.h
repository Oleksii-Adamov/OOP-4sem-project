#ifndef CREATEDASSIGNMENTSWINDOW_H
#define CREATEDASSIGNMENTSWINDOW_H

#include <QMainWindow>

namespace Ui {
class CreatedAssignmentsWindow;
}

class CreatedAssignmentsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreatedAssignmentsWindow(QWidget *parent = nullptr);
    ~CreatedAssignmentsWindow();

private:
    Ui::CreatedAssignmentsWindow *ui;
};

#endif // CREATEDASSIGNMENTSWINDOW_H
