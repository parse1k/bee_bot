#include "bee.h"
#include <iostream>

Bee::Bee(int rowInd_, int colInd_, int size_, int cellSize_, QGraphicsItem* parent)
: rowInd(rowInd_), colInd(colInd_), size(size_), cellSize(cellSize_), QGraphicsRectItem(colInd_ * size_, rowInd_ * size_, size_, size_, parent) {
    paddings = (cellSize - size) / 2;
}

void Bee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    QPixmap beePixmap("./static_files/icons/bee.png");
    int degrees = 0;
    if (yDiff == 1 && xDiff == 0) degrees = 180;
    if (yDiff == 0 && xDiff != 0) degrees = xDiff * 90;
    beePixmap = getRotatedPixmap(beePixmap, degrees);
    float xPos = (float(colInd) + colBias) * float(cellSize) + float(paddings);
    float yPos = (float(rowInd) + rowBias) * float(cellSize) + float(paddings);
    painter->drawPixmap(xPos, yPos, size, size, beePixmap);
}

QPixmap Bee::getRotatedPixmap(QPixmap pixmap, int degrees) {
    QTransform transformer;
    transformer.rotate(degrees);
    return pixmap.transformed(transformer);
}

std::pair<int, int> Bee::getPosition() {
    return std::pair<int, int> {rowInd, colInd};
}

std::pair<int, int> Bee::getForwardPosition() {
    return std::pair<int, int> {rowInd + yDiff, colInd + xDiff};
}

std::pair<int, int> Bee::getBackPosition() {
    return std::pair<int, int> {rowInd - yDiff, colInd - xDiff};
}

void Bee::goForward() {
    rowInd += yDiff;
    colInd += xDiff;
}

void Bee::goBack() {
    rowInd -= yDiff;
    colInd -= xDiff;
}

void Bee::turnLeft() {
    if (yDiff == 0) {
        xDiff *= -1;
    }
    std::swap(xDiff, yDiff);
}
void Bee::turnRight() {
    if (yDiff != 0) {
        yDiff *= -1;
    }
    std::swap(xDiff, yDiff);
}

void Bee::knockForwardWall() {
    moveBias(yDiff * bias, xDiff * bias);
    sleep(300);
    moveBias(0, 0);
}

void Bee::knockBackWall() {
    moveBias(-1 * yDiff * bias, -1 * xDiff * bias);
    sleep(300);
    moveBias(0, 0);
}

void Bee::moveBias(float rowBias_, float colBias_) {
    rowBias = rowBias_;
    colBias = colBias_;
}

void Bee::sleep(int time) {
    QTime dieTime= QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}