#include "classroomslistwindow.h"
#include "ui_classroomslistwindow.h"
#include "font.h"
#include "classroomwindow.h"
#include "classroomwindowstudentstrategy.h"
#include "classroomwindowteacherstrategy.h"

ClassroomsListWindow::ClassroomsListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassroomsListWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Classrooms");

    classrooms_list_as_student_model_.reset(new ClassroomsListModel());
    classrooms_list_as_teacher_model_.reset(new ClassroomsNameListModel());

    ui->label_as_teacher->setFont(Font::BigFont());
    ui->label_as_student->setFont(Font::BigFont());
    ui->pushButton_create->setFont(Font::RegularFont());
    ui->pushButton_join->setFont(Font::RegularFont());
    ui->pushButton_delete->setFont(Font::RegularFont());

    ui->classromms_list_view_as_student->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->classromms_list_view_as_teacher->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->classromms_list_view_as_student->setFont(Font::RegularListViewFont());
    ui->classromms_list_view_as_teacher->setFont(Font::RegularListViewFont());
    ui->classromms_list_view_as_student->setModel(classrooms_list_as_student_model_.data());
    ui->classromms_list_view_as_teacher->setModel(classrooms_list_as_teacher_model_.data());

    connect(ui->classromms_list_view_as_student, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnStudentClassroomClicked(QModelIndex)));
    connect(ui->classromms_list_view_as_teacher, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnTeacherClassroomClicked(QModelIndex)));

    classrooms_list_as_teacher_model_->PushBack(ClassroomInfo(1, "General algebra", "Linder"));
    classrooms_list_as_student_model_->PushBack(ClassroomInfo(2, "Probability theory", "Rozora"));
    classrooms_list_as_student_model_->PushBack(ClassroomInfo(3, "OOP", "Zhereb"));
}

void ClassroomsListWindow::OnStudentClassroomClicked(const QModelIndex& classroom_index)
{
    ClassroomWindow* new_window  = new ClassroomWindow(classrooms_list_as_student_model_->GetClassroomInfo(classroom_index),
                                                            QSharedPointer<ClassroomWindowStrategy>(new ClassroomWindowStudentStrategy), this);
    new_window->show();
}

void ClassroomsListWindow::OnTeacherClassroomClicked(const QModelIndex& classroom_index)
{
    ClassroomWindow* new_window  = new ClassroomWindow(classrooms_list_as_teacher_model_->GetClassroomInfo(classroom_index),
                                                            QSharedPointer<ClassroomWindowStrategy>(new ClassroomWindowTeacherStrategy), this);
    new_window->show();
}

ClassroomsListWindow::~ClassroomsListWindow()
{
    delete ui;
}
