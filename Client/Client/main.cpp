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

void CheckClient(Client* client) {
  std::this_thread::sleep_for(500ms);
  client->Update();
  CheckClient(client);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client* client = Client::GetInstance();
    client->Connect("127.0.0.1", 60000);
    std::thread checkClientThread(CheckClient, client);

    // Client::GetInstance()->Connect("127.0.0.1", 60000);
    // Client::GetInstance()->Update();
    
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

    checkClientThread.join();

    return a.exec();
}
