#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("border-image: url(:/res/happy.jpg);");

    Fps=60;
    LabelHead=nullptr;
    GiftHead=nullptr;

    loaddata();

    But_slow=new QPushButton(this);
    But_reset=new QPushButton(this);
    But_next=new QPushButton(this);
    pointer=new MovingLabel(new QLabel(this));
    SpawnTem=new MovingLabel(nullptr);
    GiftTem=new MovingLabel(nullptr);
    InfoBoard=new MovingLabel(new QLabel(this));

    InfoBoard->label->setStyleSheet("QLabel{border-image: url(:/res/block.png);font: 28pt;font-weight:bold;}");
    InfoBoard->label->setAlignment(Qt::AlignCenter);

    connect(But_slow,&QPushButton::pressed,this,[=](){getresult();});
    connect(But_reset,&QPushButton::pressed,this,[=](){reset();});
    connect(But_next,&QPushButton::pressed,this,[=](){nextgift();});

    But_fps=new QPushButton(this);
    But_fps->setGeometry(0,0,50,50);
    But_fps->setText("60fps");
    connect(But_fps,&QPushButton::pressed,this,[=](){changeFps();});

    GlobalTimer=startTimer(1000/Fps);

    {
        giftaddr[0]="food1.jpg";
        giftaddr[1]="food2.jpg";
        giftaddr[2]="food2.jpg";
        giftaddr[3]="food3.jpg";
        giftaddr[4]="food4.jpg";

        for(int i=0;i<=4;i++)
        {
            giftInfo[i]="零食大礼包\n——抓住程序员的心，先从胃开始";
        }

        giftaddr[5]="growhair.jpg";
        giftInfo[5]="超级大奖\n——关心程序员，从头发做起";

        giftaddr[6]="Humidifier.jpg";
        giftInfo[6]="加湿器&香薰机\n——美丽的宿舍，程序员们的家";

        for(int i=7;i<12;i++)
            giftaddr[i]="milktea.png",
            giftInfo[i]="奶茶x4\n——是你的奶茶哟~";

        for(int i=12;i<18;i++)
            giftaddr[i]="head.jpg",
            giftInfo[i]="头部按摩仪\n——关心程序员，从头做起（双关？）";

        for(int i=18;i<=24;i++)
            giftaddr[i]="hammer.jpg",
            giftInfo[i]="按摩锤\n——脖子不舒服，锤一锤就好了";


        giftnum=24;

        for(int i=0;i<giftnum;i++)
            giftoraddr[i]=giftaddr[i];
    }

    reset();

    {
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

    tnext=nullptr;
    while(GiftHead!=nullptr)
    {
        tnext=GiftHead->next;
        delete GiftHead;
        GiftHead=tnext;
    }

    TimeRate=1;
    SlowingRate=0;
    LabelCount=0;
    ntime=0;
    Distence=80;
    GiftDistence=200;
    GlobalCounter=0;
    select=nullptr;
    Giftselect=nullptr;
    isRunning=true;

    But_slow->show();
    But_slow->setGeometry(1030,80,150,80);
    But_slow->setText("抽一个小可爱~");
    But_slow->setStyleSheet("QPushButton{border-image: url(:/res/button3.png);font: 15pt;font-weight: bold}");

    But_reset->hide();
    But_reset->setGeometry(1030,80,150,80);
    But_reset->setText("不行！重抽一个！");
    But_reset->setStyleSheet("QPushButton{border-image: url(:/res/button3.png);font: 13pt;font-weight: bold}");

    But_next->hide();
    But_next->setGeometry(1030,200,150,80);
    But_next->setText("抬走！下一位！");
    But_next->setStyleSheet("QPushButton{border-image: url(:/res/button3.png);font: 15pt;font-weight: bold}");


    pointer->label->setStyleSheet("border-image: url(:/res/pointer.png);");
    pointer->setXY(500,380);
    pointer->setWH(100,60);

    SpawnTem->setXY(300,800);
    SpawnTem->setWH(200,80);
    SpawnTem->setV_Y(-1234);
    SpawnTem->setV_W(-SpawnTem->getV_Y()/4);
    SpawnTem->setV_H(-SpawnTem->getV_Y()/8);

    GiftTem->setXY(800,-50);
    GiftTem->setWH(100,130);
    GiftTem->setV_Y(2346);
    GiftTem->setV_W(GiftTem->getV_Y()/4);
    GiftTem->setV_H(GiftTem->getV_Y()/8);

    InfoBoard->label->hide();
    InfoBoard->setXY(600,900);
    InfoBoard->setWH(800,200);
    InfoBoard->stop();

    std::srand(qrand()%(unsigned)-1);
    std::random_shuffle(names,names+stunum);
    std::random_shuffle(giftaddr,giftaddr+giftnum);
    GlobalCounter=0;
    GiftCounter=0;
}

