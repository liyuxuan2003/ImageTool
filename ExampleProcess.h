#ifndef EXAMPLEPROCESS_H
#define EXAMPLEPROCESS_H

#include <QFrame>
#include <QFile>
#include <QDateTime>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include "ProcessThread.h"

namespace Ui
{
    class ExampleProcess;
}

class ExampleProcess : public QFrame
{
    Q_OBJECT

public:
    explicit ExampleProcess(QWidget *parent = nullptr);
    ~ExampleProcess();

    void Init(QStringList sourcePath,QString targetPath);

    void AddTask(int threadCode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::ExampleProcess *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;
    LiFixedToLayout* lf;

    ProcessThread** thread;
    int threadAmount=4;

    QStringList sourcePath;
    QString targetPath;
    int amount;

    int frontIndex;
    int processedAmount;
    int succeedAmount;
    int failedAmount;
    int* processingIndex;

public slots:
    void TaskFinished(int threadCode,ProcessThread::State threadState);

private slots:
    void on_pushButtonBack_clicked();

signals:
    void ShowMenu();
};

#endif // EXAMPLEPROCESS_H
