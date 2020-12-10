#ifndef WIDGET_H
#define WIDGET_H
#include<QTimerEvent>
#include <QWidget>
#include<QtOpenGL/qgl.h>
#include<GL/gl.h>
#include<GL/glu.h>


#include<vector>

#include <QGLWidget>


typedef struct Vertex {
    //定义三维图形的
    //用于face结构体中
    float x, y, z;
} Vertex;
typedef struct Face {
    //多边形（三角形）面的结构体
  //  Face(void) : vert_number(0), verts(0) {};
    int vert_number;        //记录顶点的个数
    Vertex **verts;          //这是一个面的所有 顶点数组（含有坐标）
    float normal[3];         //记录点的法向量，分别是x，y，z三个方向
} Face;
typedef struct myMesh {
    int vert_number=0;        //总的顶点个数
    Vertex *verts;             //顶点数组
    int face_number=0;                 //面的数目
    Face *faces;
    QVector<Vertex>point;
} myMesh;


class Widget : public QGLWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void initializeGL();

    void resizeGL(int width, int height);

    void paintGL();
    void timerEvent(QTimerEvent *event);

    void mousePressEvent(QMouseEvent *event);
private:

    void draw();
    void mousehandle();
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;
    QString   file_name;
    myMesh* inf;
    bool done=false;
    GLfloat mRotate = 0;
};



#endif // WIDGET_H

