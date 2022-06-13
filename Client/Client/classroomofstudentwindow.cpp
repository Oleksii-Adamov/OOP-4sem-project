#include "classroomofstudentwindow.h"
#include "ui_classroomofstudentwindow.h"

ClassroomOfStudentWindow::ClassroomOfStudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassroomOfStudentWindow)
{
    assignments_list_model.reset(new AssignmentsListModel());

    ui->setupUi(this);
    ui->assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    QFont list_view_font;
    list_view_font.setPointSize(30);
    ui->assignments_list_view->setFont(list_view_font);
    ui->assignments_list_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->assignments_list_view->setModel(assignments_list_model.data());

    connect(ui->assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

    assignments_list_model->Push(AssignmentInfo(1, "A1", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(2, "A2", "12:01 14.06.2022"));
}

void ClassroomOfStudentWindow::OnAssignmentClicked(const QModelIndex& assignment) {
   qDebug() << assignments_list_model->GetId(assignment);
}

ClassroomOfStudentWindow::~ClassroomOfStudentWindow()
{
    delete ui;
}
