#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menu.h"
#include "./Settings/Settings.h"
#include <QListWidget>
#include <vector>
#include <utility>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Menu* masterMenu;
    Menu* mainMenuOG;

    Ui::MainWindow *ui;
    QListWidget *activeQListWidget;

    Settings* setting;

    bool powerStatus;

    int uiMode;
    int indexHighlighted;
    int lastUiMode;

    void powerChange();
    void initializeMainMenu(Menu*);
    void powerModeUpdated();
    bool updateDisplay();
    void setRedLight(bool);
    void setBlueLight(bool);
    void setGreenLight(bool);
    bool gotoEndSession(int, float, float, float, float, float, float);
    void setCoheranceValue(float);
    void setDurationValue(float);
    void setAchievementScore(float);
    void updateBatteryLvl(float);
    bool drawHRVGraph(std::vector<std::pair<float,float>>);
    bool setBreathLightPercentage(float);

private slots:
    bool changeUiMode(int);
    void pushSelector();
    void goBack();
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    void pushMenu();






};
#endif // MAINWINDOW_H
