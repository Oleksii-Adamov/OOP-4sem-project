#ifndef CLIENTSUBSCRIBERGUI_H
#define CLIENTSUBSCRIBERGUI_H

#include "clientsubscriber.h"

class ClientSubscriberGui : ClientSubscriber
{
public:
    ClientSubscriberGui();
    virtual ~ClientSubscriberGui();
    void Update(net::message<CustomMsgTypes> msg) override;
};

#endif // CLIENTSUBSCRIBERGUI_H
