#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    area=new PaintBackground();
    scrollArea=new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(area);      //将画布添加到scrollArea中
    scrollArea->widget()->setMinimumSize(700,500);

    setCentralWidget(scrollArea);      //将scrollArea加入到主窗口中间

    isSaved=false;
    currentFile=tr("noname.png");

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if(event->type()==QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ifSave()==true)
        qApp->quit();
    else
        event->ignore(); //防止窗口默认关闭
}

void MainWindow::on_actionCreate_triggered()
{
    Dialog dialog;
    if(dialog.exec()==QDialog::Accepted)
    {
        int width=dialog.getWidth();
        int height=dialog.getHeight();
        QColor color=dialog.getBackColor();

        area->setImageSize(width,height);
        scrollArea->widget()->resize(width,height);
        area->setImageColor(color);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    doOpen();
}

void MainWindow::on_actionSave_triggered()
{
    doFileSave();
}

void MainWindow::on_actionExit_triggered()
{
    if(ifSave()==true)
        qApp->quit();
}

void MainWindow::on_actionSaveAs_triggered()
{
    doFileSaveAs();
}
void MainWindow::on_actionPrint_triggered()
{
    area->doPrint();
}

bool MainWindow::ifSave()
{
    if(area->IsModified()==true)
    {
        QMessageBox::StandardButton box;
        //警告型
        box=QMessageBox::warning(this,tr("保存图片"),tr("图片发生改变过，是否保存?"),
                                 QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(box==QMessageBox::Yes)
            return doFileSave();
        else if(box==QMessageBox::Cancel)
            return false;
    }
    return true;
}
bool MainWindow::saveFile(QString filename)
{
    if(area->saveImage(filename,"png"))
    {
        isSaved=true;
        return true;
    }
    return false;
}
void MainWindow::doCreate()
{
    if(ifSave()==true)
    {
        Dialog dialog;
        if(dialog.exec()==QDialog::Accepted)
        {
            area->clearImage();
            area->setImageSize(dialog.getWidth(),dialog.getHeight());
            scrollArea->widget()->resize(dialog.getWidth(),dialog.getHeight());
            area->setImageColor(dialog.getBackColor());

            isSaved=false;
        }
    }
}
void MainWindow::doOpen()
{
    if(ifSave()==true)
    {
        QString filename=QFileDialog::getOpenFileName(this,
                                                      tr("打开文件"),QDir::currentPath());
        if(filename.isEmpty()==false)
        {
            area->openImage(filename);
            scrollArea->widget()->resize(area->getImageSize());
                //获得图片大小 后更改scrollArea大小
            isSaved=true;
            currentFile=filename;
        }
    }
}
bool MainWindow::doFileSave()
{
    if(isSaved==true)
    {
        if(area->saveImage(currentFile,"png"))
        {
            isSaved=true;
            return true;
        }
        return false;
    }
    return doFileSaveAs();
}
bool MainWindow::doFileSaveAs()
{
    QString filename=QFileDialog::getSaveFileName(this,tr("另存为"),currentFile);
    if(filename.isEmpty()==true)
        return false;
    return saveFile(filename);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    area->setPenWidth(arg1);
}
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0: area->setPenColor(Qt::black);break;
    case 1:area->setPenColor(Qt::red);break;
    case 2:area->setPenColor(Qt::yellow);break;
    case 3:area->setPenColor(Qt::green);break;
    case 4:area->setPenColor(Qt::blue);break;
    case 5:area->setPenColor(Qt::white);break;

    default:area->setPenColor(Qt::black);break;
    }
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    area->setGraphyKind(index);
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    area->setPenStyle(index);
}

void MainWindow::on_actionClear_triggered()
{
    area->clearImage();
}

void MainWindow::on_actionRedraw_triggered()
{
    area->repaintImage();
}

void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    area->setOperation(index);
}

void MainWindow::on_actionRotation_triggered()
{
    area->doRotation();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    area->setRotationAngle(arg1);
}

void MainWindow::on_actionMagnify_triggered()
{
    area->doMaginify();
}

void MainWindow::on_actionNarrow_triggered()
{
    area->doNarrow();
}
