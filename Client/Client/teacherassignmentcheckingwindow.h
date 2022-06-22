#ifndef TEACHERASSIGNMENTCHECKINGWINDOW_H
#define TEACHERASSIGNMENTCHECKINGWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessioninfoforteacher.h"
#include "Assignment.h"
#include "clientsubscriber.h"
#include <QJsonDocument>

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

private slots:
    void on_pushButton_rate_clicked();

private:
    Ui::TeacherAssignmentCheckingWindow *ui;
    StudentAssignmentSessionInfoForTeacher student_assignment_session_info_for_teacher_;
    void GetStudentAnswer();
    void GetAssignmentAnswer();
    void FromJSON(const QJsonDocument& student_json_doc, const QJsonDocument& teacher_json_doc);
    bool student_data_ready = false;
    bool teacher_data_ready = false;
    QJsonDocument student_json_doc;
    QJsonDocument teacher_json_doc;
};

#endif // TEACHERASSIGNMENTCHECKINGWINDOW_H
