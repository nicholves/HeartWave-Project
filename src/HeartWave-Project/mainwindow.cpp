#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Create menu tree
    // Create menu tree
    masterMenu = new Menu("MAIN MENU", {"START NEW SESSION","SETTINGS","LOG/HISTORY"}, nullptr);
    mainMenuOG = masterMenu;
    initializeMainMenu(masterMenu);

    // Initialize the main menu view
    //ui missing QList for adding items
    activeQListWidget = ui->mainMenuListView;
    activeQListWidget->addItems(masterMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    ui->menuLabel->setText(masterMenu->getName());

    //Device is "off" initially
    powerStatus = false;
    powerModeUpdated();
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerChange);

    // device interface button connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::navigateUpMenu);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::navigateDownMenu);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::navigateSubMenu);
    connect(ui->MenuButton, &QPushButton::pressed, this, &MainWindow::navigateToMainMenu);
    //ui missing back button
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::changePowerLevelUp);
    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::changePowerLevelDown);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeMainMenu(Menu* m) {

    QStringList newSession;
    QStringList settingList;


    Menu* programs = new Menu("START NEW SESSION", newSession, m);
    Menu* setting = new Menu("SETTINGS", settingList, m);
    Menu* history = new Menu("HISTORY", {"VIEW","CLEAR"}, m);


    m->addChildMenu(history);

    for (Settings* s : this->setting) {
        setting->addChildMenu(new Menu(s->getName(), {}, setting));
    }


    Menu* viewHistory = new Menu("VIEW",{}, history);
    Menu* clearHistory = new Menu("CLEAR", {"YES","NO"}, history);
    history->addChildMenu(viewHistory);
    history->addChildMenu(clearHistory);



}


void MainWindow :: powerChange(){}
