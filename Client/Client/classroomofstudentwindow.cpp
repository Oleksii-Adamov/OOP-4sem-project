#include "classroomofstudentwindow.h"
#include "ui_classroomofstudentwindow.h"
#include "font.h"

ClassroomOfStudentWindow::ClassroomOfStudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassroomOfStudentWindow)
{
    assignments_list_model.reset(new AssignmentsListModel());

    ui->setupUi(this);

    ui->name_label->setFont(Font::BigFont());
    ui->teacher_label->setFont(Font::RegularFont());
    ui->assignments_label->setFont(Font::BigFont());

    ui->assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->assignments_list_view->setFont(Font::AssignmentsFont());
    ui->assignments_list_view->setModel(assignments_list_model.data());

    connect(ui->assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

    assignments_list_model->Push(AssignmentInfo(1, "A1", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(2, "A2", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "12:01 14.06.2022"));
}

void ClassroomOfStudentWindow::OnAssignmentClicked(const QModelIndex& assignment) {
   qDebug() << assignments_list_model->GetId(assignment);
}

ClassroomOfStudentWindow::~ClassroomOfStudentWindow()
{
    delete ui;
}
