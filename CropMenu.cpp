#include "CropMenu.h"
#include "ui_CropMenu.h"

CropMenu::CropMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CropMenu)
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
    l1->AddUnit(ui->labelCropTitle);
    l1->AddUnit(ui->labelOutputPath);
    l1->AddUnit(ui->pushButtonOutputPath);

    l1->AddUnit();
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonCropPixel,ui->labelCropPixel},2);
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonCropPercentH,ui->labelCropPercentH},2);
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonCropPercentV,ui->labelCropPercentV},2);

    l1->AddUnit(new QWidget*[3]{ui->labelCropH,ui->spinBoxH,ui->labelUnitH},3);
    l1->AddUnit(new QWidget*[3]{ui->labelCropV,ui->spinBoxV,ui->labelUnitV},3);
    l1->AddUnit(ui->checkBoxRatio);
    l1->AddUnit(new QWidget*[4]{ui->labelCropRatio,ui->spinBoxWidth,ui->labelColon,ui->spinBoxHeight},4);

    l1->AddUnit(new QWidget*[3]{ui->labelCropMH,ui->spinBoxMH,ui->labelUnitMH},3);
    l1->AddUnit(new QWidget*[3]{ui->labelCropMV,ui->spinBoxMV,ui->labelUnitMV},3);

    l2->AddUnit(new QWidget*[2]{ui->pushButtonStart,ui->labelStart},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

CropMenu::~CropMenu()
{
    delete ui;
}

void CropMenu::Init(QStringList sourcePath)
{
    amount=sourcePath.size();
    this->sourcePath=sourcePath;
    this->targetPath=StandardDir(QStandardPaths::PicturesLocation);

    cropMode=PixelMode;
    valH=300;
    valV=200;
    valMH=0;
    valMV=0;
    isRatio=true;
    ratioWidth=3;
    ratioHeight=2;

    ChangeUnit();
    SetUiWithValue();

    ui->checkBoxRatio->setCheckState(Qt::Checked);
}

void CropMenu::resizeEvent(QResizeEvent * event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void CropMenu::on_pushButtonOutputPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择输出文件夹",targetPath,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    targetPath=DirAddSlash(dir);
    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void CropMenu::ChangeUnit()
{
    ChangeUnit(cropMode);
}

void CropMenu::ChangeUnit(CropMode mode)
{
    cropMode=mode;
    QString unitName="";
    if(cropMode==PixelMode)
    {
        unitName="px";
        ui->spinBoxH->setRange(1,100000);
        ui->spinBoxH->setSingleStep(100);
        ui->spinBoxV->setRange(1,100000);
        ui->spinBoxV->setSingleStep(100);
        ui->spinBoxMH->setRange(0,100000);
        ui->spinBoxMH->setSingleStep(10);
        ui->spinBoxMV->setRange(0,100000);
        ui->spinBoxMV->setSingleStep(10);
    }
    else
    {
        ui->spinBoxH->setRange(1,100);
        ui->spinBoxH->setSingleStep(1);
        ui->spinBoxV->setRange(1,100);
        ui->spinBoxV->setSingleStep(1);
        ui->spinBoxMH->setRange(0,100);
        ui->spinBoxMH->setSingleStep(1);
        ui->spinBoxMV->setRange(0,100);
        ui->spinBoxMV->setSingleStep(1);
    }

    if(cropMode==PercentModeH)
        unitName="%H";
    if(cropMode==PercentModeV)
        unitName="%V";

    if(cropMode!=PercentMode)
    {
        ui->labelUnitH->setText(unitName);
        ui->labelUnitV->setText(unitName);
        ui->labelUnitMH->setText(unitName);
        ui->labelUnitMV->setText(unitName);
    }
    else if(cropMode==PercentMode)
    {
        ui->labelUnitH->setText("%H");
        ui->labelUnitV->setText("%V");
        ui->labelUnitMH->setText("%H");
        ui->labelUnitMV->setText("%V");
    }
}

void CropMenu::SetUiWithValue()
{
    SetUiWithValue(valH,valV,valMH,valMV);
}

void CropMenu::SetUiWithValue(int h,int v,int mh,int mv)
{
    valH=h;
    valV=v;
    valMH=mh;
    valMV=mv;

    ui->spinBoxH->blockSignals(true);
    ui->spinBoxV->blockSignals(true);
    ui->spinBoxMH->blockSignals(true);
    ui->spinBoxMV->blockSignals(true);
    ui->spinBoxWidth->blockSignals(true);
    ui->spinBoxHeight->blockSignals(true);

    ui->spinBoxH->setValue(valH);
    ui->spinBoxV->setValue(valV);
    ui->spinBoxMH->setValue(valMH);
    ui->spinBoxMV->setValue(valMV);
    ui->spinBoxWidth->setValue(ratioWidth);
    ui->spinBoxHeight->setValue(ratioHeight);

    ui->spinBoxH->blockSignals(false);
    ui->spinBoxV->blockSignals(false);
    ui->spinBoxMH->blockSignals(false);
    ui->spinBoxMV->blockSignals(false);
    ui->spinBoxWidth->blockSignals(false);
    ui->spinBoxHeight->blockSignals(false);
}

void CropMenu::on_pushButtonCropPixel_clicked()
{
    if(cropMode==PixelMode)
        return;
    ChangeUnit(PixelMode);
    SetUiWithValue(300,300/ratioWidth*ratioHeight,0,0);
}

void CropMenu::on_pushButtonCropPercentH_clicked()
{
    if(cropMode==PercentModeH)
        return;
    ChangeUnit(PercentModeH);
    SetUiWithValue(60,60/ratioWidth*ratioHeight,0,0);
}

void CropMenu::on_pushButtonCropPercentV_clicked()
{
    if(cropMode==PercentModeV)
        return;
    ChangeUnit(PercentModeV);
    SetUiWithValue(60*ratioHeight/ratioWidth,60,0,0);
}

void CropMenu::on_pushButtonCropPercent_clicked()
{
    if(cropMode==PercentMode)
        return;
    ChangeUnit(PercentMode);
    SetUiWithValue(50,50,0,0);

    ui->checkBoxRatio->blockSignals(true);
    ui->checkBoxRatio->setCheckState(Qt::Unchecked);
    ui->checkBoxRatio->blockSignals(false);

    on_checkBoxRatio_stateChanged(Qt::Unchecked);
    ui->checkBoxRatio->setDisabled(true);
}

void CropMenu::on_spinBoxMH_valueChanged(int arg1)
{
    valMH=arg1;
}

void CropMenu::on_spinBoxMV_valueChanged(int arg1)
{
    valMV=arg1;
}

void CropMenu::on_checkBoxRatio_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
        isRatio=true;
        ui->spinBoxWidth->setEnabled(true);
        ui->spinBoxHeight->setEnabled(true);
        valV=valH/ratioWidth*ratioHeight;
        SetUiWithValue();
    }
    if(arg1==Qt::Unchecked)
    {
        isRatio=false;
        ui->spinBoxWidth->setEnabled(false);
        ui->spinBoxHeight->setEnabled(false);
    }
}

void CropMenu::on_spinBoxWidth_valueChanged(int arg1)
{
    ratioWidth=arg1;
    valV=valH/ratioWidth*ratioHeight;
    SetUiWithValue();
}

void CropMenu::on_spinBoxHeight_valueChanged(int arg1)
{
    ratioHeight=arg1;
    valV=valH/ratioWidth*ratioHeight;
    SetUiWithValue();
}

void CropMenu::on_spinBoxH_valueChanged(int arg1)
{
    valH=arg1;
    if(isRatio==true)
        valV=valH/ratioWidth*ratioHeight;
    SetUiWithValue();
}

void CropMenu::on_spinBoxV_valueChanged(int arg1)
{
    valV=arg1;
    if(isRatio==true)
        valH=valV*ratioHeight/ratioWidth;
    SetUiWithValue();
}
