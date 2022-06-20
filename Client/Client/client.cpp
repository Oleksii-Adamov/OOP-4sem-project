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
        /*switch(message.header.id)
        {
            case CustomMsgTypes::ServerPing : {
                std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point timeThen;
                message >> timeThen;
                qDebug() << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
                break;
            }
            case CustomMsgTypes::RETURN_TEST_ASSIGMENT:
            {
              uint64_t size;
              message >> size;
              std::string json = "";
              for (uint64_t i = 0; i < size; i++) {
                char c;
                message >> c;
                json = c + json;
              }
              qDebug() << QString::fromStdString(json);
              break;
            }
        }*/

    }

}
