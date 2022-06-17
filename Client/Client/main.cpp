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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client:: GetInstance()->Connect("127.0.0.1", 60000);
    MainWindow w;
    //AssignmentCreationWindow w;
    //AuthorizationWindow w;
    //ClassroomWindow w;
    //ClassroomsListWindow w;
    //MainMenuWindow w;
    //SendAssignmentWindow w;
    w.show();
    return a.exec();
}
