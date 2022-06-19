#ifndef STUDENTASSIGNMENTWINDOW_H
#define STUDENTASSIGNMENTWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessioninfo.h"

namespace Ui {
class StudentAssignmentWindow;
}

class StudentAssignmentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentAssignmentWindow(const StudentAssignmentSessionInfo& student_assignment_session_info, QWidget *parent = nullptr);
    ~StudentAssignmentWindow();

private:
    Ui::StudentAssignmentWindow *ui;
};

#endif // STUDENTASSIGNMENTWINDOW_H
