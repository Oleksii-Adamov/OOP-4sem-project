#ifndef SUBMITASSIGNMENT_H
#define SUBMITASSIGNMENT_H

#include<QObject>
/*!
 * \brief Singelton Class that implements assignment submition
 *
 * Implements receiving signal (slot) from submit button.
 * Using Singelton pattern, because slots (getting a sender) only works with classes, and we don't need more than 1 instance of this object
 */
class SubmitAssignment : public QObject
{
    Q_OBJECT
public:
    static SubmitAssignment* GetInstance();
    SubmitAssignment(const SubmitAssignment&) = delete;
    SubmitAssignment& operator=(const SubmitAssignment& other) = delete;
private:
    SubmitAssignment();

public slots:

void OnSubmitButtonClicked();

};

#endif // SUBMITASSIGNMENT_H
