#include "clientsubscribergui.h"
#include "serverdowndialog.h"
#include "client.h"

ClientSubscriberGui::ClientSubscriberGui()
    : ClientSubscriber()
{
}

ClientSubscriberGui::~ClientSubscriberGui()
{

}

void ClientSubscriberGui::Update(net::message<CustomMsgTypes> msg)
{
    if (msg.header.id == CustomMsgTypes::ERROR_DATABASE || msg.header.id == CustomMsgTypes::SERVER_DOWN)
    {
        ServerDownDialog* dialog = new ServerDownDialog(Client::GetInstance()->GetApp()->activeWindow());
        dialog->setModal(true);
        dialog->show();
    }
}
