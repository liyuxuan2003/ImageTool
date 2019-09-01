#include "ExampleMenu.h"
#include "ui_ExampleMenu.h"

ExampleMenu::ExampleMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExampleMenu)
{
    ui->setupUi(this);

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

    l2->AddUnit(new QWidget*[2]{ui->pushButtonStart,ui->labelStart},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

ExampleMenu::~ExampleMenu()
{
    delete ui;
}

void ExampleMenu::Init(QStringList sourcePath)
{
    this->sourcePath=sourcePath;
    this->targetPath=GetDirByPath(sourcePath[0]);

    ui->labelImageAmount->setText("图像数量："+QString::number(sourcePath.size()));
    ui->labelSourcePath->setText("图像源路径："+GetDirByPath(sourcePath[0]));

    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void ExampleMenu::resizeEvent(QResizeEvent * event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void ExampleMenu::on_pushButtonOutputPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择输出文件夹",targetPath,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    targetPath=DirAddSlash(dir);
    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void ExampleMenu::on_pushButtonStart_clicked()
{
    emit(ShowExampleProcess(sourcePath,targetPath));
}

void ExampleMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
