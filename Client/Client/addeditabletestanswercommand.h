#ifndef ADDEDITABLETESTANSWERCOMMAND_H
#define ADDEDITABLETESTANSWERCOMMAND_H

#include "command.h"
#include <QWidget>
#include <QLayout>
#include "editablelabel.h"

class AddEditableTestAnswerCommand : public Command
{
private:
    QLayout* layout_;
    QWidget* widget_;
    QWidget* added_widget_ = nullptr;
    const QString& answer_text_;
public:
    AddEditableTestAnswerCommand(QLayout* layout, QWidget* widget, const QString& answer_text = "Answer");
    bool execute() override;
    void undo() override;
};

#endif // ADDEDITABLETESTANSWERCOMMAND_H
