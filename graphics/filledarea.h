#ifndef FILLEDAREA_H
#define FILLEDAREA_H

#include "paintbackground.h"
#include <QStack>
#include <QQueue>

class FilledArea
{
public:
    FilledArea(QPoint p,QColor color1,QColor color2){
        start_x=p.x();
        start_y=p.y();
        backColor=color1;
        newColor=color2;
        newColor_rgb=newColor.rgb();
        max_width=max_height=0;
        pp.clear();
    }
    void BoundaryFill(QImage &image){
        QSize size=image.size();
        max_width=size.width();
        max_height=size.height();
        if(backColor!=newColor)
        {
            BoundaryScanFill(image);
            /*int x=start_x;
            while(x>0)
                if(image.pixelColor(x,start_y)==backColor)
                    x--;
            x++;
            QPoint p(x,start_y);
            pp.push_back(p);
            while(!pp.empty())
                BoundaryScanFill(image);
                */
        }
    }
private:
    //用队列实现的洪泛填充
    void BoundaryScanFill(QImage &image){
        QPoint p_start(start_x,start_y);
        QQueue<QPoint> points;
        points.enqueue(p_start);
        while(!points.empty())
        {
            QPoint p=points.dequeue();
            int x=p.x(),y=p.y();
            if(image.pixelColor(x,y)==newColor)
                continue;
            image.setPixel(x,y,newColor_rgb);
            if(x>0)
                if(image.pixelColor(x-1,y)==backColor)
                    points.enqueue(QPoint(x-1,y));
            if(y>0)
                if(image.pixelColor(x,y-1)==backColor)
                    points.enqueue(QPoint(x,y-1));
            if(x<max_width)
                if(image.pixelColor(x+1,y)==backColor)
                    points.enqueue(QPoint(x+1,y));
            if(y<max_height)
                if(image.pixelColor(x,y+1)==backColor)
                    points.enqueue(QPoint(x,y+1));
        }
    }
    //扫描线边界填充(failed)
    /*
    void BoundaryScanFill(QImage &image){
        QPoint point=pp.top();
        pp.pop();
        int x=point.x(),y=point.y();
        QColor c=image.pixelColor(x,y);
        if(c==backColor)
        {
            //image.setPixelColor(x,y,newColor);
            bool up_exist=false,down_exist=false;
            int x_move=x;
            while(x_move<max_width)
            {
                if(y-1>0)
                {
                    if(image.pixelColor(x_move,y-1)==backColor)
                    {
                        if(up_exist==false)
                        {
                            QPoint p(x_move,y-1);
                            pp.push(p);
                            up_exist=true;
                        }
                    }
                    else
                        up_exist=false;
                }
                if(y+1<max_height)
                {
                    if(image.pixelColor(x_move,y+1)==backColor)
                    {
                        if(down_exist==false)
                        {
                            QPoint p(x_move,y+1);
                            pp.push(p);
                            down_exist=true;
                        }
                    }
                    else
                        down_exist=false;
                }
                if(image.pixelColor(x_move,y)==backColor)
                {
                    image.setPixel(x_move,y,newColor_rgb);
                    x_move++;
                }
                else
                    break;
            }
        }
    }
*/
    QStack<QPoint> pp;
    int start_x;
    int start_y;
    int max_width,max_height;
    QColor backColor;
    QColor newColor;
    QRgb newColor_rgb;
};

#endif // FILLEDAREA_H
