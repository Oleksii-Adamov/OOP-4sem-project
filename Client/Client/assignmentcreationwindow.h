#ifndef ASSIGNMENTCREATIONWINDOW_H
#define ASSIGNMENTCREATIONWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
//#include "assignmentcreationwindowmemento.h"
#include "commandhistory.h"
#include <QVBoxLayout>

namespace Ui {
class AssignmentCreationWindow;
}

class AssignmentCreationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssignmentCreationWindow(QWidget *parent = nullptr);
    ~AssignmentCreationWindow();

private:
    Ui::AssignmentCreationWindow *ui;
    CommandHistory history_;
    QVBoxLayout* assignment_layout_;
    QWidget* assignment_container_;
    unsigned long long cur_assignment_id = 0;

    void execute_command(Command* command);
    void undo();
    void AddHeader(const QString& text);
    void AddTest(const QString& text);
    void AddTestAnswer(const QString& text, QWidget* container, QLayout* layout);
public:
    QJsonDocument ToJSON();
    void FromJSON(const QJsonDocument& json_doc);

    /*AssignmentCreationWindowMemento save();
    void restore(const AssignmentCreationWindowMemento& memento);*/
private slots:
    void OnAddHeaderButtonClicked();
    void OnUndoButtonClicked();
    void OnAddTestButtonClicked();
public slots:
    void OnAddTestAnswerButtonClicked();
};

#endif // ASSIGNMENTCREATIONWINDOW_H
