TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT += core gui widgets network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
        Block.cpp \
        Character.cpp \
        Config.cpp \
        Entry.cpp \
        MainWindow.cpp \
        main.cpp

HEADERS += \
    Block.h \
    Character.h \
    Config.h \
    Entry.h \
    MainWindow.h

RESOURCES += \
    LinkGame.qrc
