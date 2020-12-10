#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "paintbackground.h"
class Ellipse:public Shape
{
public:
    Ellipse(QPoint p1,QPoint p2){
        kind=5;
        center_x=(p1.x()+p2.x())/2;
        center_y=(p1.y()+p2.y())/2;
        rx=abs(p2.x()-center_x);
        ry=abs(p2.y()-center_y);
    }
    ~Ellipse(){ }
    void draw(QPainter &pic){
        pen=pic.pen();
        draw_ellipse(pic);
    }
    bool beChosen(QPoint point){
        int a=rx,b=ry;
        double sqa=a*a,sqb=b*b;
        double d=sqb+sqa*(0.25-b);
        int x=0;
        int y=b;
        if(near_4points(0,b,point.x(),point.y()))
            return true;
        while(sqb*(x+1)<sqa*(y-0.5))
        {
            if(d<0)
                d=d+sqb*(2*x+3);
            else
            {
                d=d+(sqb*(2*x+3)+sqa*(2-2*y));
                y--;
            }
            x++;
            if(near_4points(x,y,point.x(),point.y()))
                return true;
        }
        d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
        while(y>0)
        {
            if(d<0)
            {
                d=d+sqb*(2*x+2)+sqa*(3-2*y);
                x++;
            }
            else
                d=d+sqa*(3-2*y);
            y--;
            if(near_4points(x,y,point.x(),point.y()))
                return true;
        }
        return false;
    }
    void draw_ellipse(QPainter &pic){
        int a=rx,b=ry;
        double sqa=a*a,sqb=b*b;
        double d=sqb+sqa*(0.25-b);
        int x=0;
        int y=b;
        draw_4points(pic,0,b);
        while(sqb*(x+1)<sqa*(y-0.5))
        {
            if(d<0)
                d=d+sqb*(2*x+3);
            else
            {
                d=d+(sqb*(2*x+3)+sqa*(2-2*y));
                y--;
            }
            x++;
            draw_4points(pic,x,y);
        }
        d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
        while(y>0)
        {
            if(d<0)
            {
                d=d+sqb*(2*x+2)+sqa*(3-2*y);
                x++;
            }
            else
                d=d+sqa*(3-2*y);
            y--;
            draw_4points(pic,x,y);
        }
    }
    void deleteShape(QPainter &pic,QColor backcolor){
        pen.setColor(backcolor);
        pen.setWidth(pen.width()+1);
        pic.setPen(pen);
        draw_ellipse(pic);
    }
    void changeSize(int index){
        if(index==0)
        {
            if(ry==0)
                return;
            double m=rx/ry;
            if(m>=1)
            {
                if(ry>2)
                {
                    rx=rx-2*m;
                    ry=ry-2;
                }
            }
            else
            {
                if(rx>2)
                {
                    rx=rx-2;
                    ry=ry-2/m;
                }
            }
        }
        else
        {
               double m=rx/ry;
               if(m>=1)
               {
                   rx=rx+2*m;
                   ry=ry+2;
               }
               else
               {
                   rx=rx+2;
                   ry=ry+2/m;
               }
        }
    }
    void showBorder(QPainter &pic){

    }
    void translation(QPoint p1,QPoint p2){
        center_x=center_x+p2.x()-p1.x();
        center_y=center_y+p2.y()-p1.y();
    }
    void cut(QPainter &pic,QPoint p1,QPoint p2,QColor backColor){

    }
    void rotation(int angle){

    }
    void end(){

    }
private:
    void draw_4points(QPainter &pic,int x,int y){
        pic.drawPoint(center_x+x,center_y+y);
        pic.drawPoint(center_x-x,center_y+y);
        pic.drawPoint(center_x+x,center_y-y);
        pic.drawPoint(center_x-x,center_y-y);
    }
    bool near_4points(int x,int y,int tx,int ty){
        int pos_x,pos_y;
        pos_x=center_x+x; pos_y=center_y+y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x-x; pos_y=center_y+y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x+x; pos_y= center_y-y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x-x; pos_y=center_y-y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        return false;
    }
    QPen pen;
    int center_x;
    int center_y;
    int rx;
    int ry;
};

#endif // ELLIPSE_H
