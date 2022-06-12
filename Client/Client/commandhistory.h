#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include "command.h"
#include <vector>

/*!
 * \brief History of commands (Command pattern)
 */
class CommandHistory
{
private:
    std::vector<Command*> history_;
public:
    CommandHistory();
    void push(Command* command);
    Command* pop();
};

#endif // COMMANDHISTORY_H
