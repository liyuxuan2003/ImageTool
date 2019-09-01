#include "CompressMenu.h"
#include "ui_CompressMenu.h"

CompressMenu::CompressMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CompressMenu)
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

    l1->AddUnit(ui->labelCompressTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelOutputPath,ui->pushButtonOutputPath},2);

    l1->AddUnit();
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonPixel,ui->labelButtonPixel},2);
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonPercent,ui->labelButtonPercent},2);

    l1->AddUnit(new QWidget*[3]{ui->labelCompressPercent,ui->spinBoxPercent,ui->labelPercent},3);
    l1->AddUnit(ui->labelStateTitle);
    l1->AddUnit(ui->labelStateOriginal);
    l1->AddUnit(ui->labelStateCompress);

    l1->AddUnit(new QWidget*[3]{ui->labelWidth,ui->spinBoxWidth,ui->labelPxW},3);
    l1->AddUnit(new QWidget*[3]{ui->labelHeight,ui->spinBoxHeight,ui->labelPxH},3);
    l1->AddUnit(new QWidget*[2]{ui->labelRatioCrash,ui->comboBoxRatioCrash},2);

    l2->AddUnit(new QWidget*[2]{ui->pushButtonStart,ui->labelStart},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

CompressMenu::~CompressMenu()
{
    delete ui;
}

void CompressMenu::Init(QStringList sourcePath)
{
    this->sourcePath=sourcePath;
    this->targetPath=GetDirByPath(sourcePath[0]);

    ui->labelImageAmount->setText("图像数量："+QString::number(sourcePath.size()));
    ui->labelSourcePath->setText("图像源路径："+GetDirByPath(sourcePath[0]));

    ui->labelOutputPath->setText("输出路径："+targetPath);

    LiReadImageInfo* reader=new LiReadImageInfo();
    reader->ReadWidthAndHeight(sourcePath[0],exampleWidth,exampleHeight);

    ui->spinBoxWidth->setValue(300);
    ui->spinBoxHeight->setValue(200);
    ui->spinBoxPercent->setValue(50);

    compressPercent=50;
    compressWidth=300;
    compressHeight=200;

    ChangeToPixelMode();
}

void CompressMenu::resizeEvent(QResizeEvent * event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void CompressMenu::on_pushButtonOutputPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择输出文件夹",targetPath,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    targetPath=DirAddSlash(dir);
    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void CompressMenu::on_spinBoxPercent_valueChanged(int arg1)
{
    compressPercent=arg1;
    int compressWidth=exampleWidth*arg1/100;
    int compressHeight=exampleHeight*arg1/100;
    ui->labelStateOriginal->setText("原图的分辨率："+QString::number(exampleWidth)+" * "+QString::number(exampleHeight));
    ui->labelStateCompress->setText("压缩后分辨率："+QString::number(compressWidth)+" * "+QString::number(compressHeight));
}

void CompressMenu::ChangeToPixelMode()
{
    mode=CompressMode::PixelWidth;
    ui->comboBoxRatioCrash->setCurrentIndex(0);

    ui->labelCompressPercent->hide();
    ui->spinBoxPercent->hide();
    ui->labelPercent->hide();
    ui->labelStateTitle->hide();
    ui->labelStateOriginal->hide();
    ui->labelStateCompress->hide();

    ui->labelWidth->show();
    ui->spinBoxWidth->show();
    ui->labelPxW->show();
    ui->labelHeight->show();
    ui->spinBoxHeight->show();
    ui->labelPxH->show();
    ui->labelRatioCrash->show();
    ui->comboBoxRatioCrash->show();
}

void CompressMenu::ChangeToPercentMode()
{
    mode=CompressMode::Percent;

    ui->labelCompressPercent->show();
    ui->spinBoxPercent->show();
    ui->labelPercent->show();
    ui->labelStateTitle->show();
    ui->labelStateOriginal->show();
    ui->labelStateCompress->show();

    ui->labelWidth->hide();
    ui->spinBoxWidth->hide();
    ui->labelPxW->hide();
    ui->labelHeight->hide();
    ui->spinBoxHeight->hide();
    ui->labelPxH->hide();
    ui->labelRatioCrash->hide();
    ui->comboBoxRatioCrash->hide();
}

void CompressMenu::on_pushButtonPixel_clicked()
{
    ChangeToPixelMode();
}

void CompressMenu::on_pushButtonPercent_clicked()
{
    ChangeToPercentMode();
}

void CompressMenu::on_spinBoxWidth_valueChanged(int arg1)
{
    compressWidth=arg1;
}

void CompressMenu::on_spinBoxHeight_valueChanged(int arg1)
{
    compressHeight=arg1;
}

void CompressMenu::on_pushButtonStart_clicked()
{
    emit(ShowCompressProcess(sourcePath,targetPath,compressWidth,compressHeight,compressPercent,mode));
}

void CompressMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void CompressMenu::on_comboBoxRatioCrash_currentIndexChanged(const QString &arg1)
{
    if(arg1=="以水平边为基准")
        mode=CompressMode::PixelWidth;
    if(arg1=="以垂直边为基准")
        mode=CompressMode::PixelHeight;
    if(arg1=="忽略比例并强制变形")
        mode=CompressMode::PixelIgnore;
}
