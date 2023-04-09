#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "HeartWave/HeartWave.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void powerModeUpdated(bool);
    bool updateDisplay();
    void setRedLight(bool);
    void setBlueLight(bool);
    void setGreenLight(bool);
    bool gotoEndSession(int, float, float, float, float, float, float);
    void setCoheranceValue(float);
    void setDurationValue(float);
    void setAchievementScore(float);
    void updateBatteryLvl(float);
    bool drawHRVGraph(vector<pair<float,float>>);
    bool setBreathLightPercentage(float);

private:
    Ui::MainWindow *ui;

    int uiMode;
    int indexHighlighted;
    int lastUiMode;
    HeartWave hw;

    qint64 lastUpdate = 0; // the last time we drew the graph

private slots:
    bool changeUiMode(int);
    void pushSelector();
    void goBack();
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    void pushMenu();
    void makePlot();




};
#endif // MAINWINDOW_H
