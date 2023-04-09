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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals() {
    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::pushPower);
}

void MainWindow::powerModeUpdated(bool b) {
    power = b;
}

//slots
bool MainWindow::changeUiMode(int){

}

void MainWindow::pushSelector(){

}

void MainWindow::pushPower() {
    powerModeUpdated(~power);
}

void MainWindow::goBack(){

}

bool MainWindow::goUp(){

}

bool MainWindow::goDown(){

}

bool MainWindow::goLeft(){

}

bool MainWindow::goRight(){

}

void MainWindow::pushMenu(){

}

bool MainWindow::updateDisplay() {
    makePlot();
}

void MainWindow::makePlot()
{
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
