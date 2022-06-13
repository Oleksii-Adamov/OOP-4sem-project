#ifndef CLASSROOMOFSTUDENTWINDOW_H
#define CLASSROOMOFSTUDENTWINDOW_H

#include <QMainWindow>
#include "assignmentslistmodel.h"

namespace Ui {
class ClassroomOfStudentWindow;
}

class ClassroomOfStudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassroomOfStudentWindow(QWidget *parent = nullptr);
    ~ClassroomOfStudentWindow();

public slots:
    void OnAssignmentClicked(const QModelIndex& assignment);

private:
    Ui::ClassroomOfStudentWindow *ui;
    QSharedPointer<AssignmentsListModel> assignments_list_model;
};

#endif // CLASSROOMOFSTUDENTWINDOW_H
