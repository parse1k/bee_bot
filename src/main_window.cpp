#include "main_window.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    ui.stackedWidget->setCurrentIndex(1);

    initLevelButtons();
    initControls();

    gameBoard = new GameBoard(this);
    ui.graphViewLayout->addWidget(gameBoard, 1, 1);
    connect(gameBoard, SIGNAL(win()), this, SLOT(openWinDialog()));

    winDialog = new WinDialog();
    winDialog->setModal(true);
    connect(winDialog, SIGNAL(toMenu()), this, SLOT(toMenu()));
}

void MainWindow::initLevelButtons() {
    for (int rowInd = 0; rowInd < levelButtonsRowsNumber; rowInd++) {
        for (int colInd = 0; colInd < levelButtonsColsNumber; colInd++) {
            int levelInd = rowInd * levelButtonsColsNumber + colInd;
            LevelButton* levelButton = new LevelButton(levelInd);
            levelButtons.push_back(levelButton);
            ui.levelsLayout->addWidget(levelButton, rowInd, colInd);

            connect(levelButton, &LevelButton::leftClicked, this,
                    &MainWindow::handleLevelButtonClick);
        }
    }
}

void MainWindow::handleLevelButtonClick(int levelInd) {
    currentLevelInd = levelInd;
    initGame();
}

void MainWindow::initGame() {
    instructions.clear();
    drawInstructions();
    ui.stackedWidget->setCurrentIndex(0);
    gameBoard->newGame(currentLevelInd);
//    ui.graphViewLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
//    ui.gameLayout->addWidget(gameBoard, 1, 2);
}

void MainWindow::initControls() {
    setButtonIcon(ui.forwardButton, "arrow_forward.png");
    setButtonIcon(ui.backwardButton, "arrow_backward.png");
    setButtonIcon(ui.turnLeftButton, "turn_left.png");
    setButtonIcon(ui.turnRightButton, "turn_right.png");

    connectControlButtons();
}

void MainWindow::setButtonIcon(QPushButton* button, QString filename, int iconSize) {
    QPixmap pixmap("./static_files/icons/" + filename);
    button->setIcon(pixmap);
    button->setIconSize(QSize(iconSize, iconSize));
}

void MainWindow::connectControlButtons() {
    connect(ui.runButton, &QPushButton::clicked, this, &MainWindow::handleRun);
    connect(ui.clearButton, &QPushButton::clicked, this, &MainWindow::restart);
    connect(ui.menuButton, &QPushButton::clicked, this, &MainWindow::toMenu);

    connect(ui.forwardButton, &QPushButton::clicked, [this]() { this->handleControlClick("forward"); });
    connect(ui.backwardButton, &QPushButton::clicked, [this]() { this->handleControlClick("back"); });
    connect(ui.turnLeftButton, &QPushButton::clicked, [this]() { this->handleControlClick("left"); });
    connect(ui.turnRightButton, &QPushButton::clicked, [this]() { this->handleControlClick("right"); });
}

void MainWindow::handleControlClick(std::string instruction) {
    instructions.push_back(instruction);
    drawInstructions();
}

void MainWindow::drawInstructions() {
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    for (int instructionInd = 0; instructionInd < instructions.size(); instructionInd++) {
        QString filename;
        if (instructions[instructionInd] == "forward") {
            filename = "arrow_forward.png";
        } else if (instructions[instructionInd] == "back") {
            filename = "arrow_backward.png";
        } else if (instructions[instructionInd] == "left") {
            filename = "turn_left.png";
        } else {
            filename = "turn_right.png";
        }
        QPixmap pixmap("./static_files/icons/" + filename);
        pixmap = pixmap.scaled(30, 30, Qt::KeepAspectRatio);
        QGraphicsPixmapItem *pm = scene->addPixmap(pixmap);
        pm->setPos(instructionInd * 30, 0);
    }
}

void MainWindow::handleRun() {
    gameBoard->runBee(instructions);
}

void MainWindow::restart() {
    initGame();
}

void MainWindow::openWinDialog() {
    winDialog->show();
}

void MainWindow::toMenu() {
    ui.stackedWidget->setCurrentIndex(1);
    winDialog->hide();
}