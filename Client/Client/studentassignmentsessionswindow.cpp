#include "studentassignmentsessionswindow.h"
#include "ui_studentassignmentsessionswindow.h"
#include "font.h"
#include "teacherassignmentcheckingwindow.h"

StudentAssignmentSessionsWindow::StudentAssignmentSessionsWindow(const AssignmentSessionInfo& assignment_session_info, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(), ui(new Ui::StudentAssignmentSessionsWindow),
    assignment_session_info_(assignment_session_info)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Student assignments for " + QString::fromStdString(assignment_session_info.assignment.getAssignmentName()));

    student_assignments_list_model.reset(new StudentAssignmentSessionsForTeacherListModel(assignment_session_info_.assignment.getAssignmentMaxScore()));

    ui->label_assignment_name->setFont(Font::BigFont());
    ui->label_deadline->setFont(Font::RegularListViewFont());
    ui->label_student_assignments->setFont(Font::BigFont());

    ui->student_assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->student_assignments_list_view->setFont(Font::RegularListViewFont());
    ui->student_assignments_list_view->setModel(student_assignments_list_model.data());

    connect(ui->student_assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnStudentAssignmentClicked(QModelIndex)));

    ui->label_assignment_name->setText(QString::fromStdString(assignment_session_info_.assignment.getAssignmentName()));
    ui->label_deadline->setText("Deadline: " + QString::fromStdString(assignment_session_info_.assignment_session.getAssignmentSessionEndDate()));
    student_assignments_list_model->PushBack(StudentAssignmentSessionInfoForTeacher(StudentAssignmentSession(1,1,StudentAssignmentSessionStatus::submitted, "", 0, "19.06.2022 23:21"), User(1,"login", "student name")));
//    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(2, StudentAssignmentSessionStatus::checked, "17:59 18.06.2022", "User name2", 3));
//    student_assignments_list_model->PushBack(StudentAssignmentSessionInfo(3, StudentAssignmentSessionStatus::not_submitted, "17:59 18.06.2022", "User name3"));
}

void StudentAssignmentSessionsWindow::Update(net::message<CustomMsgTypes>& msg)
{

}

void StudentAssignmentSessionsWindow::OnStudentAssignmentClicked(const QModelIndex& student_assignment)
{
    TeacherAssignmentCheckingWindow* new_window = new TeacherAssignmentCheckingWindow(student_assignments_list_model->GetData(student_assignment),
                                                                                      assignment_session_info_.assignment, this);
    new_window->show();
}

StudentAssignmentSessionsWindow::~StudentAssignmentSessionsWindow()
{
    delete ui;
}
