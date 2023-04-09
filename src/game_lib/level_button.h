#ifndef BEE_BOT_LEVEL_BUTTON_H
#define BEE_BOT_LEVEL_BUTTON_H

#include <QObject>
#include <QtWidgets>
#include <QPushButton>
#include <QMouseEvent>
/// Переопределенный класс кнопки для кнопки уровня
class LevelButton : public QPushButton {
    Q_OBJECT
public:
    LevelButton(int levelInd_, QWidget *parent = nullptr);
private:
    int levelInd;
    int width = 300;
    int height = 200;
    QFont font;
    /// Инициализация параметров кнопки
    void initParams();
    /// Инициализация текста кнопки
    void initText();
    /// Инициализация css стилей кнопки
    void initStyle();
    /// Инициализация шрифта кнопки
    void initFont();
    /// Изменение размера кнопки
    void resize();

protected:
    /// Переопределение события нажатия на кнопку
    void mousePressEvent(QMouseEvent *event) override;
    /// Переопределение события нажатия на кнопку(release)
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    /// Сигнал нажатия на кнопку
    void leftClicked(int levelInd);
};


#endif //BEE_BOT_LEVEL_BUTTON_H
