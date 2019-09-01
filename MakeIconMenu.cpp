#include "MakeIconMenu.h"
#include "ui_MakeIconMenu.h"

MakeIconMenu::MakeIconMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MakeIconMenu)
{
    ui->setupUi(this);

    size=new bool[6]{false};

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.5f,0.4f);
    l2=new LiEasyLayout(0,width(),height(),LiEasyLayout::right,0.0f);
    lf=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelInfoTitle);
    l1->AddUnit(ui->labelSourcePath);
    l1->AddUnit(ui->labelImageAmount);
    l1->AddUnit(ui->line1);

    l1->AddUnit(ui->labelOutputTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelOutputPath,ui->pushButtonOutputPath},2);

    l1->AddUnit(ui->labelSizeTitle);

    l1->AddUnit(ui->checkBox016);
    l1->AddUnit(ui->checkBox032);
    l1->AddUnit(ui->checkBox048);
    l1->AddUnit(ui->checkBox064);
    l1->AddUnit(ui->checkBox128);
    l1->AddUnit(ui->checkBox256);

    l2->AddUnit(new QWidget*[2]{ui->pushButtonStart,ui->labelStart},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

MakeIconMenu::~MakeIconMenu()
{
    delete ui;
}

void MakeIconMenu::Init(QStringList sourcePath)
{
    this->sourcePath=sourcePath;
    this->targetPath=GetDirByPath(sourcePath[0]);

    ui->labelImageAmount->setText("图像数量："+QString::number(sourcePath.size()));
    ui->labelSourcePath->setText("图像源路径："+GetDirByPath(sourcePath[0]));

    ui->labelOutputPath->setText("输出路径："+targetPath);

    ui->checkBox016->setCheckState(Qt::Unchecked);
    ui->checkBox032->setCheckState(Qt::Unchecked);
    ui->checkBox048->setCheckState(Qt::Unchecked);
    ui->checkBox064->setCheckState(Qt::Unchecked);
    ui->checkBox128->setCheckState(Qt::Unchecked);
    ui->checkBox256->setCheckState(Qt::Unchecked);

    for(int i=0;i<5;i++)
        size[i]=false;
}

void MakeIconMenu::resizeEvent(QResizeEvent * event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void MakeIconMenu::on_pushButtonOutputPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择输出文件夹",targetPath,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    targetPath=DirAddSlash(dir);
    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void MakeIconMenu::on_pushButtonStart_clicked()
{
    emit(ShowMakeIconProcess(sourcePath,targetPath,size));
}

void MakeIconMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void MakeIconMenu::on_checkBox016_stateChanged(int arg1)
{
    SetSize(arg1,0);
}

void MakeIconMenu::on_checkBox032_stateChanged(int arg1)
{
    SetSize(arg1,1);
}

void MakeIconMenu::on_checkBox048_stateChanged(int arg1)
{
    SetSize(arg1,2);
}

void MakeIconMenu::on_checkBox064_stateChanged(int arg1)
{
    SetSize(arg1,3);
}

void MakeIconMenu::on_checkBox128_stateChanged(int arg1)
{
    SetSize(arg1,4);
}

void MakeIconMenu::on_checkBox256_stateChanged(int arg1)
{
    SetSize(arg1,5);
}

void MakeIconMenu::SetSize(int state,int sizeId)
{
    bool isNeedSize=false;
    if(state==Qt::Unchecked)
        isNeedSize=false;
    if(state==Qt::Checked)
        isNeedSize=true;
    size[sizeId]=isNeedSize;
}






