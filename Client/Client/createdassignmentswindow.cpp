#include "createdassignmentswindow.h"
#include "ui_createdassignmentswindow.h"
#include "font.h"

CreatedAssignmentsWindow::CreatedAssignmentsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatedAssignmentsWindow)
{
    ui->setupUi(this);

    ui->label_created_assignments->setFont(Font::BigFont());
    ui->pushButton_create_new->setFont(Font::RegularFont());
    ui->pushButton_edit->setFont(Font::RegularFont());
    ui->pushButton_delete->setFont(Font::RegularFont());

    this->setWindowTitle("Created assignments");

    assignments_list_model.reset(new AssignmentsListModel());

    ui->assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->assignments_list_view->setFont(Font::RegularListViewFont());
    ui->assignments_list_view->setModel(assignments_list_model.data());

    connect(ui->assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

    assignments_list_model->PushBack(Assignment(1,1,"Name","12321","",5));
}

void CreatedAssignmentsWindow::OnAssignmentClicked(const QModelIndex& index)
{

}

CreatedAssignmentsWindow::~CreatedAssignmentsWindow()
{
    delete ui;
}
