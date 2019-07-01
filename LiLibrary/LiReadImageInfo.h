#ifndef LIREADIMAGEINFO_H
#define LIREADIMAGEINFO_H

#include <QObject>
#include <QProcess>

class LiReadImageInfo: public QObject
{
    Q_OBJECT

public:
    LiReadImageInfo();

    void ReadWidthAndHeight(QString file,int& width,int& height);

private:
    QProcess* readWH;
    int WHtemp_width;
    int WHtemp_height;

private slots:
    void ProcessWHDone(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // LIREADIMAGEINFO_H
