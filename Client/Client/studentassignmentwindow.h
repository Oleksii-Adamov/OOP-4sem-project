#ifndef STUDENTASSIGNMENTWINDOW_H
#define STUDENTASSIGNMENTWINDOW_H

#include <QMainWindow>
#include "studentassignmentsessioninfo.h"
#include "clientsubscriber.h"
#include <QVBoxLayout>
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

    void on_pushButton_submit_clicked();

private:
    void GetData();
    void FromJSON(const QJsonDocument& json_doc);
    QJsonDocument ToJSON();
    Ui::StudentAssignmentWindow *ui;
    StudentAssignmentSessionInfo student_assignment_session_info_;
    QWidget* assignment_container_;
    QVBoxLayout* assignment_layout_;
};

#endif // STUDENTASSIGNMENTWINDOW_H
