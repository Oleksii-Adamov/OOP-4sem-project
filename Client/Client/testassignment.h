#ifndef TESTASSIGNMENT_H
#define TESTASSIGNMENT_H

#include <string>
#include <vector>
#include "testanswer.h"

enum class TestType { one_choice, multiple_choice};

class TestAssignment
{
private:
    std::string question_;
    std::vector<TestAnswer> answers_;
    TestType test_type_;
public:
    TestAssignment();
    TestAssignment(const std::string& question, const std::vector<TestAnswer>& answers, TestType test_type);
    TestAssignment(const std::string& question);
    void set_question(const std::string& input);
    std::string get_question() const;
    void set_answers(const std::vector<TestAnswer>& input);
    std::vector<TestAnswer> get_answers() const;
    void set_test_type(TestType input);
    TestType get_test_type() const;
    void PushAnswer(const TestAnswer& test_answer);
};

#endif // TESTASSIGNMENT_H
