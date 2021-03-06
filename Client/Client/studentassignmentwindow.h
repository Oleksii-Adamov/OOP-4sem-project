#ifndef STUDENTASSIGNMENTWINDOW_H
#define STUDENTASSIGNMENTWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessioninfo.h"
#include "clientsubscriber.h"

namespace Ui {
class StudentAssignmentWindow;
}

class StudentAssignmentWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit StudentAssignmentWindow(const StudentAssignmentSessionInfo& student_assignment_session_info, QWidget *parent = nullptr);
    ~StudentAssignmentWindow();
    void Update(net::message<CustomMsgTypes> msg) override;

private slots:
    void on_actionUpdate_triggered();

private:
    void GetData();
    void FromJSON(const QJsonDocument& json_doc);
    Ui::StudentAssignmentWindow *ui;
    StudentAssignmentSessionInfo student_assignment_session_info_;
};

#endif // STUDENTASSIGNMENTWINDOW_H
