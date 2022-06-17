#include "testanswer.h"

TestAnswer::TestAnswer()
{

}

TestAnswer::TestAnswer(std::string answer_text, bool is_answer_checked)
    : answer_text(answer_text), is_checked(is_answer_checked)
{

}

void TestAnswer::set_answer_text(const std::string& input)
{
    answer_text = input;
}

std::string TestAnswer::get_answer_text() const
{
    return answer_text;
}

void TestAnswer::set_is_answer_checked(const bool input)
{
    is_checked = input;
}

bool TestAnswer::get_is_answer_checked() const
{
    return is_checked;
}
