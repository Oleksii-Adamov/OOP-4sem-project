#ifndef TESTANSWER_H
#define TESTANSWER_H
#include <string>

enum class IsAnswerCorrect { correct, wrong, inaccessible};
/*!
 * \brief
 *
 * somewhat inefficient memory usage becaise incaccesible is_answer_correct has no reason to store
 * could do this withot this field, and make derived with this field. But that will add complexity to code.
 * In common use cases there won't be a lot of tests, and this object won't be stored for a long time,
 * so no premature optimization
 */
class TestAnswer
{
private:
    std::string answer_text;
    IsAnswerCorrect is_answer_correct;
public:
    TestAnswer();
    TestAnswer(std::string answer_text, IsAnswerCorrect is_answer_correct = IsAnswerCorrect::inaccessible);
    void set_answer_text(const std::string& input);
    std::string get_answer_text() const;
    void set_is_answer_correct(const IsAnswerCorrect input);
    IsAnswerCorrect get_is_answer_correct() const;
};

#endif // TESTANSWER_H
