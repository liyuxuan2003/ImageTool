#include "ConnectMenu.h"
#include "ui_ConnectMenu.h"

ConnectMenu::ConnectMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConnectMenu)
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
    l1->AddUnit(new QWidget*[2]{ui->labelOutputFileName,ui->lineEditOutputFileName},2);
    l1->AddUnit(new QWidget*[2]{ui->labelOutputFormat,ui->comboBoxFormat},2);

    l1->AddUnit(ui->labelNowMode);

    l1->AddUnit();
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonModeH,ui->labelModeH},2);
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonModeV,ui->labelModeV},2);
    l1->AddElementInUnit(new QWidget*[2]{ui->pushButtonModeM,ui->labelModeM},2);

    l1->AddUnit();
    l1->AddElementInUnit(new QWidget*[3]{ui->labelSetMax,ui->spinBoxMax,ui->labelUnitPixel},3);
    l1->AddElementInUnit(new QWidget*[4]{ui->labelLayoutWay,ui->spinBoxImgInRow,ui->labelUnitSymbol,ui->spinBoxImgInColumn},4);

    l2->AddUnit(new QWidget*[2]{ui->pushButtonStart,ui->labelStart},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

ConnectMenu::~ConnectMenu()
{
    delete ui;
}

void ConnectMenu::resizeEvent(QResizeEvent* event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void ConnectMenu::Init(QStringList sourcePath)
{
    this->sourcePath=sourcePath;

    ui->labelImageAmount->setText("图像数量："+QString::number(sourcePath.size()));
    ui->labelSourcePath->setText("图像源路径："+GetDirByPath(sourcePath[0]));

    targetPath=StandardDir(QStandardPaths::PicturesLocation);
    ui->labelOutputPath->setText("输出路径："+targetPath);

    mode=ConnectMode::Horizontal;
    ModeChange(mode);

    maxSize=20000;
    matrixRow=5;
    matrixColumn=5;

    outputFormat="JPG";
    outputFileName=GetNameByPath(sourcePath[0])+"-Connect";

    ui->spinBoxMax->setValue(maxSize);
    ui->spinBoxImgInRow->setValue(matrixRow);
    ui->spinBoxImgInColumn->setValue(matrixColumn);

    ui->comboBoxFormat->setCurrentIndex(0);
    ui->lineEditOutputFileName->setText(outputFileName);
}

void ConnectMenu::ModeChange(ConnectMode::Mode m)
{
    mode=m;
    if(mode==ConnectMode::Horizontal || mode==ConnectMode::Vertical)
    {
        ui->labelLayoutWay->hide();
        ui->spinBoxImgInRow->hide();
        ui->labelUnitSymbol->hide();
        ui->spinBoxImgInColumn->hide();
        if(mode==ConnectMode::Horizontal)
            ui->labelNowMode->setText("当前模式：水平模式");
        if(mode==ConnectMode::Vertical)
            ui->labelNowMode->setText("当前模式：垂直模式");
    }
    else if(mode==ConnectMode::Matrix)
    {
        ui->labelLayoutWay->show();
        ui->spinBoxImgInRow->show();
        ui->labelUnitSymbol->show();
        ui->spinBoxImgInColumn->show();
        ui->labelNowMode->setText("当前模式：矩阵模式");
    }
}

void ConnectMenu::on_pushButtonOutputPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择输出文件夹",targetPath,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    targetPath=DirAddSlash(dir);
    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void ConnectMenu::on_pushButtonModeH_clicked()
{
    ModeChange(ConnectMode::Horizontal);
}

void ConnectMenu::on_pushButtonModeV_clicked()
{
    ModeChange(ConnectMode::Vertical);
}

void ConnectMenu::on_pushButtonModeM_clicked()
{
    ModeChange(ConnectMode::Matrix);
}

void ConnectMenu::on_pushButtonStart_clicked()
{
    emit(ShowConnectProcess(sourcePath,targetPath,mode,maxSize,matrixRow,matrixColumn,outputFileName,outputFormat));
}

void ConnectMenu::on_lineEditOutputFileName_textChanged(const QString &arg1)
{
    outputFileName=arg1;
}

void ConnectMenu::on_comboBoxFormat_currentIndexChanged(const QString &arg1)
{
    outputFormat=arg1.right(arg1.size()-arg1.indexOf(".")-1);
    qDebug() << outputFormat;
}

void ConnectMenu::on_spinBoxMax_valueChanged(int arg1)
{
    maxSize=arg1;
}

void ConnectMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void ConnectMenu::on_spinBoxImgInRow_valueChanged(int arg1)
{
    matrixRow=arg1;
}

void ConnectMenu::on_spinBoxImgInColumn_valueChanged(int arg1)
{
    matrixColumn=arg1;
}
