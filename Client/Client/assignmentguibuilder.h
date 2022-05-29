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
    QSharedPointer<QLayout> layout;
public:
    AssignmentGUIBuilder();
    ~AssignmentGUIBuilder();
    void ProduceHeader(const std::string& header_text) const override;
    void ProduceTestAssignment(const TestAssignment& test_assignment) const override;
    /// creates new instance of Qlayout
    void Reset();
    /*!
     * \brief returns pointer to built QLayout and forget about it, now client is responsible for this memmory
     *
     * (overrides pointer with new instance of QLayout)
     */
    QSharedPointer<QLayout> GetLayout();
};

#endif // ASSIGNMENTGUIBUILDER_H
