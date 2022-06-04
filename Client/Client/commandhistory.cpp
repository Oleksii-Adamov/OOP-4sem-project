#include "commandhistory.h"

CommandHistory::CommandHistory()
{

}

void CommandHistory::push(Command* command)
{
    history_.push_back(command);
}
Command* CommandHistory::pop()
{
    Command* ret = history_.back();
    history_.pop_back();
    return ret;
}
