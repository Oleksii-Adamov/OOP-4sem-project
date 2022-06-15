#ifndef CLASSROOMSLISTWINDOW_H
#define CLASSROOMSLISTWINDOW_H

#include <QMainWindow>
#include "classroomslistmodel.h"

namespace Ui {
class ClassroomsListWindow;
}

class ClassroomsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassroomsListWindow(QWidget *parent = nullptr);
    ~ClassroomsListWindow();

private:
    Ui::ClassroomsListWindow *ui;
    QSharedPointer<ClassroomsListModel> classrooms_list_as_student_model_;
    QSharedPointer<ClassroomsListModel> classrooms_list_as_teacher_model_;
};

#endif // CLASSROOMSLISTWINDOW_H
