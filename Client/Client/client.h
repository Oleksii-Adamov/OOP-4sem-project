#ifndef CLIENT_H
#define CLIENT_H
#include "net.h"
#include "messagetypes.h"
#include <QDebug>
#include "clientsubscriber.h"
#include <QObject>
#include "User.h"

class Client : public QObject, public net::client_interface<CustomMsgTypes>
{
    Q_OBJECT
private:
    bool key[3] = { false, false, false };
    bool old_key[3] = { false, false, false };
    std::vector<ClientSubscriber*> subscribers_;
    User user_ = User(1,"login","user_name");
    Client();
    void NotifySubscribers(net::message<CustomMsgTypes>& msg);
public:
    static Client* GetInstance();
    Client(const Client&) = delete;
    Client& operator=(const Client& other) = delete;
    void Subscribe(ClientSubscriber* subscriber);
    void UnSubscribe(ClientSubscriber* subscriber);
    User GetUser() const;
    ~Client(){}
public slots:
    void Update();
};

#endif // CLIENT_H
