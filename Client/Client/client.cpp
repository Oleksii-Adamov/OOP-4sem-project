#include "client.h"

Client::Client()
{

}

Client* Client::GetInstance()
{
    // first time it will be instancieted, than referenced
    static Client instance;
    return &instance;
}

void Client::Subscribe(ClientSubscriber* subscriber)
{
    subscribers_.push_back(subscriber);
}

void Client::UnSubscribe(ClientSubscriber* subscriber)
{
    subscribers_.erase(std::find(subscribers_.begin(), subscribers_.end(), subscriber));
}

void Client::NotifySubscribers(net::message<CustomMsgTypes>& msg)
{
    for (std::size_t i = 0; i < subscribers_.size(); i++) {
        subscribers_[i]->Update(msg);
    }
}

void Client::Update()
{
    if (!Incoming().empty()) {
        net::message<CustomMsgTypes> message = Incoming().pop_front().msg;
        NotifySubscribers(message);
    }
}

User Client::GetUser() const
{
    return user_;
}
