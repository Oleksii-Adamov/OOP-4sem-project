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
    long long id_ = -1;
public:
    TestAssignment();
    TestAssignment(const std::string& question, const std::vector<TestAnswer>& answers, TestType test_type, long long id);
    TestAssignment(const std::string& question, long long id);
    void set_question(const std::string& question);
    std::string get_question() const;
    void set_answers(const std::vector<TestAnswer>& answers);
    std::vector<TestAnswer> get_answers() const;
    void set_test_type(TestType test_type);
    TestType get_test_type() const;
    void set_id(long long id);
    long long get_id() const;
    void PushAnswer(const TestAnswer& test_answer);
};

#endif // TESTASSIGNMENT_H
