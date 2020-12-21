#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fps=60;
    LabelHead=nullptr;
    SlowingRate=0;
    LabelCount=0;
    ntime=0;

    But_slow=new QPushButton(this);
    But_slow->setGeometry(50,50,200,100);
    But_slow->setText("Slow");
    connect(But_slow,&QPushButton::pressed,this,[=](){getresult();});

    SpawnTem=new MovingLabel(nullptr);
    SpawnTem->setXY(680,800);
    SpawnTem->setWH(200,80);
    SpawnTem->setV_Y(-100);
    SpawnTem->setV_X(0);
    SpawnTem->setA_Y(-20);

//    QLabel* Labelmp4=new QLabel(this);

//    LabelHead=new MovingLabel(Labelmp4);
//    LabelHead->setXY(640,768);
//    LabelHead->setWH(200,80);
//    LabelHead->setV_Y(-100);
//    LabelHead->setA_Y(10);
//    Labelmp4->setStyleSheet("border-image: url(:/res/glass.png);");

//    QMediaPlayer* player;
//    QVideoWidget* widget;
//    QVBoxLayout* layout;


//    player=new QMediaPlayer;
//    widget=new QVideoWidget;
//    layout = new QVBoxLayout;
//    layout->setMargin(1);

//    player->setVideoOutput(widget);
//    player->setMedia(QMediaContent(QUrl("qrc:/res/testvideo.avi")));
//    Labelmp4->setLayout(layout);
//    Labelmp4->show();
    GlobalTimer=startTimer(1000/Fps);
}

void MainWindow::getresult()
{
    SlowingRate=10;
    qDebug()<<"slow";
}

void MainWindow::timerEvent(QTimerEvent *)
{
    ntime++;
    qDebug()<<SpawnTem->getV_Y()<<' '<<SpawnTem->getA_Y();
    if(SlowingRate!=0)
    {
        double tv=SpawnTem->getV_Y();
        double ta=SpawnTem->getA_Y();
        double timepass=Fps/1000;
        if((tv-ta*timepass)*tv<=0)
        {
            SpawnTem->setV_Y(0);
            SpawnTem->setA_Y(0);
        }
        else
        {
            SpawnTem->setV_Y(tv-ta*timepass);
        }
    }
    if(LabelHead==nullptr)
    {
        QLabel* nl=new QLabel(this);
        nl->setStyleSheet("border-image: url(:/res/glass.png);");
        nl->setText(QString::number(ntime));
        nl->show();
        LabelHead=new MovingLabel(nl);
        LabelHead->copy(SpawnTem);
        LabelCount++;
    }
    MovingLabel* tp=LabelHead;
    if(fabs(SpawnTem->getY()-tp->getY())>50)
    {
        QLabel* nl=new QLabel(this);
        nl->setStyleSheet("border-image: url(:/res/glass.png);");
        nl->setText(QString::number(ntime));
        nl->show();
        MovingLabel* nm=new MovingLabel(nl);
        nm->copy(SpawnTem);
        nm->next=LabelHead;
        LabelHead=nm;
        LabelCount++;
    }
    tp=LabelHead;
    while(tp!=nullptr)
    {
        if(SlowingRate==0)
        {
            tp->update(Fps/1000);
        }
        else
        {
            if(tp->getV_Y()!=0)
            {
                //if(tp->getA_Y()<0)
                    tp->setA_Y(tp->getA_Y()+SlowingRate*Fps/1000);
            }
            tp->slowdown(Fps/1000);
        }
        if(tp->getY()<300&&tp->getA_Y()<0)
        {
            tp->setA_Y(-tp->getA_Y());
        }
        tp=tp->next;
    }
    tp=LabelHead;
    MovingLabel* pp=nullptr;
    while(tp->next!=nullptr)
    {
        pp=tp;
        tp=tp->next;
    }
    if(tp!=nullptr&&pp!=nullptr)
    {
//        qDebug()<<tp->getY()<<' '<<tp->getH()/2<<' '<<tp->getY()+tp->getH()/2;
        if(tp->getY()+tp->getH()/2<=0)
        {
            pp->next=nullptr;
            delete tp;
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
