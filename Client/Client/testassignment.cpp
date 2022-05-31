#include "testassignment.h"

TestAssignment::TestAssignment()
{

}

TestAssignment::TestAssignment(const std::string& question, const std::vector<TestAnswer>& answers, TestType test_type, long long id)
    : question_(question), answers_(answers), test_type_(test_type), id_(id)
{

}

TestAssignment::TestAssignment(const std::string& question, long long id)
    : question_(question), id_(id)
{

}
void TestAssignment::set_question(const std::string& question)
{
  question_ = question;
}

std::string TestAssignment::get_question() const
{
    return question_;
}

void TestAssignment::set_answers(const std::vector<TestAnswer>& answers)
{
    answers_ = answers;
}

std::vector<TestAnswer> TestAssignment::get_answers() const
{
    return answers_;
}

void TestAssignment::set_test_type(TestType test_type)
{
    test_type_ = test_type;
}

TestType TestAssignment::get_test_type() const
{
    return test_type_;
}

void TestAssignment::set_id(long long id)
{
    id_ = id;
}
long long TestAssignment::get_id() const
{
    return id_;
}

void TestAssignment::PushAnswer(const TestAnswer& test_answer)
{
    answers_.push_back(test_answer);
}
