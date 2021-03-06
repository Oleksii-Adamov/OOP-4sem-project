#include "assignmentcreationwindow.h"
#include "ui_assignmentcreationwindow.h"
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include "addeditableheadercommand.h"
#include "addeditabletestassignmentcommand.h"
#include "addeditabletestanswercommand.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QGroupBox>
#include <QCheckBox>
#include "saveeditableassignmentcommand.h"
#include "enterassignmentnamedialog.h"
#include "filepath.h"
#include "jsonfile.h"
#include "font.h"
#include <algorithm>
#include "client.h"

AssignmentCreationWindow::AssignmentCreationWindow(const Assignment& assignment, QWidget *parent) :
    QMainWindow(parent), ClientSubscriber(), ui(new Ui::AssignmentCreationWindow),
    assignment_(assignment)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    InitAssignmentDir();

    QLayout* layout = ui->centralwidget->layout();

    ui->label_max_score->setFont(Font::RegularListViewFont());
    ui->spinBox_max_score->setFont(Font::RegularListViewFont());

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    assignment_container_ = new QWidget(this);
    scrollArea->setWidget(assignment_container_);
    assignment_layout_ = new QVBoxLayout(assignment_container_);

    QWidget* command_buttons_container = new QWidget(this);
    layout->addWidget(command_buttons_container);
    QHBoxLayout* command_buttons_layout = new QHBoxLayout(command_buttons_container);

    QPushButton* add_header_button = new QPushButton("Add Header", command_buttons_container);
    command_buttons_layout->addWidget(add_header_button);
    add_header_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    add_header_button->setFont(Font::RegularFont());
    QAbstractButton::connect(
        add_header_button, &QPushButton::clicked,
        this, &AssignmentCreationWindow::OnAddHeaderButtonClicked
    );

    QPushButton* undo_button = new QPushButton("Undo (structure)", command_buttons_container);
    command_buttons_layout->addWidget(undo_button);
    undo_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    undo_button->setFont(Font::RegularFont());
    QAbstractButton::connect(
        undo_button, &QPushButton::clicked,
        this, &AssignmentCreationWindow::OnUndoButtonClicked
    );

    QPushButton* add_test_button = new QPushButton("Add test", command_buttons_container);
    command_buttons_layout->addWidget(add_test_button);
    add_test_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    add_test_button->setFont(Font::RegularFont());
    QAbstractButton::connect(
        add_test_button, &QPushButton::clicked,
        this, &AssignmentCreationWindow::OnAddTestButtonClicked
    );

    QPushButton* save_button = new QPushButton("Save", command_buttons_container);
    command_buttons_layout->addWidget(save_button);
    save_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    save_button->setFont(Font::RegularFont());
    QAbstractButton::connect(
        save_button, &QPushButton::clicked,
        this, &AssignmentCreationWindow::OnSaveButtonClicked
    );

    if (assignment.getAssignmentId() != 0) {
        ui->spinBox_max_score->setValue(assignment_.getAssignmentMaxScore());
        //FromJSON(QJsonDocumentFromJsonFile("../../from_teacher_to_server.json"));
        this->setWindowTitle(QString::fromStdString(assignment_.getAssignmentName()));
        //Client::GetInstance()->Subscribe(this);
        //FromJSON(QJsonDocumentFromJsonFile("../../from_teacher_to_server.json"));
        GetData();
    }
}

void AssignmentCreationWindow::GetData()
{
    net::message<CustomMsgTypes> message;
    message.header.id = CustomMsgTypes::GET_TEST_ASSIGNMENT;
    Client::GetInstance()->Send(message);
}

void AssignmentCreationWindow::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::RETURN_TEST_ASSIGMENT)
    {
        FromJSON(QJsonDocumentFromServerMessage(msg));
        //FromJSON(QJsonDocumentFromJsonFile("../../from_teacher_to_server.json"));
    }
}

AssignmentCreationWindow::~AssignmentCreationWindow()
{
    delete ui;
}

void AssignmentCreationWindow::execute_command(Command* command, bool is_needed_to_save)
{
    if (command->execute() && is_needed_to_save)
    {
        history_.push(command);
    }
    else {
        delete command;
    }
}

void AssignmentCreationWindow::undo()
{
    Command* command = history_.pop();
    if (command != nullptr) {
        command->undo();
        delete command;
    }
}

void AssignmentCreationWindow::AddHeader(const QString& text, bool is_needed_to_save)
{
    execute_command(new AddEditableHeaderCommand(assignment_layout_, assignment_container_, text), is_needed_to_save);
}

void AssignmentCreationWindow::AddTest(const QString& text, bool is_needed_to_save)
{
    execute_command(new AddEditableTestAssignmentCommand(assignment_layout_, assignment_container_, this, cur_assignment_id, text), is_needed_to_save);
    cur_assignment_id++;
}

void AssignmentCreationWindow::AddTestAnswer(const QString& text, QWidget* container, QLayout* layout, bool is_needed_to_save, bool is_checked)
{
    execute_command(new AddEditableTestAnswerCommand(layout, container, text, is_checked), is_needed_to_save);
}

void AssignmentCreationWindow::OnAddHeaderButtonClicked()
{
    AddHeader("Header");
}

