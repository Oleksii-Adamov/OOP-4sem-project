#ifndef ASSIGNMENTCREATIONWINDOW_H
#define ASSIGNMENTCREATIONWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include "assignmentcreationwindowmemento.h"
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
public:
    QJsonDocument ToJSON();
    void FromJSON(const QJsonDocument& json_doc);
    AssignmentCreationWindowMemento save();
    void restore(const AssignmentCreationWindowMemento& memento);
};

#endif // ASSIGNMENTCREATIONWINDOW_H
