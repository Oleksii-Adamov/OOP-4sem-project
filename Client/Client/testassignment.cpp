#include "testassignment.h"

TestAssignment::TestAssignment()
{

}

TestAssignment::TestAssignment(std::string question, const std::vector<TestAnswer>& answers, TestType test_type)
    : question(question), answers(answers), test_type(test_type)
{

}
void TestAssignment::set_question(const std::string& input)
{
  question = input;
}

std::string TestAssignment::get_question() const
{
    return question;
}

void TestAssignment::set_answers(const std::vector<TestAnswer>& input)
{
    answers = input;
}

std::vector<TestAnswer> TestAssignment::get_answers() const
{
    return answers;
}

void TestAssignment::set_test_type(TestType input)
{
    test_type = input;
}

TestType TestAssignment::get_test_type() const
{
    return test_type;
}
