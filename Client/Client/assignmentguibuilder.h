#ifndef ASSIGNMENTGUIBUILDER_H
#define ASSIGNMENTGUIBUILDER_H
#include "assignmentbuilder.h"
#include <QLayout>
#include <QSharedPointer>
#include <QPushButton>

/*!
 * \brief Adds GUI assignment elements to layout (Builder pattern - Concrete builder)
 */
class AssignmentGUIBuilder : public AssignmentBuilder
{
private:
    QLayout* layout_;
    QWidget* widget_;
    bool is_editable_;
public:
    AssignmentGUIBuilder();
    ~AssignmentGUIBuilder();
    void ProduceHeader(const std::string& header_text) const override;
    void ProduceTestAssignment(const TestAssignment& test_assignment,
                               const TestAssignment& test_assignment_compare_to = TestAssignment()) const override;
    void ProduceSubmitButton() const;
    /// cleares references to pointers
    void Reset();
    /*!
     * \brief set
     * \param input_layout QLayout where content will be placed
     * \param input_widget QWidget responsible for deleting created widgets
     */
    void Set(QLayout* input_layout, QWidget* input_widget, bool is_editable = false);
    bool IsEditable() const;
};

#endif // ASSIGNMENTGUIBUILDER_H
