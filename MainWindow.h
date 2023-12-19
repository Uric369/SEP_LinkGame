#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <fstream>
#include <sstream>

class MainWindow : public QGraphicsView {
public:
    MainWindow(QWidget* parent = nullptr, bool isResume = false);
    bool isSelectTest(int row, int col, QKeyEvent* event)
    {
        return isSelect(row, col, event);
    }
    void setBlockInMap(int row, int col, Block* block)
    {
        blockMap[row][col] = block;
    }

    Block* getBlockFromMap(int row, int col) const
    {
        return blockMap[row][col];
    }
    void setLinkPair(int index, Block* block)
    {
        block->near();
        block->select();
        linkPair[index] = block;
    }

    Block* getLinkPair(int index) const
    {
        return linkPair[index];
    }
    bool isLinkableTest()
    {
            return isLinkable();
    }

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
    Button *saveButton;
    int seconds;
    int residue;
    bool isPaused;
    bool isSaved;
    void updateSeconds();

    void createMap(QGraphicsScene* scene);
    void createCharacter(QGraphicsScene* scene);
    void createProps(QGraphicsScene* scene);
    void createComponents();
    void createMapBound();

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
