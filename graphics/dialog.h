#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QPalette>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    int getWidth();
    int getHeight();
    QColor getBackColor();

private slots:
    void on_toolButton_clicked();
private:
    Ui::Dialog *ui;
    QColor backColor;
};

#endif // DIALOG_H
