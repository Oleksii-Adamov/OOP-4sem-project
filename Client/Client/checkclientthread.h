#ifndef CHECKCLIENTTHREAD_H
#define CHECKCLIENTTHREAD_H

#include<QThread>

class CheckClientThread : public QThread
{
    Q_OBJECT
public:
    CheckClientThread(QObject* parent = nullptr)
        : QThread(parent)
    {}
signals:
        void TimeToUpdate();
private:
    void run() override {
        while(true) {
            QThread::msleep(50);
            emit TimeToUpdate();
        }
    }
};

#endif // CHECKCLIENTTHREAD_H
