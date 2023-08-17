TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT += core gui widgets network multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
        Block.cpp \
        Character.cpp \
        Config.cpp \
        CountDownClock.cpp \
        Effect.cpp \
        Entry.cpp \
        MainWindow.cpp \
        main.cpp

HEADERS += \
    Block.h \
    Character.h \
    Config.h \
    CountDownClock.h \
    Effect.h \
    Entry.h \
    MainWindow.h

RESOURCES += \
    LinkGame.qrc
