#ifndef STUDENTASSIGNMENTSESSIONSWINDOW_H
#define STUDENTASSIGNMENTSESSIONSWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessionslistmodel.h"

namespace Ui {
class StudentAssignmentSessionsWindow;
}

class StudentAssignmentSessionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentAssignmentSessionsWindow(QWidget *parent = nullptr);
    ~StudentAssignmentSessionsWindow();

public slots:
    void OnStudentAssignmentClicked(const QModelIndex& student_assignment);

private:
    Ui::StudentAssignmentSessionsWindow *ui;
    QSharedPointer<StudentAssignmentSessionsListModel> student_assignments_list_model;
};

#endif // STUDENTASSIGNMENTSESSIONSWINDOW_H
