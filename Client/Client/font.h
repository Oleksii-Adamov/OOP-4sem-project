#ifndef FONT_H
#define FONT_H

#include<QFont>

class Font
{
public:
    Font() = delete;
    static QFont TestHeaderFont();
    static QFont TestQuestionFont();
    static QFont TestAnswerFont();
    static QFont BigFont();
    static QFont RegularListViewFont();
    static QFont RegularFont();
};

#endif // FONT_H
