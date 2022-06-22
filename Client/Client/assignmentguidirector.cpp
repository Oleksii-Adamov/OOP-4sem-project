#include "assignmentguidirector.h"
#include <QJsonObject>
#include <QJsonArray>

AssignmentGUIDirector::AssignmentGUIDirector()
{

}

void AssignmentGUIDirector::set_builder(AssignmentGUIBuilder* builder)
{
    builder_ = builder;
}

void AssignmentGUIDirector::BuildFromJSON(const QJsonDocument& json_document,
                                          const QJsonDocument& json_document_compare_to)
{
    QJsonObject json_document_object = json_document.object();
    QJsonObject json_document_compare_to_object = json_document_compare_to.object();
    QJsonArray assignment_layout =  json_document_object.take("Assignment").toArray();
    QJsonArray assignment_layout_compare_to =  json_document_compare_to_object.take("Assignment").toArray();
    for (int i = 0; i < assignment_layout.size(); i++)
    {
        QJsonObject cur_object = assignment_layout.at(i).toObject();
        QJsonObject cur_object_compare_to = assignment_layout_compare_to.at(i).toObject();
        QString type =  cur_object.take("type").toString();
        if (type == "Header")
        {
            builder_->ProduceHeader(cur_object.take("content").toString().toStdString());
        }
        else if (type == "test_assignment")
        {
            QJsonObject test_assignment_obj = cur_object.take("content").toObject();
            long long id = (long long) test_assignment_obj.take("id").toDouble();
            std::string question = test_assignment_obj.take("question").toString().toStdString();
            TestAssignment test_assignment(question, id);
            QString type = test_assignment_obj.take("type").toString();

            TestType test_type = TestType::one_choice;
            if (type == "one choice")
            {
                test_type = TestType::one_choice;
            }
            else if (type == "multiple choice")
            {
                test_type = TestType::multiple_choice;
            }
            test_assignment.set_test_type(test_type);

            TestAssignment test_assignment_compare_to;
            QJsonObject test_assignment_compare_to_obj = cur_object_compare_to.take("content").toObject();
            QJsonArray answers_compare_to;
            if (test_assignment_compare_to_obj != QJsonObject()) {
                long long test_assignment_compare_to_id = (long long) test_assignment_compare_to_obj.take("id").toDouble();
                test_assignment_compare_to.set_id(test_assignment_compare_to_id);
                answers_compare_to = test_assignment_compare_to_obj.take("answers").toArray();
            }

            QJsonArray answers = test_assignment_obj.take("answers").toArray();
            for (int j = 0; j < answers.size(); j++)
            {
                std::string answer_text = answers.at(j).toObject().take("answer_text").toString().toStdString();
                QJsonValue is_checked_json = answers.at(j).toObject().take("is_answer_chosen");
                bool is_checked = false;
                if (is_checked_json == QJsonValue::Undefined || !is_checked_json.toBool()) {
                    is_checked = false;
                }
                else if (is_checked_json.toBool())
                {
                    is_checked = true;
                }
                TestAnswer correct_answer = TestAnswer();

                QJsonValue is_checked_compare_to_json = answers_compare_to.at(j).toObject().take("is_correct");
                if (is_checked_compare_to_json != QJsonValue::Undefined) {
                    correct_answer.set_is_answer_checked(is_checked_compare_to_json.toBool());
                    correct_answer.set_answer_text(answers_compare_to.at(j).toObject().take("answer_text").toString().toStdString());
                }

                test_assignment.PushAnswer(TestAnswer(answer_text, is_checked));
                test_assignment_compare_to.PushAnswer(correct_answer);
            }
            if (id == test_assignment_compare_to.get_id()) {
                builder_->ProduceTestAssignment(test_assignment, test_assignment_compare_to);
            }
            else {
                builder_->ProduceTestAssignment(test_assignment);
            }
        }
    }
    if (builder_->IsEditable()) {
        //builder_->ProduceSubmitButton();
    }
}
