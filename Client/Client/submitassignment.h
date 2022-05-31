#ifndef SUBMITASSIGNMENT_H
#define SUBMITASSIGNMENT_H

#include<QObject>
// maybe Singelton
class SubmitAssignment : public QObject
{
    Q_OBJECT
public:
    SubmitAssignment();

public slots:

void OnSubmitButtonClicked();

};

#endif // SUBMITASSIGNMENT_H
