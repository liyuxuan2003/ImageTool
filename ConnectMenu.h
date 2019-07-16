#ifndef CONNECTMENU_H
#define CONNECTMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

namespace Ui
{
    class ConnectMenu;
}

class ConnectMode
{
public:
    enum Mode{Horizontal,Vertical,Matrix};
};

class ConnectMenu : public QFrame
{
    Q_OBJECT

public:
    explicit ConnectMenu(QWidget *parent = nullptr);
    ~ConnectMenu();

    void Init(QStringList sourcePath);

protected:
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void on_pushButtonOutputPath_clicked();

    void on_pushButtonModeH_clicked();

    void on_pushButtonModeV_clicked();

    void on_pushButtonModeM_clicked();

    void on_pushButtonStart_clicked();

    void on_lineEditOutputFileName_textChanged(const QString &arg1);

    void on_comboBoxFormat_currentIndexChanged(const QString &arg1);

    void on_spinBoxMax_valueChanged(int arg1);

    void on_pushButtonExit_clicked();

    void on_spinBoxImgInRow_valueChanged(int arg1);

    void on_spinBoxImgInColumn_valueChanged(int arg1);

private:
    Ui::ConnectMenu *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;

    LiFixedToLayout* lf;

    QStringList sourcePath;
    QString targetPath;

    QString outputFileName;
    QString outputFormat;

    ConnectMode::Mode mode;

    int maxSize;

    int matrixRow;
    int matrixColumn;

    void ModeChange(ConnectMode::Mode m);

signals:
    void ShowConnectProcess(QStringList sourcePath,QString targetPath,ConnectMode::Mode mode,int maxSize,int matrixRow,int matrixColumn,QString outputFileName,QString outputFormat);
    void ShowMenu();
};

#endif // CONNECTMENU_H
