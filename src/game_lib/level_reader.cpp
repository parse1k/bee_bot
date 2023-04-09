#include "level_reader.h"

LevelReader::LevelReader(int levelInd_) : levelInd(levelInd_){
    readLevel();
}

void LevelReader::readLevel() {
    std::fstream file("static_files/levels/level_" + std::to_string(levelInd) + ".beelvl", std::ios_base::in);

    std::string line;
    std::getline(file, line);
    std::istringstream in(line);
    in >> rowsNumber;
    in >> colsNumber;

    std::getline(file, line);
    in = std::istringstream(line);
    int roadsNumber;
    in >> roadsNumber;

    for (int roadInd = 0; roadInd < roadsNumber; roadInd++) {
        std::getline(file, line);
        in = std::istringstream(line);
        int roadRowInd, roadColInd;
        in >> roadRowInd >> roadColInd;
        roads.push_back(std::pair<int, int> {roadRowInd, roadColInd});
    }

    std::getline(file, line);
    in = std::istringstream(line);
    int beeRowInd, beeColInd;
    in >> beeRowInd >> beeColInd;
    beePos = std::pair<int, int> {beeRowInd, beeColInd};

    std::getline(file, line);
    in = std::istringstream(line);
    int aimRowInd, aimColInd;
    in >> aimRowInd >> aimColInd;
    aimPos = std::pair<int, int> {aimRowInd, aimColInd};
}