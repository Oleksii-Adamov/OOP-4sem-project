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
//#include "Assignment.h"
//#include "AssignmentSession.h"

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
//    ts_client.push_front(client);
//    std::thread checkClientThread(CheckClient);
//    std::thread mainThread(Main, argc, argv);
    
//    checkClientThread.join();
//    mainThread.join();
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
    return a.exec();

}
