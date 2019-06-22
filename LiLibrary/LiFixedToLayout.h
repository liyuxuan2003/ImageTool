#ifndef LIFIXEDTOLAYOUT_H
#define LIFIXEDTOLAYOUT_H

#include <QWidget>
#include <QDebug>

#include <vector>

class LiFixedCorner
{
public:
    enum FixedCorner{LeftUp,LeftDown,RightUp,RightDown};
};

class LiFixedToLayoutUnit
{
public:
    LiFixedToLayoutUnit(int id,QWidget* widget,int width,int height,LiFixedCorner::FixedCorner);

    int id;

    QWidget* widget;

    int leftGap;
    int rightGap;
    int upGap;
    int downGap;

    LiFixedCorner::FixedCorner corner;
};

class LiFixedToLayout
{
public:
    LiFixedToLayout();

    void AddUnit(QWidget* widget,int width,int height,LiFixedCorner::FixedCorner corner);

    void ResizeWithFixedToLayout(int width,int height);

private:
    std::vector<LiFixedToLayoutUnit*> fixedToLayout;
};

#endif // LIEASYLAYOUT_H
