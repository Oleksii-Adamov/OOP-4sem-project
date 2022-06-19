#include "studentassignmentsessionswindow.h"
#include "ui_studentassignmentsessionswindow.h"
#include "font.h"

StudentAssignmentSessionsWindow::StudentAssignmentSessionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentAssignmentSessionsWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    long long max_score = 5;
    student_assignments_list_model.reset(new StudentAssignmentSessionsListModel(max_score));

    ui->label_assignment_name->setFont(Font::BigFont());
    ui->label_deadline->setFont(Font::RegularListViewFont());
    ui->label_student_assignments->setFont(Font::BigFont());

    ui->student_assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->student_assignments_list_view->setFont(Font::RegularListViewFont());
    ui->student_assignments_list_view->setModel(student_assignments_list_model.data());

    connect(ui->student_assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnStudentAssignmentClicked(QModelIndex)));

    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(1, StudentAssignmentSessionStatus::submitted, "17:59 18.06.2022", "User name"));
    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(2, StudentAssignmentSessionStatus::checked, "17:59 18.06.2022", "User name2", 3));
    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(3, StudentAssignmentSessionStatus::not_submitted, "17:59 18.06.2022", "User name3"));
}

void StudentAssignmentSessionsWindow::OnStudentAssignmentClicked(const QModelIndex& student_assignment)
{

}

StudentAssignmentSessionsWindow::~StudentAssignmentSessionsWindow()
{
    delete ui;
}
