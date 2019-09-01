#ifndef CROPPROCESS_H
#define CROPPROCESS_H

#include <QFrame>

#include <QFile>
#include <QDateTime>
#include <QDesktopServices>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include "ProcessThread.h"
#include "CropMenu.h"

namespace Ui
{
    class CropProcess;
}

class CropProcess : public QFrame
{
    Q_OBJECT

public:
    explicit CropProcess(QWidget *parent = nullptr);
    ~CropProcess();

    void Init(QStringList sourcePath,QString targetPath,int valH,int valV,int valMH,int valMV,CropMenu::CropMode mode);

    void AddTask(int threadCode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::CropProcess *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;

    LiFixedToLayout* lf;

    ProcessThread** thread;
    int threadAmount=4;

    QStringList sourcePath;
    int amount;

    QString targetPath;

    int valH;
    int valV;
    int valMH;
    int valMV;

    CropMenu::CropMode mode;

    int frontIndex;
    int processedAmount;

    int succeedAmount;
    int failedAmount;

    int* processingIndex;

    int tmpWidth;
    int tmpHeight;
    QProcess* process;

public slots:
    void TaskFinished(int threadCode,ProcessThread::State threadState);

private slots:
    void ProcessDone(int exitCode, QProcess::ExitStatus exitStatus);

    void on_pushButtonBack_clicked();

    void on_pushButtonOpen_clicked();

signals:
    void ShowMenu();
};

#endif // CROPPROCESS_H
