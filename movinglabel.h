#ifndef MOVINGLABEL_H
#define MOVINGLABEL_H
#include <QLabel>

class MovingLabel
{
private:
    double x,y;//中心位置
    double v_x,v_y;//移动速度
    double a_x,a_y;//加速度

    double w,h;//图像大小
    double v_w,v_h;//大小变化速率
    double a_w,a_h;//加速度
public:
    QLabel* label;

    MovingLabel* next;

    void setX(double nx);
    void setY(double ny);
    void setXY(double nx,double ny);
    void setV_X(double nvx);
    void setV_Y(double nvy);
    void setA_X(double nax);
    void setA_Y(double nay);

    void setW(double nw);
    void setH(double nh);
    void setWH(double nw,double nh);
    void setV_W(double nvw);
    void setV_H(double nvh);
    void setA_W(double naw);
    void setA_H(double nah);

    double getX();
    double getY();
    double getV_X();
    double getV_Y();
    double getA_X();
    double getA_Y();
    double getW();
    double getH();
    double getV_W();
    double getV_H();
    double getA_W();
    double getA_H();

    void slowdown(double timepass);
    void stop();
    void update(double timepass);

    void copy(MovingLabel* target);

    MovingLabel(QLabel* nlabel);
    ~MovingLabel();
};

#endif // MOVINGLABEL_H
