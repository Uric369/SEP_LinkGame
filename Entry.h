#ifndef ENTRY_H
#define ENTRY_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QDesktopWidget>
#include "MainWindow.h"
#include "MainWindow_multiplayer.h"
#include "Block.h"
#include "Button.h"

class Entry : public QWidget {
public:
    Entry(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    Button *singlePlayer;
    Button *twoPlayer;
    Button *loadGame;
    Button *exitGame;
    QSoundEffect* bgm;

    void initializeComponents();
    void singlePlayerMode();
    void twoPlayerMode();
    void loadGameMode();
    void exit();

};

#endif // ENTRY_H
