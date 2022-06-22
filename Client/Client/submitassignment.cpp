#include "submitassignment.h"
#include <QGroupBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include "jsonfile.h"
#include "client.h"

SubmitAssignment::SubmitAssignment()
{

}

SubmitAssignment* SubmitAssignment::GetInstance()
{
    // first time it will be instancieted, than referenced
    static SubmitAssignment instance;
    return &instance;
}

void SubmitAssignment::OnSubmitButtonClicked()
{
    QWidget* sender_widget = qobject_cast<QWidget*>(sender());
    QWidget* parent_widget = qobject_cast<QWidget*>(sender_widget->parent());
    auto layout_items = parent_widget->findChildren<QWidget*>();
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
    //writeJsonFile(QJsonDocument(main_json_obj), "assinment_json_from_student_to_server.json");
}
