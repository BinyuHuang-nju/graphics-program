#include "paintbackground.h"

/*PaintBackground::PaintBackground(QWidget *parent) : QWidget(parent)
{

}*/

PaintBackground::PaintBackground()
{
    image=QImage(700,500,QImage::Format_RGB32);
    backColor=qRgb(255,255,255);
    backgroundColor=Qt::white;
    image.fill(backColor);
    isModified=false;
    pen_width=2;
    pen_color=Qt::black;
    myPen.setColor(pen_color);
    myPen.setWidth(pen_width);
    myPen.setStyle(Qt::SolidLine);
    graphic_kind=PEN;
    operation=TRANSLATION;
    drawing=false;
    is_chosen=false;
    ready_do=false;
    in_operating=false;
    mouseLR=false;
    cur_shape=NULL;
    polygon_first=true;
    curve_first=true;
    tempImage=image;
    angle=0;
}
void PaintBackground::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(drawing==false ||
       (!in_operating&&(graphic_kind==FILLED ||graphic_kind==CURVE||graphic_kind==POLYGON))||
                          graphic_kind==RUBBER|| graphic_kind == PEN  )
        painter.drawImage(0,0,image);
    else
        painter.drawImage(0,0,tempImage);

/*    image.fill(backColor);

    for(int i=0;i<shapes.size();i++)
        shapes[i]->draw(painter);
    if(cur_shape)
        cur_shape->draw(painter);
    painter.drawImage(0,0,image);
*/
}

void PaintBackground::wheelEvent(QWheelEvent *event)
{
    if(is_chosen && cur_shape)
    {
        QPainter painter(&image);
        cur_shape->deleteShape(painter,backgroundColor);
        painter.setPen(myPen);
        if(event->delta()>0)
        {
            cur_shape->changeSize(1);
            cur_shape->draw(painter);
        }
        if(event->delta()<0)
        {
            cur_shape->changeSize(0);
            cur_shape->draw(painter);
        }
    }
    update();
}
void PaintBackground::doMaginify(){
    if(is_chosen && cur_shape)
    {
        QPainter painter(&image);
        cur_shape->deleteShape(painter,backgroundColor);
        painter.setPen(myPen);
        cur_shape->changeSize(1);
        cur_shape->draw(painter);
    }
    update();
}
void PaintBackground::doNarrow(){
    if(is_chosen && cur_shape)
    {
        QPainter painter(&image);
        cur_shape->deleteShape(painter,backgroundColor);
        painter.setPen(myPen);
        cur_shape->changeSize(0);
        cur_shape->draw(painter);
    }
    update();
}
void PaintBackground::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(is_chosen==true)
    {
        if(cur_shape && cur_shape->beChosen(firstPoint))
        {
            QPainter painter(&image);
            cur_shape->deleteShape(painter,backgroundColor);
            painter.setPen(myPen);
            if(event->button()==Qt::LeftButton)
            {
                cur_shape->changeSize(1);
                cur_shape->draw(painter);
            }
            if(event->button()==Qt::RightButton)
            {
                cur_shape->changeSize(0);
                cur_shape->draw(painter);
            }
        }
    }
    update();
}


void PaintBackground::doRotation()
{
    drawing=false;
    if(is_chosen && cur_shape)
    {
        QPainter painter(&image);

        cur_shape->deleteShape(painter,backgroundColor);
        cur_shape->rotation(angle);
        painter.setPen(myPen);
        cur_shape->draw(painter);
    }
    update();
}

