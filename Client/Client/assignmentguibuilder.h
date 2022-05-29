#ifndef ASSIGNMENTGUIBUILDER_H
#define ASSIGNMENTGUIBUILDER_H
#include "assignmentbuilder.h"
#include <QLayout>
#include <QSharedPointer>

/*!
 * \brief Adds GUI assignment elements to layout (Builder pattern - Concrete builder)
 */
class AssignmentGUIBuilder : AssignmentBuilder
{
private:
    QLayout* layout_;
    QWidget* widget_;
public:
    AssignmentGUIBuilder();
    ~AssignmentGUIBuilder();
    void ProduceHeader(const std::string& header_text) const override;
    void ProduceTestAssignment(const TestAssignment& test_assignment) const override;
    /// cleares references to pointers
    void Reset();
    /*!
     * \brief set
     * \param input_layout QLayout where content will be placed
     * \param input_widget QWidget responsible for deleting created widgets
     */
    void Set(QLayout* input_layout, QWidget* input_widget);
    /*!
     * \brief returns pointer to built QLayout and forget about it and about QWidget, now client is responsible for this memmory
     *
     * (pointers = nullptr)
     */
    //QSharedPointer<QLayout> get_layout();
};

#endif // ASSIGNMENTGUIBUILDER_H
