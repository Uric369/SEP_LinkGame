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

const QString images_select[10] = {
    ":/Block_select/image/blocks_select/banana.GIF",
    ":/Block_select/image/blocks_select/cherry.GIF",
    ":/Block_select/image/blocks_select/eggplant.GIF",
    ":/Block_select/image/blocks_select/grape.GIF",
    ":/Block_select/image/blocks_select/greenApple.GIF",
    ":/Block_select/image/blocks_select/mango.GIF",
    ":/Block_select/image/blocks_select/pear.gif",
    ":/Block_select/image/blocks_select/pineapple.GIF",
    ":/Block_select/image/blocks_select/raspberry.GIF",
    ":/Block_select/image/blocks_select/strawberry.gif",
};


enum State {
    normal, //正常状态
    near, //靠近状态
    selected //选中状态
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
    void setType(int type);
    void setNewPos(int x, int y);

private:
    int x, y;
    int type;
    bool isMultiPlayer; //是否为双人模式
    State state;
    QGraphicsProxyWidget* proxyWidget; //用于显示选中状态下的动图
};

#endif // BLOCK_H
