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


class MainWindow : public QGraphicsView {
public:
    MainWindow(QWidget* parent = nullptr);

private:
    QGraphicsScene* scene;
    QSoundEffect* bgm;
    Effect* effect;
    Character* character;
    CountDownClock* countDownClock;
    std::vector<std::vector<Block*>> blockMap;
    Block* linkPair[2];
    std::vector<std::pair<int, int>> linkPath;

    void createMap(QGraphicsScene* scene);

    void keyPressEvent(QKeyEvent *event);
    bool isSelect(int x, int y, QKeyEvent *event);

    void resetBlocks(int x, int y);
    void resetBlock(int x, int y);
    void nearBlocks(int x, int y);
    void nearBlock(int x, int y);

    void linkBlock(int x, int y);
    bool isLinkable();
    bool isLinkable_zeroAngle(int x1, int y1, int x2, int y2, bool isDirect, bool examEndPoint);
    bool isLinkable_oneAngle(int x1, int y1, int x2, int y2);
    bool isLinkable_twoAngle(int x1, int y1, int x2, int y2);

    void linkEffect();
    void eraseLinkEffect();
};

#endif // MAINWINDOW_H
