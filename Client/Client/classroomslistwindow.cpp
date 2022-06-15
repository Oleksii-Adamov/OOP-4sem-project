#include "classroomslistwindow.h"
#include "ui_classroomslistwindow.h"
#include "font.h"

ClassroomsListWindow::ClassroomsListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassroomsListWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    classrooms_list_as_student_model_.reset(new ClassroomsListModel());
    classrooms_list_as_teacher_model_.reset(new ClassroomsListModel());

    ui->setupUi(this);

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

    // Connect items double click to slot (open classroom)
    //connect(ui->assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

    classrooms_list_as_teacher_model_->PushBack(ClassroomInfo(1, "General algebra", "Linder"));
    classrooms_list_as_student_model_->PushBack(ClassroomInfo(2, "Probability theory", "Rozora"));
    classrooms_list_as_student_model_->PushBack(ClassroomInfo(3, "OOP", "Zhereb"));
}

ClassroomsListWindow::~ClassroomsListWindow()
{
    delete ui;
}
