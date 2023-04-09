#ifndef BEE_BOT_GAME_BOARD_H
#define BEE_BOT_GAME_BOARD_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include <vector>
#include <string>

#include "board_cell.h"
#include "bee.h"
#include "level_reader.h"
/// Класс инкапсулирует графическое отображение и логику поведения игрового поля
class GameBoard : public QGraphicsView {
Q_OBJECT
public:
    GameBoard(QWidget *parent = nullptr);
    /// Начинает новую игру с уровнем по levelInd_
    void newGame(int levelInd_);
private:
    int levelInd;
    int boardRowsNumber = 10;
    int boardColsNumber = 10;
    int cellSize = 60;
    int width;
    int height;
    int sleepTimeInMSec = 500;
    QGraphicsScene* scene;
    std::vector<std::vector<BoardCell*>> boardCells;
    Bee* bee;
    LevelReader* levelReader;
    QTimer *timer;
    /// Инициализирует параметры поля
    void initBoardParams();
    /// Инициализирует сцену для QGraphicsView
    void initScene();
    /// Инициализирует клетки игрового поля
    void initCells();
    /// Инициализирует объект и положение пчелы на поле
    void initBee();
    /// Создает клетку в положении rowInd, colInd
    void createCell(int rowInd, int colInd);
    /// Изменяет размер QGraphicsView
    void resize();
    /// Запускает инструкции для пчелы
    bool runInstruction(std::string instruction);
    /// Возвращает, может ли пчела попасть в клетку
    bool isRightPosition(std::pair<int, int>);
    /// Проверяет и обрабатывает победу
    void verifyWin();
    /// Задержка
    void sleep(int time);
public slots:
    /// Запускает пчелу с переданными инструкциями
    void runBee(std::vector<std::string> instructions);
    /// Обновляет графику
    void updateView();
signals:
    /// Сигнал победы
    void win();
};


#endif //BEE_BOT_GAME_BOARD_H
