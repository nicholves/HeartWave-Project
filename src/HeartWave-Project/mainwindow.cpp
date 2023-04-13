#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "HeartWave/HeartWave.h"
#include "Record/Record.h"

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
    ui->historyList->setCurrentRow(0);
    ui->settingsList->setCurrentRow(0);


    ui->summaryView->hide();
    ui->historyList->hide();
    ui->historyDataView->hide();
    ui->settingsList->hide();
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
    lastUiMode = uiMode;
    uiMode = m;
    updateDisplay();
    ui->menuList->setCurrentRow(0);
    ui->historyList->setCurrentRow(0);
    ui->settingsList->setCurrentRow(0);
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

        else if (content == "View History") {
            changeUiMode(MenuMode::HistoryList);
            updateHistoryList();
        }

        else if (content == "Settings") {
            changeUiMode(MenuMode::SettingsView);
            updateDisplay();
            updateSettings();
        }
    }
    else if(uiMode == MenuMode::SettingsView) {
        auto text = ui->settingsList->currentItem()->text().toStdString();
        auto content = text.substr(0, 6);


        Settings& settings = hw.getSettings();
        if (content == "Challe") {
            settings.setChallengeLevel(((settings.getChallengeLevel()) % 4) + 1);
        } else if (content == "Breath") {
            settings.setBreathPace(((settings.getBreathPace()) % 30) + 1);
        }

        updateSettings();
    }
    else if(uiMode == MenuMode::HistoryList) {
        auto content = ui->historyList->currentItem()->text();

        if (content == "Clear History") {
            hw.getHistoryManager().wipeHistory();
            updateHistoryList();
        } else {
            int index = ui->historyList->currentRow();
            updateData(hw.getHistoryManager().getSessions()[index - 1]);
            changeUiMode(MenuMode::HistoryEntry);
            updateDisplay();
        }
    }
    else if(uiMode == MenuMode::GraphView) {
        hw.stopSession();
        changeUiMode(MenuMode::SummaryView);
        updateSummary();
        updateDisplay();
    }
    else if (uiMode == MenuMode::SummaryView) {
        changeUiMode(MenuMode::MainMenu);
        updateDisplay();
    }
    else if (uiMode == MenuMode::HistoryEntry) {
        changeUiMode(MenuMode::HistoryList);
        updateHistoryList();
    }
}

void MainWindow::pushPower() {
    powerModeUpdated(!power);
}

void MainWindow::goBack(){
    if (!power) {
        return;
    }
    changeUiMode(lastUiMode);
    updateDisplay();
}

bool MainWindow::goUp(){
    if (!power) {
        return false;
    }

    if (uiMode == MenuMode::MainMenu) {

        int current = ui->menuList->currentRow();
        if (current - 1 < 0) {
            return false;
        }
        ui->menuList->setCurrentRow(current - 1);

    } else if (uiMode == MenuMode::HistoryList) {

        int current = ui->historyList->currentRow();
        if (current - 1 < 0) {
            return false;
        }
        ui->historyList->setCurrentRow(current - 1);

    }
    else if (uiMode == MenuMode::SettingsView) {
        int current = ui->settingsList->currentRow();
        if (current - 1 < 0) {
            return false;
        }
        ui->settingsList->setCurrentRow(current - 1);
    }



    updateDisplay();
    return true;
}

bool MainWindow::goDown(){
    if (!power) {
        return false;
    }

    if (uiMode == MenuMode::MainMenu) {

        int current = ui->menuList->currentRow();
        if (current + 1 >= ui->menuList->count()) {
            return false;
        }
        ui->menuList->setCurrentRow(current + 1);

    } else if (uiMode == MenuMode::HistoryList) {

        int current = ui->historyList->currentRow();
        if (current + 1 >= ui->historyList->count()) {
            return false;
        }
        ui->historyList->setCurrentRow(current + 1);

    }
    else if (uiMode == MenuMode::SettingsView) {
        int current = ui->settingsList->currentRow();
        if (current + 1 >= ui->settingsList->count()) {
            return false;
        }
        ui->settingsList->setCurrentRow(current + 1);
    }

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
        ui->HRContact->setStyleSheet("image: url(:/new/prefix1/images/buttons/heart-rate-1-svgrepo-com.svg);");
        return false;
    }

    if (hw.beatIsDetected()) {
        ui->HRContact->setStyleSheet("image: url(:/new/prefix1/images/buttons/heart-rate-1-green-svgrepo-com.png);");
    } else {
        ui->HRContact->setStyleSheet("image: url(:/new/prefix1/images/buttons/heart-rate-1-svgrepo-com.svg);");
    }

    if (uiMode == MenuMode::GraphView) {
        CoheranceLevel cl = coheranceNumToEnum(hw.getCurrentCoherance());

        switch (cl) {
        case CoheranceLevel::low:
            ui->RGB_Indicator->setStyleSheet("background-color: rgb(255, 0, 0)");
            break;
        case CoheranceLevel::medium:
            ui->RGB_Indicator->setStyleSheet("background-color: rgb(0, 0, 255)");
            break;

        case CoheranceLevel::high:
            ui->RGB_Indicator->setStyleSheet("background-color: rgb(0, 255, 0)");
            break;
        }
    }

    updateMenu();
    updateLayers();


    makePlot();
}