void AssignmentCreationWindow::OnUndoButtonClicked()
{
    undo();
}

void AssignmentCreationWindow::OnAddTestAnswerButtonClicked()
{
    QWidget* container = qobject_cast<QWidget*>(sender()->parent());
    QLayout* layout = container->layout();
    AddTestAnswer("Answer", container, layout);
}

void AssignmentCreationWindow::OnAddTestButtonClicked()
{
    AddTest("Question");
}

QJsonDocument AssignmentCreationWindow::ToJSON()
{
    auto layout_items = this->findChildren<QWidget*>();
    QJsonArray content_array;
    foreach(auto layout_item, layout_items) {
        if (layout_item->objectName().lastIndexOf("test_assignment") == 0)
        {
            QJsonObject assignment;
            assignment.insert("type", QJsonValue("test_assignment"));
            QJsonObject assignment_info;
            long long id = layout_item->objectName().mid(QString("test_assignment").size()).toLongLong();
            assignment_info.insert("id", QJsonValue(id));
            EditableLabel* question = layout_item->findChild<EditableLabel*>();
            assignment_info.insert("question", QJsonValue(question->text()));
            auto check_boxes_group_boxes = layout_item->findChildren<QGroupBox*>();
            QJsonArray answers;
            unsigned long long correct_answer_count = 0;
            foreach(auto check_box_group_box, check_boxes_group_boxes) {
                QJsonObject answer_info;
                EditableLabel* answer_text = check_box_group_box->findChild<EditableLabel*>();
                answer_info.insert("answer_text", answer_text->text());
                QCheckBox* check_box = check_box_group_box->findChild<QCheckBox*>();
                answer_info.insert("is_correct", QJsonValue(check_box->isChecked()));
                answers.push_back(answer_info);
                if (check_box->isChecked()) {
                    correct_answer_count++;
                }
            }
            if (correct_answer_count == 1) {
                assignment_info.insert("type", QJsonValue("one choice"));
            }
            else {
                assignment_info.insert("type", QJsonValue("multiple choice"));
            }
            assignment_info.insert("answers", answers);
            assignment.insert("content", assignment_info);
            content_array.push_back(assignment);
        }
        else if (layout_item->objectName() == "header")
        {
            EditableLabel* header = qobject_cast<EditableLabel*>(layout_item);
            QJsonObject header_info;
            header_info.insert("type", "Header");
            header_info.insert("content", header->text());
            content_array.push_back(header_info);
        }
    }
    QJsonObject main_json_obj;
    main_json_obj.insert("Assignment", content_array);
    //main_json_obj.insert("Assignment_name", QJsonValue(assignment_name_));
    return QJsonDocument(main_json_obj);
}

void AssignmentCreationWindow::OnSaveButtonClicked()
{
    /*if (assignment_name_ == "") {
        EnterAssignmentNameDialog* new_dialog  = new EnterAssignmentNameDialog(this);
        connect(new_dialog, SIGNAL(NameChanged(const QString&)), this, SLOT(NameChanged(const QString&)));
        new_dialog->setModal(true);
        new_dialog->show();
    }
    else {
        execute_command(new SaveEditableAssignmentCommand(ToJSON(), assignment_name_));
    }*/
}

void AssignmentCreationWindow::NameChanged(const QString& name)
{
    /*QString prev_name = assignment_name_;
    assignment_name_ = name;
    this->setWindowTitle(assignment_name_);
    if (prev_name == "") {
        CreateFile(QString::fromStdString(GetAssignmentPath(assignment_name_.toStdString())));
        execute_command(new SaveEditableAssignmentCommand(ToJSON(), assignment_name_));
    }
    else {
        RenameFile(QString::fromStdString(GetAssignmentPath(prev_name.toStdString())),
                    QString::fromStdString(GetAssignmentPath(assignment_name_.toStdString())));
    }*/
}
void AssignmentCreationWindow::FromJSON(const QJsonDocument& json_doc)
{
    QJsonObject json_document_object = json_doc.object();
    QJsonArray assignment_layout =  json_document_object.take("Assignment").toArray();
    foreach (QJsonValue item, assignment_layout)
    {
        QJsonObject cur_object = item.toObject();
        QString type =  cur_object.take("type").toString();
        if (type == "Header")
        {
            AddHeader(cur_object.take("content").toString(), false);
        }
        else if (type == "test_assignment")
        {
            QJsonObject test_assignment_obj = cur_object.take("content").toObject();
            unsigned long long id = (unsigned long long) test_assignment_obj.take("id").toDouble();
            cur_assignment_id = std::max(cur_assignment_id, id);
            QString question = test_assignment_obj.take("question").toString();
            QJsonArray answers = test_assignment_obj.take("answers").toArray();
            // create command and get widget
            AddEditableTestAssignmentCommand* add_test_command =
                    new AddEditableTestAssignmentCommand(assignment_layout_, assignment_container_, this, id, question);
            add_test_command->execute();
            foreach(QJsonValue answer, answers)
            {
                AddTestAnswer(answer.toObject().take("answer_text").toString(),
                              add_test_command->GetAddedWidget(), add_test_command->GetAddedWidget()->layout(), false, answer.toObject().take("is_correct").toBool());
            }
        }
    }
    cur_assignment_id++;
}
