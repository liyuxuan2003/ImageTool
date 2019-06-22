#include <LiLibrary/LiFixedToLayout.h>

LiFixedToLayout::LiFixedToLayout()
{

}

void LiFixedToLayout::AddUnit(QWidget* widget,int width,int height,LiFixedCorner::FixedCorner corner)
{
    fixedToLayout.push_back(new LiFixedToLayoutUnit(fixedToLayout.size(),widget,width,height,corner));
}

void LiFixedToLayout::ResizeWithFixedToLayout(int width,int height)
{
    for(int i=0;i<fixedToLayout.size();i++)
    {
        if(fixedToLayout[i]->corner==LiFixedCorner::LeftUp){/*nothing to do*/}

        if(fixedToLayout[i]->corner==LiFixedCorner::LeftDown)
            fixedToLayout[i]->widget->move(fixedToLayout[i]->widget->x(),height-fixedToLayout[i]->downGap);

        if(fixedToLayout[i]->corner==LiFixedCorner::RightUp)
            fixedToLayout[i]->widget->move(width-fixedToLayout[i]->rightGap,fixedToLayout[i]->widget->y());

        if(fixedToLayout[i]->corner==LiFixedCorner::RightDown)
            fixedToLayout[i]->widget->move(width-fixedToLayout[i]->rightGap,height-fixedToLayout[i]->downGap);
    }
}

LiFixedToLayoutUnit::LiFixedToLayoutUnit(int id,QWidget* widget,int width,int height,LiFixedCorner::FixedCorner corner)
{
    this->id=id;
    this->widget=widget;
    this->leftGap=widget->x();
    this->rightGap=width-widget->x();
    this->upGap=widget->y();
    this->downGap=height-widget->y();
    this->corner=corner;
}

