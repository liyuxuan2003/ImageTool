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

    connect(menu,SIGNAL(ShowFormatMenu()),this,SLOT(ShowFormatMenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    menu->resize(width(),height());
    formatMenu->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();
    formatMenu->hide();
}

void MainWindow::ShowFormatMenu()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择图片","D:/",
        "Images (*.JPG *.JPEG *.PNG *.GIF *.TIF *.TIFF *.BMP *.PPM)");
    if(files.size()==0)
        return;
    HideAllFrame();
    formatMenu->show();
}
