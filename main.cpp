#include <QApplication>

#include "Entry.h"
#include "MainWindow.h"
#include "MainWindow_multiplayer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Entry entry;
    entry.show();
//    MainWindow mainWindow;
//    mainWindow.show();
//    MainWindow_m mainWindow_m;
//    mainWindow_m.show();

    return app.exec();
}
