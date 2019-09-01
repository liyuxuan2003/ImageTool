#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir(StandardDir(QStandardPaths::PicturesLocation));
    dir.mkdir("ImageToolTemp");

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

    compressProcess=new CompressProcess(this);
    compressProcess->move(0,0);
    compressProcess->hide();

    connectMenu=new ConnectMenu(this);
    connectMenu->move(0,0);
    connectMenu->hide();

    connectProcess=new ConnectProcess(this);
    connectProcess->move(0,0);
    connectProcess->hide();

    makeIconMenu=new MakeIconMenu(this);
    makeIconMenu->move(0,0);
    makeIconMenu->hide();

    makeIconProcess=new MakeIconProcess(this);
    makeIconProcess->move(0,0);
    makeIconProcess->hide();

    connect(menu,SIGNAL(ShowFormatMenu()),this,SLOT(ShowFormatMenu()));
    connect(menu,SIGNAL(ShowCropMenu()),this,SLOT(ShowCropMenu()));
    connect(menu,SIGNAL(ShowCompressMenu()),this,SLOT(ShowCompressMenu()));
    connect(menu,SIGNAL(ShowConnectMenu()),this,SLOT(ShowConnectMenu()));
    connect(menu,SIGNAL(ShowMakeIconMenu()),this,SLOT(ShowMakeIconMenu()));

    connect(formatMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(formatMenu,SIGNAL(ShowFormatProcess(QStringList,QString,QString,QString,QString,QString)),this,SLOT(ShowFormatProcess(QStringList,QString,QString,QString,QString,QString)));
    connect(formatProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));

    connect(cropMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(cropMenu,SIGNAL(ShowCropProcess(QStringList,QString,int,int,int,int,CropMenu::CropMode)),this,SLOT(ShowCropProcess(QStringList,QString,int,int,int,int,CropMenu::CropMode)));
    connect(cropProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));

    connect(compressMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(compressMenu,SIGNAL(ShowCompressProcess(QStringList,QString,int,int,int,CompressMode::Mode)),this,SLOT(ShowCompressProcess(QStringList,QString,int,int,int,CompressMode::Mode)));
    connect(compressProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));

    connect(connectMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(connectMenu,SIGNAL(ShowConnectProcess(QStringList,QString,ConnectMode::Mode,int,int,int,QString,QString)),this,SLOT(ShowConnectProcess(QStringList,QString,ConnectMode::Mode,int,int,int,QString,QString)));
    connect(connectProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));

    connect(makeIconMenu,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
    connect(makeIconMenu,SIGNAL(ShowMakeIconProcess(QStringList,QString,bool*)),this,SLOT(ShowMakeIconProcess(QStringList,QString,bool*)));
    connect(makeIconProcess,SIGNAL(ShowMenu()),this,SLOT(ShowMenu()));
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
    compressProcess->resize(width(),height());

    connectMenu->resize(width(),height());
    connectProcess->resize(width(),height());

    makeIconMenu->resize(width(),height());
    makeIconProcess->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();

    formatMenu->hide();
    formatProcess->hide();

    cropMenu->hide();
    cropProcess->hide();

    compressMenu->hide();
    compressProcess->hide();

    connectMenu->hide();
    connectProcess->hide();

    makeGifMenu->hide();

    makeIconMenu->hide();
    makeIconProcess->hide();

    QDir dir(StandardDir(QStandardPaths::PicturesLocation)+"ImageToolTemp/");
    dir.setFilter(QDir::Files);
    for(int i=0;i<dir.count();i++)
        dir.remove(dir[i]);
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

void MainWindow::ShowCompressProcess(QStringList sourcePath,QString targetPath,int compressWidth,int compressHeight,int compressPercent,CompressMode::Mode mode)
{
    HideAllFrame();
    compressProcess->show();
    compressProcess->Init(sourcePath,targetPath,compressWidth,compressHeight,compressPercent,mode);
}

void MainWindow::ShowConnectMenu()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择图片","D:/",
        "Images (*.JPG *.JPEG *.PNG *.GIF *.TIF *.TIFF *.BMP *.PPM)");
    if(files.size()==0)
        return;
    HideAllFrame();
    connectMenu->show();
    connectMenu->Init(files);
}

void MainWindow::ShowConnectProcess(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat)
{
    HideAllFrame();
    connectProcess->show();
    connectProcess->Init(sourcePath,targetPath,mode,maxSize,matrixRow,matrixColumn,outputFileName,outputFormat);
}

void MainWindow::ShowMakeIconMenu()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择图片","D:/",
        "Images (*.JPG *.JPEG *.PNG *.GIF *.TIF *.TIFF *.BMP *.ICO *.ICON *.PPM)");
    if(files.size()==0)
        return;
    HideAllFrame();
    makeIconMenu->show();
    makeIconMenu->Init(files);
}

void MainWindow::ShowMakeIconProcess(QStringList sourcePath,QString targetPath,bool* size)
{
    HideAllFrame();
    makeIconProcess->show();
    makeIconProcess->Init(sourcePath,targetPath,size);
}
