#include "classroomwindow.h"
#include "ui_classroomwindow.h"
#include "font.h"
#include <QDebug>
#include "client.h"

ClassroomWindow::ClassroomWindow(const ClassroomInfo& classroom_info, QSharedPointer<ClassroomWindowStrategy> strategy,
                                 QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(),
    ui(new Ui::ClassroomWindow),  strategy_(strategy), classroom_info_(classroom_info)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->name_label->setFont(Font::BigFont());
    ui->teacher_label->setFont(Font::RegularFont());
    ui->assignments_label->setFont(Font::BigFont());
    ui->assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->assignments_list_view->setFont(Font::RegularListViewFont());

    this->setWindowTitle(QString::fromStdString(classroom_info_.classroom.getName()));
    ui->name_label->setText(QString::fromStdString(classroom_info_.classroom.getName()));
    if (classroom_info_.teacher.getUserId() == 0)
    {
        ui->teacher_label->hide();
    }
    else {
        ui->teacher_label->setText(QString::fromStdString(classroom_info_.teacher.getUserName()));
    }

    strategy_->SetModel(assignments_list_model);

    ui->assignments_list_view->setModel(assignments_list_model.data());

    connect(ui->assignments_list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

//    Client::GetInstance()->Subscribe(this);
      net::message<CustomMsgTypes> msg;
      Update(msg);
//    assignments_list_model->Push(AssignmentInfo(1, "A1", "12:01 14.06.2022"));
//    assignments_list_model->Push(AssignmentInfo(2, "A2", "12:01 14.06.2022"));
//    assignments_list_model->Push(AssignmentInfo(3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "12:01 14.06.2022"));
}

void ClassroomWindow::OnAssignmentClicked(const QModelIndex& index) {
   strategy_->OnAssignmentClicked(index, assignments_list_model);
}

void ClassroomWindow::Update(net::message<CustomMsgTypes> msg)
{
    strategy_->Update(msg, assignments_list_model);
}

void ClassroomWindow::GetData()
{
    strategy_->GetData(classroom_info_);
}

ClassroomWindow::~ClassroomWindow()
{
//    Client::GetInstance()->UnSubscribe(this);
    delete ui;
}

void ClassroomWindow::on_actionUpdate_triggered()
{

}

