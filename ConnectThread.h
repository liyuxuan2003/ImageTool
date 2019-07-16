#ifndef CONNECTTHREAD_H
#define CONNECTTHREAD_H

#include <QThread>

#include <queue>

#include <LiLibrary/LiFileName.h>
#include <LiLibrary/LiReadImageInfo.h>

#include "ConnectMenu.h"

class ConnectThread : public QThread
{
    Q_OBJECT

public:
    ConnectThread();

    void Init(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat);

protected:
    virtual void run();

private:
    QStringList sourcePath;
    QString targetPath;
    int amount;

    ConnectMode::Mode mode;
    int maxSize;
    int matrixRow;
    int matrixColumn;

    QString outputFileName;
    QString outputFormat;

signals:
    void AppendLog(QString text);
    void ProcessDone(bool isSucceeded);
};

#endif // CONNECTTHREAD_H
