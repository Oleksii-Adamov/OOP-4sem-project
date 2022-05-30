#include "assignmentguibuilder.h"
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>

AssignmentGUIBuilder::AssignmentGUIBuilder()
{
    Reset();
}
AssignmentGUIBuilder::~AssignmentGUIBuilder()
{

}

void AssignmentGUIBuilder::Reset()
{
    layout_ = nullptr;
    widget_ = nullptr;
}

void AssignmentGUIBuilder::Set(QLayout* input_layout, QWidget* input_widget)
{
    layout_ = input_layout;
    widget_ = input_widget;
}

void AssignmentGUIBuilder::ProduceHeader(const std::string& header_text) const
{
    QLabel* header_label = new QLabel(QString::fromStdString(header_text), widget_);
    header_label->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    QFont header_font;
    header_font.setPointSize(40);
    header_label->setFont(header_font);
    header_label->setAlignment(Qt::AlignHCenter);
    layout_->addWidget(header_label);
}

void AssignmentGUIBuilder::ProduceTestAssignment(const TestAssignment& test_assignment) const
{
    if (test_assignment.get_test_type() == TestType::one_choice) {
        QGroupBox* group_box = new QGroupBox(QString::fromStdString(test_assignment.get_question()), widget_);
        QFont question_font;
        question_font.setPointSize(20);
        group_box->setFont(question_font);
        QVBoxLayout* v_layout = new QVBoxLayout(group_box);
        std::vector<TestAnswer> answers = test_assignment.get_answers();
        for (std::size_t i = 0; i < answers.size(); i++) {
            QRadioButton* radio_button = new QRadioButton(QString::fromStdString(answers[i].get_answer_text()), widget_);
            v_layout->addWidget(radio_button);
        }
        layout_->addWidget(group_box);
    }
    else if (test_assignment.get_test_type() == TestType::multiple_choice) {

    }
}




