#ifndef LIEASYLAYOUT_H
#define LIEASYLAYOUT_H

#include <QWidget>
#include <QString>

#include <QDebug>

#include <algorithm>
#include <vector>

class LiEasyLayoutUnit
{
public:
    LiEasyLayoutUnit();

    int id;

    QWidget* base;

    int unitStart;
    int unitEnd;
    int unitSize;

    std::vector<QWidget*> elements;
    std::vector<int> offset;
    std::vector<int> leftSpace;
    std::vector<int> rightSpace;

    static bool cmp(LiEasyLayoutUnit p1,LiEasyLayoutUnit p2);
};

class LiEasyLayout
{
public:
    enum LayoutDirection{left,right};

    LiEasyLayout(int start,int width,int height,LayoutDirection direction,float li,float headOptimize=-1.0f);

    int AddUnit();

    int AddUnit(QWidget* elementInUnit);
    int AddUnit(QWidget** elementsInUnit,int size);

    void AddElementInUnit(int unitId,QWidget* widget);
    void AddElementInUnit(int unitId,QWidget** widget,int size);

    void AddElementInUnit(QWidget* widget);
    void AddElementInUnit(QWidget** widget,int size);

    void LayoutConfigDone();

    void ResizeWithEasyLayout(int width,int height);

private:
    float li;

    float headOptimize;
    bool isNeedHeadOptimize;

    std::vector<LiEasyLayoutUnit> easyLayout;

    LayoutDirection direction;

    int lastUseUnit;

    bool isConfigDone;
    bool CheckIsCongfigDone();

    int startPos;
    int endPos;
    int baseTotalHeight;
    int baseTotalWidth;
    int baseLayoutHeight;
    int widgetTotalHeight;

    int* gap;
    float* ratio;

    float ratioSum=0.0f;
};

#endif // LIEASYLAYOUT_H
