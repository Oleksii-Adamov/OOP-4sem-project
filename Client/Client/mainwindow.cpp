#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include "assignmentguibuilder.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(ui->centralwidget);
    AssignmentGUIBuilder assignment_GUI_builder;
    assignment_GUI_builder.Set(layout, this);
    assignment_GUI_builder.ProduceHeader("Header1");
    assignment_GUI_builder.ProduceHeader("Header2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

