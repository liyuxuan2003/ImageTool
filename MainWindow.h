#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <LiLibrary/LiFileName.h>

#include "Menu.h"

#include "FormatMenu.h"
#include "FormatProcess.h"

#include "CropMenu.h"
#include "CropProcess.h"

#include "CompressMenu.h"
#include "CompressProcess.h"

#include "ConnectMenu.h"
#include "ConnectProcess.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ShowMenu();

    void ShowFormatMenu();
    void ShowFormatProcess(QStringList sourcePath, QString targetPath, QString format, QString suffixName, QString filePrefix, QString fileSuffix);

    void ShowCropMenu();
    void ShowCropProcess(QStringList sourcePath,QString targetPath,int valH,int valV,int valMH,int valMV,CropMenu::CropMode mode);

    void ShowCompressMenu();
    void ShowCompressProcess(QStringList sourcePath,QString targetPath,int compressWidth,int compressHeight,int compressPercent,CompressMode::Mode mode);

    void ShowConnectMenu();
    void ShowConnectProcess(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow* ui;

    Menu* menu;

    FormatMenu* formatMenu;
    FormatProcess* formatProcess;

    CropMenu* cropMenu;
    CropProcess* cropProcess;

    CompressMenu* compressMenu;
    CompressProcess* compressProcess;

    ConnectMenu* connectMenu;
    ConnectProcess* connectProcess;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
