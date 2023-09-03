#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <iostream>
#include "Config.h"


class Character : public QGraphicsPixmapItem {
public:
    Character(QGraphicsItem *parent = nullptr, int x = 0, int y = 0, int type = 0, bool isMultiPlayer = false);
    void keyPressEvent(QKeyEvent *event) override;
    int getX();
    int getY();

private:
    int x, y, type;
    bool isMultiPlayer;

    void moveCharacter(int dx, int dy);
};

#endif // CHARACTER_H
