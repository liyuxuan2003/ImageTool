#ifndef MAKEICONMENU_H
#define MAKEICONMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

namespace Ui
{
    class MakeIconMenu;
}

class MakeIconMenu : public QFrame
{
    Q_OBJECT

public:
    explicit MakeIconMenu(QWidget *parent = nullptr);
    ~MakeIconMenu();

    void Init(QStringList sourcePath);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonOutputPath_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

    void on_checkBox016_stateChanged(int arg1);

    void on_checkBox032_stateChanged(int arg1);

    void on_checkBox048_stateChanged(int arg1);

    void on_checkBox064_stateChanged(int arg1);

    void on_checkBox128_stateChanged(int arg1);

    void on_checkBox256_stateChanged(int arg1);

private:
    Ui::MakeIconMenu *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;
    LiFixedToLayout* lf;

    QStringList sourcePath;
    QString targetPath;

    bool* size;

    void SetSize(int state,int sizeId);

signals:
    void ShowMakeIconProcess(QStringList sourcePath,QString targetPath,bool* size);
    void ShowMenu();
};

#endif // MAKEICONMENU_H
