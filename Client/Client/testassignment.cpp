#include "testassignment.h"

TestAssignment::TestAssignment()
{

}

TestAssignment::TestAssignment(const std::string& question, const std::vector<TestAnswer>& answers, TestType test_type)
    : question_(question), answers_(answers), test_type_(test_type)
{

}

TestAssignment::TestAssignment(const std::string& question)
    : question_(question)
{

}
void TestAssignment::set_question(const std::string& input)
{
  question_ = input;
}

std::string TestAssignment::get_question() const
{
    return question_;
}

void TestAssignment::set_answers(const std::vector<TestAnswer>& input)
{
    answers_ = input;
}

std::vector<TestAnswer> TestAssignment::get_answers() const
{
    return answers_;
}

void TestAssignment::set_test_type(TestType input)
{
    test_type_ = input;
}

TestType TestAssignment::get_test_type() const
{
    return test_type_;
}

void TestAssignment::PushAnswer(const TestAnswer& test_answer)
{
    answers_.push_back(test_answer);
}
