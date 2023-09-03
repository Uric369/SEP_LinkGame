#ifndef MAINWINDOW_MULTIPLAYER_H
#define MAINWINDOW_MULTIPLAYER_H

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

class MainWindow_m : public QGraphicsView {
public:
    MainWindow_m(QWidget* parent = nullptr);

private slots:
    void handleCountdownFinished();

private:
    QGraphicsScene* scene;
    QSoundEffect* bgm;
    Effect* effect;
    Character* character[2];
    CountDownClock* countDownClock;
    std::vector<std::vector<Block*>> blockMap;
//    Block* linkPair1[2];
//    std::vector<std::pair<int, int>> linkPath1;
//    Block* linkPair2[2];
//    std::vector<std::pair<int, int>> linkPath2;
    Block* linkPair[2][2];
    std::vector<std::pair<int, int>> linkPath[2];
//    std::vector<Prop*> props;
    QTimer *timer;
//    ScoreBoard* scoreboard1;
//    ScoreBoard* scoreboard2;
    ScoreBoard* scoreboard[2];
    int score[2];
    Button *pauseButton;
    int seconds;
    int residue;
    bool isPaused;
    void updateSeconds();

    void createMap(QGraphicsScene* scene);
//    void createProps(QGraphicsScene* scene);

    void keyPressEvent(QKeyEvent *event);
    bool isSelect(int x, int y, int character, QKeyEvent *eventt);

    void resetBlocks(int x, int y);
    void resetBlock(int x, int y);
    void nearBlocks(int x, int y);
    void nearBlock(int x, int y);
//    void triggerProp(int x, int y);
//    void shuffle();
//    void hint();
//    bool findLinkPair(bool isLink);
    bool findLinkPair();
    void findLinkPair_certainAmount();

    void linkBlock(int x, int y, int charIdx);
    bool isLinkable(int charIdx);
    bool isLinkable(int x1, int y1, int x2, int y2, int charIdx);
    bool isLinkable_zeroAngle(int x1, int y1, int x2, int y2, bool isDirect, bool examEndPoint, int charIdx);
    bool isLinkable_oneAngle(int x1, int y1, int x2, int y2, int charIdx);
    bool isLinkable_twoAngle(int x1, int y1, int x2, int y2, int charIdx);

    void linkEffect(int charIdx);
    void eraseLinkEffect();
    void blackMask();

    void judger();

    void pauseGame();
};


#endif // MAINWINDOW_MULTIPLAYER_H
