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
    MovingLabel* pointer;
    MovingLabel* select=nullptr;

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
    int randomno[1000];
    int GlobalCounter;

    QPushButton* But_slow;
    QPushButton* But_reset;
    QPushButton* But_fps;

    void timerEvent(QTimerEvent *);
public:
    explicit MainWindow(QWidget *parent = 0);

    void reset();
    void getresult();
    void loaddata();
    void changeFps();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
