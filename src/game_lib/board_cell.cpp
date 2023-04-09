#include "board_cell.h"

BoardCell::BoardCell(int rowInd_, int colInd_, int size_, QGraphicsItem* parent)
: rowInd(rowInd_), colInd(colInd_), size(size_), QGraphicsRectItem(colInd_ * size_, rowInd_ * size_, size_, size_, parent) {

}

void BoardCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(0,0,0));

    if (isBackground) {
        painter->setBrush(QBrush(QColor(139,194,76)));
    }

    if (isWay) {
        painter->setBrush(QBrush(QColor(131, 148, 154)));
    }
    painter->setPen(pen);
    painter->drawRect(colInd * size, rowInd * size, size, size);

    if (isAim) {
        QPixmap aimPixmap("./static_files/icons/flower.png");
        painter->drawPixmap(colInd * size + 10, rowInd * size + 10, size - 20, size - 20, aimPixmap);
    }
}

void BoardCell::setWay() {
    isWay = true;
    isBackground = false;
}

void BoardCell::setAim() {
    isAim = true;
    isBackground = false;
}