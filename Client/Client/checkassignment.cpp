#include "checkassignment.h"
#include <QJsonObject>
#include <QJsonArray>

CheckAssignment::CheckAssignment()
{

}

AutoScore CheckAssignment::GetScore(const QJsonDocument& json_document, const QJsonDocument& json_document_compare_to)
{
    AutoScore ret;
    QJsonObject json_document_object = json_document.object();
    QJsonObject json_document_compare_to_object = json_document_compare_to.object();
    QJsonArray assignment_layout =  json_document_object.take("Assignment").toArray();
    QJsonArray assignment_layout_compare_to =  json_document_compare_to_object.take("Assignment").toArray();
    for (int i = 0; i < assignment_layout.size(); i++)
    {
        QJsonObject cur_object = assignment_layout.at(i).toObject();
        QJsonObject cur_object_compare_to = assignment_layout_compare_to.at(i).toObject();
        QString type =  cur_object.take("type").toString();
        if (type == "test_assignment")
        {
            QJsonObject test_assignment_obj = cur_object.take("content").toObject();
            long long test_assignment_id = (long long) test_assignment_obj.take("id").toDouble();
            QString type = test_assignment_obj.take("type").toString();

            QJsonObject test_assignment_compare_to_obj = cur_object_compare_to.take("content").toObject();
            long long test_assignment_compare_to_id = (long long) test_assignment_compare_to_obj.take("id").toDouble();

            if (test_assignment_id == test_assignment_compare_to_id)
            {
                QJsonArray answers_compare_to = test_assignment_compare_to_obj.take("answers").toArray();
                QJsonArray answers = test_assignment_obj.take("answers").toArray();
                for (int j = 0; j < answers.size(); j++)
                {
                    QJsonValue is_checked_json = answers.at(j).toObject().take("is_answer_chosen");
                    bool is_checked = false;
                    if (is_checked_json == QJsonValue::Undefined || !is_checked_json.toBool()) {
                        is_checked = false;
                    }
                    else if (is_checked_json.toBool())
                    {
                        is_checked = true;
                    }

                    bool is_correct = false;
                    QJsonValue is_checked_compare_to_json = answers_compare_to.at(j).toObject().take("is_correct");
                    if (is_checked_compare_to_json != QJsonValue::Undefined) {
                        is_correct = is_checked_compare_to_json.toBool();
                    }

                    if (is_checked && is_correct)
                    {
                        if (type == "one choice")
                        {
                            ret.score += one_choice_answer_weight_;
                        }
                        else if (type == "multiple choice")
                        {
                            ret.score += multiple_choice_answer_weight_;
                        }
                    }

                    if (is_correct)
                    {
                        if (type == "one choice")
                        {
                            ret.max_score += one_choice_answer_weight_;
                        }
                        else if (type == "multiple choice")
                        {
                            ret.max_score += multiple_choice_answer_weight_;
                        }
                    }
                }
            }
        }
    }
    return ret;
}