void PaintBackground::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        firstPoint=event->pos();
        lastPoint=secondPoint=firstPoint;

        ready_do=false;
        int thatone=0;
        if(is_chosen==true)
        {
            if(operation==CUT)  //cut
            {
                drawing=true;
                in_operating=true;
            }
            else if(cur_shape && cur_shape->beChosen(firstPoint)) // edit
            {
                //qDebug()<<1<<endl;
                drawing=true;
                in_operating=true;

                QPainter painter(&image);
                cur_shape->deleteShape(painter,backgroundColor);
            }
            else
            {
                if(drawing==false)
                {
                    is_chosen=false;
                    for(int i=0;i<shapes.size();i++)
                        if(shapes[i]->beChosen(firstPoint))
                        {
                            is_chosen=true;
                            thatone=i;
                            break;
                        }

                    if(is_chosen==true)
                    {
                        if(cur_shape)
                            shapes.push_back(cur_shape);
                        ready_do=true;
                        //qDebug()<<111<<endl;
                        cur_shape=shapes[thatone];
                        shapes.erase(shapes.begin()+thatone);

                        //QPainter painter(&image);
                        //painter.setPen(myPen);
                        //cur_shape->showBorder(painter);
                    }
                    else
                        goto l1;
                }
            }
        }
        else
        {
            if(drawing==false)
            {
                //qDebug()<<11<<endl;
                is_chosen=false;
                for(int i=0;i<shapes.size();i++)
                    if(shapes[i]->beChosen(firstPoint))
                    {
                        is_chosen=true;
                        thatone=i;
                        break;
                    }
            }
            if(is_chosen==true)
            {
                if(cur_shape)
                    shapes.push_back(cur_shape);
                ready_do=true;
                //qDebug()<<11.1<<endl;
                cur_shape=shapes[thatone];
                shapes.erase(shapes.begin()+thatone);

                //QPainter painter(&image);
               //painter.setPen(myPen);
                //cur_shape->showBorder(painter);
            }
            else
            {
                l1:
                //qDebug()<<11.2<<endl;
                if(cur_shape)
                    shapes.push_back(cur_shape);
                cur_shape=NULL;

                is_chosen=false;
                drawing=true;
                mouseLR=false;
                switch(graphic_kind)
                {
                case FILLED: case POLYGON: case CURVE:
                {
                paint(image);
                break;
                }
                default:   break;
                }
            }
        }
    }
    if(event->button()==Qt::RightButton)
    {
        switch(graphic_kind)
        {
        case CURVE:{
            mouseLR=true;
            paint(image);
            break;
        }
        default: break;
        }
    }

}
void PaintBackground::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        if(in_operating)
        {
            switch(operation)
            {
            case CUT:{
                secondPoint=event->pos();

                tempImage=image;
                paint(tempImage);
                break;
            }
            default:{
                //qDebug()<<2<<endl;
                lastPoint=secondPoint;
                secondPoint=event->pos();
                tempImage=image;
                paint(tempImage);
                break;
            }
            }
            return;
        }
        if(is_chosen &&ready_do){
            //qDebug()<<22<<endl;
            return;
        }
        switch(graphic_kind)
        {
        case PEN: case RUBBER:
        {
            secondPoint=event->pos();
            paint(image);
            break;
        }
        case FILLED: case POLYGON: case CURVE:
        {
            secondPoint=event->pos();
            break;
        }
        default:
        {
            //processing=true;
            //paint(image);
           secondPoint=event->pos();
           // processing=false;
           tempImage=image;
           paint(tempImage);
            break;
        }
        }
    }
}

