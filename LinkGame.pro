TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT += core gui widgets network multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
        Block.cpp \
        Button.cpp \
        Character.cpp \
        Config.cpp \
        CountDownClock.cpp \
        Effect.cpp \
        Entry.cpp \
        MainWindow.cpp \
        MainWindow_multiplayer.cpp \
        Prop.cpp \
        ScoreBoard.cpp \
        main.cpp

HEADERS += \
    Block.h \
    Button.h \
    Character.h \
    Config.h \
    CountDownClock.h \
    Effect.h \
    Entry.h \
    MainWindow.h \
    MainWindow_multiplayer.h \
    Prop.h \
    ScoreBoard.h

RESOURCES += \
    LinkGame.qrc
