#ifndef COMPRESSPROCESS_H
#define COMPRESSPROCESS_H

#include <QFrame>

#include <QDateTime>
#include <QDesktopServices>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include <LiLibrary/LiReadImageInfo.h>

#include "ProcessThread.h"

#include "CompressMenu.h"

namespace Ui
{
    class CompressProcess;
}

class CompressProcess : public QFrame
{
    Q_OBJECT

public:
    explicit CompressProcess(QWidget *parent = nullptr);
    ~CompressProcess();

    void Init(QStringList sourcePath,QString targetPath,int compressWidth,int compressHeight,int compressPercent,CompressMode::Mode mode);

    void AddTask(int threadCode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::CompressProcess *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;

    LiFixedToLayout* lf;

    LiReadImageInfo* reader;

    ProcessThread** thread;
    int threadAmount=4;

    int frontIndex;
    int processedAmount;

    int succeedAmount;
    int failedAmount;

    int* processingIndex;

    QStringList sourcePath;
    QString targetPath;
    int amount;
    int compressWidth;
    int compressHeight;
    int compressPercent;
    CompressMode::Mode mode;

public slots:
    void TaskFinished(int threadCode,ProcessThread::State threadState);

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonOpen_clicked();

signals:
    void ShowMenu();
};

#endif // COMPRESSPROCESS_H
