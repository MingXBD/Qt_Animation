#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fps=60;
    LabelHead=nullptr;

    loaddata();

    But_slow=new QPushButton(this);
    But_reset=new QPushButton(this);
    pointer=new MovingLabel(new QLabel(this));
    SpawnTem=new MovingLabel(nullptr);

    connect(But_slow,&QPushButton::pressed,this,[=](){getresult();});
    connect(But_reset,&QPushButton::pressed,this,[=](){reset();});

    But_fps=new QPushButton(this);
    But_fps->setGeometry(0,0,50,50);
    But_fps->setText("60fps");
    connect(But_fps,&QPushButton::pressed,this,[=](){changeFps();});

    GlobalTimer=startTimer(1000/Fps);

    reset();


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

}

void MainWindow::reset()
{
    MovingLabel* tnext=nullptr;
    while(LabelHead!=nullptr)
    {
        tnext=LabelHead->next;
        delete LabelHead;
        LabelHead=tnext;
    }

    TimeRate=1;
    SlowingRate=0;
    LabelCount=0;
    ntime=0;
    Distence=80;
    GlobalCounter=0;
    select=nullptr;
    isRunning=true;

    But_slow->show();
    But_slow->setGeometry(1000,50,100,80);
    But_slow->setText("Slow");
    But_slow->setStyleSheet("border-image: url(:/res/button3.png);");

    But_reset->hide();
    But_reset->setGeometry(1000,50,100,80);
    But_reset->setText("Reset");
    But_reset->setStyleSheet("border-image: url(:/res/button3.png);");

    pointer->label->setStyleSheet("border-image: url(:/res/pointer.png);");
    pointer->setXY(500,380);
    pointer->setWH(100,60);

    SpawnTem->setXY(300,800);
    SpawnTem->setWH(200,80);
    SpawnTem->setV_Y(-1234);
    SpawnTem->setV_W(-SpawnTem->getV_Y()/4);
    SpawnTem->setV_H(-SpawnTem->getV_Y()/8);

}

void MainWindow::getresult()
{
    SlowingRate=-0.01;
    But_slow->hide();
    qDebug()<<"slow";
}

void MainWindow::loaddata()
{
    std::ifstream fin;
    QString fileName = QCoreApplication::applicationDirPath();
    qDebug()<<fileName;
    fin.open((fileName+"/data.txt").toStdString());
    if(!fin.is_open())
    {
        qDebug()<<"read fail";
        return;
    }
    fin.seekg(0);
    std::string name;
    std::string num;
    stunum=0;
    while(fin>>name>>num)
    {
        names[stunum++]=QString::fromStdString(name+"\n"+num);
    }
    std::srand(qrand()%(unsigned)-1);
    std::random_shuffle(names,names+stunum);
    qDebug()<<"load succeed with "<<stunum<<" students";
}

void MainWindow::changeFps()
{
    if(Fps==60)
        Fps=30;
    else
        Fps=60;
    But_fps->setText(QString::number(Fps)+"fps");
    killTimer(GlobalTimer);
    GlobalTimer=startTimer(1000/Fps);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    ntime++;
    //qDebug()<<ntime;
    if(SlowingRate!=0)
    {
        TimeRate+=TimeRate*SlowingRate;
    }
    if(TimeRate<=0.005)
    {
        MovingLabel* tp=LabelHead;
        while(tp!=nullptr)
        {
            tp->stop();
            tp=tp->next;
        }
        TimeRate=1;
        SlowingRate=0;
//        qDebug()<<"stop";
//        qDebug()<<select->label->text();
        select->setV_W(200);
        select->setV_H(90);
        isRunning=false;
        tp=LabelHead;
        while(tp!=nullptr)
        {
            if(tp==select)
            {
                tp=tp->next;
                continue;
            }
            tp->setA_X((qrand()%2==0?1:-1)*(qrand()%600+400));
            tp=tp->next;
        }
        pointer->setA_X(400);
        But_reset->show();
        qDebug()<<"change end";
    }
    if(!isRunning)
    {
        if(select->getW()>600)
            select->stop();
        if(pointer->getX()>1400)
            pointer->stop();
        else
            pointer->update(1/Fps);
    }
    if(LabelHead==nullptr)
    {
        QLabel* nl=new QLabel(this);
        //nl->setStyleSheet("border-image: url(:/res/pigbut.png);");
        nl->setText("我知道你们看不见这条嘿嘿嘿");
        nl->show();
        LabelHead=new MovingLabel(nl);
        LabelHead->copy(SpawnTem);
        LabelCount++;
    }
    MovingLabel* tp=LabelHead;
    if(fabs(SpawnTem->getY()-tp->getY())>Distence&&isRunning)
    {
        QLabel* nl=new QLabel(this);
        //nl->setStyleSheet("border-image: url(:/res/block.png);font:"+QString::number(int(SpawnTem->getW()/10))+"pt;");
        nl->setAlignment(Qt::AlignCenter);
        //nl->setText("宋克斐 919106840631");
        if(GlobalCounter!=stunum)
        {
            nl->setText(names[GlobalCounter++]);
        }
        else
        {
            std::srand(qrand()%(unsigned)-1);
            std::random_shuffle(names,names+stunum);
            GlobalCounter=0;
            qDebug()<<QTime::currentTime();
            nl->setText(names[GlobalCounter++]);
        }
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
        tp->update(1/Fps*TimeRate);
        if(select==nullptr||fabs(select->getY()-pointer->getY())>fabs(tp->getY()-pointer->getY()))
            select=tp;
        tp->label->setStyleSheet("border-image: url(:/res/block.png);font:"+QString::number(int(tp->getW()/15))+"pt;");
        if(tp->getY()<=pointer->getY()&&tp->getV_H()>0&&isRunning)
        {
            //tp->setA_Y(-tp->getA_Y());
            tp->setV_W(-tp->getV_W());
            tp->setV_H(-tp->getV_H());
            //tp->setA_W(-tp->getA_W());
            //tp->setA_H(-tp->getA_H());
        }
        tp=tp->next;
    }
    if(select!=nullptr)
        select->label->raise();
    tp=LabelHead;
    MovingLabel* pp=nullptr;
    while(tp!=nullptr)
    {
        MovingLabel* tnext=tp->next;
        if(
                (tp->getY()+tp->getH()/2<=0)||
                (tp->getY()-tp->getH()/2>=768)||
                (tp->getX()+tp->getW()/2<=0)||
                (tp->getX()-tp->getW()/2>=1280)
          )
        {
            delete tp;
        }
        else
        {
            tp->next=pp;
            pp=tp;
        }
        tp=tnext;
    }
    tp=pp;
    LabelHead=nullptr;
    while(tp!=nullptr)
    {
        MovingLabel* tnext=tp->next;
        tp->next=LabelHead;
        LabelHead=tp;
        tp=tnext;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
