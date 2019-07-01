#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

#include "FormatMenu.h"
#include "FormatProcess.h"

#include "CropMenu.h"
#include "CropProcess.h"

#include "CompressMenu.h"

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

    void HideAllFrame();
};

#endif // MAINWINDOW_H
