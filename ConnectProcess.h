#ifndef CONNECTPROCESS_H
#define CONNECTPROCESS_H

#include <QFrame>

#include <QFile>
#include <QDateTime>
#include <QDesktopServices>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include "ConnectMenu.h"
#include "ConnectThread.h"

namespace Ui
{
    class ConnectProcess;
}

class ConnectProcess : public QFrame
{
    Q_OBJECT

public:
    explicit ConnectProcess(QWidget *parent = nullptr);
    ~ConnectProcess();

    void Init(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat);

    void AddTask(int threadCode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::ConnectProcess *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;
    LiFixedToLayout* lf;

    ConnectThread* connectThread;

    QStringList sourcePath;
    QString targetPath;
    int amount;

    ConnectMode::Mode mode;
    int maxSize;
    int matrixRow;
    int matrixColumn;

    QString outputFileName;
    QString outputFormat;

public slots:
    void AppendLog(QString text);
    void ProcessDone(bool isSucceeded);

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonOpen_clicked();

signals:
    void ShowMenu();
};

#endif // CONNECTPROCESS_H
