#include "ExampleProcess.h"
#include "ui_ExampleProcess.h"

ExampleProcess::ExampleProcess(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExampleProcess)
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
    l1->AddUnit(ui->pushButtonBack);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
}

ExampleProcess::~ExampleProcess()
{
    delete ui;
}

void ExampleProcess::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void ExampleProcess::Init(QStringList sourcePath,QString targetPath)
{
    this->sourcePath=sourcePath;
    this->targetPath=targetPath;
    this->amount=sourcePath.size();

    // Your Init Content
    // Your Init Content

    frontIndex=0;
    processedAmount=0;
    succeedAmount=0;
    failedAmount=0;

    ui->plainTextEdit->clear();

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t1+"  "+"图像【动词】开始！");
    ui->plainTextEdit->appendPlainText("\n");

    QString t2=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t2+"  "+"ImageTool启用了"+QString::number(threadAmount)+"个线程处理本次【动词】...");
    ui->plainTextEdit->appendPlainText("\n");

    ui->labelInfo->show();
    ui->labelProcessDone->hide();
    ui->labelSummary->hide();
    ui->labelBackInfo->hide();
    ui->pushButtonBack->hide();

    ui->labelProcessNum->setText("正在处理："+QString::number(processedAmount)+"/"+QString::number(amount));
    ui->progressBar->setValue(0);

    for(int i=0;i<threadAmount;i++)
        thread[i]->Init(1000);

    for(int i=0;i<threadAmount;i++)
        AddTask(i);
}

void ExampleProcess::TaskFinished(int threadCode,ProcessThread::State threadState)
{
    processedAmount++;
    ui->labelProcessNum->setText("正在处理："+QString::number(processedAmount)+"/"+QString::number(amount));
    ui->progressBar->setValue(processedAmount*100/amount);

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");
    QString s=GetFullNameByPath(sourcePath[processingIndex[threadCode]]);

    if(threadState==ProcessThread::Succeeded)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"线程"+QString::number(threadCode)+"：成功处理"+s+"至目标文件夹！");
        succeedAmount++;
    }
    else if(threadState==ProcessThread::SameName)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"线程"+QString::number(threadCode)+"：未能处理"+s+"，目标文件夹下有重名文件，已跳过该图像。");
        failedAmount++;
    }
    else if(threadState==ProcessThread::Failed)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"线程"+QString::number(threadCode)+"：未能处理"+s+"，发生错误，已跳过该图像。");
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
        ui->labelSummary->setText("ImageTool共处理了"+QString::number(amount)+"张图像，成功"+QString::number(succeedAmount)+"张，失败"+QString::number(failedAmount)+"张。");
        QString t2=QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->plainTextEdit->appendPlainText(t2+"  "+"全部图像处理完毕！");
        ui->plainTextEdit->appendPlainText("\n");
    }

    AddTask(threadCode);
}

void ExampleProcess::AddTask(int threadCode)
{
    if(frontIndex>=amount)
        return;

    if(isHidden()==true)
        return;

    QString source=sourcePath[frontIndex];
    QString target=targetPath+GetFullNameByPath(source);

    processingIndex[threadCode]=frontIndex;

    if(QFile::exists(target)==true)
    {
        frontIndex++;
        TaskFinished(threadCode,ProcessThread::SameName);
    }
    else
    {
        QString command="Your command";
        command.replace("/","\\");
        thread[threadCode]->SetTask(command);
        thread[threadCode]->start();
        frontIndex++;
    }
}

void ExampleProcess::on_pushButtonBack_clicked()
{
    emit(ShowMenu());
}
