#ifndef COMMAND_H
#define COMMAND_H

#include<QObject>

/*!
 * \brief Abstract command class (Command pattern)
 */
class Command : public QObject
{
    Q_OBJECT
public:
    Command();
    virtual ~Command(){}
    virtual bool execute() = 0;
    virtual void undo() {}
};

#endif // COMMAND_H
