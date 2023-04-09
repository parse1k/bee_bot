#ifndef BEE_BOT_BOARD_CELL_H
#define BEE_BOT_BOARD_CELL_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QtWidgets>
/// Класс инкапсулирует графическое отображение и логику поведения ячеек игрового поля
class BoardCell : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    BoardCell(int rowInd_, int colInd_, int size_, QGraphicsItem* parent = nullptr);
    /// Переопределение функции paint QGraphicsRectItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    /// Ставит флаг пути
    void setWay();
    /// Возвращает значение флага пути
    bool getIsWay() { return isWay; };
    /// Ставит флаг цели
    void setAim();
    /// Возвращает значение флага цели
    bool getIsAim() { return isAim; };
private:
    int rowInd;
    int colInd;
    int size;
    bool isBackground = true;
    bool isWay = false;
    bool isAim = false;
};


#endif //BEE_BOT_BOARD_CELL_H
