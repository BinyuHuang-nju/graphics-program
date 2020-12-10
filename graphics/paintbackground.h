#ifndef PAINTBACKGROUND_H
#define PAINTBACKGROUND_H

#include <iostream>
#include <QtDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QVector>
#include <QImage>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QPointF>
#include <QString>
#include <QSize>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QRect>
#include <cmath>
#include <QtMath>
#include "shape.h"
#include "dialog.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include "ellipse.h"
#include "filledarea.h"
#include "polygon.h"
#include "curve.h"


enum Graphic_Kind {PEN,LINE,CURVE,RECT,CIRCLE,
                   ELLIPSE,FILLED,POLYGON,RUBBER};
enum Operation {TRANSLATION,CUT};

struct Filled{
   QPoint p;
   QColor color;
};

class PaintBackground : public QWidget
{
//    Q_OBJECT
public:
//    explicit PaintBackground(QWidget *parent = nullptr);
    PaintBackground();
    void setImageSize(int width,int height);
    void setImageColor(QColor color);
    void setPenColor(QColor color);
    void setPenWidth(int width);
    void setPenStyle(int index);
    void setGraphyKind(int tag);
    void setRotationAngle(int index);
    bool openImage(QString &filename);
    bool saveImage(QString &filename,char *fileformat);
    void clearImage();
    void repaintImage();
    void setOperation(int index);
    bool IsModified();

    void doMaginify();
    void doNarrow();
    void doRotation();
    QSize getImageSize();
    void doPrint();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    void paint(QImage& Image);


private:
    QImage image;
    QImage tempImage;
    QRgb backColor;
    QColor backgroundColor;
    int pen_width;
    QColor pen_color;
    QPen myPen;
    QPoint firstPoint,secondPoint;
    QPoint lastPoint;
    int angle;

    Graphic_Kind graphic_kind;
    Operation operation;
    Shape* cur_shape;
    QVector<Shape*> shapes;
    QVector<Filled> filled_points;
    bool is_chosen;
    bool isModified;

    bool ready_do;
    bool in_operating;
    bool drawing;
    bool mouseLR;
    bool polygon_first;
    bool curve_first;

    Circle* circle;
    Ellipse* ellipse;
    Line* line;
    Rect* rect;
    Polygon* polygon;
    Curve* curve;
//signals:
//public slots:
};

#endif // PAINTBACKGROUND_H
