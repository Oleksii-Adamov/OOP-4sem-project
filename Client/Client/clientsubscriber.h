#ifndef CLIENTSUBSCRIBER_H
#define CLIENTSUBSCRIBER_H

#include "net.h"
#include "messagetypes.h"

class ClientSubscriber
{
public:
    ClientSubscriber();
    virtual ~ClientSubscriber();
    virtual void Update(net::message<CustomMsgTypes> msg) = 0;
};

#endif // CLIENTSUBSCRIBER_H
