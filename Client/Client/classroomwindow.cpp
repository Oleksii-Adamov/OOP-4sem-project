#include "classroomwindow.h"
#include "ui_classroomwindow.h"
#include "font.h"


ClassroomWindow::ClassroomWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassroomWindow)
{
    ui->setupUi(this);

    assignments_list_model.reset(new AssignmentsListModel());

    ui->name_label->setFont(Font::BigFont());
    ui->teacher_label->setFont(Font::RegularFont());
    ui->assignments_label->setFont(Font::BigFont());

    ui->assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->assignments_list_view->setFont(Font::RegularListViewFont());
    ui->assignments_list_view->setModel(assignments_list_model.data());

    connect(ui->assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

    assignments_list_model->Push(AssignmentInfo(1, "A1", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(2, "A2", "12:01 14.06.2022"));
    assignments_list_model->Push(AssignmentInfo(3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "12:01 14.06.2022"));
}

void ClassroomWindow::OnAssignmentClicked(const QModelIndex& assignment) {
   qDebug() << assignments_list_model->GetId(assignment);
   //strategy_->OnAssignmentClicked(assignments_list_model->GetId(assignment));
}

ClassroomWindow::~ClassroomWindow()
{
    delete ui;
}
