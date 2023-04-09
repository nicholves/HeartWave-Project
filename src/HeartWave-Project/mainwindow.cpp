#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "HeartWave/HeartWave.h"

#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, &this->hw, &HeartWave::update);
    timer->start(10);

    connect(&this->hw, &HeartWave::readyToUpdateDisplay, this, &MainWindow::updateDisplay);

    connectSignals();


    QListWidgetItem* item;
    ui->menuList->addItem(QString("Settings"));

    ui->menuList->addItem(QString("Start Session"));

    ui->menuList->addItem(QString("View History"));


    ui->menuList->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals() {
   connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::pushPower);
   connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::goBack);
   connect(ui->upButton, &QPushButton::clicked, this, &MainWindow::goUp);
   connect(ui->downButton, &QPushButton::clicked, this, &MainWindow::goDown);
   connect(ui->leftButton, &QPushButton::clicked, this, &MainWindow::goLeft);
   connect(ui->rightButton, &QPushButton::clicked, this, &MainWindow::goRight);
   connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::pushSelector);
   connect(ui->MenuButton, &QPushButton::clicked, this, &MainWindow::pushMenu);
}

void MainWindow::powerModeUpdated(bool b) {
    if (!b) {
        ui->blocker->show();
    } else {
        ui->blocker->hide();
    }
    power = b;
}

//slots
bool MainWindow::changeUiMode(MenuMode m){
    uiMode = m;
}

void MainWindow::pushSelector(){
    if (!power) {
        return;
    }

    if (uiMode == MenuMode::MainMenu) {
        auto content = ui->menuList->currentItem()->text();

        if (content == "Start Session") {
            changeUiMode(MenuMode::GraphView);
            hw.startSession();
        }
    }
    else if(uiMode == MenuMode::SettingsView) {
    }
    else if(uiMode == MenuMode::HistoryList) {
    }
    else if(uiMode == MenuMode::GraphView) {
        hw.stopSession();
        changeUiMode(MenuMode::SummaryView);
    }
}

void MainWindow::pushPower() {
    powerModeUpdated(!power);
}

void MainWindow::goBack(){
    if (!power) {
        return;
    }
}

bool MainWindow::goUp(){
    if (!power) {
        return false;
    }

    int current = ui->menuList->currentRow();
    if (current - 1 < 0) {
        return false;
    }
    ui->menuList->setCurrentRow(current - 1);
    updateDisplay();
    return true;
}

bool MainWindow::goDown(){
    if (!power) {
        return false;
    }

    int current = ui->menuList->currentRow();
    if (current + 1 >= ui->menuList->count()) {
        return false;
    }
    ui->menuList->setCurrentRow(current + 1);
    updateDisplay();
    return true;
}

bool MainWindow::goLeft(){

}

bool MainWindow::goRight(){

}

void MainWindow::pushMenu(){
    hw.stopSession();
    changeUiMode(MenuMode::MainMenu);
    updateDisplay();
}

bool MainWindow::updateDisplay() {
    if (!power) {
        return false;
    }

    updateMenu();
    updateLayers();


    makePlot();
}

void MainWindow::updateLayers() {
    switch (uiMode) {
    case MenuMode::GraphView:
        ui->menuList->hide();
        break;
    case MenuMode::MainMenu:
        ui->menuList->show();
        break;
    case MenuMode::SettingsView:
        ui->menuList->show();
        break;
    case MenuMode::HistoryList:
        ui->menuList->show();
        break;
    case MenuMode::HistoryEntry:
        ui->menuList->show();
        break;
    case MenuMode::SummaryView:
        ui->menuList->hide();
        break;
    }
}

void MainWindow::makePlot()
{
    if (!power) {
        ui->customPlot->clearGraphs();
        ui->customPlot->clearItems();
        ui->customPlot->clearPlottables();

        ui->customPlot->xAxis2->setVisible(false);
        ui->customPlot->xAxis2->setTickLabels(false);
        ui->customPlot->yAxis2->setVisible(false);
        ui->customPlot->yAxis2->setTickLabels(false);

        ui->customPlot->replot();
        return;
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    QVector<double> x, y;
    std::vector<std::pair<float, float>> amplitudes = hw.getAmplitudes();

    for (const auto a : amplitudes) {
        x.push_back(a.first);
        y.push_back(a.second);
    }


    // configure right and top axis to show ticks but no labels:
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(x, y);

    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->xAxis->scaleRange(1.1);
    ui->customPlot->yAxis->scaleRange(1.1);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    qint64 delta = QDateTime::currentMSecsSinceEpoch() - lastUpdate;

    if (delta >= 10) {
        ui->customPlot->replot();
        lastUpdate = QDateTime::currentMSecsSinceEpoch();
    }
}

void MainWindow::updateMenu() {
    int count = ui->menuList->count();
    for (int i = 0; i < count; ++i) {
        ui->menuList->item(i)->setBackground(Qt::white);
    }
    auto test = ui->menuList->currentRow();
    ui->menuList->currentItem()->setBackground(QBrush(Qt::blue));
}
