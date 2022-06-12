#include "testanswer.h"

TestAnswer::TestAnswer()
{

}

TestAnswer::TestAnswer(std::string answer_text, IsAnswerCorrect is_answer_correct)
    : answer_text(answer_text), is_answer_correct(is_answer_correct)
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

void TestAnswer::set_is_answer_correct(const IsAnswerCorrect input)
{
    is_answer_correct = input;
}

IsAnswerCorrect TestAnswer::get_is_answer_correct() const
{
    return is_answer_correct;
}
