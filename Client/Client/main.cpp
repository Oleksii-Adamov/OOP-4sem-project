#include "mainwindow.h"
#include "assignmentcreationwindow.h"
#include <QApplication>
#include "jsonfile.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Client:: GetInstance()->Connect("127.0.0.1", 60000);

    //AssignmentCreationWindow w(QJsonDocumentFromJsonFile("./Assignments/A1.json"));
    w.show();
    return a.exec();
}
