#ifndef BEE_BOT_WIN_DIALOG_H
#define BEE_BOT_WIN_DIALOG_H

#include <QDialog>
#include "../ui/ui_win_dialog.h"
/// Модальное окно, которое открывается при прохождении уровня
class WinDialog : public QDialog {
    Q_OBJECT
public:
    WinDialog(QWidget *parent = nullptr);
public slots:
    /// Слот обрабатывает нажатие кнопки возврата в меню
    void handleMenuButtonClick();
private:
    Ui_WinDialog ui;

signals:
    /// Сигнал возврата в меню
    void toMenu();
};


#endif //BEE_BOT_WIN_DIALOG_H
