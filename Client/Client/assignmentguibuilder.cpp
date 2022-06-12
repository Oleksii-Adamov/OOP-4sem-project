#include "assignmentguibuilder.h"
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include "submitassignment.h"
#include "font.h"

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
    header_label->setFont(Font::TestHeaderFont());
    header_label->setAlignment(Qt::AlignHCenter);
    layout_->addWidget(header_label);
}

void AssignmentGUIBuilder::ProduceTestAssignment(const TestAssignment& test_assignment) const
{
    QGroupBox* group_box = new QGroupBox(QString::fromStdString(test_assignment.get_question()), widget_);
    //group_box->setFlat(true);
    group_box->setObjectName("test_assignment" + QString::number(test_assignment.get_id()));
    group_box->setFont(Font::TestQuestionFont());
    QVBoxLayout* v_layout = new QVBoxLayout(group_box);
    std::vector<TestAnswer> answers = test_assignment.get_answers();
    for (std::size_t i = 0; i < answers.size(); i++) {
        QWidget* option = nullptr;
        if (test_assignment.get_test_type() == TestType::one_choice) {
            option = new QRadioButton(QString::fromStdString(answers[i].get_answer_text()), widget_);
        }
        else if (test_assignment.get_test_type() == TestType::multiple_choice) {
            option = new QCheckBox(QString::fromStdString(answers[i].get_answer_text()), widget_);
        }
        if (option != nullptr) {
            option->setFont(Font::TestAnswerFont());
            v_layout->addWidget(option);
        }
    }
    layout_->addWidget(group_box);
}

void AssignmentGUIBuilder::ProduceSubmitButton() const
{
    QPushButton* submit_button = new QPushButton("Відправити", widget_);
    QFont submit_button_font;
    submit_button_font.setPointSize(20);
    submit_button->setFont(submit_button_font);
    QAbstractButton::connect(
        submit_button, &QPushButton::clicked,
        SubmitAssignment::GetInstance(), &SubmitAssignment::OnSubmitButtonClicked
    );
    layout_->addWidget(submit_button);
}


