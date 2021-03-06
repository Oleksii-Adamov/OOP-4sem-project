#include "font.h"
QFont Font::TestHeaderFont()
{
    QFont header_font;
    header_font.setPointSize(40);
    return header_font;
}

QFont Font::TestQuestionFont()
{
    QFont question_font;
    question_font.setPointSize(20);
    return question_font;
}

QFont Font::TestAnswerFont()
{
    QFont answer_font;
    answer_font.setPointSize(15);
    return answer_font;
}

QFont Font::BigFont()
{
    QFont font;
    font.setPointSize(40);
    return font;
}

QFont Font::RegularListViewFont()
{
    QFont font;
    font.setPointSize(30);
    return font;
}

QFont Font::RegularFont()
{
    QFont font;
    font.setPointSize(15);
    return font;
}
