#ifndef FORMATMENU_H
#define FORMATMENU_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui {
class FormatMenu;
}

class FormatMenu : public QFrame
{
    Q_OBJECT

public:
    explicit FormatMenu(QWidget *parent = nullptr);
    ~FormatMenu();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::FormatMenu* ui;

    LiEasyLayout* l1;
    LiEasyLayout* l2;

    LiFixedToLayout* lf;
};

#endif // FORMATMENU_H
