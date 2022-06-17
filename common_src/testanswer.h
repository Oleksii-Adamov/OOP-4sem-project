#ifndef TESTANSWER_H
#define TESTANSWER_H
#include <string>

enum class IsAnswerChecked {yes, no, inaccessible};
/*!
 * \brief
 *
 * somewhat inefficient memory usage becaise incaccesible is_checked has no reason to store.
 * Could do this withot this field, and make derived with this field. But that will add complexity to code.
 * In common use cases there won't be a lot of tests, and this object won't be stored for a long time,
 * so no premature optimization.
 */
class TestAnswer
{
private:
    std::string answer_text = "";
    IsAnswerChecked is_checked = IsAnswerChecked::inaccessible;
public:
    TestAnswer();
    TestAnswer(std::string answer_text, IsAnswerChecked is_answer_checked = IsAnswerChecked::inaccessible);
    void set_answer_text(const std::string& input);
    std::string get_answer_text() const;
    void set_is_answer_checked(const IsAnswerChecked input);
    IsAnswerChecked get_is_answer_checked() const;
};

#endif // TESTANSWER_H
