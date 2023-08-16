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

class MainWindow : public QGraphicsView {
public:
    MainWindow(QWidget* parent = nullptr);

private:
    QGraphicsScene* scene;
    std::vector<std::vector<Block*>> blockMap;
    Block* linkPair[2];

    void createMap(QGraphicsScene* scene);

    void keyPressEvent(QKeyEvent *event);
    bool isSelect(int x, int y, QKeyEvent *event);

    void resetBlocks(int x, int y);
    void resetBlock(int x, int y);
    void nearBlocks(int x, int y);
    void nearBlock(int x, int y);

    void linkBlock(int x, int y);
    bool isLinkable();
};

#endif // MAINWINDOW_H
