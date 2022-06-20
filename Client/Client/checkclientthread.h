#ifndef CHECKCLIENTTHREAD_H
#define CHECKCLIENTTHREAD_H

#include<QThread>

class CheckClientThread : public QThread
{
    Q_OBJECT
public:
    CheckClientThread();
signals:
        void TimeToUpdate();
private:
    void run() override {
        QThread::msleep(50);
        emit TimeToUpdate();
    }
};

#endif // CHECKCLIENTTHREAD_H
