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

    connect(menu,SIGNAL(ShowFormatMenu()),this,SLOT(ShowFormatMenu()));
    connect(formatMenu,SIGNAL(ShowFormatProcess(QStringList,QString,QString,QString,QString,QString)),this,SLOT(ShowFormatProcess(QStringList,QString,QString,QString,QString,QString)));
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
}

void MainWindow::HideAllFrame()
{
    menu->hide();
    formatMenu->hide();
    formatProcess->hide();
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

void MainWindow::ShowMenu()
{
    HideAllFrame();
    menu->show();
}
