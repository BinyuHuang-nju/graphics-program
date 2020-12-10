#ifndef SHAPE_H
#define SHAPE_H

#include "paintbackground.h"

class Shape
{
public:
    Shape() {}
    virtual bool beChosen(QPoint point)=0;
    virtual void draw(QPainter &pic)=0;
    virtual void showBorder(QPainter &pic)=0;
    virtual void translation(QPoint p1,QPoint p2)=0;
    virtual void changeSize(int index)=0;
    virtual void deleteShape(QPainter &pic,QColor backcolor)=0;
    virtual void end()=0;
    virtual void cut(QPainter &pic,QPoint p1,QPoint p2,QColor backColor)=0;
    virtual void rotation(int angle)=0;
    int getkind(){return kind;}
protected:
    int kind;
};


#endif // SHAPE_H
