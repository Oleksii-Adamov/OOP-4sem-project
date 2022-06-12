#include "mainwindow.h"
#include "assignmentcreationwindow.h"
#include <QApplication>
#include "jsonfile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //AssignmentCreationWindow w(QJsonDocumentFromJsonFile("./Assignments/A1.json"));
    w.show();
    return a.exec();
}
