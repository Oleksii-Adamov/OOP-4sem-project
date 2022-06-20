#ifndef CREATEDASSIGNMENTSWINDOW_H
#define CREATEDASSIGNMENTSWINDOW_H

#include <QMainWindow>
#include "assignmentslistmodel.h"

namespace Ui {
class CreatedAssignmentsWindow;
}

class CreatedAssignmentsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreatedAssignmentsWindow(QWidget *parent = nullptr);
    ~CreatedAssignmentsWindow();

public slots:
    void OnAssignmentClicked(const QModelIndex& index);

private slots:
    void on_pushButton_create_new_clicked();

private:
    Ui::CreatedAssignmentsWindow *ui;
    QSharedPointer<AssignmentsListModel> assignments_list_model;
};

#endif // CREATEDASSIGNMENTSWINDOW_H
