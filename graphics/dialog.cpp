#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    backColor=Qt::white; //背景颜色初始化为白色
}

Dialog::~Dialog()
{
    delete ui;
}
int Dialog::getWidth()
{
    return ui->widthSpinBox->text().toInt();
}
int Dialog::getHeight()
{
    return ui->heightSpinBox->text().toInt();
}
QColor Dialog::getBackColor()
{
    return backColor;
}
void Dialog::on_toolButton_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid())
    {
        backColor=color;
        //用textBrower来显示用户选择的颜色
        QPalette palette=ui->textBrowser->palette();
        palette.setColor(QPalette::Base,backColor);
        ui->textBrowser->setPalette(palette);
        update();
    }
}
