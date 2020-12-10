#include<QtOpenGL/qgl.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<assert.h>
#include<iostream>
#include "widget.h"
#include"qfiledialog.h"
#include <QMouseEvent>

#include <QColorDialog>
using namespace std;
//#include <GLU.h>

#include <Windows.h>

myMesh * ReadOffFile(QString filename)
{
    char*  ch;

    QByteArray ba = filename.toLatin1(); // must

    ch=ba.data();

    int i;
    FILE *fp;     //开始读入文件
    if (!(fp = fopen(ch, "r"))) {
        cout << "无法打开文件" << endl;
        return 0;
    }
  //  tmpfile.open(QIODevice::ReadOnly);
    myMesh *mesh = new myMesh();        //建立我们的mesh类
    //进行读入文件的操作
    int vert_number = 0;                            //记录顶点个数
    int face_number = 0;                                    //记录面的个数
    int line_number = 0;                                   //记录边的个数
    int line_count = 0;                               //这个是我读入了几行
    char buffer[1024];
    while (fgets(buffer, 1023, fp)) {
        line_count++;
        char *bufferp = buffer;
        while (isspace(*bufferp)) bufferp++;
        if (*bufferp == '#') continue;
        if (*bufferp == '\0') continue;
        if (vert_number == 0) {
            if (!strstr(bufferp, "OFF")) {
                if ((sscanf(bufferp, "%d%d%d", &vert_number, &face_number, &line_number) != 3) || (vert_number == 0)) {
                    cout << "存在语法错误！"  << endl;
                    fclose(fp);
                    return NULL;
                }
                //存储顶点的信息
                cout << "aa" << vert_number << "--" << face_number << endl;
                mesh->verts = new Vertex [vert_number];
                assert(mesh->verts);
                //存储面的信息
                mesh->faces = new Face [face_number];
                assert(mesh->faces);
            }
        }
        else if (mesh->vert_number < vert_number) {
            Vertex& vert = mesh->verts[mesh->vert_number++];
            if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
                cout << "点的信息中，数据量不足（3个）" << endl;
                fclose(fp);
                return NULL;
            }
        }
        else if (mesh->face_number < face_number) {
            Face& face = mesh->faces[mesh->face_number++];          //新建一个face对象
            bufferp = strtok(bufferp, " \t");
            if (bufferp) face.vert_number = atoi(bufferp);
            else {
                fclose(fp);
                return NULL;
            }
            face.verts = new Vertex *[face.vert_number];
            //建立面的数组
            assert(face.verts);
            for (i = 0; i < face.vert_number; i++) {
                bufferp = strtok(NULL, " \t");
                if (bufferp) face.verts[i] = &(mesh->verts[atoi(bufferp)]);
                else {
                    fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
                    fclose(fp);
                    return NULL;
                }
            }
            //get_normal(face);
        }
        else {
            cout << "格式存在错误！"  << endl;
            break;
        }
    }
    fclose(fp);
    return mesh;
}

Widget::Widget(QWidget *parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    rotationX = -21.0;

    rotationY = -57.0;

    rotationZ = -0.0;
}

Widget::~Widget()
{

}



void Widget::initializeGL()
{
    qglClearColor(Qt::white);

    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
}

void Widget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    GLfloat x = GLfloat(width) / height;

    glFrustum(-x,+x,-1.0,+1.0,4.0,15.0);

    glMatrixMode(GL_MODELVIEW);

    if (file_name.isEmpty())
    {
        file_name = QFileDialog::getOpenFileName(this, tr("Open File"),
                                     "",tr("OFF (*.off)"));
          inf=ReadOffFile(file_name);
    }
}



void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}



void Widget::draw()
{
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    //glTranslatef(-1.5f, 0.0f, -6.0f);
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(mRotate, 1.0, 1.0, 0.0);
    {

        GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式

        GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBA模式的环境光，为0

        GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBA模式的漫反射光，全白光

        GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBA模式下的镜面光 ，全白光

        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);

        glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);

        glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);

        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
        //开启灯光

        glEnable(GL_LIGHT0);

        glEnable(GL_LIGHTING);

        glEnable(GL_DEPTH_TEST);

    }

    for(int i = 0; i < inf->face_number; ++i)
    {
        glLoadName(i);
        glBegin(GL_TRIANGLES);
        if(i%3==0)
        qglColor(Qt::blue);

       else if(i%3==1)
             qglColor(Qt::red);
        else if(i%3==2)
             qglColor(Qt::yellow);

        for(int j = 0; j <inf->faces[i].vert_number; ++j)
        {
            glVertex3f(inf->faces[i].verts[j]->x,inf->faces[i].verts[j]->y,inf->faces[i].verts[j]->z);
            //glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);

        }

        glEnd();
    }
    done=true;

}
void Widget::timerEvent(QTimerEvent *event)
{    mRotate += 0.1f;
     //mRotateQuad -= 0.15f;
      updateGL();
       QGLWidget::timerEvent(event);
}

void Widget::mousehandle()
{
    mRotate += 5;
    if (mRotate > 360)
    {
        mRotate -= 360;
    }
    this->updateGL();
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)  //按左键旋转
    {
        mousehandle();
    }
}

