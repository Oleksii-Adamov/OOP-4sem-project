#ifndef STUDENTASSIGNMENTSESSIONSWINDOW_H
#define STUDENTASSIGNMENTSESSIONSWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessionsforteacherlistmodel.h"
#include "assignmentsessioninfo.h"

namespace Ui {
class StudentAssignmentSessionsWindow;
}

class StudentAssignmentSessionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentAssignmentSessionsWindow(const AssignmentSessionInfo& assignment_session_info, QWidget *parent = nullptr);
    ~StudentAssignmentSessionsWindow();

public slots:
    void OnStudentAssignmentClicked(const QModelIndex& student_assignment);

private:
    Ui::StudentAssignmentSessionsWindow *ui;
    QSharedPointer<StudentAssignmentSessionsForTeacherListModel> student_assignments_list_model;
    AssignmentSessionInfo assignment_session_info_;
};

#endif // STUDENTASSIGNMENTSESSIONSWINDOW_H