void MainWindow::nextgift()
{
    if(stunum!=1)
    for(int i=0;i<stunum;i++)
    {
        if(names[i]==select->OriInfo)
        {
            QString temp=names[stunum-1];
            names[stunum-1]=names[i];
            names[i]=temp;
            stunum-=1;
            break;
        }
    }
    if(giftnum!=1)
    for(int i=0;i<giftnum;i++)
    {
        if(giftaddr[i]==Giftselect->OriInfo)
        {
            QString temp=giftaddr[giftnum-1];
            giftaddr[giftnum-1]=giftaddr[i];
            giftaddr[i]=temp;
            giftnum-=1;
            break;
        }
    }
    reset();
}

void MainWindow::getresult()
{
    SlowingRate=-0.01;
    But_slow->hide();
    qDebug()<<"slow";
}

void MainWindow::loaddata()
{
//    std::ifstream fin;
//    QString fileName = QCoreApplication::applicationDirPath();
//    qDebug()<<fileName;
//    fin.open((fileName+"/data.txt").toStdString());
//    if(!fin.is_open())
//    {
//        qDebug()<<"read fail";
//        return;
//    }
//    fin.seekg(0);
//    std::string name;
//    std::string num;
//    stunum=0;
//    while(fin>>name>>num)
//    {
//        names[stunum++]=QString::fromStdString(name+"\n"+num);
//    }

    QString tname[]={
        "919102270213\n郑涵予",
        "919103860142\n薛瑞",
        "919103860248\n赵金欣",
        "919106840101\n陈子颖",
        "919106840102\n崔艺霖",
        "919106840103\n地那尔·吾克力汗",
        "919106840104\n杜兆琪",
        "919106840105\n黄梓伊",
        "919106840106\n梁玉婷",
        "919106840107\n罗露",
        "919106840108\n秦华宇",
        "919106840110\n雍麒燕",
        "919106840111\n于舒琪",
        "919106840112\n张青艳",
        "919106840113\n周芷萌",
        "919106840114\n曹洋",
        "919106840115\n曾祥武",
        "919106840116\n陈令涛",
        "919106840117\n成吴浩",
        "919106840118\n戴鹏程",
        "919106840119\n丁少童",
        "919106840120\n俄合拉斯·博拉提江",
        "919106840121\n方梦麒",
        "919106840122\n冯毅",
        "919106840123\n候志鹏",
        "919106840124\n霍谦",
        "919106840125\n季若曦",
        "919106840127\n李骜",
        "919106840128\n李弘瑄",
        "919106840129\n李鹏飞",
        "919106840131\n李兴昊",
        "919106840132\n李洲诚",
        "919106840133\n李子园",
        "919106840134\n刘星辰",
        "919106840135\n申明",
        "919106840136\n史浚申",
        "919106840137\n孙亦刘",
        "919106840138\n汪思贤",
        "919106840139\n谢伊凡",
        "919106840140\n徐双鹏",
        "919106840141\n杨轶凡",
        "919106840142\n杨玉超",
        "919106840143\n伊拉塔",
        "919106840144\n张壮",
        "919106840145\n周俊刚",
        "919106840146\n周旭",
        "919106840147\n朱彬闻",
        "919106840148\n庄文韬",
        "919106840149\n邹文泽",
        "919107390102\n贡金金",
        "9191160D0236\n王子辉",
        "9191160D0539\n张俊杰",
        "919000730008\n陈一涵",
        "9191010E0505\n陈强",
        "9191010E0525\n唐湖添",
        "9191010E0643\n周航",
        "919103350220\n吴立言",
        "919106840201\n陈雅娟",
        "919106840202\n高宏艳",
        "919106840204\n李嘉琳",
        "919106840205\n林煊",
        "919106840206\n马琬鎏",
        "919106840207\n庞冬梅",
        "919106840208\n山杜哈西·土鲁四拜克",
        "919106840209\n许瑶琪",
        "919106840210\n殷莹莹",
        "919106840211\n张嘉琪",
        "919106840212\n周运莲",
        "919106840213\n邹申申",
        "919106840215\n陈观遥",
        "919106840216\n陈豪",
        "919106840217\n东宸阳",
        "919106840219\n方伟铭",
        "919106840220\n顾涵霖",
        "919106840221\n顾思淳",
        "919106840222\n顾子阳",
        "919106840223\n黄栋篪",
        "919106840224\n李奕慷",
        "919106840225\n李仲宇",
        "919106840226\n刘禄",
        "919106840227\n刘伟强",
        "919106840228\n刘兴泽",
        "919106840229\n卢云",
        "919106840230\n满达",
        "919106840231\n尚恕诚",
        "919106840232\n田思圆",
        "919106840233\n汪乾傲",
        "919106840234\n王浩宇",
        "919106840235\n王宏睿",
        "919106840236\n王龙",
        "919106840237\n王轩",
        "919106840238\n武子凡",
        "919106840239\n谢石林",
        "919106840241\n宰群彬",
        "919106840242\n张晨浩",
        "919106840243\n张淏辰",
        "919106840244\n张伟",
        "919106840245\n张霄",
        "919106840246\n赵非凡",
        "919106840247\n赵明慧",
        "919106840248\n赵耀",
        "919107810330\n刘陈昕",
        "919108320105\n陈博宏",
        "9191100Y0201\n耿嘉仪",
        "919102380112\n郑陈烨",
        "919103860337\n肖建文",
        "919103860612\n陈润泽",
        "919106840301\n蔡琛",
        "919106840302\n曹露婷",
        "919106840303\n顾晨旭",
        "919106840304\n桂雯静",
        "919106840305\n黄芊芊",
        "919106840306\n李莲玉",
        "919106840307\n王子祺",
        "919106840308\n谢东娜",
        "919106840309\n徐唱",
        "919106840310\n杨丽琛",
        "919106840311\n张倩",
        "919106840312\n张潇丹",
        "919106840313\n张云香",
        "919106840314\n曹笛",
        "919106840315\n陈震杰",
        "919106840316\n陈子航",
        "919106840317\n成喆",
        "919106840318\n程洲",
        "919106840319\n崔科宇",
        "919106840320\n崔禹斌",
        "919106840321\n丁浩楠",
        "919106840322\n洪毅涛",
        "919106840323\n解志琦",
        "919106840324\n李秉珂",
        "919106840325\n李琦",
        "919106840326\n李庆烨",
        "919106840327\n李永康",
        "919106840328\n林雨浓",
        "919106840329\n刘豪杰",
        "919106840330\n毛日勇",
        "919106840331\n宁栗晨",
        "919106840332\n沈思宇",
        "919106840333\n孙傲歆",
        "919106840334\n唐理",
        "919106840335\n汪起羽",
        "919106840336\n王澳",
        "919106840337\n王博凡",
        "919106840338\n王鸣逸",
        "919106840339\n王念业",
        "919106840340\n王文楷",
        "919106840341\n王子杰",
        "919106840342\n魏文玺",
        "919106840343\n辛梓帆",
        "919106840344\n修国栋",
        "919106840345\n徐盛东",
        "919106840346\n杨健",
        "919106840348\n郑伟杰",
        "919113100209\n代领",
        "919113250213\n宛浩宇",
        "9191010E0636\n王宇星",
        "919102380118\n方雨辰",
        "919103860607\n林思捷",
        "9191040G0930\n唐梓舜",
        "919106840401\n陈晓佳",
        "919106840402\n陈馨悦",
        "919106840403\n丁以佳",
        "919106840404\n傅雪桐",
        "919106840405\n李岸昱",
        "919106840406\n苏新评",
        "919106840407\n吴苏湘",
        "919106840408\n许越",
        "919106840409\n杨舟",
        "919106840410\n叶晓敏",
        "919106840411\n张楠秀",
        "919106840412\n张文燕",
        "919106840413\n陈建",
        "919106840414\n顾陈一飞",
        "919106840415\n郭廷章",
        "919106840416\n胡嘉宇",
        "919106840417\n江楠",
        "919106840418\n姜宇",
        "919106840419\n金雨凡",
        "919106840420\n阚东",
        "919106840421\n李广通",
        "919106840422\n李龙雨",
        "919106840423\n刘明承",
        "919106840424\n柳翰坤",
        "919106840425\n吕辉",
        "919106840426\n朴理龙",
        "919106840427\n钱浩",
        "919106840428\n邱俊杰",
        "919106840429\n谭鑫",
        "919106840430\n唐子恒",
        "919106840432\n涂子朋",
        "919106840433\n王德磊",
        "919106840434\n王瀚楠",
        "919106840435\n王宏扬",
        "919106840436\n王炜杰",
        "919106840437\n王鑫宇",
        "919106840438\n王政",
        "919106840439\n王周",
        "919106840440\n韦永贤",
        "919106840441\n卫子涛",
        "919106840442\n张灿",
        "919106840443\n张衡",
        "919106840444\n张赛赛",
        "919106840445\n张小阳",
        "919106840446\n张郑",
        "919106840447\n钟柱",
        "919106840448\n朱煜庭",
        "919107820115\n王顺风",
        "918106840410\n夏一璠",
        "9191010F0209\n郭晟男",
        "919103860301\n曾佑泠",
        "919103860327\n李守欢",
        "9191040G0328\n宋禹润",
        "919106840501\n蔡瑾瑶",
        "919106840502\n顾玮颉",
        "919106840503\n韩心源",
        "919106840504\n蒋锦怡",
        "919106840506\n孙笑笑",
        "919106840507\n王晨旭",
        "919106840508\n王雨昕",
        "919106840510\n钟丽环",
        "919106840511\n周新宜",
        "919106840512\n朱蓓蕾",
        "919106840513\n曹直树",
        "919106840514\n陈硕",
        "919106840515\n陈新鹏",
        "919106840516\n代吾然·阿吉吐尔逊",
        "919106840517\n符子悦",
        "919106840518\n高洁金",
        "919106840519\n黄光景",
        "919106840520\n黄子进",
        "919106840522\n李博",
        "919106840523\n李孟涛",
        "919106840524\n李若晨",
        "919106840525\n梁梓涛",
        "919106840526\n刘睿捷",
        "919106840527\n刘诗祥",
        "919106840528\n刘梓旭",
        "919106840530\n钱楠良",
        "919106840531\n邱凌峰",
        "919106840532\n沈祺尧",
        "919106840533\n覃日煜",
        "919106840534\n王涵正",
        "919106840535\n王佳龙",
        "919106840536\n王杉",
        "919106840537\n王星",
        "919106840538\n吴瀚",
        "919106840539\n闫馥麟",
        "919106840540\n严宇昂",
        "919106840541\n姚济昌",
        "919106840542\n姚凯",
        "919106840543\n张文涛",
        "919106840545\n钟峻锴",
        "919106840546\n周子凯",
        "919106840547\n朱竑典",
        "919106840548\n左孟辰",
        "919107390108\n李若璇",
        "919108320106\n樊一君",
        "919113590116\n傅沐晖",
        "9191160D0110\n朱铭泽",
        "9191160D0119\n李辰豪",
        "918106840143\n吴强",
        "9191010E0318\n李建华",
        "9191010F0110\n胡景潇",
        "919102270135\n彭世昱",
        "919106840602\n顾芷瑜",
        "919106840603\n黄贝柔",
        "919106840604\n黄思琪",
        "919106840605\n黄甜",
        "919106840606\n林叶洁",
        "919106840607\n陆静雯",
        "919106840609\n王文静",
        "919106840610\n吴昕睿",
        "919106840611\n薛瑞琦",
        "919106840612\n张歆雨",
        "919106840613\n阿巴斯·阿卜力孜",
        "919106840614\n陈雪鹏",
        "919106840615\n邓毛毛",
        "919106840616\n付顺亮",
        "919106840617\n高屹楷",
        "919106840618\n戈世奇",
        "919106840619\n贺琮瀚",
        "919106840620\n季文卓",
        "919106840621\n金琪",
        "919106840622\n李春奇",
        "919106840623\n李福滨",
        "919106840624\n李海鑫",
        "919106840625\n李旷宇",
        "919106840626\n李沛昂",
        "919106840627\n林鑫鹏",
        "919106840628\n刘耀宁",
        "919106840629\n罗帅",
        "919106840631\n宋克斐",
        "919106840632\n宋庆福",
        "919106840633\n孙涵",
        "919106840634\n王国伟",
        "919106840635\n吴宇凡",
        "919106840636\n夏天",
        "919106840637\n夏泽宇",
        "919106840638\n肖林航",
        "919106840639\n谢静",
        "919106840640\n严润宇",
        "919106840641\n阳德群",
        "919106840642\n喻新棋",
        "919106840643\n张斌奇",
        "919106840644\n张天晨",
        "919106840645\n张子龙",
        "919106840646\n赵奎",
        "919106840648\n邹雨果",
        "919107390118\n程一浩",
        "919107820406\n况宇",
        "919108320224\n叶瑾",
        "919109540127\n张雨彤",
        "919114070212\n考翊鸣",
        "9191160D0139\n吴启来",
        "918106840204\n何佳雯",
        "9191010E0334\n徐子放",
        "919101170126\n林栋",
        "919102270118\n付兴",
        "919103860326\n李胜辉",
        "919106840701\n曹璇",
        "919106840702\n陈梦李",
        "919106840704\n董悠",
        "919106840705\n韩琳",
        "919106840706\n沈博宇",
        "919106840707\n唐惠彬",
        "919106840708\n王倩",
        "919106840709\n王晓爽",
        "919106840710\n王雨洁",
        "919106840711\n袁晓",
        "919106840712\n诸雨婷",
        "919106840713\n蔡薛民",
        "919106840714\n崇琪坚",
        "919106840716\n邓龙欣",
        "919106840717\n符宇轩",
        "919106840719\n耿鸿豪",
        "919106840720\n顾弋飞",
        "919106840721\n郭文越",
        "919106840722\n黄邦",
        "919106840723\n霍思捷",
        "919106840724\n孔起弟",
        "919106840725\n李鸿斌",
        "919106840726\n李杰",
        "919106840727\n李洋洋",
        "919106840728\n林天皓",
        "919106840729\n刘畅",
        "919106840730\n马云飞",
        "919106840731\n缪思奇",
        "919106840732\n瞿湛",
        "919106840734\n芮明强",
        "919106840736\n王伟廷",
        "919106840737\n王一康",
        "919106840738\n严文杰",
        "919106840739\n余帅波",
        "919106840740\n俞国峰",
        "919106840741\n袁游洋",
        "919106840742\n张博文",
        "919106840743\n张华祥",
        "919106840744\n张冉",
        "919106840745\n张思岩",
        "919106840746\n张啸",
        "919106840747\n赵永恒",
        "919106840748\n郑宇",
        "919107810115\n谢文慧",
        "919108320223\n武兆玮",
        "9191160D0104\n金若羽",
        "9191160D0434\n汪铠阳"
    };
    for(int i=0;i<sizeof(tname)/sizeof(QString);i++)
    {
        names[i]=tname[i];
    }
    stunum=sizeof(tname)/sizeof(QString);
    for(int i=0;i<stunum;i++)
    {
        qDebug()<<names[i];
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
    if(Giftselect!=nullptr)
    qDebug()<<"Begin\n"
            <<Giftselect->getX()<<' '<<Giftselect->getY()<<'\n'
            <<Giftselect->getW()<<' '<<Giftselect->getH()<<'\n'
            <<Giftselect->getV_X()<<' '<<Giftselect->getV_Y()<<'\n'
            <<Giftselect->getV_W()<<' '<<Giftselect->getV_H()<<'\n';
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
        tp=GiftHead;
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
        select->setA_Y(pointer->getY()-select->getY());
        Giftselect->setV_W(200);
        Giftselect->setV_H(200);
        Giftselect->setA_Y(pointer->getY()-Giftselect->getY());
        InfoBoard->label->show();
        for(int i=0;i<giftnum;i++)
        {
            if(Giftselect->OriInfo==giftoraddr[i])
            {
                InfoBoard->label->setText(giftInfo[i]);
                if(select->OriInfo==QString("919106840631\n宋克斐")||select->OriInfo==QString("宋克斐\n919106840631"))
                    InfoBoard->label->setText(QString("什么！我竟然能中奖？\n（虽然大概率你只能在源码里看见这句话）"));
                break;
            }
        }
        InfoBoard->setA_Y(-30);
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
        tp=GiftHead;
        while(tp!=nullptr)
        {
            if(tp==Giftselect)
            {
                tp=tp->next;
                continue;
            }
            tp->setA_X((qrand()%2==0?1:-1)*(qrand()%600+400));
            tp=tp->next;
        }
        pointer->setA_X(400);
        But_reset->show();
        But_next->show();
        //qDebug()<<"change end";
    }
    if(!isRunning)
    {
        select->movetoY(pointer->getY(),1/Fps);
        Giftselect->movetoY(pointer->getY(),1/Fps);
        if(select->getW()>600)
            select->sizestop();
        if(Giftselect->getW()>300)
            Giftselect->sizestop();
        if(pointer->getX()>1400)
            pointer->stop();
        else
            pointer->update(1/Fps);
        InfoBoard->movetoY(675,1/Fps);
    }


    if(LabelHead==nullptr&&isRunning)
    {
        QLabel* nl=new QLabel(this);
        //nl->setStyleSheet("border-image: url(:/res/pigbut.png);");
        nl->setText("我知道你们看不见这条嘿嘿嘿");
        nl->show();
        LabelHead=new MovingLabel(nl);
        LabelHead->copy(SpawnTem);
    }
    if(GiftHead==nullptr&&isRunning)
    {
        QLabel* nl=new QLabel(this);
        //nl->setStyleSheet("border-image: url(:/res/pigbut.png);");
        nl->setText("我也知道你们看不见这条嘿嘿嘿");
        nl->show();
        GiftHead=new MovingLabel(nl);
        GiftHead->copy(GiftTem);
    }
    MovingLabel* tp=LabelHead;
    if(fabs(SpawnTem->getY()-tp->getY())>Distence&&isRunning)
    {
        QLabel* nl=new QLabel(this);
        MovingLabel* nm=new MovingLabel(nl);
        //nl->setStyleSheet("border-image: url(:/res/block.png);font:"+QString::number(int(SpawnTem->getW()/10))+"pt;");
        nl->setAlignment(Qt::AlignCenter);
        //nl->setText("宋克斐 919106840631");
        if(GlobalCounter!=stunum)
        {
            nm->OriInfo=names[GlobalCounter];
            nl->setText(names[GlobalCounter++]);
        }
        else
        {
            std::srand(qrand()%(unsigned)-1);
            std::random_shuffle(names,names+stunum);
            GlobalCounter=0;
            //qDebug()<<QTime::currentTime();
            nm->OriInfo=names[GlobalCounter];
            nl->setText(names[GlobalCounter++]);
        }
        nl->show();
        nm->copy(SpawnTem);
        nm->next=LabelHead;
        LabelHead=nm;
    }


    tp=GiftHead;
    if(fabs(GiftTem->getY()-tp->getY())>Distence&&isRunning)
    {
        QLabel* nl=new QLabel(this);
        MovingLabel* nm=new MovingLabel(nl);
        if(GiftCounter!=giftnum)
        {
            nm->OriInfo=giftaddr[GiftCounter];
            nl->setStyleSheet("border-image: url(:/res/"+giftaddr[GiftCounter++]+")");
        }
        else
        {
            std::srand(qrand()%(unsigned)-1);
            std::random_shuffle(giftaddr,giftaddr+giftnum);
            GiftCounter=0;
            nm->OriInfo=giftaddr[GiftCounter];
            nl->setStyleSheet("border-image: url(:/res/"+giftaddr[GiftCounter++]+")");
        }
        nl->show();
        nm->copy(GiftTem);
        nm->next=GiftHead;
        GiftHead=nm;
    }


    tp=LabelHead;
    while(tp!=nullptr)
    {
        if(!isRunning&&tp==select)
        {
            tp->label->setStyleSheet("border-image: url(:/res/block.png);font:"+QString::number(int(tp->getW()/15))+"pt;");
            tp=tp->next;
            continue;
        }
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

    tp=GiftHead;
    while(tp!=nullptr)
    {
        if(!isRunning&&tp==Giftselect)
        {
            tp=tp->next;
            continue;
        }
        tp->update(1/Fps*TimeRate);
        if(Giftselect==nullptr||fabs(Giftselect->getY()-pointer->getY())>fabs(tp->getY()-pointer->getY()))
            Giftselect=tp;
        if(tp->getY()>=pointer->getY()&&tp->getV_H()>0&&isRunning)
        {
            //tp->setA_Y(-tp->getA_Y());
            tp->setV_W(-tp->getV_W());
            tp->setV_H(-tp->getV_H());
            //tp->setA_W(-tp->getA_W());
            //tp->setA_H(-tp->getA_H());
        }
        tp=tp->next;
    }
    if(Giftselect!=nullptr)
        Giftselect->label->raise();


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

    tp=GiftHead;
    pp=nullptr;
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
    GiftHead=nullptr;
    while(tp!=nullptr)
    {
        MovingLabel* tnext=tp->next;
        tp->next=GiftHead;
        GiftHead=tp;
        tp=tnext;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
