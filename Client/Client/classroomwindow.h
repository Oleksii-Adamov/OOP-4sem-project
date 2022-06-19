#ifndef CLASSROOMWINDOW_H
#define CLASSROOMWINDOW_H

#include <QMainWindow>
#include "assignmentslistmodel.h"
#include "classroomwindowstrategy.h"
#include "classroominfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ClassroomWindow;
}
QT_END_NAMESPACE

class ClassroomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassroomWindow(const ClassroomInfo& classroom, QSharedPointer<ClassroomWindowStrategy> strategy, QWidget *parent = nullptr);
    ~ClassroomWindow();

public slots:
    void OnAssignmentClicked(const QModelIndex& assignment);

private:
    Ui::ClassroomWindow *ui;
    QSharedPointer<AssignmentsListModel> assignments_list_model;
    QSharedPointer<ClassroomWindowStrategy> strategy_;
    ClassroomInfo classroom_;
};

#endif // CLASSROOMWINDOW_H
