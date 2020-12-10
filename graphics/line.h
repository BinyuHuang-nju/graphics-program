#ifndef LINE_H
#define LINE_H

#include <iomanip>
#include "paintbackground.h"

class Line:public Shape
{
public:
    Line(QPoint p1,QPoint p2)
    {
        kind=1;
        firstPoint=p1;
        secondPoint=p2;
        leftBitCode=1;
        rightBitCode=2;
        buttomBitCode=4;
        topBitCode=8;
    }
    ~Line(){ }
    void draw(QPainter &pic){
        draw_line(pic);
    }
    bool beChosen(QPoint point){
        int x=firstPoint.x(),y=firstPoint.y();
        int dx=abs(secondPoint.x()-firstPoint.x());
        int dy=abs(secondPoint.y()-firstPoint.y());
        int s1,s2;
        if(secondPoint.x()>firstPoint.x())
            s1=1;
        else
            s1=-1;
        if(secondPoint.y()>firstPoint.y())
            s2=1;
        else
            s2=-1;
        bool changed=false;
        if(dy>dx)
        {
            int temp=dx;
            dx=dy;
            dy=temp;
            changed=true;
        }
        int p=2*dy-dx;
        for(int i=1;i<=dx;i=i+1)
        {
            if((x-point.x())*(x-point.x())+(y-point.y())*(y-point.y())<=49)
                return true;
            if(p>=0)
            {
                if(changed==false)
                    y=y+s2;
                else
                    x=x+s1;
                p=p+2*(dy-dx);
            }
            else
                p=p+2*dy;
            if(changed==false)
                x=x+s1;
            else
                y=y+s2;
        }
        return false;
    }
    void draw_line(QPainter &pic){     //BresenhamLine
       // int xs=width;
        pen=pic.pen();

        int x=firstPoint.x(),y=firstPoint.y();
        int dx=abs(secondPoint.x()-firstPoint.x());
        int dy=abs(secondPoint.y()-firstPoint.y());
        int s1,s2;
        if(secondPoint.x()>firstPoint.x())
            s1=1;
        else
            s1=-1;
        if(secondPoint.y()>firstPoint.y())
            s2=1;
        else
            s2=-1;
        bool changed=false;
        if(dy>dx)
        {
            int temp=dx;
            dx=dy;
            dy=temp;
            changed=true;
        }
        int p=2*dy-dx;
        for(int i=1;i<=dx;i=i+1)
        {
            pic.drawPoint(x,y);
            if(p>=0)
            {
                if(changed==false)
                    y=y+s2;
                else
                    x=x+s1;
                p=p+2*(dy-dx);
            }
            else
                p=p+2*dy;
            if(changed==false)
                x=x+s1;
            else
                y=y+s2;
        }
    }
    void deleteShape(QPainter &pic,QColor backcolor){
        pen.setColor(backcolor);
        pic.setPen(pen);
        draw_line(pic);
    }
    void deletePartShape(QPainter &pic,QColor backcolor,QPoint p1,QPoint p2){
        pen.setColor(backcolor);
        pen.setWidth(pen.width()+1);
        pic.setPen(pen);
        int x=firstPoint.x(),y=firstPoint.y();
        int dx=abs(secondPoint.x()-firstPoint.x());
        int dy=abs(secondPoint.y()-firstPoint.y());
        int s1,s2;
        if(secondPoint.x()>firstPoint.x())
            s1=1;
        else
            s1=-1;
        if(secondPoint.y()>firstPoint.y())
            s2=1;
        else
            s2=-1;
        bool changed=false;
        if(dy>dx)
        {
            int temp=dx;
            dx=dy;
            dy=temp;
            changed=true;
        }
        int p=2*dy-dx;
        if(p1.x()>p2.x())
        {
            QPoint temp=p1;
            p1=p2;
            p2=temp;
        }
        for(int i=1;i<=dx;i=i+1)
        {
            if(x<p1.x() || x>p2.x())
                pic.drawPoint(x,y);
            if(p>=0)
            {
                if(changed==false)
                    y=y+s2;
                else
                    x=x+s1;
                p=p+2*(dy-dx);
            }
            else
                p=p+2*dy;
            if(changed==false)
                x=x+s1;
            else
                y=y+s2;
        }
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
    void showBorder(QPainter &pic){

    }
    void translation(QPoint p1,QPoint p2){
        firstPoint=firstPoint+p2-p1;
        secondPoint=secondPoint+p2-p1;
    }
    void cut(QPainter &pic,QPoint p1,QPoint p2,QColor backColor){
        //const int winMin_x=(p1.x()>p2.x())?p2.x():p1.x();
        //const int winMax_x=(p1.x()>p2.x())?p1.x():p2.x();
        //const int winMin_y=(p1.y()>p2.y())?p2.y():p1.y();
        //const int winMax_y=(p1.y()>p2.y())?p1.y():p2.y();
        int winMin_x,winMax_x,winMin_y,winMax_y;
        if(p1.x()<p2.x())
        {
            winMin_x=p1.x();
            winMax_x=p2.x();
        }
        else
        {
            winMin_x=p2.x();
            winMax_x=p1.x();
        }
        if(p1.y()<p2.y())
        {
            winMin_y=p1.y();
            winMax_y=p2.y();
        }
        else
        {
            winMin_y=p2.y();
            winMax_y=p1.y();
        }
        //qDebug()<<winMin_x<<" "<<winMax_x<<" "<<winMin_y<<" "<<winMax_y<<endl;
        bool done=false,plotLine=false;
        double k=0;
        QPoint point1(firstPoint);
        QPoint point2(secondPoint);
        if(point2.x()!=point1.x())
            k=((double)point2.y()-point1.y())/((double)point2.x()-point1.x());
        //qDebug()<<k<<endl;
        while(!done)
        {
           //qDebug()<<point1.x()<<" "<<point1.y()<<" "<<point2.x()<<" "<<point2.y()<<endl;
            int code1=encode(point1,winMin_x,winMax_x,winMin_y,winMax_y);
            int code2=encode(point2,winMin_x,winMax_x,winMin_y,winMax_y);
            //qDebug()<<code1<<" "<<code2<<endl;
            if(accept(code1,code2))
            {
                done=true;
                plotLine=true;
            }
            else
            {
                if(reject(code1,code2))
                    done=true;
                else
                {
                    //qDebug()<<"in"<<endl;
                    if(inside(code1))
                    {
                        QPoint temp(point1);
                        point1=point2;
                        point2=temp;
                        int cotemp=code1;
                        code1=code2;
                        code2=cotemp;
                    }
                   //if(point2.x()!=point1.x())
                        //k=(point2.y()-point1.y())/(point2.x()-point1.x());
                    if(code1&leftBitCode)
                    {
                        int goal_y=point1.y()+(winMin_x-point1.x())*k;
                        point1.setY(goal_y);
                        point1.setX(winMin_x);
                    }
                    else if(code1&rightBitCode)
                    {
                        int goal_y=point1.y()+(winMax_x-point1.x())*k;
                       // qDebug()<<"goal_y="<<goal_y<<endl;
                        point1.setY(goal_y);
                        point1.setX(winMax_x);
                    }
                    else if(code1&buttomBitCode)
                    {
                        if(point1.x()!=point2.x())
                        {
                            int goal_x=point1.x()+(winMin_y-point1.y())/k;
                            point1.setX(goal_x);
                        }
                        point1.setY(winMin_y);
                    }
                    else if(code1&topBitCode)
                    {
                        if(point1.x()!=point2.x())
                        {
                            int goal_x=point1.x()+(winMax_y-point1.y())/k;
                            point1.setX(goal_x);
                        }
                        point1.setY(winMax_y);
                    }
                }
            }
        }
        if(plotLine)
        {
            deletePartShape(pic,backColor,point1,point2);
            firstPoint=point1;
            secondPoint=point2;
            //draw_line(pic);
        }
        else
        {
            deleteShape(pic,backColor);
            QPoint p(0,0);
            firstPoint=secondPoint=p;
        }
    }
    void end(){

    }
    void rotation(int angle){
        int x=secondPoint.x()-firstPoint.x();
        int y=secondPoint.y()-firstPoint.y();
        int x1=cos(angle / 180.0 * 3.14159265)*x-sin(angle / 180.0 * 3.14159265)*y;
        int y1=sin(angle / 180.0 * 3.14159265)*x+cos(angle / 180.0 * 3.14159265)*y;
        secondPoint.setX(firstPoint.x()+x1);
        secondPoint.setY(firstPoint.y()+y1);
    }
private:
    inline bool inside(int code){return (code==0);}
    inline bool accept(int code1,int code2){
        return ((code1==0)&&(code2==0));
    }
    inline bool reject(int code1,int code2){
        return ((code1&code2)!=0);
    }
    int encode(QPoint p,int left,int right,int buttom,int top){
        int code=0;
        if(p.x()<left)
            code=code|leftBitCode;
        if(p.x()>right)
            code=code|rightBitCode;
        if(p.y()<buttom)
            code=code|buttomBitCode;
        if(p.y()>top)
            code=code|topBitCode;
        return code;
    }

    int leftBitCode;
    int rightBitCode;
    int buttomBitCode;
    int topBitCode;
    QPen pen;
    QPoint firstPoint;
    QPoint secondPoint;
};

#endif // LINE_H
