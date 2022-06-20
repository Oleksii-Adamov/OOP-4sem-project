#ifndef TEACHERASSIGNMENTCHECKINGWINDOW_H
#define TEACHERASSIGNMENTCHECKINGWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessioninfoforteacher.h"
#include "Assignment.h"
#include "clientsubscriber.h"

namespace Ui {
class TeacherAssignmentCheckingWindow;
}

class TeacherAssignmentCheckingWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit TeacherAssignmentCheckingWindow(const StudentAssignmentSessionInfoForTeacher& student_assignment_session_info_for_teacher, const Assignment& assignment, QWidget *parent = nullptr);
    ~TeacherAssignmentCheckingWindow();
    void Update(net::message<CustomMsgTypes> msg) override;

private:
    Ui::TeacherAssignmentCheckingWindow *ui;
};

#endif // TEACHERASSIGNMENTCHECKINGWINDOW_H
