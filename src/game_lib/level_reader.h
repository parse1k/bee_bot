#ifndef BEE_BOT_LEVEL_READER_H
#define BEE_BOT_LEVEL_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
/// Класс менеджера уровней для считывания данных уровня из файла
class LevelReader {
public:
    LevelReader(int levelInd_);
    /// Возвращает размеры игрового поля
    std::pair<int, int> getBoardSize() { return std::pair<int, int> {rowsNumber, colsNumber}; };
    /// Возвращает вектор дорог
    std::vector<std::pair<int ,int>> getRoads() { return roads; };
    /// Возвращает позицию пчелы
    std::pair<int, int> getBeePos() { return beePos; };
    /// Возвращает позицию цели
    std::pair<int, int> getAimPos() { return aimPos; };
private:
    int levelInd;
    int rowsNumber;
    int colsNumber;
    std::vector<std::pair<int ,int>> roads;
    std::pair<int, int> beePos;
    std::pair<int, int> aimPos;
    /// Считывает данные уровня из файла по levelInd
    void readLevel();

};


#endif //BEE_BOT_LEVEL_READER_H
