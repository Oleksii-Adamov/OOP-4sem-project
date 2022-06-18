#ifndef CLASSROOMSLISTWINDOW_H
#define CLASSROOMSLISTWINDOW_H

#include <QMainWindow>
#include "classroomslistmodel.h"
#include "classroomsnamelistmodel.h"

namespace Ui {
class ClassroomsListWindow;
}

class ClassroomsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassroomsListWindow(QWidget *parent = nullptr);
    ~ClassroomsListWindow();

public slots:
    void OnStudentClassroomClicked(const QModelIndex& classroom_index);
    void OnTeacherClassroomClicked(const QModelIndex& classroom_index);

private:
    Ui::ClassroomsListWindow *ui;
    QSharedPointer<ClassroomsListModel> classrooms_list_as_student_model_;
    QSharedPointer<ClassroomsNameListModel> classrooms_list_as_teacher_model_;
};

#endif // CLASSROOMSLISTWINDOW_H
