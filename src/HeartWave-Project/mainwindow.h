#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void makePlot();

private:
    Ui::MainWindow *ui;

    int uiMode;
    int indexHighlighted;
    int lastUiMode;

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
    bool drawHRVGraph(Vector<Pair<Float,Float>>);
    bool setBreathLightPercentage(float);

private slots:
    bool changeUiMode(int);
    void pushSelector();
    void goBack();
    bool goUp();
    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();
    void pushMenu();




};
#endif // MAINWINDOW_H