void PaintBackground::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(in_operating)
        {
            switch(operation)
            {
            case CUT:{
                secondPoint=event->pos();
                //tempImage=image;
                //QPainter painter(&tempImage);
                //painter.setPen(myPen);
               // cur_shape->cut(painter,firstPoint,secondPoint,backgroundColor);
                //update();

                drawing=false;                
                QPainter painter(&image);
                //painter.setPen(myPen);
                cur_shape->cut(painter,firstPoint,secondPoint,backgroundColor);
                //myPen.setColor(pen_color);
                //painter.setPen(myPen);
                //cur_shape->draw(painter);

                if(cur_shape)
                    shapes.push_back(cur_shape);
                cur_shape=NULL;
                is_chosen=false;
                in_operating=false;
                update();
                break;
            }
            default:{
                //qDebug()<<3<<endl;
                drawing=false;
                lastPoint=secondPoint;
                secondPoint=event->pos();
                paint(image);

                //shapes.push_back(cur_shape);
                in_operating=false;
                break;
            }
            }
            return;
        }
        if(is_chosen && ready_do)
        {
            qDebug()<<33<<endl;
            return;
        }
        drawing=false;
        switch(graphic_kind)
        {
        case FILLED: case POLYGON: case CURVE:
        {
            if(!polygon_first)
                drawing=true;
            secondPoint=event->pos();
            break;
        }
        case CIRCLE:{
            secondPoint=event->pos();
            paint(image);

            shapes.push_back(circle);
            break;
        }
        case ELLIPSE:{
            secondPoint=event->pos();
            paint(image);

            shapes.push_back(ellipse);
            break;
        }
        case LINE:{
            secondPoint=event->pos();
            paint(image);

            shapes.push_back(line);
            break;
        }
        case RECT:{
            secondPoint=event->pos();
            paint(image);

            shapes.push_back(rect);
            break;
        }
        default:{
            secondPoint=event->pos();
            paint(image);
            break;
        }
        }
    }
}
void PaintBackground::paint(QImage& Image)
{
    QPainter pic(&Image);
    myPen.setColor(pen_color);

    pic.setPen(myPen);
    if(in_operating)
    {
        //qDebug()<<4<<endl;
        switch (operation) {
        case TRANSLATION:{
            cur_shape->translation(lastPoint,secondPoint);
            cur_shape->draw(pic);
            break;
        }
        case CUT:{
            QPen onepen(myPen);
            onepen.setColor(QColor(255,0,255,127));
            onepen.setWidth(1);
            pic.setPen(onepen);
            Rect rec(firstPoint,secondPoint);
            rec.draw_rect(pic);
            break;
        }
        default: break;
        }
    }
    else
    {
        switch(graphic_kind)
        {
        case PEN:
        {
            pic.drawLine(firstPoint,secondPoint);
            firstPoint=secondPoint;
            break;
        }
        case RUBBER:
        {

            QPen onepen;
            onepen.setColor(backgroundColor);
            onepen.setWidth(pen_width);
            onepen.setStyle(Qt::SolidLine);
            pic.setPen(onepen);
            pic.drawLine(firstPoint,secondPoint);
            firstPoint=secondPoint;
            break;
        }
        case LINE:
        {
        //pic.drawLine(firstPoint,secondPoint);
        //Line line(firstPoint,secondPoint);
        //line.draw_line(pic);
           line=new Line(firstPoint,secondPoint);
           line->draw_line(pic);
           break;
        }
        case RECT:{
       // int  rect_length=secondPoint.x()-firstPoint.x();
        //int rect_height=secondPoint.y()-firstPoint.y();
        //pic.drawRect(firstPoint.x(),firstPoint.y(),rect_length,rect_height);
           rect=new Rect(firstPoint,secondPoint);
           rect->draw_rect(pic);
           break;
        }
        case CIRCLE:
        {
        //int circle_length=secondPoint.x()-firstPoint.x();
        //pic.drawEllipse(firstPoint.x(),firstPoint.y(),circle_length,circle_length);

            circle=new Circle(firstPoint,secondPoint);
            circle->draw_circle(pic);
            break;
        }
        case ELLIPSE:
        {
        //int ellipse_length=secondPoint.x()-firstPoint.x();
        //int ellipse_height=secondPoint.y()-firstPoint.y();
       // pic.drawEllipse(firstPoint.x(),firstPoint.y(),ellipse_length,ellipse_height);
            ellipse=new Ellipse(firstPoint,secondPoint);
            ellipse->draw_ellipse(pic);
            break;
        }
        case FILLED:
        {
            QColor current_backColor=image.pixelColor(firstPoint);
            FilledArea filledarea(firstPoint,current_backColor,pen_color);
            filledarea.BoundaryFill(image);
            Filled temp;
            temp.p=firstPoint;
            temp.color=pen_color;
            filled_points.push_back(temp);
            break;
        }
        case CURVE:
        {
            if(curve_first==true)
            {
                if(mouseLR==false)
                {
                    QRgb rgb=image.pixelColor(firstPoint).rgb();
                    curve=new Curve(firstPoint,rgb);
                    image.setPixel(firstPoint,0);
                    curve_first=false;
                }
            }
            else
            {
                if(mouseLR==false)
                {
                    QRgb rgb=image.pixelColor(firstPoint).rgb();
                    curve->addPoint(firstPoint,rgb);
                    image.setPixel(firstPoint,0);
                }
                else
                {
                    curve->paintCurve(pic,image);

                    shapes.push_back(curve);
                    drawing=false;
                    curve_first=true;
                }
            }
            break;
        }
        case POLYGON:
        {
            if(polygon_first==true)
            {
                polygon=new Polygon(firstPoint);
                pic.drawPoint(firstPoint);
                polygon_first=false;
            }
            else
            {
                QPoint p_start=polygon->firstPoint();
                int dis_x=(p_start.x()-firstPoint.x())*(p_start.x()-firstPoint.x());
                int dis_y=(p_start.y()-firstPoint.y())*(p_start.y()-firstPoint.y());
                if(dis_x+dis_y<=100)
               {
                    polygon->paintFinalLine(pic);

                    shapes.push_back(polygon);
                    drawing=false;
                    polygon_first=true;
                }
                else
                {
                    polygon->add_point(firstPoint);
                    polygon->paintLine(pic);
                }
            }
            break;
        }
        default:break;
        }
    }
    isModified=true;
    update();
}
//LINE,CURVE,RECT,CIRCLE,ELLIPSE,FILLED
void PaintBackground::setOperation(int index)
{
    switch(index)
    {
    case 0: operation=TRANSLATION;break;
    case 1: operation=CUT;break;
    default:break;
    }
}

