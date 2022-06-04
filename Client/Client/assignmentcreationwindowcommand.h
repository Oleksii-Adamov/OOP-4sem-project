#ifndef ASSIGNMENTCREATIONWINDOWCOMMAND_H
#define ASSIGNMENTCREATIONWINDOWCOMMAND_H

#include "assignmentcreationwindow.h"

class AssignmentCreationWindowCommand
{
protected:
    AssignmentCreationWindow* assignment_creation_window;
public:
    AssignmentCreationWindowCommand() {}
    virtual ~AssignmentCreationWindowCommand(){}
    virtual bool execute() = 0;
    virtual void undo() {}
};

#endif // ASSIGNMENTCREATIONWINDOWCOMMAND_H
