#ifndef FORMATPROCESS_H
#define FORMATPROCESS_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

namespace Ui {
class FormatProcess;
}

class FormatProcess : public QFrame
{
    Q_OBJECT

public:
    explicit FormatProcess(QWidget *parent = nullptr);
    ~FormatProcess();

    void Init(QStringList sourcePath,QString targetPath,QString format,QString suffixName,QString filePrefix,QString fileSuffix);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::FormatProcess *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* lf;

    QStringList sourcePath;
    int amount;

    QString targetPath;
    QString format;
    QString suffixName;

    QString filePrefix;
    QString fileSuffix;
};

#endif // FORMATPROCESS_H
