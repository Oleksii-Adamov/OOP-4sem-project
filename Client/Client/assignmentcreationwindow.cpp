#include "assignmentcreationwindow.h"
#include "ui_assignmentcreationwindow.h"
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include "addeditableheadercommand.h"

AssignmentCreationWindow::AssignmentCreationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssignmentCreationWindow)
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(ui->centralwidget);

    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
    assignment_container_ = new QWidget(this);
    scrollArea->setWidget(assignment_container_);
    assignment_layout_ = new QVBoxLayout(assignment_container_);

    QWidget* command_buttons_container = new QWidget(this);
    layout->addWidget(command_buttons_container);
    QHBoxLayout* command_buttons_layout = new QHBoxLayout(command_buttons_container);

    QPushButton* add_header_button = new QPushButton("Add Header", command_buttons_container);
    command_buttons_layout->addWidget(add_header_button);
    add_header_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    QAbstractButton::connect(
        add_header_button, &QPushButton::clicked,
        this, &AssignmentCreationWindow::OnAddHeaderButtonClicked
    );

    QPushButton* undo_button = new QPushButton("Undo (structure)", command_buttons_container);
    command_buttons_layout->addWidget(undo_button);
    undo_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
    QAbstractButton::connect(
        undo_button, &QPushButton::clicked,
        this, &AssignmentCreationWindow::OnUndoButtonClicked
    );
}

AssignmentCreationWindow::~AssignmentCreationWindow()
{
    delete ui;
}

void AssignmentCreationWindow::execute_command(Command* command)
{
    if (command->execute())
    {
        history_.push(command);
    }
}

void AssignmentCreationWindow::undo()
{
    Command* command = history_.pop();
    command->undo();
    delete command;
}

void AssignmentCreationWindow::AddHeader(const QString& text)
{
    execute_command(new AddEditableHeaderCommand(assignment_layout_, assignment_container_, text));
}

void AssignmentCreationWindow::OnAddHeaderButtonClicked()
{
    AddHeader("Header");
}

void AssignmentCreationWindow::OnUndoButtonClicked()
{
    undo();
}
