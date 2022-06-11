#include "addeditableheadercommand.h"
#include "font.h"

AddEditableHeaderCommand::AddEditableHeaderCommand(QLayout* layout, QWidget* widget, const QString& header_text)
    : layout_(layout), widget_(widget), header_text_(header_text)
{

}
bool AddEditableHeaderCommand::execute()
{
    EditableLabel* header_editable_label = new EditableLabel(header_text_, widget_);
    header_editable_label->setObjectName("header");
    header_editable_label->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    header_editable_label->setFont(Font::TestHeaderFont());
    header_editable_label->setAlignment(Qt::AlignHCenter);
    layout_->addWidget(header_editable_label);
    added_widget_ = header_editable_label;
    return true;
}
void AddEditableHeaderCommand::undo()
{
    layout_->removeWidget(added_widget_);
    added_widget_->hide();
}
