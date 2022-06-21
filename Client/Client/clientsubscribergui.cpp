#include "clientsubscribergui.h"
#include <QMessageBox>

ClientSubscriberGui::ClientSubscriberGui(QWidget *parent)
    : ClientSubscriber(), QMainWindow(parent)
{
}

ClientSubscriberGui::~ClientSubscriberGui()
{

}

void ClientSubscriberGui::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::ERROR_DATABASE || msg.header.id == CustomMsgTypes::SERVER_DOWN)
    {
        QMessageBox::critical(this, "Server down", "Server is down! Try later");
        this->close();
    }
}
