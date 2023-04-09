#include "level_button.h"
#include <QDebug>

LevelButton::LevelButton(int levelInd_, QWidget *parent) : levelInd(levelInd_), QPushButton(parent) {
    initParams();
}

void LevelButton::initParams() {
    initFont();
    initStyle();
    initText();
    resize();
}

void LevelButton::initText() {
    this->setText("УРОВЕНЬ " + QString::number(levelInd + 1));
}

void LevelButton::initStyle() {
    this->setStyleSheet("background-color: #8bc24c; color: #FFFFFF; border: 0; border-radius: 20px;");
}

void LevelButton::initFont() {
    font = QFont("Century Gothic");
    font.setPointSize(25);
    this->setFont(font);
}

void LevelButton::resize() {
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
}

void LevelButton::mousePressEvent (QMouseEvent *event) {
    QPushButton::mousePressEvent(event);
}

void LevelButton::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton)
    {
        emit leftClicked(levelInd);
    }
}