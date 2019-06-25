#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

#include "FormatMenu.h"
#include "FormatProcess.h"

#include "CropMenu.h"

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

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow* ui;

    Menu* menu;

    FormatMenu* formatMenu;
    FormatProcess* formatProcess;

    CropMenu* cropMenu;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
