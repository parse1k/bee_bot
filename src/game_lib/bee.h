#ifndef BEE_BOT_BEE_H
#define BEE_BOT_BEE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QtWidgets>

#include <chrono>
#include <thread>
#include <vector>
#include <string>
/// Класс инкапсулирует графическое отображение и логику поведения пчелы
class Bee : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bee(int rowInd_, int colInd_, int size_, int cellSize, QGraphicsItem* parent = nullptr);
    /// Переопределение функции paint QGraphicsRectItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    std::pair<int, int> getPosition();
    std::pair<int, int> getForwardPosition();
    std::pair<int, int> getBackPosition();
    /// Ход вперед
    void goForward();
    /// Ход назад
    void goBack();
    /// Поворот направо
    void turnRight();
    /// Поворот налево
    void turnLeft();
    /// Стук в стену спереди (когда невозможно сходить вперед)
    void knockForwardWall();
    /// Стук в стену сзади (когда невозможно сходить назад)
    void knockBackWall();
    /// Смещение пчелы на rowBias_ по y и colBias_ по x
    void moveBias(float rowBias_, float colBias_);
private:
    int rowInd;
    int colInd;
    float rowBias = 0;
    float colBias = 0;
    float bias = 0.2;
    int size;
    int cellSize;
    int paddings;
    int yDiff = -1;
    int xDiff = 0;
    /// Возвращает повернутое изображение на degrees
    QPixmap getRotatedPixmap(QPixmap pixmap, int degrees);
    /// Задержка
    void sleep(int time);
signals:
    /// Сигнал для обновления графики
    void updateScene();
};


#endif //BEE_BOT_BEE_H
