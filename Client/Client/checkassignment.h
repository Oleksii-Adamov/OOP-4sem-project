#ifndef CHECKASSIGNMENT_H
#define CHECKASSIGNMENT_H

#include<QJsonDocument>

struct AutoScore
{
    long long score = 0;
    long long max_score = 0;
};

class CheckAssignment
{
private:
    long long one_choice_answer_weight_ = 1;
    long long multiple_choice_answer_weight_ = 1;
public:
    CheckAssignment();
    AutoScore GetScore(const QJsonDocument& json_document, const QJsonDocument& json_document_compare_to);
};

#endif // CHECKASSIGNMENT_H
