#ifndef FORMATMENU_H
#define FORMATMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <LiLibrary/LiFileName.h>

namespace Ui {
class FormatMenu;
}

class FormatMenu : public QFrame
{
    Q_OBJECT

public:
    explicit FormatMenu(QWidget *parent = nullptr);
    ~FormatMenu();

    void Init(QStringList sourcePath);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonOutputPath_clicked();

    void on_comboBoxFormat_currentIndexChanged(const QString &arg1);

    void on_lineEditSuffixName_textChanged(const QString &arg1);

    void on_lineEditPrefix_textChanged(const QString &arg1);

    void on_lineEditSuffix_textChanged(const QString &arg1);

    void on_pushButtonExit_clicked();

    void on_pushButtonStart_clicked();

private:
    Ui::FormatMenu* ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;

    LiFixedToLayout* lf;

    QStringList sourcePath;
    int amount;

    QString targetPath;
    QString format;
    QString suffixName;

    QString filePrefix;
    QString fileSuffix;

    void ReloadExample();

signals:
    void ShowMenu();
    void ShowFormatProcess(QStringList sourcePath, QString targetPath, QString format, QString suffixName, QString filePrefix, QString fileSuffix);
};

#endif // FORMATMENU_H
