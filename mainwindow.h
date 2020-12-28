#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <algorithm>
#include <fstream>
#include <movinglabel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MovingLabel* LabelHead;
    MovingLabel* SpawnTem;
    MovingLabel* GiftHead;
    MovingLabel* GiftTem;
    MovingLabel* pointer;
    MovingLabel* select;
    MovingLabel* Giftselect;
    MovingLabel* InfoBoard;

    int ntime;
    int GlobalTimer;
    double Fps;
    double TimeRate;
    double SlowingRate;
    int LabelCount;
    double Distence;

    bool isRunning;

    int stunum;
    QString names[1000];
    int GlobalCounter;

    int giftnum;
    QString giftaddr[100];
    QString giftoraddr[100];
    QString giftInfo[100];
    int GiftCounter;
    double GiftDistence;

    QPushButton* But_slow;
    QPushButton* But_reset;
    QPushButton* But_fps;
    QPushButton* But_next;

    void timerEvent(QTimerEvent *);
public:
    explicit MainWindow(QWidget *parent = 0);

    void reset();
    void nextgift();
    void getresult();
    void loaddata();
    void changeFps();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
