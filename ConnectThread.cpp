#include "ConnectThread.h"

ConnectThread::ConnectThread()
{

}

void ConnectThread::Init(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat)
{
    this->sourcePath=sourcePath;
    this->targetPath=targetPath;
    this->amount=sourcePath.size();

    this->mode=mode;
    this->maxSize=maxSize;
    this->matrixRow=matrixRow;
    this->matrixColumn=matrixColumn;

    this->outputFileName=outputFileName;
    this->outputFormat=outputFormat;
}

void ConnectThread::run()
{
    int widthMax=-1;
    int heightMax=-1;
    int* arrWidth=new int[amount];
    int* arrHeight=new int[amount];

    LiReadImageInfo* reader=new LiReadImageInfo();

    for(int i=0;i<amount;i++)
    {
        emit(AppendLog("正在读取图像信息"+QString::number(i+1)+"/"+QString::number(amount)));
        reader->ReadWidthAndHeight(sourcePath[i],arrWidth[i],arrHeight[i]);
        if(arrWidth[i]>widthMax)
            widthMax=arrWidth[i];
        if(arrHeight[i]>heightMax)
            heightMax=arrHeight[i];
    }

    if(mode==ConnectMode::Horizontal || mode==ConnectMode::Vertical)
    {
        int resw=widthMax;
        int resh=heightMax;
        int widthSum=0;
        int heightSum=0;
        for(int i=0;i<amount;i++)
        {
            widthSum+=(arrWidth[i]*heightMax/arrHeight[i]);
            heightSum+=(arrHeight[i]*widthMax/arrWidth[i]);
        }

        if(heightSum>maxSize)
            resw=widthMax*maxSize/heightSum;
        if(widthSum>maxSize)
            resh=heightMax*maxSize/widthSum;

        QString strw=QString::number(resw);
        QString strh=QString::number(resh);

        emit(AppendLog("开始拼接图像，这可能需要一些时间，请耐心等待。"));
        QString appendCommand="";
        if(mode==ConnectMode::Horizontal)
            appendCommand="magick convert -geometry x"+strh+" +append";
        if(mode==ConnectMode::Vertical)
            appendCommand="magick convert -geometry "+strw+" -append";
        for(int i=0;i<amount;i++)
            appendCommand=appendCommand+" \""+sourcePath[i]+"\"";
        appendCommand=appendCommand+" \""+targetPath+outputFileName+"."+outputFormat+"\"";
        appendCommand.replace("/","\\");
        QProcess::execute(appendCommand);

        emit(AppendLog("图像拼接完成！"));
    }
    else if(mode==ConnectMode::Matrix)
    {
        if(amount==matrixRow*matrixColumn)
            emit(AppendLog("矩阵拼接开始！"));
        else if(amount>matrixRow*matrixColumn)
            emit(AppendLog("选定照片多于需要，程序已自动舍弃多余照片，矩阵拼接开始!"));
        else if(amount<matrixRow*matrixColumn)
        {
            emit(AppendLog("选定照片少于需要，但拼接仍然可以进行，矩阵拼接开始！"));
            matrixRow=((amount-1)/matrixColumn)+1;
        }

        int maxLengthRow=-1;
        QString temp=StandardDir(QStandardPaths::PicturesLocation)+"ImageToolTemp/";
        for(int a=0;a<matrixRow;a++)
        {
            int resw=widthMax;
            int resh=heightMax;
            int widthSum=0;
            int heightSum=0;
            for(int i=a*matrixColumn;i<(a+1)*matrixColumn;i++)
            {
                if(i>=amount)
                    break;
                widthSum+=(arrWidth[i]*heightMax/arrHeight[i]);
                heightSum+=(arrHeight[i]*widthMax/arrWidth[i]);
            }

            if(widthSum>maxLengthRow)
                maxLengthRow=widthSum;

            if(heightSum>maxSize)
                resw=widthMax*maxSize/heightSum;
            if(widthSum>maxSize)
                resh=heightMax*maxSize/widthSum;

            QString strw=QString::number(resw);
            QString strh=QString::number(resh);
            QString suffix="-Temp"+QString::number(a);

            emit(AppendLog("正在拼接图像的第"+QString::number(a+1)+"行，请耐心等待..."));

            QString appendCommand="magick convert -geometry x"+strh+" +append";
            for(int i=a*matrixColumn;i<(a+1)*matrixColumn;i++)
            {
                if(i>=amount)
                    break;
                appendCommand=appendCommand+" \""+sourcePath[i]+"\"";
            }
            appendCommand=appendCommand+" \""+temp+outputFileName+suffix+"."+outputFormat+"\"";
            appendCommand.replace("/","\\");
            QProcess::execute(appendCommand);
        }

        emit(AppendLog("正在拼接图像的各行，请不要关闭或退出程序！"));
        if(maxLengthRow>=maxSize)
            maxLengthRow=maxSize;
        QString appendRowCommand="magick convert -geometry "+QString::number(maxLengthRow)+" -append";
        for(int i=0;i<matrixRow;i++)
        {
            QString suffix="-Temp"+QString::number(i);
            appendRowCommand=appendRowCommand+" \""+temp+outputFileName+suffix+"."+outputFormat+"\"";
        }

        QString sctName=temp+outputFileName+"-SecondTemp"+"."+outputFormat;
        QString finalName=targetPath+outputFileName+"."+outputFormat;

        appendRowCommand=appendRowCommand+" \""+sctName+"\"";
        appendRowCommand.replace("/","\\");
        QProcess::execute(appendRowCommand);

        emit(AppendLog("正在进行图像输出，这是最后的步骤，请耐心等待！"));
        QString finalCompressCommand="magick convert \""+sctName+"\" -resize x"+QString::number(maxSize)+"> \""+finalName+"\"";
        finalCompressCommand.replace("/","\\");
        QProcess::execute(finalCompressCommand);

        emit(AppendLog("图像拼接完成！"));
    }

    emit(ProcessDone(true));
}
