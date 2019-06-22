#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"
#include "FormatMenu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ShowFormatMenu();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow* ui;

    Menu* menu;
    FormatMenu* formatMenu;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
