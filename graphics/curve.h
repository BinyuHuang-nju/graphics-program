#ifndef CURVE_H
#define CURVE_H

#include "paintbackground.h"
#include <QVector>

class Curve:public Shape
{
public:
    Curve(QPoint p_start,QRgb rgb){
        kind=2;
        points.push_back(p_start);
        old_colors.push_back(rgb);
    }
    ~Curve() {points.clear();}
    void addPoint(QPoint p,QRgb rgb){
        points.push_back(p);
        old_colors.push_back(rgb);
    }
    void draw(QPainter &pic){
        int size=points.size();
        QPointF pre = points[0];
        double t = 0;
        int n = size - 1;
        pic.setRenderHint(QPainter::HighQualityAntialiasing);
        for(int i = 1; i <= 40; i++)
        {
            t += 0.025;
            QPointF now(0, 0);
            for(int j = 0; j < size; j++)
                now += points[j] * C(n, j) * qPow(t, j) * qPow(1-t, n-j);
            pic.drawLine(pre, now);
            pre = now;
        }
    }
    bool beChosen(QPoint point){
        int size=points.size();
        QPointF pre = points[0];
        double t = 0;
        int n = size - 1;
        for(int i = 1; i <= 40; i++)
        {
            t += 0.025;
            QPointF now(0, 0);
            for(int j = 0; j < size; j++)
                now += points[j] * C(n, j) * qPow(t, j) * qPow(1-t, n-j);
            if((point.x()-pre.x())*(point.x()-pre.x())+(point.y()-pre.y())*(point.y()-pre.y())<=49)
                return true;
            pre = now;
        }
        return false;
    }
    void paintCurve(QPainter &pic,QImage &image){
        pen=pic.pen();
        int size=points.size();
        QPointF pre = points[0];
        double t = 0;
        int n = size - 1;
        pic.setRenderHint(QPainter::HighQualityAntialiasing);
        for(int i = 1; i <= 40; i++)
        {
            t += 0.025;
            QPointF now(0, 0);
            for(int j = 0; j < size; j++)
                now += points[j] * C(n, j) * qPow(t, j) * qPow(1-t, n-j);
            pic.drawLine(pre, now);
            pre = now;
        }
        for(int i=0;i<size;i++)
        {
            image.setPixel(points[i],old_colors[i]);
        }
    }
    void deleteShape(QPainter &pic,QColor backcolor){
        pen.setColor(backcolor);
        pen.setWidth(pen.width()+1);
        pic.setPen(pen);
        draw(pic);
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
    void showBorder(QPainter &pic){

    }
    void translation(QPoint p1,QPoint p2){
        for(int i=0;i<points.size();i++)
        {
            points[i]=points[i]+p2-p1;
        }
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

    double C(int n, int k)
    {
        double res = 1;
        for(int i = 1; i <= k; i++)
        {
            res *= n + 1 - i;
            res /= i;
        }
        return res;
    }
    QPen pen;
    QVector<QPoint> points;
    QVector<QRgb> old_colors;
};

#endif // CURVE_H
