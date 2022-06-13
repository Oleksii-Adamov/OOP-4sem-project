#include "mainwindow.h"
#include "assignmentcreationwindow.h"
#include <QApplication>
#include "jsonfile.h"
#include "client.h"
#include "authorizationwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Client:: GetInstance()->Connect("127.0.0.1", 60000);
    //MainWindow w;
    //AssignmentCreationWindow w(QJsonDocumentFromJsonFile("./Assignments/A1.json"));
    AuthorizationWindow w;
    w.show();
    return a.exec();
}
