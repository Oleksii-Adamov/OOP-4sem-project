#ifndef COMMAND_H
#define COMMAND_H


class Command
{
public:
    Command();
    virtual ~Command(){}
    virtual bool execute() = 0;
    virtual void undo() {}
};

#endif // COMMAND_H
