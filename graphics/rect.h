#ifndef RECT_H
#define RECT_H

#include "line.h"
#include "paintbackground.h"

class Rect:public Shape
{
public:
    Rect(QPoint p1,QPoint p2){
        kind=3;
        firstPoint=p1;
        secondPoint=p2;
        QPoint pp1(firstPoint.x(),secondPoint.y());
        QPoint pp2(secondPoint.x(),firstPoint.y());
        point1=pp1;
        point2=pp2;
    }
    ~Rect(){ }
    void draw(QPainter &pic){
        draw_rect(pic);
    }
    bool beChosen(QPoint point){
        Line line1(firstPoint,point1);
        if(line1.beChosen(point))
            return true;
        Line line2(point1,secondPoint);
        if(line2.beChosen(point))
            return true;
        Line line3(secondPoint,point2);
        if(line3.beChosen(point))
            return true;
        Line line4(firstPoint,point2);
        if(line4.beChosen(point))
            return true;
        return false;
    }
    void draw_rect(QPainter &pic){
        pen=pic.pen();
        Line line1(firstPoint,point1);
        Line line2(point1,secondPoint);
        Line line3(secondPoint,point2);
        Line line4(firstPoint,point2);
        line1.draw_line(pic);
        line2.draw_line(pic);
        line3.draw_line(pic);
        line4.draw_line(pic);
    }
    void deleteShape(QPainter &pic,QColor backcolor){
        pen.setColor(backcolor);
        pic.setPen(pen);
        draw_rect(pic);
    }
    void showBorder(QPainter &pic){

    }
    void changeSize(int index){
        int mid_x=(firstPoint.x()+secondPoint.x())/2;
        int mid_y=(firstPoint.y()+secondPoint.y())/2;
        QPoint p_mid(mid_x,mid_y);
        if(index==0)
        {
            firstPoint=p_mid+0.95*(firstPoint-p_mid);
            secondPoint=p_mid+0.95*(secondPoint-p_mid);
        }
        else
        {
            firstPoint=p_mid+1.05*(firstPoint-p_mid);
            secondPoint=p_mid+1.05*(secondPoint-p_mid);
        }
    }
    void translation(QPoint p1,QPoint p2){
        firstPoint=firstPoint+p2-p1;
        secondPoint=secondPoint+p2-p1;
        point1=point1+p2-p1;
        point2=point2+p2-p1;
    }
    void cut(QPainter &pic,QPoint p1,QPoint p2,QColor backColor){

    }
    void rotation(int angle){
        int x1=secondPoint.x()-firstPoint.x();
        int y1=secondPoint.y()-firstPoint.y();
        int x11=cos(angle / 180.0 * 3.14159265)*x1-sin(angle / 180.0 * 3.14159265)*y1;
        int y11=sin(angle / 180.0 * 3.14159265)*x1+cos(angle / 180.0 * 3.14159265)*y1;
        secondPoint.setX(firstPoint.x()+x11);
        secondPoint.setY(firstPoint.y()+y11);

        int x2=point1.x()-firstPoint.x();
        int y2=point1.y()-firstPoint.y();
        int x22=cos(angle / 180.0 * 3.14159265)*x2-sin(angle / 180.0 * 3.14159265)*y2;
        int y22=sin(angle / 180.0 * 3.14159265)*x2+cos(angle / 180.0 * 3.14159265)*y2;
        point1.setX(firstPoint.x()+x22);
        point1.setY(firstPoint.y()+y22);

        int x3=point2.x()-firstPoint.x();
        int y3=point2.y()-firstPoint.y();
        int x33=cos(angle / 180.0 * 3.14159265)*x3-sin(angle / 180.0 * 3.14159265)*y3;
        int y33=sin(angle / 180.0 * 3.14159265)*x3+cos(angle / 180.0 * 3.14159265)*y3;
        point2.setX(firstPoint.x()+x33);
        point2.setY(firstPoint.y()+y33);
    }
    void end(){

    }
private:
    QPen pen;
    QPoint firstPoint;
    QPoint secondPoint;
    QPoint point1,point2;
};

#endif // RECT_H
