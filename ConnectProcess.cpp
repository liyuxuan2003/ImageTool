#include "ConnectProcess.h"
#include "ui_ConnectProcess.h"

ConnectProcess::ConnectProcess(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConnectProcess)
{
    ui->setupUi(this);

    connectThread=new ConnectThread();

    connect(connectThread,SIGNAL(AppendLog(QString)),this,SLOT(AppendLog(QString)));
    connect(connectThread,SIGNAL(ProcessDone(bool)),this,SLOT(ProcessDone(bool)));

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.5f,0.5f);
    lf=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelProcessNum);
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

ConnectProcess::~ConnectProcess()
{
    delete ui;
}

void ConnectProcess::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void ConnectProcess::Init(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat)
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

    ui->plainTextEdit->clear();

    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t1+"  "+"图像拼接开始！");
    ui->plainTextEdit->appendPlainText("\n");

    ui->labelInfo->show();
    ui->labelProcessDone->hide();
    ui->labelSummary->hide();
    ui->labelBackInfo->hide();
    ui->pushButtonBack->hide();
    ui->pushButtonOpen->hide();

    if(QFile::exists(targetPath+outputFileName+"."+outputFormat)==true)
    {
        AppendLog("目标文件夹下发现同名文件，已放弃拼接！");
        ProcessDone(false);
        return;
    }

    connectThread->Init(sourcePath,targetPath,mode,maxSize,matrixRow,matrixColumn,outputFileName,outputFormat);
    connectThread->start();
}

void ConnectProcess::AppendLog(QString text)
{
    QString t1=QDateTime::currentDateTime().toString("hh:mm:ss");;
    ui->plainTextEdit->appendPlainText(t1+"  "+text);
    ui->plainTextEdit->appendPlainText("\n");
}

void ConnectProcess::ProcessDone(bool isSucceeded)
{
    ui->labelInfo->hide();
    ui->labelProcessDone->show();
    ui->labelSummary->show();
    ui->labelBackInfo->show();
    ui->pushButtonBack->show();
    ui->pushButtonOpen->show();

    if(isSucceeded==true)
        ui->labelSummary->setText("ImageTool成功完成拼接！");
    if(isSucceeded==false)
        ui->labelSummary->setText("ImageTool无法完成拼接！拼接失败 :(");
}

void ConnectProcess::on_pushButtonBack_clicked()
{
    emit(ShowMenu());
}

void ConnectProcess::on_pushButtonOpen_clicked()
{
    QString url=targetPath;
    QDesktopServices::openUrl("file:"+url);
}
