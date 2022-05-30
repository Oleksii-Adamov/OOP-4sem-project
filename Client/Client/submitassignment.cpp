#include "submitassignment.h"
#include "qwidget.h"
#include <QGroupBox>

SubmitAssignment::SubmitAssignment()
{

}

void SubmitAssignment::OnSubmitButtonClicked()
{
    QWidget* sender_widget = qobject_cast<QWidget*>(sender());
    QWidget* parent_widget = qobject_cast<QWidget*>(sender_widget->parent());
    auto test_assignments = parent_widget->findChildren<QGroupBox*>("test_assignment");
    foreach(auto test_assignment, test_assignments) {
        qDebug() << test_assignment->title();
        //auto answers = test_assignment->findChildren<Q>("test_assignment");
    }
}
