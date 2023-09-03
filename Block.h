#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "Config.h"
#include <iostream>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QMovie>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QObject>
#include <chrono>
#include <thread>


const QString images[10] = {
    ":/Block/image/blocks/banana.png",
    ":/Block/image/blocks/cherry.png",
    ":/Block/image/blocks/eggplant.png",
    ":/Block/image/blocks/grapes.png",
    ":/Block/image/blocks/greenApple.png",
    ":/Block/image/blocks/mango.png",
    ":/Block/image/blocks/pear.png",
    ":/Block/image/blocks/pineapple.png",
    ":/Block/image/blocks/raspberry.png",
    ":/Block/image/blocks/strawberry.png"
};

const QString images_near[10] = {
    ":/Block_near/image/blocks_near/banana.PNG",
    ":/Block_near/image/blocks_near/cherry.PNG",
    ":/Block_near/image/blocks_near/eggplant.PNG",
    ":/Block_near/image/blocks_near/grapes.PNG",
    ":/Block_near/image/blocks_near/greenApple.PNG",
    ":/Block_near/image/blocks_near/mango.PNG",
    ":/Block_near/image/blocks_near/pear.PNG",
    ":/Block_near/image/blocks_near/pineapple.PNG",
    ":/Block_near/image/blocks_near/raspberry.png",
    ":/Block_near/image/blocks_near/strawberry.PNG"
};

enum State {
    normal,
    near,
    selected
};

class Block : public QGraphicsPixmapItem {
public:
    Block(int x = 0, int y = 0, int type = 0, bool isMultiPlayer = false);
    void reset();
    void resetFromSelect();
    void near();
    bool select();
    void selectByHint();
    void link();
    int getType();
    int getX();
    int getY();
    void setNewPos(int x, int y);

private:
    int x, y;
    int type;
    bool isMultiPlayer;
    State state;
    QGraphicsProxyWidget* proxyWidget;
};

#endif // BLOCK_H
