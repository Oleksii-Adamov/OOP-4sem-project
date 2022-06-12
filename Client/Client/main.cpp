#include "mainwindow.h"
#include "assignmentcreationwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    AssignmentCreationWindow w;
    w.show();
    return a.exec();
}
