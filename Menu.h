#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include <QDebug>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>

namespace Ui
{
    class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonFormat_clicked();

    void on_pushButtonCrop_clicked();

    void on_pushButtonCompress_clicked();

    void on_pushButtonConnect_clicked();

private:
    Ui::Menu* ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;

signals:
    void ShowFormatMenu();

    void ShowCropMenu();

    void ShowCompressMenu();

    void ShowConnectMenu();
};

#endif // MENU_H
