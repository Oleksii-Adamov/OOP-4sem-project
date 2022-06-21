#ifndef CLIENTSUBSCRIBERGUI_H
#define CLIENTSUBSCRIBERGUI_H

#include "clientsubscriber.h"
#include <QMainWindow>

class ClientSubscriberGui : public ClientSubscriber, public QMainWindow
{
    /*Q_OBJECT*/
public:
    explicit ClientSubscriberGui(QWidget *parent = nullptr);
    virtual ~ClientSubscriberGui();
    virtual void Update(net::message<CustomMsgTypes> msg) override;
};

#endif // CLIENTSUBSCRIBERGUI_H
