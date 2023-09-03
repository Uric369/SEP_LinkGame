#ifndef PROP_H
#define PROP_H

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
#include <QSound>

const QString propImages[6] = {
    ":/Prop/image/props/+1s.PNG",
    ":/Prop/image/props/shuffle.PNG",
    ":/Prop/image/props/hint.PNG",
    ":/Prop/image/props/flash.PNG",
    ":/Prop/image/props/+1s.PNG",
    ":/Prop/image/props/+1s.PNG",
};

class Prop : public QGraphicsPixmapItem {
public:
    Prop(int x, int y, int type);
    void trigger();
    int getType();
    int getX();
    int getY();
    void setNewPos(int x, int y);

private:
    int x, y;
    int type;
    QGraphicsProxyWidget* proxyWidget;
};


#endif // PROP_H
