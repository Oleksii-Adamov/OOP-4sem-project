#include <QApplication>
#include "client.h"
#include "mainmenuwindow.h"
#include "checkclientthread.h"

int main(int argc, char *argv[])
{
    Client* client = Client::GetInstance();
    client->Connect("127.0.0.1", 60000);
    CheckClientThread* check_client_thread = new CheckClientThread;
    QObject::connect(check_client_thread, &CheckClientThread::TimeToUpdate,
                         client, &Client::Update);
    check_client_thread->start();

    QApplication a(argc, argv);
    MainMenuWindow w;
    w.show();
    int ret = a.exec();
    check_client_thread->exit(0);
    return ret;

}
