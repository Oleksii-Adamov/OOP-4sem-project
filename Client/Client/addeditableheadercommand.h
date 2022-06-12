#ifndef ADDEDITABLEHEADERCOMMAND_H
#define ADDEDITABLEHEADERCOMMAND_H

#include "command.h"
#include <QWidget>
#include <QLayout>
#include "editablelabel.h"

class AddEditableHeaderCommand : public Command
{
private:
    QLayout* layout_;
    QWidget* widget_;
    QWidget* added_widget_ = nullptr;
    const QString& header_text_;
public:
    AddEditableHeaderCommand(QLayout* layout, QWidget* widget, const QString& header_text = "Header");
    bool execute() override;
    void undo() override;
};

#endif // ADDEDITABLEHEADERCOMMAND_H
