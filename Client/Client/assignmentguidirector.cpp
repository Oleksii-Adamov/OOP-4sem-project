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

void AssignmentGUIDirector::BuildFromJSON(const QJsonDocument& json_document)
{
    QJsonObject json_document_object = json_document.object();
    QJsonArray assignment_layout =  json_document_object.take("Assignment").toArray();
    foreach (QJsonValue item, assignment_layout)
    {
        QJsonObject cur_object = item.toObject();
        QString type =  cur_object.take("type").toString();
        if (type == "Header")
        {
            builder_->ProduceHeader(cur_object.take("content").toString().toStdString());
        }
        else if (type == "TestAssignment")
        {
            QJsonObject test_assignment_obj = cur_object.take("content").toObject();
            TestAssignment test_assignment(test_assignment_obj.take("question").toString().toStdString());
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
            QJsonArray answers = test_assignment_obj.take("answers").toArray();
            foreach(QJsonValue answer, answers)
            {
                test_assignment.PushAnswer(TestAnswer(answer.toObject().take("answer_text").toString().toStdString()));
            }
            builder_->ProduceTestAssignment(test_assignment);
        }
    }
}
