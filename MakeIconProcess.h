#ifndef MAKEICONPROCESS_H
#define MAKEICONPROCESS_H

#include <QFrame>

#include <QDateTime>
#include <QDesktopServices>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include <vector>

#include "ProcessThread.h"

namespace Ui
{
    class MakeIconProcess;
}

class MakeIconProcess : public QFrame
{
    Q_OBJECT

public:
    explicit MakeIconProcess(QWidget *parent = nullptr);
    ~MakeIconProcess();

    void Init(QStringList sourcePath,QString targetPath,bool* size);

    void AddTask(int threadCode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MakeIconProcess *ui;

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

    std::vector<int> size;

public slots:
    void TaskFinished(int threadCode,ProcessThread::State threadState);

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonOpen_clicked();

signals:
    void ShowMenu();
};

#endif // MAKEICONPROCESS_H
