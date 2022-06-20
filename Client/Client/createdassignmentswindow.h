#ifndef CREATEDASSIGNMENTSWINDOW_H
#define CREATEDASSIGNMENTSWINDOW_H

#include <QMainWindow>
#include "assignmentslistmodel.h"
#include "clientsubscriber.h"

namespace Ui {
class CreatedAssignmentsWindow;
}

class CreatedAssignmentsWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit CreatedAssignmentsWindow(QWidget *parent = nullptr);
    ~CreatedAssignmentsWindow();
    void Update(net::message<CustomMsgTypes> msg) override;

public slots:
    void OnAssignmentClicked(const QModelIndex& index);

private slots:
    void on_pushButton_create_new_clicked();

private:
    Ui::CreatedAssignmentsWindow *ui;
    QSharedPointer<AssignmentsListModel> assignments_list_model;
    void GetData();
};

#endif // CREATEDASSIGNMENTSWINDOW_H
