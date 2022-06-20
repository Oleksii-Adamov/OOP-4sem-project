#include "clientsubscriber.h"
#include "client.h"

ClientSubscriber::ClientSubscriber()
{
    Client::GetInstance()->Subscribe(this);
}

ClientSubscriber::~ClientSubscriber()
{
    Client::GetInstance()->UnSubscribe(this);
}
