#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "assignmentguibuilder.h"
#include "assignmentguidirector.h"
#include "jsonfile.h"
#include "editablelabel.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout(ui->centralwidget);

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    QWidget* assignment_container = new QWidget(this);
    scrollArea->setWidget(assignment_container);

    QVBoxLayout* assignment_layout = new QVBoxLayout(assignment_container);

    AssignmentGUIBuilder assignment_GUI_builder;
    assignment_GUI_builder.Set(assignment_layout, assignment_container);
    AssignmentGUIDirector assignment_GUI_director;
    assignment_GUI_director.set_builder(&assignment_GUI_builder);
    assignment_GUI_director.BuildFromJSON(QJsonDocumentFromJsonFile("../../assinment_json_from_server_to_student_example.json"));
    /*assignment_GUI_builder.ProduceHeader("Header1");
    std::vector<TestAnswer> test_answers1 = {TestAnswer("4", IsAnswerCorrect::inaccessible),
                                             TestAnswer("5", IsAnswerCorrect::inaccessible)};
    TestAssignment test_assignment1("What is 2+2 ?", test_answers1, TestType::one_choice);
    assignment_GUI_builder.ProduceTestAssignment(test_assignment1);
    TestAssignment test_assignment2("What is 2+2 ?", test_answers1, TestType::one_choice);
    assignment_GUI_builder.ProduceTestAssignment(test_assignment2);
    assignment_GUI_builder.ProduceHeader("Header2");
    assignment_GUI_builder.ProduceSubmitButton();
    assignment_GUI_builder.Reset();*/
    EditableLabel* editable_label = new EditableLabel("Text", this);
    assignment_layout->addWidget(editable_label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

