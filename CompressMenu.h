#ifndef COMPRESSMENU_H
#define COMPRESSMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

#include <LiLibrary/LiReadImageInfo.h>

namespace Ui
{
    class CompressMenu;
}

class CompressMode
{
public:
    enum Mode{PixelWidth,PixelHeight,PixelIgnore,Percent};
};

class CompressMenu : public QFrame
{
    Q_OBJECT

public:
    explicit CompressMenu(QWidget *parent = nullptr);
    ~CompressMenu();

    void Init(QStringList sourcePath);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonOutputPath_clicked();

    void on_spinBoxPercent_valueChanged(int arg1);

    void on_pushButtonPixel_clicked();

    void on_pushButtonPercent_clicked();

    void on_spinBoxWidth_valueChanged(int arg1);

    void on_spinBoxHeight_valueChanged(int arg1);

    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

    void on_comboBoxRatioCrash_currentIndexChanged(const QString &arg1);

private:
    Ui::CompressMenu *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;
    LiFixedToLayout* lf;

    QStringList sourcePath;
    QString targetPath;

    int compressPercent;

    int compressWidth;
    int compressHeight;

    int exampleWidth;
    int exampleHeight;

    void ChangeToPixelMode();
    void ChangeToPercentMode();

    CompressMode::Mode mode;

signals:
    void ShowCompressProcess(QStringList sourcePath,QString targetPath,int compressWidth,int compressHeight,int compressPercent,CompressMode::Mode mode);
    void ShowMenu();
};

#endif // COMPRESSMENU_H
