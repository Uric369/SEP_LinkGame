#include <QApplication>

#include "Entry.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

//    Entry entry;
//    entry.show();
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
