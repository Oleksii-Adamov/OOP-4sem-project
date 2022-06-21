#ifndef CLASSROOMSLISTWINDOW_H
#define CLASSROOMSLISTWINDOW_H

#include <QMainWindow>
#include "classroomslistmodel.h"
#include "classroomsnamelistmodel.h"
#include "clientsubscribergui.h"

namespace Ui {
class ClassroomsListWindow;
}

class ClassroomsListWindow : public ClientSubscriberGui
{
    Q_OBJECT

public:
    explicit ClassroomsListWindow(QWidget *parent = nullptr);
    ~ClassroomsListWindow();
    void Update(net::message<CustomMsgTypes> msg) override;

public slots:
    void OnStudentClassroomClicked(const QModelIndex& classroom_index);
    void OnTeacherClassroomClicked(const QModelIndex& classroom_index);

private slots:
    void on_pushButton_join_clicked();

    void on_pushButton_create_clicked();

    void on_actionUpdate_triggered();

private:
    Ui::ClassroomsListWindow *ui;
    QSharedPointer<ClassroomsListModel> classrooms_list_as_student_model_;
    QSharedPointer<ClassroomsNameListModel> classrooms_list_as_teacher_model_;
    void GetStudentClassroomsData();
    void GetTeacherClassroomsData();
};

#endif // CLASSROOMSLISTWINDOW_H
