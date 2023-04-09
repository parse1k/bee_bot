#include "win_dialog.h"

WinDialog::WinDialog(QWidget *parent) : QDialog(parent) {
    ui.setupUi(this);

    connect(ui.menuButton, SIGNAL(clicked(bool)), this, SLOT(handleMenuButtonClick()));
}

void WinDialog::handleMenuButtonClick() {
    emit toMenu();
}