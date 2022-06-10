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
    if (history_.size() > 0) {
        Command* ret = history_.back();
        history_.pop_back();
        return ret;
    }
    else {
        return nullptr;
    }
}
