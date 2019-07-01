#include <LiLibrary/LiReadImageInfo.h>

LiReadImageInfo::LiReadImageInfo()
{
    readWH=new QProcess();

    connect(readWH,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(ProcessWHDone(int,QProcess::ExitStatus)));
}

void LiReadImageInfo::ReadWidthAndHeight(QString file, int& width, int& height)
{
    QString command="magick identify -format %wx%h \""+file+"\"";
    command.replace("/","\\");
    readWH->start(command);
    readWH->waitForFinished();
    width=WHtemp_width;
    height=WHtemp_height;
}

void LiReadImageInfo::ProcessWHDone(int,QProcess::ExitStatus)
{
    QString output=readWH->readAllStandardOutput();
    WHtemp_width=output.left(output.indexOf("x")).toInt();
    WHtemp_height=output.right(output.length()-output.indexOf("x")-1).toInt();
}
