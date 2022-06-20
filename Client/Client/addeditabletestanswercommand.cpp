#include "addeditabletestanswercommand.h"
#include <QGroupBox>
#include "font.h"
#include <QCheckBox>

AddEditableTestAnswerCommand::AddEditableTestAnswerCommand(QLayout* layout, QWidget* widget, const QString& answer_text, bool is_checked)
    : layout_(layout), widget_(widget), answer_text_(answer_text), is_checked_(is_checked)
{

}

bool AddEditableTestAnswerCommand::execute()
{
    QLayoutItem* add_button = layout_->itemAt(layout_->count() - 1);
    layout_->removeItem(add_button);
    QGroupBox* group_box = new QGroupBox(widget_);
    group_box->setFont(Font::TestAnswerFont());
    QHBoxLayout* h_layout = new QHBoxLayout(group_box);
    QCheckBox* option = new QCheckBox(group_box);
    option->setChecked(is_checked_);
    EditableLabel* answer = new EditableLabel(answer_text_, group_box);
    h_layout->addWidget(option);
    h_layout->addWidget(answer);
    layout_->addWidget(group_box);
    layout_->addItem(add_button);
    added_widget_ = group_box;
    return true;
}

void AddEditableTestAnswerCommand::undo()
{
    layout_->removeWidget(added_widget_);
    added_widget_->hide();
}
