#include "studentassignmentwindow.h"
#include "ui_studentassignmentwindow.h"
#include "font.h"
#include <QScrollArea>
#include "assignmentguidirector.h"
#include "jsonfile.h"
#include "client.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include "font.h"
#include <QMessageBox>

StudentAssignmentWindow::StudentAssignmentWindow(const StudentAssignmentSessionInfo& student_assignment_session_info, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(),
    ui(new Ui::StudentAssignmentWindow), student_assignment_session_info_(student_assignment_session_info)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->label_deadline->setFont(Font::RegularListViewFont());
    ui->pushButton_submit->setFont(Font::RegularListViewFont());
    this->setWindowTitle(QString::fromStdString(student_assignment_session_info.assignment.getAssignmentName()));
    ui->label_deadline->setText("Deadline: " + QString::fromStdString(student_assignment_session_info.assignment_session.getAssignmentSessionEndDate()));
    GetData();
    //FromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_server_to_student.json"));
}

void StudentAssignmentWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::RETURN_STUDENT_ASSIGNMENT_SESSION_ANSWER)
    {
        FromJSON(QJsonDocumentFromServerMessage(msg));
    }
    if (msg.header.id == CustomMsgTypes::SUCCESS_SUBMIT_STUDENT_ASSIGNMENT)
    {
        QMessageBox::information(this, "Submition info", "Submitted!");
        this->close();
    }
}

StudentAssignmentWindow::~StudentAssignmentWindow()
{
    delete ui;
}

void StudentAssignmentWindow::GetData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_STUDENT_ASSIGNMENT_SESSION_ANSWER;
    message << (ID) student_assignment_session_info_.student_assignment_session.getAssignmentSessionId() << (ID) Client::GetInstance()->GetUser().getUserId();
    Client::GetInstance()->Send(message);
}

void StudentAssignmentWindow::FromJSON(const QJsonDocument& json_doc)
{
    QVBoxLayout* layout = new QVBoxLayout(ui->assignment_widget);

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    assignment_container_ = new QWidget(this);
    scrollArea->setWidget(assignment_container_);

    assignment_layout_ = new QVBoxLayout(assignment_container_);

    AssignmentGUIBuilder assignment_GUI_builder;
    bool is_editable = false;
    if (student_assignment_session_info_.student_assignment_session.getStudentAssignmentSessionStatus() == StudentAssignmentSessionStatus::not_submitted) {
        is_editable = true;
    }
    assignment_GUI_builder.Set(assignment_layout_, assignment_container_, is_editable);
    AssignmentGUIDirector assignment_GUI_director;
    assignment_GUI_director.set_builder(&assignment_GUI_builder);
    assignment_GUI_director.BuildFromJSON(json_doc);
    if (!assignment_GUI_builder.IsEditable()) ui->pushButton_submit->hide();
}

void StudentAssignmentWindow::on_actionUpdate_triggered()
{
    GetData();
}

QJsonDocument StudentAssignmentWindow::ToJSON()
{
    auto layout_items = assignment_container_->findChildren<QWidget*>();
    QJsonArray assignments;
    foreach(auto layout_item, layout_items) {
        if (layout_item->objectName() == "header")
        {
            QLabel* header = qobject_cast<QLabel*>(layout_item);
            QJsonObject header_info;
            header_info.insert("type", "Header");
            header_info.insert("content", header->text());
            assignments.push_back(header_info);
        }
        else if (layout_item->objectName().lastIndexOf("test_assignment") == 0)
        {
            QGroupBox* test_assignment = qobject_cast<QGroupBox*>(layout_item);
            QJsonObject assignment;
            assignment.insert("type", QJsonValue("test_assignment"));
            QJsonObject assignment_info;
            long long id = test_assignment->objectName().mid(QString("test_assignment").size()).toLongLong();
            assignment_info.insert("id", QJsonValue(id));
            assignment_info.insert("question", QJsonValue(test_assignment->title()));
            auto radio_buttons = test_assignment->findChildren<QRadioButton*>();
            auto check_boxes = test_assignment->findChildren<QCheckBox*>();
            QJsonArray answers;
            if (radio_buttons.size() > 0) {
                assignment_info.insert("type", QJsonValue("one choice"));
                foreach(QRadioButton* radio_button, radio_buttons) {
                    QJsonObject answer_info;
                    answer_info.insert("answer_text", radio_button->text());
                    answer_info.insert("is_answer_chosen", QJsonValue(radio_button->isChecked()));
                    answers.push_back(answer_info);
                }
            }
            else {
                assignment_info.insert("type", QJsonValue("multiple choice"));
                foreach(QCheckBox* check_box, check_boxes) {
                    QJsonObject answer_info;
                    answer_info.insert("answer_text", check_box->text());
                    answer_info.insert("is_answer_chosen", QJsonValue(check_box->isChecked()));
                    answers.push_back(answer_info);
                }
            }
            assignment_info.insert("answers", answers);
            assignment.insert("content", assignment_info);
            assignments.push_back(assignment);
        }
    }
    QJsonObject main_json_obj;
    main_json_obj.insert("Assignment", assignments);
    return QJsonDocument(main_json_obj);
}

void StudentAssignmentWindow::on_pushButton_submit_clicked()
{
    net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::SUBMIT_STUDENT_ASSIGNMENT;
    WriteJsonToMsg(ToJSON(), msg);
    msg << student_assignment_session_info_.student_assignment_session.getAssignmentSessionId() << student_assignment_session_info_.student_assignment_session.getStudentUserId();
    Client::GetInstance()->Send(msg);
}

