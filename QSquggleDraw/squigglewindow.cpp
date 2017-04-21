
#include <QFileDialog>
#include <math.h>

#include "squigglewindow.h"
#include "ui_squigglewindow.h"

SquiggleWindow::SquiggleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SquiggleWindow)
{
    ui->setupUi(this);
    xstep = 1;
    ystep = 160;
    ymult = 3;
    imageScaleUp = 3;
    xsmooth = 128.0;
    liner = new QPainterPath();
}

SquiggleWindow::~SquiggleWindow()
{
    delete ui;
}

void SquiggleWindow::on_btnOpen_clicked()
{
    QString f = QFileDialog::getOpenFileName(this,tr("图像"),"./",tr("Image(*.jpg *.png)"));
    sourceimg = QImage(f);
    ui->label->setPixmap(QPixmap::fromImage(sourceimg));
}

void SquiggleWindow::RenderImage()
{
    //彩色变成灰度图片
    QImage gray = sourceimg;
    QRgb *grays = (QRgb *)sourceimg.scanLine(0);
    double r = 0.0;
    double a = 0.0; // 振动幅度
    double z = 0;
    int gray_value = 0;
    delete liner;
    liner = new QPainterPath();

    for(int y =0;y<gray.height();y+=(height()/ystep))
    {
        QPointF start(0.0,y);
        liner->moveTo(start);

        for(int x=0;x<gray.width();x+=xstep)
        {
            //gray scale
            gray_value = qGray(grays[x+y*(gray.width())]);
            z = 256-gray_value;
            r = (z/(double)ystep)*ymult;
            a += z/(xsmooth*1.0);
            double ym = y+(sin(a)*r);
            QPointF po(x,ym);
            liner->lineTo(po);
        }
    }
}

void SquiggleWindow::DrawImage()
{
    QImage s(sourceimg.width(),sourceimg.height(),QImage::Format_RGB32);
    s.fill(Qt::white);
    QPainter painter(&s);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawPath(*liner);
    painter.end();
    ui->label->setPixmap(QPixmap::fromImage(s));
}

void SquiggleWindow::on_fds_clicked()
{
    RenderImage();
    DrawImage();
}

//xstep change
void SquiggleWindow::on_sliderXt_valueChanged(int value)
{
    ui->xsteplabel->setText(tr("%1").arg(value));
    xstep = value;
    on_fds_clicked();
}

//ystep change
void SquiggleWindow::on_sliderYt_valueChanged(int value)
{
    ui->ysteplabel->setText(tr("%1").arg(value));
    ystep = value;
    on_fds_clicked();
}

//ymult change
void SquiggleWindow::on_sliderYm_valueChanged(int value)
{
    ui->ymultlabel->setText(tr("%1").arg(value));
    ymult = value;
    on_fds_clicked();
}

//xsmooth change
void SquiggleWindow::on_sliderSm_valueChanged(int value)
{
   ui->xsmoothlabel->setText(tr("%1").arg(value));
   xsmooth = value;
    on_fds_clicked();
}
