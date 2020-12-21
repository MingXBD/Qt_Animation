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
#include <movinglabel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MovingLabel* LabelHead;
    MovingLabel* SpawnTem;

    int ntime;
    int GlobalTimer;
    double Fps;
    double SlowingRate;
    int LabelCount;

    QPushButton* But_slow;

    void timerEvent(QTimerEvent *);
public:
    explicit MainWindow(QWidget *parent = 0);

    void getresult();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
