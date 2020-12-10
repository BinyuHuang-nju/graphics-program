#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintbackground.h"
#include "dialog.h"
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QEvent>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_actionCreate_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_actionSaveAs_triggered();
    void on_actionPrint_triggered();

    void on_spinBox_valueChanged(int arg1);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(int index);

    void on_actionClear_triggered();
    void on_actionRedraw_triggered();
    void on_comboBox_4_currentIndexChanged(int index);

    void on_actionRotation_triggered();
    void on_spinBox_2_valueChanged(int arg1);
    void on_actionMagnify_triggered();
    void on_actionNarrow_triggered();

private:
    Ui::MainWindow *ui;
    PaintBackground *area;        //画板类
    QScrollArea *scrollArea;      //滚动区域类

    bool isSaved;
    QString currentFile;       //当前文件路径
    bool ifSave();               //是否保存文件
    bool saveFile(QString filename);
    void doCreate();
    void doOpen();
    bool doFileSave();
    bool doFileSaveAs();
};

#endif // MAINWINDOW_H
