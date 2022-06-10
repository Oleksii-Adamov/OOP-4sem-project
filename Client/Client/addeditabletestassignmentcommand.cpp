#include "addeditabletestassignmentcommand.h"
#include <QGroupBox>
#include "font.h"
#include <QPushButton>
#include "assignmentcreationwindow.h"
#include <QAbstractButton>

AddEditableTestAssignmentCommand::AddEditableTestAssignmentCommand(QLayout* layout, QWidget* widget, unsigned long long id, const QString& question_text)
    : layout_(layout), widget_(widget), question_text_(question_text), id_(id)
{

}

bool AddEditableTestAssignmentCommand::execute()
{
    QGroupBox* group_box = new QGroupBox(widget_);
    group_box->setObjectName("test_assignment" + QString::number(id_));
    group_box->setFont(Font::TestQuestionFont());
    QVBoxLayout* v_layout = new QVBoxLayout(group_box);
    EditableLabel* question = new EditableLabel(question_text_, group_box);
    v_layout->addWidget(question);
    QPushButton* add_answer_button = new QPushButton("Add answer");
    /*QAbstractButton::connect(
        add_answer_button, &QPushButton::clicked,
        widget_, &AssignmentCreationWindow::OnAddTestAnswerButtonClicked
    );*/
    connect(add_answer_button, SIGNAL(clicked()), widget_, SLOT(OnAddTestAnswerButtonClicked()));
    v_layout->addWidget(add_answer_button);
    layout_->addWidget(group_box);
    added_widget_ = group_box;
    return true;
}

void AddEditableTestAssignmentCommand::undo()
{
    layout_->removeWidget(added_widget_);
    added_widget_->hide();
}
