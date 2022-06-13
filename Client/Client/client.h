#ifndef CLIENT_H
#define CLIENT_H
#include "net.h"
#include "messagetypes.h"
#include <QDebug>

class Client : public net::client_interface<CustomMsgTypes>
{
private:
    bool key[3] = { false, false, false };
    bool old_key[3] = { false, false, false };
    Client();
public:
    static Client* GetInstance()
    {
        // first time it will be instancieted, than referenced
        static Client instance;
        return &instance;
    }
    Client(const Client&) = delete;
    Client& operator=(const Client& other) = delete;

    void PingServer()
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
    }

    void Update()
    {
        if (!Incoming().empty()) {
            auto message = Incoming().pop_front().msg;
            switch(message.header.id)
            {
                case CustomMsgTypes::ServerPing : {
                    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    message >> timeThen;
                    qDebug() << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
                    break;
                }

            }
        }

    }
};

#endif // CLIENT_H
