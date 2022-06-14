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
    explicit AssignmentCreationWindow(const QJsonDocument& json_doc,QWidget *parent = nullptr);
    ~AssignmentCreationWindow();

private:
    Ui::AssignmentCreationWindow *ui;
    CommandHistory history_;
    QVBoxLayout* assignment_layout_;
    QWidget* assignment_container_;
    unsigned long long cur_assignment_id = 0;
    QString assignment_name_ = "";

    void execute_command(Command* command, bool is_needed_to_save = true);
    void undo();
    void AddHeader(const QString& text, bool is_needed_to_save = true);
    void AddTest(const QString& text, bool is_needed_to_save = true);
    void AddTestAnswer(const QString& text, QWidget* container, QLayout* layout, bool is_needed_to_save = true);
public:
    QJsonDocument ToJSON();
    void FromJSON(const QJsonDocument& json_doc);
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
