#ifndef CLIENT_H
#define CLIENT_H
#include "net.h"
#include "messagetypes.h"
#include <QDebug>
#include "clientsubscriber.h"
#include <QObject>

class Client : public QObject, public net::client_interface<CustomMsgTypes>
{
    Q_OBJECT
private:
    bool key[3] = { false, false, false };
    bool old_key[3] = { false, false, false };
    std::vector<ClientSubscriber*> subscribers_;
    Client();
public:
    static Client* GetInstance();
    Client(const Client&) = delete;
    Client& operator=(const Client& other) = delete;
    void Subscribe(ClientSubscriber* subscriber);
    void UnSubscribe(ClientSubscriber* subscriber);
    void NotifySubscribers(net::message<CustomMsgTypes>& msg);
    ~Client(){}
public slots:
    void Update();
    /*void PingServer()
    {
        net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    void MessageAll()
    {
        net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }*/


};

#endif // CLIENT_H
