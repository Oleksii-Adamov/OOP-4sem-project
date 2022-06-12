#ifndef ADDEDITABLETESTASSIGNMENTCOMMAND_H
#define ADDEDITABLETESTASSIGNMENTCOMMAND_H

#include "command.h"
#include <QWidget>
#include <QLayout>
#include "editablelabel.h"

class AddEditableTestAssignmentCommand : public Command
{
private:
    QLayout* layout_;
    QWidget* widget_;
    QWidget* widget_to_link_button_signal_;
    QWidget* added_widget_ = nullptr;
    const QString& question_text_;
    unsigned long long id_;

public:
    AddEditableTestAssignmentCommand(QLayout* layout, QWidget* widget, QWidget* widget_to_link_button_signal, unsigned long long id, const QString& question_text = "Question");
    bool execute() override;
    void undo() override;
    QWidget* GetAddedWidget();
};

#endif // ADDEDITABLETESTASSIGNMENTCOMMAND_H
