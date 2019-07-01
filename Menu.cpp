#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.4f);
    l2=new LiEasyLayout(0,width(),height(),LiEasyLayout::right,0.0f);

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonFormat,ui->labelFormat,ui->pushButtonFrame,ui->labelFrame},4);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonCrop,ui->labelCrop,ui->pushButtonWaterMark,ui->labelWaterMark},4);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonConnect,ui->labelConnect,ui->pushButtonMakeIcon,ui->labelMakeIcon},4);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonCompress,ui->labelCompress,ui->pushButtonMakeGif,ui->labelMakeGif},4);
    l1->AddUnit();
    l1->AddElementInUnit(ui->labelExtraInfo1);
    l1->AddElementInUnit(ui->labelExtraInfo2);

    l2->AddUnit(new QWidget*[2]{ui->pushButtonAbout,ui->labelAbout},2);
    l2->AddUnit(new QWidget*[2]{ui->pushButtonExit,ui->labelExit},2);

    l1->LayoutConfigDone();
    l2->LayoutConfigDone();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithEasyLayout(width(),height());
}

void Menu::on_pushButtonFormat_clicked()
{
    emit(ShowFormatMenu());
}

void Menu::on_pushButtonCrop_clicked()
{
    emit(ShowCropMenu());
}

void Menu::on_pushButtonCompress_clicked()
{
    emit(ShowCompressMenu());
}
