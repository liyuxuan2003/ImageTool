#ifndef FORMATPROCESS_H
#define FORMATPROCESS_H

#include <QFrame>
#include <QFile>
#include <QDateTime>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include "ProcessThread.h"

namespace Ui
{
    class FormatProcess;
}

class FormatProcess : public QFrame
{
    Q_OBJECT

public:
    explicit FormatProcess(QWidget *parent = nullptr);
    ~FormatProcess();

    void Init(QStringList sourcePath,QString targetPath,QString format,QString suffixName,QString filePrefix,QString fileSuffix);

    void AddTask(int threadCode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::FormatProcess *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* lf;

    ProcessThread** thread;
    int threadAmount=4;

    QStringList sourcePath;
    int amount;

    QString targetPath;
    QString format;
    QString suffixName;

    QString filePrefix;
    QString fileSuffix;

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

#endif // FORMATPROCESS_H
