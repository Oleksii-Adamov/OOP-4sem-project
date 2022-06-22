#include "createdassignmentswindow.h"
#include "ui_createdassignmentswindow.h"
#include "font.h"
#include "assignmentcreationwindow.h"
#include "client.h"
#include "jsonfile.h"
#include <QJsonObject>
#include <QJsonArray>

CreatedAssignmentsWindow::CreatedAssignmentsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatedAssignmentsWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_created_assignments->setFont(Font::BigFont());
    ui->pushButton_create_new->setFont(Font::RegularFont());
    ui->pushButton_delete->setFont(Font::RegularFont());

    this->setWindowTitle("Created assignments");

    assignments_list_model.reset(new AssignmentsListModel());

    ui->assignments_list_view->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    ui->assignments_list_view->setFont(Font::RegularListViewFont());
    ui->assignments_list_view->setModel(assignments_list_model.data());

    connect(ui->assignments_list_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnAssignmentClicked(QModelIndex)));

    //assignments_list_model->PushBack(Assignment(1,1,"Name","12321","",5));

    GetData();
}

void CreatedAssignmentsWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::RETURN_TEACHER_ASSIGNMENTS)
    {
        assignments_list_model->Clear();
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonArray assignments =  json_doc_obj.take("Assignments").toArray();
        for (int i = 0; i < assignments.size(); i++)
        {
            QJsonObject assignment_object = assignments.at(i).toObject();
            assignments_list_model->PushBack(Assignment(assignment_object.take("assignment_id").toInt(),
            assignment_object.take("teacher_user_id").toInt(), assignment_object.take("assignment_name").toString().toStdString(),
            assignment_object.take("assignment_creation_date").toString().toStdString(), "",
            assignment_object.take("assignment_max_score").toInt()));
        }
    }
}

void CreatedAssignmentsWindow::GetData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_TEACHER_ASSIGNMENTS;
    message << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}

void CreatedAssignmentsWindow::OnAssignmentClicked(const QModelIndex& index)
{
    AssignmentCreationWindow* new_window = new AssignmentCreationWindow(assignments_list_model->GetData(index), this);
    new_window->show();
}

CreatedAssignmentsWindow::~CreatedAssignmentsWindow()
{
    delete ui;
}

void CreatedAssignmentsWindow::on_pushButton_create_new_clicked()
{
    AssignmentCreationWindow* new_window = new AssignmentCreationWindow(Assignment(), this);
    new_window->show();
}

