#include "FormatProcess.h"
#include "ui_FormatProcess.h"

FormatProcess::FormatProcess(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FormatProcess)
{
    ui->setupUi(this);

    thread=new ProcessThread*[threadAmount];
    processingIndex=new int[threadAmount];
    for(int i=0;i<threadAmount;i++)
    {
        thread[i]=new ProcessThread(i);
        processingIndex[i]=-1;
        connect(thread[i],SIGNAL(TaskFinished(int,ProcessThread::State)),this,SLOT(TaskFinished(int,ProcessThread::State)));
    }

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.5f,0.5f);
    lf=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelProcessNum);
    l1->AddUnit(ui->progressBar);
    l1->AddUnit(ui->labelLogTitle);
    l1->AddUnit(ui->plainTextEdit);
    l1->AddUnit(ui->labelInfo);
    l1->AddUnit(ui->labelProcessDone);
    l1->AddUnit(ui->labelSummary);
    l1->AddUnit(ui->labelBackInfo);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonBack,ui->pushButtonOpen},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
}

FormatProcess::~FormatProcess()
{
    delete ui;
}

void FormatProcess::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void FormatProcess::Init(QStringList sourcePath, QString targetPath, QString format, QString suffixName, QString filePrefix, QString fileSuffix)
{
    this->sourcePath=sourcePath;
    this->amount=sourcePath.size();
    this->targetPath=targetPath;
    this->format=format;
    this->suffixName=suffixName;
    this->filePrefix=filePrefix;
    this->fileSuffix=fileSuffix;

    frontIndex=0;
    processedAmount=0;

    succeedAmount=0;
    failedAmount=0;

    ui->plainTextEdit->clear();

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t1+"  "+"转换开始！");
    ui->plainTextEdit->appendPlainText("\n");

    QString t2=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t2+"  "+"ImageTool启用了"+QString::number(threadAmount)+"个线程处理本次转换...");
    ui->plainTextEdit->appendPlainText("\n");

    ui->labelInfo->show();
    ui->labelProcessDone->hide();
    ui->labelSummary->hide();
    ui->labelBackInfo->hide();
    ui->pushButtonBack->hide();
    ui->pushButtonOpen->hide();

    ui->labelProcessNum->setText("正在转换："+QString::number(processedAmount)+"/"+QString::number(amount));
    ui->progressBar->setValue(0);

    for(int i=0;i<threadAmount;i++)
        thread[i]->Init(1000);

    for(int i=0;i<threadAmount;i++)
        AddTask(i);
}

void FormatProcess::TaskFinished(int threadCode,ProcessThread::State threadState)
{
    processedAmount++;
    ui->labelProcessNum->setText("正在转换："+QString::number(processedAmount)+"/"+QString::number(amount));
    ui->progressBar->setValue(processedAmount*100/amount);

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");
    QString sn=GetFullNameByPath(sourcePath[processingIndex[threadCode]]);
    QString tn=filePrefix+GetNameByPath(sourcePath[processingIndex[threadCode]])+fileSuffix+"."+suffixName;

    if(threadState==ProcessThread::Succeeded)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"线程"+QString::number(threadCode)+"：成功转换"+sn+"至目标文件夹！新文件名为"+tn+"。");
        succeedAmount++;
    }
    else if(threadState==ProcessThread::SameName)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"线程"+QString::number(threadCode)+"：未能转换"+sn+"，目标文件夹下有重名文件，已跳过该图像。");
        failedAmount++;
    }
    else if(threadState==ProcessThread::Failed)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"线程"+QString::number(threadCode)+"：未能转换"+sn+"，发生错误，已跳过该图像。");
        failedAmount++;
    }

    ui->plainTextEdit->appendPlainText("\n");

    if(processedAmount==amount)
    {
        ui->labelInfo->hide();
        ui->labelProcessDone->show();
        ui->labelSummary->show();
        ui->labelBackInfo->show();
        ui->pushButtonBack->show();
        ui->pushButtonOpen->show();
        ui->labelSummary->setText("ImageTool共处理了"+QString::number(amount)+"张图像，成功"+QString::number(succeedAmount)+"张，失败"+QString::number(failedAmount)+"张。");
        QString t2=QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->plainTextEdit->appendPlainText(t2+"  "+"全部图像处理完毕！");
        ui->plainTextEdit->appendPlainText("\n");
    }

    AddTask(threadCode);
}

void FormatProcess::AddTask(int threadCode)
{
    if(frontIndex>=amount)
        return;

    if(isHidden()==true)
        return;

    QString source=sourcePath[frontIndex];
    QString target=targetPath+filePrefix+GetNameByPath(sourcePath[frontIndex])+fileSuffix+"."+suffixName;

    processingIndex[threadCode]=frontIndex;

    if(QFile::exists(target)==true)
    {
        frontIndex++;
        TaskFinished(threadCode,ProcessThread::SameName);
    }
    else
    {
        QString command="magick convert \""+source+"\""+" "+"\""+format+":"+target+"\"";
        command.replace("/","\\");
        thread[threadCode]->SetTask(command);
        thread[threadCode]->start();
        frontIndex++;
    }
}

void FormatProcess::on_pushButtonBack_clicked()
{
    emit(ShowMenu());
}

void FormatProcess::on_pushButtonOpen_clicked()
{
    QString url=targetPath;
    QDesktopServices::openUrl("file:"+url);
}
