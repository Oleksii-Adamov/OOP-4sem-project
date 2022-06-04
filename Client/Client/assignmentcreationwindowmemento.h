#ifndef ASSIGNMENTCREATIONWINDOWMEMENTO_H
#define ASSIGNMENTCREATIONWINDOWMEMENTO_H

#include <QJsonDocument>

class AssignmentCreationWindowMemento
{
private:
    QJsonDocument state_;
    AssignmentCreationWindowMemento(const QJsonDocument& state);
    QJsonDocument get_state();
    friend class AssignmentCreationWindow;
public:

};

#endif // ASSIGNMENTCREATIONWINDOWMEMENTO_H
