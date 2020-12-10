#ifndef POLYGON_H
#define POLYGON_H

#include "paintbackground.h"
#include "line.h"
#include <QVector>

class Polygon:public Shape
{
public:
    Polygon(QPoint p_start){
        kind=7;
        points.push_back(p_start);
    }
    ~Polygon() { points.clear();}
    void draw(QPainter &pic){
        int size=points.size();
        if(size>=3)
        {
            for(int i=0;i<size-1;i++)
            {
                pic.drawLine(points[i],points[i+1]);
            }
        }
        pic.drawLine(points[size-1],points[0]);
    }
    void add_point(QPoint p){
        points.push_back(p);
    }
    QPoint firstPoint(){
        return points[0];
    }
    bool beChosen(QPoint point){
        int size=points.size();
        if(size>=3)
        {
            for(int i=0;i<size-1;i++)
            {
                Line line(points[i],points[i+1]);
                if(line.beChosen(point))
                    return true;
            }
        }
        Line line(points[size-1],points[0]);
        if(line.beChosen(point))
            return true;
        return false;
    }
    void paintLine(QPainter &pic){
        if(points.size()>=2){
            int size=points.size();
            pic.drawLine(points[size-2],points[size-1]);
        }
    }
    void paintFinalLine(QPainter &pic){
        pen=pic.pen();
        if(points.size()>=2){
            int size=points.size();
            pic.drawLine(points[size-1],points[0]);
        }
    }
    void deleteShape(QPainter &pic,QColor backcolor){
        pen.setColor(backcolor);
        pen.setWidth(pen.width()+1);
        pic.setPen(pen);
        draw(pic);
    }
    void showBorder(QPainter &pic){

    }
    void changeSize(int index){
        int mid_x=0,mid_y=0;
        for(int i=0;i<points.size();i++)
        {
            mid_x=mid_x+points[i].x();
            mid_y=mid_y+points[i].y();
        }
        mid_x=mid_x/points.size();
        mid_y=mid_y/points.size();
        QPoint p_mid(mid_x,mid_y);
        if(index==0)
        {
            for(int i=0;i<points.size();i++)
                points[i]=p_mid+0.95*(points[i]-p_mid);
        }
        else
        {
            for(int i=0;i<points.size();i++)
                points[i]=p_mid+1.05*(points[i]-p_mid);
        }
    }
    void translation(QPoint p1,QPoint p2){
        for(int i=0;i<points.size();i++)
            points[i]=points[i]+p2-p1;
    }
    void cut(QPainter &pic,QPoint p1,QPoint p2,QColor backColor){

    }
    void rotation(int angle){
        for(int i=1;i<points.size();i++)
        {
            int x=points[i].x()-points[0].x();
            int y=points[i].y()-points[0].y();
            int x1=cos(angle / 180.0 * 3.14159265)*x-sin(angle / 180.0 * 3.14159265)*y;
            int y1=sin(angle / 180.0 * 3.14159265)*x+cos(angle / 180.0 * 3.14159265)*y;
            points[i].setX(points[0].x()+x1);
            points[i].setY(points[0].y()+y1);
        }
    }
    void end(){

    }
private:
    QPen pen;
    QVector<QPoint> points;
};

#endif // POLYGON_H
