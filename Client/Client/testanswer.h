#ifndef TESTANSWER_H
#define TESTANSWER_H
#include <string>

enum class IsAnswerCorrect { correct, wrong, inaccessible};

class TestAnswer
{
private:
    std::string answer_text;
    IsAnswerCorrect is_answer_correct;
public:
    TestAnswer();
    TestAnswer(std::string answer_text, IsAnswerCorrect is_answer_correct);
    void set_answer_text(const std::string& input);
    std::string get_answer_text() const;
    void set_is_answer_correct(const IsAnswerCorrect input);
    IsAnswerCorrect get_is_answer_correct() const;
};

#endif // TESTANSWER_H
