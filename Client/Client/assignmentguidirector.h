#ifndef ASSIGNMENTGUIDIRECTOR_H
#define ASSIGNMENTGUIDIRECTOR_H

#include "assignmentguibuilder.h"
#include <QJsonDocument>

/*!
 * \brief Director of AssignmentBuilder that can build assignment from JSON (Builder pattern - Director of concrete builder)
 */
class AssignmentGUIDirector
{
private:
    AssignmentGUIBuilder* builder_;
public:
    AssignmentGUIDirector();
    void set_builder(AssignmentGUIBuilder* builder);
    void BuildFromJSON(const QJsonDocument& json_document);
};

#endif // ASSIGNMENTGUIDIRECTOR_H
