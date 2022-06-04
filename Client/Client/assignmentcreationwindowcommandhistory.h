#ifndef ASSIGNMENTCREATIONWINDOWCOMMANDHISTORY_H
#define ASSIGNMENTCREATIONWINDOWCOMMANDHISTORY_H

#include "command.h"
#include <vector>

class AssignmentCreationWindowCommandHistory
{
private:
    std::vector<Command*> history;
public:
    AssignmentCreationWindowCommandHistory();
};

#endif // ASSIGNMENTCREATIONWINDOWCOMMANDHISTORY_H
