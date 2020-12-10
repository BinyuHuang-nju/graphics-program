#ifndef CIRCLE_H
#define CIRCLE_H

#include "paintbackground.h"
#include "shape.h"

class Circle:public Shape
{       // BresenhamCircle
public:
    Circle(QPoint p1,QPoint p2){
        kind=4;
        center_x=p1.x();
        center_y=p1.y();
        double temp_d=sqrt((p2.x()-p1.x())*(p2.x()-p1.x())+(p2.y()-p1.y())*(p2.y()-p1.y()));
        int temp_i=(int)temp_d;
        double diff=temp_d-temp_i;
        if(diff<=0.5)
            radius=temp_i;
        else
            radius=temp_i+1;
        border.left=border.top=1000;
        border.right=border.bottom=0;
        is_chosen=false;
    }
    ~Circle(){ }
    void draw(QPainter &pic){
        draw_circle(pic);
    }
    bool beChosen(QPoint point){
        int x=0,y=radius;
        int p=3-2*radius;
        for(;x<=y;x++)
        {
            if(near_8points(x,y,point.x(),point.y())==true)
                return true;
            if(p>=0)
            {
                p=p+4*(x-y)+10;
                y--;
            }
            else
                p=p+4*x+6;
        }
        return false;
    }
    void draw_circle(QPainter &pic){
        pen=pic.pen();
        if(is_chosen)
            pic.setPen(onepen);
        int x=0,y=radius;
        int p=3-2*radius;
        for(;x<=y;x++)
        {
            draw_8points(pic,x,y);
            if(p>=0)
            {
                p=p+4*(x-y)+10;
                y--;
            }
            else
                p=p+4*x+6;
        }
    }
    void deleteShape(QPainter &pic,QColor backcolor){
        pen.setColor(backcolor);
        pic.setPen(pen);
        draw_circle(pic);
    }
    void changeSize(int index){
        if(index==0)
        {
            if(radius>2)
                radius=radius-2;
        }
        else
        {
            radius=radius+2;

        }
    }
    void translation(QPoint p1,QPoint p2)
    {
        center_x=center_x+p2.x()-p1.x();
        center_y=center_y+p2.y()-p1.y();
    }
    void showBorder(QPainter &pic){
        /*QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(255,0,255,127));
        pic.setPen(pen);
        pic.drawRect(border.left-2,border.top-2,border.right-border.left+4,border.bottom-border.top+4);
        */
        is_chosen=true;
        onepen=pen;
        onepen.setWidth(pen.width()+1);
        onepen.setColor(QColor(255,0,255,127));
        draw_circle(pic);
    }
    void cut(QPainter &pic,QPoint p1,QPoint p2,QColor backColor){

    }
    void rotation(int angle){
        /* do nothing */
    }
    void end(){
        is_chosen=false;
    }
private:
    void draw_8points(QPainter &pic,int x,int y){
        pic.drawPoint(center_x+x,center_y+y);
        pic.drawPoint(center_x+y,center_y+x);
        pic.drawPoint(center_x-x,center_y+y);
        pic.drawPoint(center_x-y,center_y+x);
        pic.drawPoint(center_x+x,center_y-y);
        pic.drawPoint(center_x+y,center_y-x);
        pic.drawPoint(center_x-x,center_y-y);
        pic.drawPoint(center_x-y,center_y-x);
/*        if(center_x-x<border.left)
            border.left=center_x-x;
        if(center_x-y<border.left)
            border.left=center_x-y;

        if(center_x+x>border.right)
            border.right=center_x+x;
        if(center_x+y>border.right)
            border.right=center_x+y;

        if(center_y-y<border.top)
            border.top=center_y-y;
        if(center_y-x<border.top)
            border.top=center_y-x;

        if(center_y+x>border.bottom)
            border.bottom=center_y+x;
        if(center_y+y>border.bottom)
            border.bottom=center_y+y;*/
    }
    bool near_8points(int x,int y,int tx,int ty){
        int pos_x,pos_y;
        pos_x=center_x+x; pos_y=center_y+y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x+y; pos_y=center_y+x;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x-x; pos_y= center_y+y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x-y; pos_y=center_y+x;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x+x; pos_y=center_y-y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x+y; pos_y=center_y-x;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x-x; pos_y=center_y-y;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        pos_x=center_x-y; pos_y=center_y-x;
        if((pos_x-tx)*(pos_x-tx)+(pos_y-ty)*(pos_y-ty)<=49)
            return true;
        return false;
    }
    bool is_chosen;
    QPen pen;
    QPen onepen;
    int center_x;
    int center_y;
    int radius;
    struct{
        int left;
        int right;
        int bottom;
        int top;
    }border;
};

#endif // CIRCLE_H
