#include <QApplication>

#include "Entry.h"
#include "MainWindow.h"
#include "MainWindow_multiplayer.h"
#include "TestMainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Entry entry;
    entry.show();

    return app.exec();
}



//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    int result = QTest::qExec(new TestMainWindow, argc, argv);

//    return result;
//}
