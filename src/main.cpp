#include <QApplication>
#include "main_window.h"
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
