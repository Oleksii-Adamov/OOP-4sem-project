#ifndef ASSIGNMENTCREATIONWINDOW_H
#define ASSIGNMENTCREATIONWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include "commandhistory.h"
#include <QVBoxLayout>
#include "Assignment.h"
#include "clientsubscriber.h"

namespace Ui {
class AssignmentCreationWindow;
}


class AssignmentCreationWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit AssignmentCreationWindow(const Assignment& assignment, QWidget *parent = nullptr);
    ~AssignmentCreationWindow();

private:
    Ui::AssignmentCreationWindow *ui;
    CommandHistory history_;
    QVBoxLayout* assignment_layout_;
    QWidget* assignment_container_;
    unsigned long long cur_assignment_id = 0;
    Assignment assignment_;

    void execute_command(Command* command, bool is_needed_to_save = true);
    void undo();
    void AddHeader(const QString& text, bool is_needed_to_save = true);
    void AddTest(const QString& text, bool is_needed_to_save = true);
    void AddTestAnswer(const QString& text, QWidget* container, QLayout* layout, bool is_needed_to_save = true, bool is_checked = false);
    void GetData();
public:
    QJsonDocument ToJSON();
    void FromJSON(const QJsonDocument& json_doc);
    void Update(net::message<CustomMsgTypes> msg) override;
private slots:
    void OnAddHeaderButtonClicked();
    void OnUndoButtonClicked();
    void OnAddTestButtonClicked();
    void OnSaveButtonClicked();
public slots:
    void OnAddTestAnswerButtonClicked();
    void NameChanged(const QString& name);
};

#endif // ASSIGNMENTCREATIONWINDOW_H
