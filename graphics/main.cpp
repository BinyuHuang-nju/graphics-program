#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("graphics");
    w.show();

    return a.exec();
}

/*
1、二维图形的输入功能 ：直线、曲线、多边形、填充区域
2、二维图形的编辑功能 ：直线、曲线、多边形、填充区域
3、二维图形的裁剪功能 ：裁剪窗口可编辑
4、二维图形的变换功能 ：平移、旋转、缩放
5、二维图像的存储功能 ：将绘制出来的图形保存为图像
6、三维模型的显示功能 ：载入并显示一个OFF格式的三维模型

*/
