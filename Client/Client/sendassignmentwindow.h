#ifndef SENDASSIGNMENTWINDOW_H
#define SENDASSIGNMENTWINDOW_H

#include <QMainWindow>
#include "assignmentslistmodel.h"
#include "classroomsnamelistmodel.h"

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
    QSharedPointer<AssignmentsListModel> assignments_list_model;
    QSharedPointer<ClassroomsNameListModel> classrooms_list_model;
};

#endif // SENDASSIGNMENTWINDOW_H
