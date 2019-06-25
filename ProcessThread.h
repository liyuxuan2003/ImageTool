#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>
#include <QFile>
#include <QProcess>
#include <QDebug>

class ProcessThread : public QThread
{
    Q_OBJECT

public:
    ProcessThread(int code);

    enum State{Succeeded,Failed,SameName,Processing};

    void SetTask(QString command);

    void Init(float delay);

protected:
    virtual void run();

    int code;

    QString command;
    State state;

    bool isFirstTime;
    float delay;

public slots:
    void Finished();

signals:
    void TaskFinished(int threadCode,ProcessThread::State threadState);
};

#endif // PROCESSTHREAD_H
