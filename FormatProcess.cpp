#include "FormatProcess.h"
#include "ui_FormatProcess.h"

FormatProcess::FormatProcess(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FormatProcess)
{
    ui->setupUi(this);

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
}
