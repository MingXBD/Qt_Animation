#include "movinglabel.h"

void MovingLabel::setX(double nx)
{
    x=nx;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::setY(double ny)
{
    y=ny;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::setXY(double nx, double ny)
{
    x=nx;
    y=ny;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::setV_X(double nvx)
{
    v_x=nvx;
}

void MovingLabel::setV_Y(double nvy)
{
    v_y=nvy;
}

void MovingLabel::setA_X(double nax)
{
    a_x=nax;
}

void MovingLabel::setA_Y(double nay)
{
    a_y=nay;
}

void MovingLabel::setW(double nw)
{
    w=nw;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::setH(double nh)
{
    h=nh;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::setWH(double nw, double nh)
{
    w=nw;
    h=nh;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}
void MovingLabel::setV_W(double nvw)
{
    v_w=nvw;
}

void MovingLabel::setV_H(double nvh)
{
    v_h=nvh;
}

void MovingLabel::setA_W(double naw)
{
    a_w=naw;
}

void MovingLabel::setA_H(double nah)
{
    a_h=nah;
}

double MovingLabel::getX()
{
    return x;
}

double MovingLabel::getY()
{
    return y;
}

double MovingLabel::getV_X()
{
    return v_x;
}

double MovingLabel::getV_Y()
{
    return v_y;
}

double MovingLabel::getA_X()
{
    return a_x;
}

double MovingLabel::getA_Y()
{
    return a_y;
}

double MovingLabel::getW()
{
    return w;
}

double MovingLabel::getH()
{
    return h;
}

double MovingLabel::getV_W()
{
    return v_w;
}

double MovingLabel::getV_H()
{
    return v_h;
}

double MovingLabel::getA_W()
{
    return a_w;
}

double MovingLabel::getA_H()
{
    return a_h;
}

void MovingLabel::slowdown(double timepass)
{
    if((v_x+a_x*timepass)*v_x<=0)
        v_x=0,a_x=0;
    else
        v_x+=a_x*timepass;

    if((v_y+a_y*timepass)*v_y<=0)
        v_y=0,a_y=0;
    else
        v_y+=a_y*timepass;

    if((v_w+a_w*timepass)*v_w<=0)
        v_w=0,a_w=0;
    else
        v_w+=a_w*timepass;

    if((v_h+a_h*timepass)*v_h<=0)
        v_h=0,a_h=0;
    else
        v_h+=a_h*timepass;

    x+=v_x*timepass;
    y+=v_y*timepass;
    w+=v_w*timepass;
    h+=v_h*timepass;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::stop()
{
    v_x=0;
    v_y=0;
    v_w=0;
    v_h=0;
    a_x=0;
    a_y=0;
    a_w=0;
    a_h=0;
}

void MovingLabel::sizestop()
{
    v_w=0;
    v_h=0;
    a_w=0;
    a_h=0;
}

void MovingLabel::movetoX(double tx, double timepass)
{
    v_x+=a_x*timepass;
    v_y+=a_y*timepass;
    v_w+=a_w*timepass;
    v_h+=a_h*timepass;

    if((tx-x)*(tx-x-v_x*timepass)<=0)
        x=tx,v_x=0,a_x=0;
    else
        x+=v_x*timepass;

    y+=v_y*timepass;
    w+=v_w*timepass;
    h+=v_h*timepass;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::movetoY(double ty,double timepass)
{
    v_x+=a_x*timepass;
    v_y+=a_y*timepass;
    v_w+=a_w*timepass;
    v_h+=a_h*timepass;

    if((ty-y)*(ty-y-v_y*timepass)<=0)
        y=ty,v_y=0,a_y=0;
    else
        y+=v_y*timepass;

    x+=v_x*timepass;
    w+=v_w*timepass;
    h+=v_h*timepass;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::update(double timepass)
{
    v_x+=a_x*timepass;
    v_y+=a_y*timepass;
    v_w+=a_w*timepass;
    v_h+=a_h*timepass;
    x+=v_x*timepass;
    y+=v_y*timepass;
    w+=v_w*timepass;
    h+=v_h*timepass;
    if(label!=nullptr)
        label->setGeometry(int(x-w/2),int(y-h/2),int(w),int(h));
}

void MovingLabel::copy(MovingLabel *t)
{
    x=t->getX();
    y=t->getY();
    v_x=t->getV_X();
    v_y=t->getV_Y();
    a_x=t->getA_X();
    a_y=t->getA_Y();

    w=t->getW();
    h=t->getH();
    v_w=t->getV_W();
    v_h=t->getV_H();
    a_w=t->getA_W();
    a_h=t->getA_H();
}

MovingLabel::MovingLabel(QLabel *nlabel)
{
    label=nlabel;
    v_x=0;
    v_y=0;
    v_w=0;
    v_h=0;
    a_x=0;
    a_y=0;
    a_w=0;
    a_h=0;
    x=0;
    y=0;
    w=0;
    h=0;
    next=nullptr;
}

MovingLabel::~MovingLabel()
{
    delete label;
}
