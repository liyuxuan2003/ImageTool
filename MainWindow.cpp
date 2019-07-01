#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menu=new Menu(this);
    menu->move(0,0);
    menu->show();

    formatMenu=new FormatMenu(this);
    formatMenu->move(0,0);
    formatMenu->hide();

    formatProcess=new FormatProcess(this);
    formatProcess->move(0,0);
    formatProcess->hide();

    cropMenu=new CropMenu(this);
    cropMenu->move(0,0);
    cropMenu->hide();

    cropProcess=new CropProcess(this);
    cropProcess->move(0,0);
    cropProcess->hide();

    compressMenu=new CompressMenu(this);
    compressMenu->move(0,0);
    compressMenu->hide();

    connect(menu,SIGNAL(ShowFormatMenu()),this,SLOT(ShowFormatMenu()));
    connect(menu,SIGNAL(ShowCropMenu()),this,SLOT(ShowCropMenu()));
    connect(menu,SIGNAL(ShowCompressMenu()),this,SLOT(ShowCompressMenu()));

    connect(formatMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(formatMenu,SIGNAL(ShowFormatProcess(QStringList,QString,QString,QString,QString,QString)),this,SLOT(ShowFormatProcess(QStringList,QString,QString,QString,QString,QString)));
    connect(formatProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));

    connect(cropMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(cropMenu,SIGNAL(ShowCropProcess(QStringList,QString,int,int,int,int,CropMenu::CropMode)),this,SLOT(ShowCropProcess(QStringList,QString,int,int,int,int,CropMenu::CropMode)));
    connect(cropProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    menu->resize(width(),height());
    formatMenu->resize(width(),height());
    formatProcess->resize(width(),height());
    cropMenu->resize(width(),height());
    cropProcess->resize(width(),height());
    compressMenu->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();
    formatMenu->hide();
    formatProcess->hide();
    cropMenu->hide();
    cropProcess->hide();
    compressMenu->hide();
}

void MainWindow::ShowMenu()
{
    HideAllFrame();
    menu->show();
}

void MainWindow::ShowFormatMenu()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择图片","D:/",
        "Images (*.JPG *.JPEG *.PNG *.GIF *.TIF *.TIFF *.BMP *.PPM)");
    if(files.size()==0)
        return;
    HideAllFrame();
    formatMenu->show();
    formatMenu->Init(files);
}

void MainWindow::ShowFormatProcess(QStringList sourcePath, QString targetPath, QString format, QString suffixName, QString filePrefix, QString fileSuffix)
{
    HideAllFrame();
    formatProcess->show();
    formatProcess->Init(sourcePath,targetPath,format,suffixName,filePrefix,fileSuffix);
}

void MainWindow::ShowCropMenu()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择图片","D:/",
        "Images (*.JPG *.JPEG *.PNG *.GIF *.TIF *.TIFF *.BMP *.PPM)");
    if(files.size()==0)
        return;
    HideAllFrame();
    cropMenu->show();
    cropMenu->Init(files);
}

void MainWindow::ShowCropProcess(QStringList sourcePath,QString targetPath,int valH,int valV,int valMH,int valMV,CropMenu::CropMode mode)
{
    HideAllFrame();
    cropProcess->show();
    cropProcess->Init(sourcePath,targetPath,valH,valV,valMH,valMV,mode);
}

void MainWindow::ShowCompressMenu()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择图片","D:/",
        "Images (*.JPG *.JPEG *.PNG *.GIF *.TIF *.TIFF *.BMP *.PPM)");
    if(files.size()==0)
        return;
    HideAllFrame();
    compressMenu->show();
    compressMenu->Init(files);
}

