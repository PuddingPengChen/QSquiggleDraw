#ifndef SQUIGGLEWINDOW_H
#define SQUIGGLEWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>


namespace Ui {
class SquiggleWindow;
}

class SquiggleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SquiggleWindow(QWidget *parent = 0);
    ~SquiggleWindow();

private slots:
    void on_btnOpen_clicked();

    void on_fds_clicked();

    void on_sliderXt_valueChanged(int value);

    void on_sliderYt_valueChanged(int value);



    void on_sliderYm_valueChanged(int value);

    void on_sliderSm_valueChanged(int value);

private:
    Ui::SquiggleWindow *ui;

    void RenderImage();
    void DrawImage();

    QImage sourceimg;
    QPainterPath paths;
    QPainterPath * liner;


    //参数
    int xstep;
    int ystep;
    int ymult;
    double imageScaleUp;
    double xsmooth;

};

#endif // SQUIGGLEWINDOW_H
