#ifndef ASSIGNMENTGUIDIRECTOR_H
#define ASSIGNMENTGUIDIRECTOR_H

#include "assignmentguibuilder.h"
#include <QJsonDocument>

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
