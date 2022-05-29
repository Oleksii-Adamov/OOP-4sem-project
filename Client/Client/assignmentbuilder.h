#ifndef ASSIGNMENTBUILDER_H
#define ASSIGNMENTBUILDER_H

#include "testassignment.h"

/*!
 * \brief Builder pattern - Abstract builder of assignments
 */

class AssignmentBuilder
{
public:
    virtual ~AssignmentBuilder(){}
    virtual void ProduceHeader(const std::string& header_text) const = 0;
    virtual void ProduceTestAssignment(const TestAssignment& test_assignment) const = 0;
//    virtual void ProduceCodeAssignment() const = 0;
//    virtual void ProduceFileAssignment()const = 0;
};

#endif // ASSIGNMENTBUILDER_H
