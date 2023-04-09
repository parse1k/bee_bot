#include "game_board.h"
#include <iostream>

GameBoard::GameBoard(QWidget *parent) : QGraphicsView(parent) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateView()));
    timer->start(100);
}

void GameBoard::newGame(int levelInd_) {
    levelInd = levelInd_;
    levelReader = new LevelReader(levelInd);
    initBoardParams();
    resize();
    initScene();
    initCells();
    initBee();
}

void GameBoard::initBoardParams() {
    std::pair<int, int> boardSize = levelReader->getBoardSize();
    boardRowsNumber = boardSize.first;
    boardColsNumber = boardSize.second;
    width = boardRowsNumber * cellSize + 20;
    height = boardColsNumber * cellSize + 20;
}

void GameBoard::initScene() {
//    scene = new QGraphicsScene(0, 0, this->frameSize().width(), this->frameSize().height());
    scene = new QGraphicsScene(this);
    this->setScene(scene);
}

void GameBoard::initCells() {
    boardCells = std::vector<std::vector<BoardCell*>>(boardRowsNumber, std::vector<BoardCell *>(boardColsNumber));

    for (int rowInd = 0; rowInd < boardRowsNumber; rowInd++) {
        for (int colInd = 0; colInd < boardColsNumber; colInd++) {
            createCell(rowInd, colInd);
        }
    }

    std::vector<std::pair<int, int>> roads = levelReader->getRoads();
    for (std::pair<int, int> road : roads) {
        boardCells[road.first][road.second]->setWay();
    }

    std::pair<int, int> aimPos = levelReader->getAimPos();
    boardCells[aimPos.first][aimPos.second]->setAim();
}

void GameBoard::createCell(int rowInd, int colInd) {
    BoardCell* boardCell = new BoardCell(rowInd, colInd, cellSize);
    boardCells[rowInd][colInd] = boardCell;
    scene->addItem(boardCell);
}

void GameBoard::initBee() {
    std::pair<int, int> beePos = levelReader->getBeePos();
    bee = new Bee(beePos.first, beePos.second, cellSize - 16, cellSize);
    scene->addItem(bee);
}

void GameBoard::resize() {
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    this->setAlignment(Qt::AlignCenter);
}

void GameBoard::runBee(std::vector<std::string> instructions) {
    for (std::string instruction : instructions) {
        if (!runInstruction(instruction)) {
            this->viewport()->repaint();
            break;
        }
        sleep(sleepTimeInMSec);
    }
}

bool GameBoard::runInstruction(std::string instruction) {
    if (instruction == "left") bee->turnLeft();
    else if (instruction == "right") bee->turnRight();
    else if (instruction == "forward") {
        if (isRightPosition(bee->getForwardPosition())) {
            bee->goForward();
            verifyWin();
        } else {
            bee->knockForwardWall();
            return false;
        }
    }
    else if (instruction == "back") {
        if (isRightPosition(bee->getBackPosition())) {
            bee->goBack();
            verifyWin();
        } else {
            bee->knockBackWall();
            return false;
        }
    }

    this->viewport()->repaint();

    return true;
}

bool GameBoard::isRightPosition(std::pair<int, int> position) {
    int posRowInd = position.first;
    int posColInd = position.second;

    return posRowInd >= 0 && posColInd >= 0 && posRowInd < boardRowsNumber && posColInd < boardColsNumber &&
    boardCells[posRowInd][posColInd]->getIsWay();
}

void GameBoard::verifyWin() {
    std::pair<int, int> aimPos = levelReader->getAimPos();
    std::pair<int, int> beePos = bee->getPosition();
    if (aimPos.first == beePos.first && aimPos.second == beePos.second) {
        emit win();
    }
}

void GameBoard::sleep(int time) {
    QTime dieTime= QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameBoard::updateView() {
    this->viewport()->repaint();
    timer->start(100);
}