#include "assignmentguibuilder.h"
#include <QLabel>

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

/*QSharedPointer<QLayout> AssignmentGUIBuilder::get_layout()
{
    return layout;
    reset();
}*/

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

}




