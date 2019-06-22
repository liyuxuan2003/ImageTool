#include <LiLibrary/LiEasyLayout.h>

LiEasyLayout::LiEasyLayout(int start,int width,int height,LayoutDirection direction,float li,float headOptimize)
{
    isConfigDone=false;

    startPos=0;
    endPos=height;

    lastUseUnit=-1;

    startPos=start;

    baseTotalHeight=height;
    baseTotalWidth=width;
    baseLayoutHeight=endPos-startPos;

    this->direction=direction;

    this->li=li;
    this->isNeedHeadOptimize=false;
    this->headOptimize=1.0f;
    if(headOptimize!=-1.0f && headOptimize>=0.0f)
    {
        this->isNeedHeadOptimize=true;
        this->headOptimize=headOptimize;
    }
}

int LiEasyLayout::AddUnit()
{
    if(CheckIsCongfigDone()==true)
        return -1;
    int unitId=easyLayout.size();
    lastUseUnit=unitId;
    easyLayout.push_back(LiEasyLayoutUnit());
    easyLayout[unitId].id=unitId;
    return unitId;
}

int LiEasyLayout::AddUnit(QWidget *elementInUnit)
{
    int unitId=AddUnit();
    AddElementInUnit(unitId,elementInUnit);
}

int LiEasyLayout::AddUnit(QWidget **elementsInUnit, int size)
{
    int unitId=AddUnit();
    AddElementInUnit(unitId,elementsInUnit,size);
}

void LiEasyLayout::AddElementInUnit(int unitId, QWidget* widget)
{
    if(CheckIsCongfigDone()==true)
        return;
    lastUseUnit=unitId;
    if(easyLayout[unitId].base==NULL)
        easyLayout[unitId].base=widget;
    easyLayout[unitId].elements.push_back(widget);
    easyLayout[unitId].offset.push_back(widget->y()-easyLayout[unitId].base->y());
    easyLayout[unitId].leftSpace.push_back(widget->x());
    easyLayout[unitId].rightSpace.push_back(baseTotalWidth-widget->x());

    if(widget->y()<easyLayout[unitId].unitStart)
        easyLayout[unitId].unitStart=widget->y();
    if(widget->y()+widget->height()>easyLayout[unitId].unitEnd)
        easyLayout[unitId].unitEnd=widget->y()+widget->height();
    easyLayout[unitId].unitSize=easyLayout[unitId].unitEnd-easyLayout[unitId].unitStart;
}

void LiEasyLayout::AddElementInUnit(int unitId, QWidget** widget,int size)
{
    for(int i=0;i<size;i++)
        AddElementInUnit(unitId,widget[i]);
}

void LiEasyLayout::AddElementInUnit(QWidget *widget)
{
    AddElementInUnit(lastUseUnit,widget);
}

void LiEasyLayout::AddElementInUnit(QWidget **widget, int size)
{
    AddElementInUnit(lastUseUnit,widget,size);
}

void LiEasyLayout::LayoutConfigDone()
{
    isConfigDone=true;

    std::sort(easyLayout.begin(),easyLayout.end(),LiEasyLayoutUnit::cmp);

    int* tmpPosArr=new int[easyLayout.size()+2];
    tmpPosArr[0]=startPos;
    tmpPosArr[easyLayout.size()+1]=endPos;
    for(int i=0;i<easyLayout.size();i++)
        tmpPosArr[i+1]=easyLayout[i].unitStart;

    int* tmpLenArr=new int[easyLayout.size()+2];
    tmpLenArr[0]=0;
    tmpPosArr[easyLayout.size()+1]=0;
    for(int i=0;i<easyLayout.size();i++)
        tmpLenArr[i+1]=easyLayout[i].unitSize;

    widgetTotalHeight=0;

    float avg=0;
    gap=new int[easyLayout.size()];
    for(int i=0;i<easyLayout.size();i++)
    {
        gap[i]=tmpPosArr[i+1]-(tmpPosArr[i]+tmpLenArr[i]);
        widgetTotalHeight+=easyLayout[i].unitSize;
        avg+=(float)gap[i];
    }

    ratio=new float[easyLayout.size()];
    if(isNeedHeadOptimize==true)
    {
        ratio[0]=gap[0]*headOptimize;
        avg=avg-ratio[0];
        avg/=(easyLayout.size()-1);
        ratioSum+=ratio[0];
        for(int i=1;i<easyLayout.size();i++)
        {
            ratio[i]=(float)gap[i]-((float)gap[i]-avg)*li;
            ratioSum+=ratio[i];
        }
    }
    else if(isNeedHeadOptimize==false)
    {
        avg/=(easyLayout.size());
        for(int i=0;i<easyLayout.size();i++)
        {
            ratio[i]=(float)gap[i]-((float)gap[i]-avg)*li;
            ratioSum+=ratio[i];
        }
    }
}

void LiEasyLayout::ResizeWithEasyLayout(int width,int height)
{
    if(isConfigDone==false)
    {
        qDebug() << "LiEasyLayout[Error0002]: ";
        qDebug() << "You should call the LayoutCongfigDone() before using ResizeWithEasyLayout()";
        return;
    }

    int nowPos=startPos;
    for(int i=0;i<easyLayout.size();i++)
    {
        //nowPos+=gap[i]*(height*baseLayoutHeight/baseTotalHeight-widgetTotalHeight)/(baseLayoutHeight-widgetTotalHeight);
        nowPos+=(gap[i]+(ratio[i]/ratioSum)*(float)(height-baseTotalHeight));
        easyLayout[i].base->move(easyLayout[i].base->x(),nowPos);
        for(int j=0;j<easyLayout[i].elements.size();j++)
        {
            easyLayout[i].elements[j]->move(
                        easyLayout[i].elements[j]->x(),
                        easyLayout[i].base->y()+easyLayout[i].offset[j]);

            if(direction==right)
            {
                easyLayout[i].elements[j]->move(
                            width-easyLayout[i].rightSpace[j],
                            easyLayout[i].elements[j]->y());
            }
        }
        nowPos+=easyLayout[i].unitSize;
    }
}

bool LiEasyLayout::CheckIsCongfigDone()
{
    if(isConfigDone==true)
    {
        qDebug() << "LiEasyLayout[Error0001]: ";
        qDebug() << "You can not modify anything after called of the function LayoutConfigDone()!";
        return true;
    }
    return false;
}


LiEasyLayoutUnit::LiEasyLayoutUnit()
{
    unitStart=1000000;
    unitEnd=-1000000;
    unitSize=-1;
    base=NULL;
}

bool LiEasyLayoutUnit::cmp(LiEasyLayoutUnit p1, LiEasyLayoutUnit p2)
{
    return p1.unitStart<p2.unitStart;
}
