#include "FormatMenu.h"
#include "ui_FormatMenu.h"

FormatMenu::FormatMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FormatMenu)
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
    l1->AddUnit(new QWidget*[2]{ui->labelOutputFormat,ui->comboBoxFormat},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSuffixName,ui->lineEditSuffixName},2);
    l1->AddUnit(new QWidget*[2]{ui->labelPrefix,ui->lineEditPrefix},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSuffix,ui->lineEditSuffix},2);
    l1->AddUnit(ui->labelExample);

    l2->AddUnit(new QWidget*[2]{ui->pushButtonStart,ui->labelStart},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

FormatMenu::~FormatMenu()
{
    delete ui;
}

void FormatMenu::Init(QStringList sourcePath)
{
    this->sourcePath=sourcePath;
    this->targetPath=GetDirByPath(sourcePath[0]);

    this->amount=sourcePath.size();

    ui->labelImageAmount->setText("图像数量："+QString::number(amount));
    ui->labelSourcePath->setText("图像源路径："+GetDirByPath(sourcePath[0]));

    ui->labelOutputPath->setText("输出路径："+targetPath);

    format="JPG";
    suffixName="JPG";
    filePrefix="";
    fileSuffix="";

    ui->comboBoxFormat->setCurrentIndex(0);
    ui->lineEditSuffixName->setText("JPG");

    ui->lineEditPrefix->setText("");
    ui->lineEditSuffix->setText("");

    ReloadExample();
}

void FormatMenu::ReloadExample()
{
    ui->labelExample->setText("示例："+filePrefix+GetNameByPath(sourcePath[0])+fileSuffix+"."+suffixName);
}

void FormatMenu::resizeEvent(QResizeEvent * event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

void FormatMenu::on_pushButtonOutputPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择输出文件夹",targetPath,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    targetPath=DirAddSlash(dir);
    ui->labelOutputPath->setText("输出路径："+targetPath);
}

void FormatMenu::on_comboBoxFormat_currentIndexChanged(const QString &arg1)
{
    format=arg1.right(arg1.size()-arg1.indexOf(".")-1);

    suffixName=format;
    ui->lineEditSuffixName->setText(format);

    ReloadExample();
}

void FormatMenu::on_lineEditSuffixName_textChanged(const QString &arg1)
{
    suffixName=arg1;
    ReloadExample();
}

void FormatMenu::on_lineEditPrefix_textChanged(const QString &arg1)
{
    filePrefix=arg1;
    ReloadExample();
}

void FormatMenu::on_lineEditSuffix_textChanged(const QString &arg1)
{
    fileSuffix=arg1;
    ReloadExample();
}

void FormatMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void FormatMenu::on_pushButtonStart_clicked()
{
    emit(ShowFormatProcess(sourcePath,targetPath,format,suffixName,filePrefix,fileSuffix));
}
