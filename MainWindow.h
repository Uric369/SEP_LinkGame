#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <ctime>
#include <algorithm>
#include <vector>
#include "Block.h"
#include "Character.h"
#include "Config.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QSoundEffect>
#include "Effect.h"
#include "CountDownClock.h"
#include "Button.h"
#include "ScoreBoard.h"
#include <vector>
#include <cstdlib>
#include "Prop.h"


class MainWindow : public QGraphicsView {
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void handleCountdownFinished();

private:
    QGraphicsScene* scene;
    QSoundEffect* bgm;
    Effect* effect;
    Character* character;
    CountDownClock* countDownClock;
    std::vector<std::vector<Block*>> blockMap;
    Block* linkPair[2];
    std::vector<std::pair<int, int>> linkPath;
    std::vector<Prop*> props;
    QTimer *timer;
    ScoreBoard* scoreboard;
    Button *pauseButton;
    int seconds;
    int residue;
    bool isPaused;
    void updateSeconds();

    void createMap(QGraphicsScene* scene);
    void createProps(QGraphicsScene* scene);

    void keyPressEvent(QKeyEvent *event);
    bool isSelect(int x, int y, QKeyEvent *event);

    void resetBlocks(int x, int y);
    void resetBlock(int x, int y);
    void nearBlocks(int x, int y);
    void nearBlock(int x, int y);
    void triggerProp(int x, int y);
    void shuffle();
    void hint();
    bool findLinkPair(bool isLink);
    void findLinkPair_certainAmount();

    void linkBlock(int x, int y);
    bool isLinkable();
    bool isLinkable(int x1, int y1, int x2, int y2);
    bool isLinkable_zeroAngle(int x1, int y1, int x2, int y2, bool isDirect, bool examEndPoint);
    bool isLinkable_oneAngle(int x1, int y1, int x2, int y2);
    bool isLinkable_twoAngle(int x1, int y1, int x2, int y2);

    void linkEffect();
    void eraseLinkEffect();
    void blackMask();

    void judger();

    void pauseGame();
    void saveGame();
    void loadGame();
};

#endif // MAINWINDOW_H
