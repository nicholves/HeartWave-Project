#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

#include "HeartWave/HeartWave.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

enum MenuMode {
    MainMenu,
    GraphView,
    SettingsView,
    HistoryList,
    HistoryEntry,
    SummaryView
};

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
    bool changeUiMode(MenuMode);
    void updateMenu();
    void updateLayers();
    void updateSummary();
    void updateHistoryList();
    void updateData(const Record& record);
    void updateSettings();

private:
    void connectSignals();


    Ui::MainWindow *ui;

    MenuMode uiMode = MenuMode::MainMenu;
    MenuMode lastUiMode = MenuMode::MainMenu;
    HeartWave hw;
    bool power = false;

    qint64 lastUpdate = 0; // the last time we drew the graph
    qint64 lastAchievementUpdate = 0;

private slots:
    void pushSelector();
    void goBack();
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    void pushMenu();
    void pushPower();
    void makePlot();




};
#endif // MAINWINDOW_H
