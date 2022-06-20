#ifndef CLASSROOMWINDOW_H
#define CLASSROOMWINDOW_H

#include <QMainWindow>
#include "classroomwindowstrategy.h"
#include "classroominfo.h"
#include "clientsubscriber.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ClassroomWindow;
}
QT_END_NAMESPACE

class ClassroomWindow : public QMainWindow, ClientSubscriber
{
    Q_OBJECT

public:
    explicit ClassroomWindow(const ClassroomInfo& classroom_info, QSharedPointer<ClassroomWindowStrategy> strategy, QWidget *parent = nullptr);
    ~ClassroomWindow();
    void Update(net::message<CustomMsgTypes> msg) override;

public slots:
    void OnAssignmentClicked(const QModelIndex& index);

private slots:
    void on_actionUpdate_triggered();

private:
    Ui::ClassroomWindow *ui;
    QSharedPointer<QAbstractListModel> assignments_list_model;
    QSharedPointer<ClassroomWindowStrategy> strategy_;
    ClassroomInfo classroom_info_;
};

#endif // CLASSROOMWINDOW_H
