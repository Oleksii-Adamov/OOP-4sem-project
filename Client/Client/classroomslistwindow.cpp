#include "classroomslistwindow.h"
#include "ui_classroomslistwindow.h"
#include "font.h"
#include "classroomwindow.h"
#include "classroomwindowstudentstrategy.h"
#include "classroomwindowteacherstrategy.h"
#include "joinclassroomdialog.h"
#include "createclassroomdialog.h"
#include "client.h"
#include "jsonfile.h"
#include <QJsonObject>
#include <QJsonArray>

ClassroomsListWindow::ClassroomsListWindow(QWidget *parent) :
    QMainWindow(parent), ClientSubscriberGui(), ui(new Ui::ClassroomsListWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Classrooms");

    classrooms_list_as_student_model_.reset(new ClassroomsListModel());
    classrooms_list_as_teacher_model_.reset(new ClassroomsNameListModel());

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

    connect(ui->classromms_list_view_as_student, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnStudentClassroomClicked(QModelIndex)));
    connect(ui->classromms_list_view_as_teacher, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnTeacherClassroomClicked(QModelIndex)));

    //classrooms_list_as_student_model_->PushBack(ClassroomInfo(Classroom(2,2,"Probability theory"), User(2, "rozora", "Rozora")));
    //classrooms_list_as_teacher_model_->PushBack(Classroom(1, 1, "General algebra"));
    GetStudentClassroomsData();
    GetTeacherClassroomsData();

    /*net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ERROR_DATABASE;
    Update(msg);*/
}

void ClassroomsListWindow::Update(net::message<CustomMsgTypes> msg)
{
    ClientSubscriberGui::Update(msg);
    if (msg.header.id == CustomMsgTypes::RETURN_TEACHER_CLASSROOMS)
    {
        classrooms_list_as_teacher_model_->Clear();
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonArray classrooms =  json_doc_obj.take("Classrooms").toArray();
        for (int i = 0; i < classrooms.size(); i++)
        {
            QJsonObject classroom_object = classrooms.at(i).toObject();
            classrooms_list_as_teacher_model_->PushBack(Classroom(classroom_object.take("classroom_id").toString().toULongLong(),
                                         classroom_object.take("teacher_user_id").toString().toULongLong(),
                                         classroom_object.take("name").toString().toStdString()));
        }
    }
    if (msg.header.id == CustomMsgTypes::RETURN_STUDENT_CLASSROOMS)
    {
        classrooms_list_as_student_model_->Clear();
        QJsonDocument json_doc = QJsonDocumentFromServerMessage(msg);
        QJsonObject json_doc_obj = json_doc.object();
        QJsonArray classroominfos =  json_doc_obj.take("ClassroomInfos").toArray();
        for (int i = 0; i < classroominfos.size(); i++)
        {
            QJsonObject classroominfos_object = classroominfos.at(i).toObject();
            QJsonObject classroom_object = classroominfos_object.take("Classroom").toObject();
            Classroom classroom(classroom_object.take("classroom_id").toString().toULongLong(),
                                classroom_object.take("teacher_user_id").toString().toULongLong(),
                                classroom_object.take("name").toString().toStdString());
            QJsonObject teacher_object = classroominfos_object.take("Teacher").toObject();
            User teacher(teacher_object.take("user_id").toString().toULongLong(),
                         teacher_object.take("login").toString().toStdString(),
                         teacher_object.take("user_name").toString().toStdString());
            classrooms_list_as_student_model_->PushBack(ClassroomInfo(classroom, teacher));
        }
    }
}

void ClassroomsListWindow::GetStudentClassroomsData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_STUDENT_CLASSROOMS;
    message << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}
void ClassroomsListWindow::GetTeacherClassroomsData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_TEACHER_CLASSROOMS;
    message << Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}

void ClassroomsListWindow::OnStudentClassroomClicked(const QModelIndex& classroom_index)
{
    ClassroomWindow* new_window  = new ClassroomWindow(classrooms_list_as_student_model_->GetClassroomInfo(classroom_index),
                                                            QSharedPointer<ClassroomWindowStrategy>(new ClassroomWindowStudentStrategy), this);
    new_window->show();
}

void ClassroomsListWindow::OnTeacherClassroomClicked(const QModelIndex& classroom_index)
{
    ClassroomWindow* new_window  = new ClassroomWindow(ClassroomInfo(classrooms_list_as_teacher_model_->GetClassroom(classroom_index),User()),
                                                            QSharedPointer<ClassroomWindowStrategy>(new ClassroomWindowTeacherStrategy), this);
    new_window->show();
}

ClassroomsListWindow::~ClassroomsListWindow()
{
    delete ui;
}

void ClassroomsListWindow::on_pushButton_join_clicked()
{
    JoinClassroomDialog* new_window = new JoinClassroomDialog(this);
    new_window->show();
}


void ClassroomsListWindow::on_pushButton_create_clicked()
{
    CreateClassroomDialog* new_window = new CreateClassroomDialog(this);
    new_window->show();
}


void ClassroomsListWindow::on_actionUpdate_triggered()
{
    GetStudentClassroomsData();
    GetTeacherClassroomsData();
}
