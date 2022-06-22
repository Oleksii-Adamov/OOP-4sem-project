#include "sendassignmentwindow.h"
#include "ui_sendassignmentwindow.h"
#include "font.h"
#include "client.h"
#include "jsonfile.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
SendAssignmentWindow::SendAssignmentWindow(QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(),
    ui(new Ui::SendAssignmentWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Send Assignment");
    this->setWindowState(Qt::WindowMaximized);

    assignments_list_model.reset(new AssignmentsListModel());
    classrooms_list_model.reset(new ClassroomsNameListModel());

    ui->label_assignment->setFont(Font::RegularFont());
    ui->label_classroom->setFont(Font::RegularFont());
    ui->label_deadline->setFont(Font::RegularFont());
    ui->lineEdit_deadline->setFont(Font::RegularFont());

    ui->pushButton_cancel->setFont(Font::RegularFont());
    ui->pushButton_send->setFont(Font::RegularFont());

    ui->comboBox_assignment->setFont(Font::RegularFont());
    ui->comboBox_assignment->setModel(assignments_list_model.data());

    ui->comboBox_classroom->setFont(Font::RegularFont());
    ui->comboBox_classroom->setModel(classrooms_list_model.data());
    GetClassroomsData();
    GetAssignmentsData();
//    assignments_list_model->Push(AssignmentInfo(1, "A1", "12:01 14.06.2022"));
//    assignments_list_model->Push(AssignmentInfo(2, "A2", "12:01 14.06.2022"));
//    assignments_list_model->Push(AssignmentInfo(3, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "12:01 14.06.2022"));
}

void SendAssignmentWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::RETURN_TEACHER_CLASSROOMS)
    {
        classrooms_list_model->Clear();
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonArray classrooms =  json_doc_obj.take("Classrooms").toArray();
        for (int i = 0; i < classrooms.size(); i++)
        {
            QJsonObject classroom_object = classrooms.at(i).toObject();
            classrooms_list_model->PushBack(Classroom(classroom_object.take("classroom_id").toString().toULongLong(),
                                         classroom_object.take("teacher_user_id").toString().toULongLong(),
                                         classroom_object.take("name").toString().toStdString()));
        }
    }
    if (msg.header.id == CustomMsgTypes::RETURN_TEACHER_ASSIGNMENTS)
    {
        assignments_list_model->Clear();
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonArray assignments =  json_doc_obj.take("Assignments").toArray();
        for (int i = 0; i < assignments.size(); i++)
        {
            QJsonObject assignment_object = assignments.at(i).toObject();
            assignments_list_model->PushBack(Assignment(assignment_object.take("assignment_id").toString().toULongLong(),
            assignment_object.take("teacher_user_id").toString().toULongLong(), assignment_object.take("assignment_name").toString().toStdString(),
            assignment_object.take("assignment_creation_date").toString().toStdString(), "",
            assignment_object.take("assignment_max_score").toString().toInt()));
        }
    }
    if (msg.header.id == CustomMsgTypes::FAILURE_SEND_ASSIGNMENT_TO_CLASSROOM)
    {
        QMessageBox::critical(this, "Send assignment error", "Unable to send!");
    }
    if (msg.header.id == CustomMsgTypes::SUCCESS_SEND_ASSIGNMENT_TO_CLASSROOM)
    {
        QMessageBox::information(this, "Send assignment info", "Sent!");
        this->close();
    }
}

void SendAssignmentWindow::GetClassroomsData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_TEACHER_CLASSROOMS;
    message << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}
void SendAssignmentWindow::GetAssignmentsData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_TEACHER_ASSIGNMENTS;
    message << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}

SendAssignmentWindow::~SendAssignmentWindow()
{
    delete ui;
}

void SendAssignmentWindow::on_pushButton_send_clicked()
{
    QRegularExpression rx("^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9] [0-9][0-9]:[0-9][0-9]:[0-9][0-9]$");
    if (!rx.match(ui->lineEdit_deadline->text()).hasMatch())
    {
        QMessageBox::critical(this, "Send assignment error", "Deadline is in wrong format");
    }
    else {
        net::message<CustomMsgTypes> message;
        message.header.id = CustomMsgTypes::SEND_ASSIGNMENT_TO_CLASSROOM_REQUEST;
        WriteQStringToMsg(ui->lineEdit_deadline->text(), message);
        message << classrooms_list_model->GetClassroom(classrooms_list_model->index(ui->comboBox_classroom->currentIndex())).getClassroomId()
                << assignments_list_model->GetData(assignments_list_model->index(ui->comboBox_assignment->currentIndex())).getAssignmentId();
        Client::GetInstance()->Send(message);
    }
}



void SendAssignmentWindow::on_actionUpdate_triggered()
{
    GetClassroomsData();
    GetAssignmentsData();
}

