#ifndef CROPMENU_H
#define CROPMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

namespace Ui
{
    class CropMenu;
}

class CropMenu : public QFrame
{
    Q_OBJECT

public:
    explicit CropMenu(QWidget *parent = nullptr);
    ~CropMenu();

    void Init(QStringList sourcePath);

    enum CropMode{PixelMode,PercentModeH,PercentModeV,PercentMode};

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonOutputPath_clicked();

    void on_pushButtonCropPixel_clicked();

    void on_pushButtonCropPercentH_clicked();

    void on_pushButtonCropPercentV_clicked();

    void on_pushButtonCropPercent_clicked();

    void on_spinBoxMH_valueChanged(int arg1);

    void on_spinBoxMV_valueChanged(int arg1);

    void on_checkBoxRatio_stateChanged(int arg1);

    void on_spinBoxWidth_valueChanged(int arg1);

    void on_spinBoxHeight_valueChanged(int arg1);

    void on_spinBoxH_valueChanged(int arg1);

    void on_spinBoxV_valueChanged(int arg1);

    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::CropMenu *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;
    LiFixedToLayout* lf;

    int amount;

    QStringList sourcePath;
    QString targetPath;

    CropMode cropMode;

    int valH;
    int valV;
    int valMH;
    int valMV;

    bool isRatio;
    int ratioWidth;
    int ratioHeight;

    void ChangeUnit(CropMode mode);
    void ChangeUnit();
    void SetUiWithValue(int h,int v,int mh,int mv);
    void SetUiWithValue();

signals:
    void ShowCropProcess(QStringList sourcePath,QString targetPath,int valH,int valV,int valMH,int valMV,CropMenu::CropMode mode);
    void ShowMenu();
};

#endif // CROPMENU_H