void MainWindow::updateLayers() {
    switch (uiMode) {
    case MenuMode::GraphView:
        ui->menuList->hide();
        ui->summaryView->hide();
        ui->historyList->hide();
        ui->historyDataView->hide();
        ui->settingsList->hide();
        break;
    case MenuMode::MainMenu:
        ui->menuList->show();
        ui->summaryView->hide();
        ui->historyList->hide();
        ui->historyDataView->hide();
        ui->settingsList->hide();
        break;
    case MenuMode::SettingsView:
        ui->menuList->hide();
        ui->summaryView->hide();
        ui->historyList->hide();
        ui->historyDataView->hide();
        ui->settingsList->show();
        break;
    case MenuMode::HistoryList:
        ui->menuList->hide();
        ui->summaryView->hide();
        ui->historyList->show();
        ui->historyDataView->hide();
        ui->settingsList->hide();
        break;
    case MenuMode::HistoryEntry:
        ui->menuList->hide();
        ui->summaryView->hide();
        ui->historyList->show();
        ui->historyDataView->show();
        ui->settingsList->hide();
        break;
    case MenuMode::SummaryView:
        ui->menuList->hide();
        ui->summaryView->show();
        ui->historyList->hide();
        ui->historyDataView->hide();
        ui->settingsList->hide();
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


        ui->Coherence_Int_Label->setNum(hw.getCurrentCoherance());

        qint64 st = hw.getStartTime();
        qint64 totalTime = QDateTime::currentMSecsSinceEpoch() - st;
        double totalTimeD = (double)totalTime / 1000.0; // convertion from miliseconds to seconds

        ui->length_Int_Label->setNum(totalTimeD);

        lastUpdate = QDateTime::currentMSecsSinceEpoch();
    }

    delta = QDateTime::currentMSecsSinceEpoch() - lastAchievementUpdate;

    if (delta >= 5000) {
        ui->Achievemen_Int_Label->setNum(hw.getAchievementScore());
        lastAchievementUpdate = QDateTime::currentMSecsSinceEpoch();
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

void MainWindow::updateSummary() {
    ui->summaryView->clear();


    Record record = hw.generateSummary();
    string output = "Challenge Level: " + to_string(record.getChallengeLevel());
    ui->summaryView->addItem(QString::fromStdString(output));

    output = "Percentage in low coherance: " + to_string(record.getLowPercentage()) + "%";
    ui->summaryView->addItem(QString::fromStdString(output));

    output = "Percentage in medium coherance: " + to_string(record.getMedPercentage()) + "%";
    ui->summaryView->addItem(QString::fromStdString(output));

    output = "Percentage in high coherance: " + to_string(record.getHighPercentage()) + "%";
    ui->summaryView->addItem(QString::fromStdString(output));

    output = "Average Coherance: " + to_string(record.getAVGCoherance());
    ui->summaryView->addItem(QString::fromStdString(output));

    output = "Length of session: " + to_string(record.getLengthOfSession()) + " seconds";
    ui->summaryView->addItem(QString::fromStdString(output));

    output = "Achievement Score: " + to_string(record.getAchievementScore());
    ui->summaryView->addItem(QString::fromStdString(output));
}


void MainWindow::updateHistoryList() {
    ui->historyList->clear();

    std::vector<Record> records = hw.getHistoryManager().getSessions();
    ui->historyList->addItem(QString("Clear History"));

    for (const auto& r : records) {
        ui->historyList->addItem(r.toString());
    }
    ui->historyList->setCurrentRow(0);
}

void MainWindow::updateData(const Record& record) {
    ui->historyDataView->clear();


    string output = "Challenge Level: " + to_string(record.getChallengeLevel());
    ui->historyDataView->addItem(QString::fromStdString(output));

    output = "Percentage in low coherance: " + to_string(record.getLowPercentage()) + "%";
    ui->historyDataView->addItem(QString::fromStdString(output));

    output = "Percentage in medium coherance: " + to_string(record.getMedPercentage()) + "%";
    ui->historyDataView->addItem(QString::fromStdString(output));

    output = "Percentage in high coherance: " + to_string(record.getHighPercentage()) + "%";
    ui->historyDataView->addItem(QString::fromStdString(output));

    output = "Average Coherance: " + to_string(record.getAVGCoherance());
    ui->historyDataView->addItem(QString::fromStdString(output));

    output = "Length of session: " + to_string(record.getLengthOfSession()) + " seconds";
    ui->historyDataView->addItem(QString::fromStdString(output));

    output = "Achievement Score: " + to_string(record.getAchievementScore());
    ui->historyDataView->addItem(QString::fromStdString(output));
}

void MainWindow::updateSettings() {
    int lastRow = ui->settingsList->currentRow();
    ui->settingsList->clear();

    Settings& settings = hw.getSettings();

    string output = "Challenge: " + to_string(settings.getChallengeLevel());
    ui->settingsList->addItem(QString::fromStdString(output));

    output = "Breath Pace: " + to_string(settings.getBreathPace());
    ui->settingsList->addItem(QString::fromStdString(output));

    ui->settingsList->setCurrentRow(lastRow);
}


