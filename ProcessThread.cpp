#include "ProcessThread.h"

ProcessThread::ProcessThread(int code)
{
    this->code=code;
    connect(this,SIGNAL(finished()),this,SLOT(Finished()));
}

void ProcessThread::Init(float delay)
{
    this->delay=delay;
    this->isFirstTime=true;
}

void ProcessThread::SetTask(QString command)
{
    this->command=command;
    this->state=Processing;
}

void ProcessThread::Finished()
{
    emit(TaskFinished(code,state));
}

void ProcessThread::run()
{
    if(isFirstTime==true)
    {
        isFirstTime=false;
        usleep(delay*code);
    }

    int result=QProcess::execute(command);
    if(result==0)
        state=Succeeded;
    else
        state=Failed;
}
