#ifndef TEACHERASSIGNMENTCHECKINGWINDOW_H
#define TEACHERASSIGNMENTCHECKINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class TeacherAssignmentCheckingWindow;
}

class TeacherAssignmentCheckingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherAssignmentCheckingWindow(QWidget *parent = nullptr);
    ~TeacherAssignmentCheckingWindow();

private:
    Ui::TeacherAssignmentCheckingWindow *ui;
};

#endif // TEACHERASSIGNMENTCHECKINGWINDOW_H
