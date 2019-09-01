#include "MakeIconProcess.h"
#include "ui_MakeIconProcess.h"

MakeIconProcess::MakeIconProcess(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MakeIconProcess)
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

MakeIconProcess::~MakeIconProcess()
{
    delete ui;
}

void MakeIconProcess::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void MakeIconProcess::Init(QStringList sourcePath,QString targetPath,bool* size)
{
    this->sourcePath=sourcePath;
    this->targetPath=targetPath;
    this->amount=sourcePath.size();

    this->size.clear();
    if(size[0]==true)
        this->size.push_back(16);
    if(size[1]==true)
        this->size.push_back(32);
    if(size[2]==true)
        this->size.push_back(48);
    if(size[3]==true)
        this->size.push_back(64);
    if(size[4]==true)
        this->size.push_back(128);
    if(size[5]==true)
        this->size.push_back(256);

    frontIndex=0;
    processedAmount=0;
    succeedAmount=0;
    failedAmount=0;

    ui->plainTextEdit->clear();

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t1+"  "+"图标制作开始！");
    ui->plainTextEdit->appendPlainText("\n");

    if(this->size.size()==0)
    {
        ui->plainTextEdit->appendPlainText(t1+"  "+"你没有选择任何一个输出比例！转换已终止！");
        ui->plainTextEdit->appendPlainText("\n");
        ui->labelInfo->hide();
        ui->labelProcessDone->show();
        ui->labelSummary->show();
        ui->labelBackInfo->show();
        ui->pushButtonBack->show();
        ui->pushButtonOpen->show();
        ui->labelProcessNum->setText("正在处理：0/0");
        ui->progressBar->setValue(0);
        ui->labelSummary->setText("ImageTool共处理了0张图像，成功0张，失败0张。");
        return;
    }

    QString t2=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t2+"  "+"ImageTool启用了"+QString::number(threadAmount)+"个线程处理本次转换...");
    ui->plainTextEdit->appendPlainText("\n");

    ui->labelInfo->show();
    ui->labelProcessDone->hide();
    ui->labelSummary->hide();
    ui->labelBackInfo->hide();
    ui->pushButtonBack->hide();
    ui->pushButtonOpen->hide();

    ui->labelProcessNum->setText("正在处理："+QString::number(processedAmount)+"/"+QString::number(amount*this->size.size()));
    ui->progressBar->setValue(0);

    for(int i=0;i<threadAmount;i++)
        thread[i]->Init(1000);

    for(int i=0;i<threadAmount;i++)
        AddTask(i);
}

void MakeIconProcess::TaskFinished(int threadCode,ProcessThread::State threadState)
{
    processedAmount++;
    ui->labelProcessNum->setText("正在处理："+QString::number(processedAmount)+"/"+QString::number(amount*size.size()));
    ui->progressBar->setValue(processedAmount*100/(amount*size.size()));

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");
    QString s=GetNameByPath(sourcePath[processingIndex[threadCode]/size.size()])+"-"+QString::number(size[processingIndex[threadCode]%size.size()])+".ico";

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

    if(processedAmount==amount*size.size())
    {
        ui->labelInfo->hide();
        ui->labelProcessDone->show();
        ui->labelSummary->show();
        ui->labelBackInfo->show();
        ui->pushButtonBack->show();
        ui->pushButtonOpen->show();
        ui->labelSummary->setText("ImageTool共处理了"+QString::number(amount*size.size())+"张图像，成功"+QString::number(succeedAmount)+"张，失败"+QString::number(failedAmount)+"张。");
        QString t2=QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->plainTextEdit->appendPlainText(t2+"  "+"全部图像处理完毕！");
        ui->plainTextEdit->appendPlainText("\n");
    }

    AddTask(threadCode);
}

void MakeIconProcess::AddTask(int threadCode)
{
    if(frontIndex>=amount*size.size())
        return;

    if(isHidden()==true)
        return;

    int imgId=frontIndex/size.size();
    int nowSize=size[frontIndex%size.size()];
    QString nowSizeStr=QString::number(nowSize);

    qDebug() << "Start1:" << imgId << " " << nowSize;

    QString source=sourcePath[imgId];
    QString target=targetPath+GetNameByPath(source)+"-"+nowSizeStr+".ico";

    processingIndex[threadCode]=frontIndex;

    if(QFile::exists(target)==true)
    {
        frontIndex++;
        TaskFinished(threadCode,ProcessThread::SameName);
    }
    else
    {
        QString command="magick convert "+source+" -resize "+nowSizeStr+"x"+nowSizeStr+" "+target;
        command.replace("/","\\");
        thread[threadCode]->SetTask(command);
        thread[threadCode]->start();
        frontIndex++;
    }
    qDebug() << "Start2:" << imgId << " " << nowSize;
}

void MakeIconProcess::on_pushButtonBack_clicked()
{
    emit(ShowMenu());
}

void MakeIconProcess::on_pushButtonOpen_clicked()
{
    QString url=targetPath;
    QDesktopServices::openUrl("file:"+url);
}
