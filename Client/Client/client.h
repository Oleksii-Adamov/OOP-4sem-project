#ifndef CLIENT_H
#define CLIENT_H
#include "net.h"
#include "messagetypes.h"
#include <QDebug>
#include "clientsubscriber.h"
#include <QObject>
#include "User.h"
#include <QApplication>

class Client : public QObject, public net::client_interface<CustomMsgTypes>
{
    Q_OBJECT
private:
    std::vector<ClientSubscriber*> subscribers_;
    User user_;
    QApplication* app_ = nullptr;
    Client();
    void NotifySubscribers(net::message<CustomMsgTypes>& msg);
public:
    static Client* GetInstance();
    Client(const Client&) = delete;
    Client& operator=(const Client& other) = delete;
    void Subscribe(ClientSubscriber* subscriber);
    void UnSubscribe(ClientSubscriber* subscriber);
    User GetUser() const;
    void SetUser(User user);
    QApplication* GetApp() const;
    void SetApp(QApplication* app);
    ~Client(){}
public slots:
    void Update();
};

#endif // CLIENT_H