void PaintBackground::clearImage()
{
    image=QImage(700,500,QImage::Format_RGB32);
    image.fill(backColor);
    shapes.clear();
    cur_shape=NULL;

    isModified=false;
    update();
}
void PaintBackground::repaintImage(){
    image=QImage(700,500,QImage::Format_RGB32);
    image.fill(backColor);
    QPainter painter(&image);
    painter.setPen(myPen);
    for(int i=0;i<shapes.size();i++)
        shapes[i]->draw(painter);
    if(cur_shape)
        cur_shape->draw(painter);
    for(int i=0;i<filled_points.size();i++)
    {
        QColor current_backColor=image.pixelColor(filled_points[i].p);
        FilledArea filledarea(filled_points[i].p,current_backColor,filled_points[i].color);
        filledarea.BoundaryFill(image);
    }
    update();
}

void PaintBackground::setRotationAngle(int index)
{
    angle=index;
}

void PaintBackground::setImageSize(int width,int height)
{
    QImage newImage(width,height,QImage::Format_RGB32);
    image=newImage;
    update();
}
void PaintBackground::setImageColor(QColor color)
{
    backColor=color.rgb();
    backgroundColor=color;
    image.fill(backColor);
    update();
}
void PaintBackground::setPenWidth(int width)
{
    pen_width=width;
    myPen.setWidth(width);
}
void PaintBackground::setPenColor(QColor color)
{
    pen_color=color;
    myPen.setColor(color);
}
void PaintBackground::setPenStyle(int index)
{
    switch(index)
    {
    case 0: myPen.setStyle(Qt::SolidLine); break;
    case 1: myPen.setStyle(Qt::DashLine);break;
    case 2: myPen.setStyle(Qt::DotLine); break;
    case 3: myPen.setStyle(Qt::DashDotLine); break;
    case 4: myPen.setStyle(Qt::NoPen); break;
    default: break;
    }
}
void PaintBackground::setGraphyKind(int tag)
{
    graphic_kind= (Graphic_Kind)tag;
}

bool PaintBackground::openImage(QString &filename)
{
    QImage openimage;
    if(!openimage.load(filename))
        return false;
    QSize newsize=openimage.size();
    setImageSize(newsize.width(),newsize.height());
    image=openimage;

    isModified=false;
    update();
    return true;
}
bool PaintBackground::saveImage(QString &filename,char *fileformat)
{
    QImage saveimage=image;
    if(saveimage.save(filename,fileformat))
    {
        isModified=false;
        return true;
    }
    return false;
}
bool PaintBackground::IsModified()
{
    return isModified;
}

QSize PaintBackground::getImageSize()
{
    return image.size();
}
void PaintBackground::doPrint()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *printdialog=new QPrintDialog(&printer,this);
    if(printdialog->exec()==QDialog::Accepted)
    {
        QPainter painter(&printer);
        QRect rect=painter.viewport();
        QSize size=image.size();
        size.scale(rect.size(),Qt::KeepAspectRatio); //保证图片完整显示
        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0,0,image);
    }
}
