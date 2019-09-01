#ifndef EXAMPLEMENU_H
#define EXAMPLEMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

namespace Ui
{
    class ExampleMenu;
}

class ExampleMenu : public QFrame
{
    Q_OBJECT

public:
    explicit ExampleMenu(QWidget *parent = nullptr);
    ~ExampleMenu();

    void Init(QStringList sourcePath);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonOutputPath_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::ExampleMenu *ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;
    LiFixedToLayout* lf;

    QStringList sourcePath;
    QString targetPath;

signals:
    void ShowExampleProcess(QStringList sourcePath,QString targetPath);
    void ShowMenu();
};

#endif // EXAMPLEMENU_H
