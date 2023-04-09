#ifndef BEE_BOT_MAIN_WINDOW_H
#define BEE_BOT_MAIN_WINDOW_H

#include <QMainWindow>
#include "../ui/ui_main_window.h"
#include "win_dialog.h"
#include "game_lib/level_button.h"
#include "game_lib/game_board.h"

#include <vector>
#include <string>
/// Главное окно приложения
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    /// Слот обрабатывает запуск уровня
    void handleLevelButtonClick(int levelInd);
    /// Слот обрабатывает нажатие на элемент управления
    void handleControlClick(std::string instruction);
    /// Слот обрабатывает запуск инструкций
    void handleRun();
    /// Слот перезапуска игры
    void restart();
    /// Слот возвращения в меню
    void toMenu();
    /// Слот открытия модального окна при победе
    void openWinDialog();
private:
    Ui_MainWindow ui;

    std::vector<QPushButton *> levelButtons;
    LevelReader* levelReader;
    WinDialog* winDialog;
    int currentLevelInd = 0;
    int levelsNumber = 6;
    int levelButtonsRowsNumber= 2;
    int levelButtonsColsNumber = levelsNumber / levelButtonsRowsNumber;

    std::vector<std::string> instructions;
    GameBoard* gameBoard;

    /// Инициализирует кнопки выбора уровня
    void initLevelButtons();
    /// Инициализирует объекты игрового поля
    void initGame();
    /// Инициализирует элементы управления
    void initControls();
    /// Устанавливает иконку для кнопки
    void setButtonIcon(QPushButton* button, QString filename, int iconSize = 50);
    /// Подключает слоты к элементам управления
    void connectControlButtons();
    /// Отрисовывает список выбранных инструкций
    void drawInstructions();
};


#endif //BEE_BOT_MAIN_WINDOW_H
