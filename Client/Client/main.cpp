#include "mainwindow.h"
#include "assignmentcreationwindow.h"
#include <QApplication>
#include "jsonfile.h"
#include "client.h"
#include "authorizationwindow.h"
#include "classroomwindow.h"
#include "classroomslistwindow.h"
#include "mainmenuwindow.h"
#include "sendassignmentwindow.h"
#include "studentassignmentsessionswindow.h"
#include "teacherassignmentcheckingwindow.h"
#include "checkclientthread.h"

using namespace std::chrono_literals;

std::recursive_mutex mlock;

void CheckClient() {
    std::this_thread::sleep_for(50ms);
    while (!mlock.try_lock()) {}
    Client::GetInstance()->Update();
//    qDebug() << "Thread1 :" << Client::GetInstance();
    mlock.unlock();
    CheckClient();
}

int Main(int argc, char *argv[]) {
    std::this_thread::sleep_for(500ms);
//    while (!mlock.try_lock()) {}
//    qDebug() << "Thread2 :" << Client::GetInstance();
//    mlock.unlock();
    QApplication a(argc, argv);
    //MainWindow w;
    //AssignmentCreationWindow w;
    //AuthorizationWindow w;
    //ClassroomWindow w;
    //ClassroomsListWindow w;
    MainMenuWindow w;
    //SendAssignmentWindow w;
    //StudentAssignmentSessionsWindow w;
    //TeacherAssignmentCheckingWindow w;
    w.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    Client* client = Client::GetInstance();
    client->Connect("127.0.0.1", 60000);
    CheckClientThread check_client_thread;
//    connect(check_client_thread, SIGNAL(TimeToUpdate()), client, SLOT(Update()));
    QObject::connect(&check_client_thread, &CheckClientThread::TimeToUpdate,
                         client, &Client::Update);
    check_client_thread.start();
  //  std::thread checkClientThread(CheckClient);
  //  std::thread mainThread(Main, argc, argv);

    //checkClientThread.join();
    //mainThread.join();
//return 0;

    QApplication a(argc, argv);
    //MainWindow w;
    //AssignmentCreationWindow w;
    //AuthorizationWindow w;
    //ClassroomWindow w;
    //ClassroomsListWindow w;
    MainMenuWindow w;
    //SendAssignmentWindow w;
    //StudentAssignmentSessionsWindow w;
    //TeacherAssignmentCheckingWindow w;
    w.show();
    int ret = a.exec();
    check_client_thread.quit();
    return ret;

}
