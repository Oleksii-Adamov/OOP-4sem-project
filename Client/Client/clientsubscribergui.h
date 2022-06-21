#ifndef CLIENTSUBSCRIBERGUI_H
#define CLIENTSUBSCRIBERGUI_H

#include "clientsubscriber.h"

class ClientSubscriberGui : public ClientSubscriber
{
public:
    ClientSubscriberGui();
    virtual ~ClientSubscriberGui();
    virtual void Update(net::message<CustomMsgTypes> msg) override;
};

#endif // CLIENTSUBSCRIBERGUI_H
