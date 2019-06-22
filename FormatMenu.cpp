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

    lf->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightUp);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

FormatMenu::~FormatMenu()
{
    delete ui;
}

void FormatMenu::resizeEvent(QResizeEvent * event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
    lf->ResizeWithFixedToLayout(width(),height());
}

