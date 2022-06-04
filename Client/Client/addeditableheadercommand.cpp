#include "addeditableheadercommand.h"

AddEditableHeaderCommand::AddEditableHeaderCommand(QLayout* layout, QWidget* widget, const QString& header_text)
    : layout_(layout), widget_(widget), header_text_(header_text)
{

}
bool AddEditableHeaderCommand::execute()
{
    EditableLabel* header_editable_label = new EditableLabel(header_text_, widget_);
    header_editable_label->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    QFont header_font;
    header_font.setPointSize(40);
    header_editable_label->setFont(header_font);
    header_editable_label->setAlignment(Qt::AlignHCenter);
    layout_->addWidget(header_editable_label);
    added_header_ = header_editable_label;
    return true;
}
void AddEditableHeaderCommand::undo()
{
    layout_->removeWidget(added_header_);
    added_header_->hide();
}
