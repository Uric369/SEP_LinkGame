#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <iostream>
#include "Config.h"

class Character : public QGraphicsPixmapItem {
public:
    Character(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    int getX();
    int getY();

private:
    int x, y;

    void moveCharacter(int dx, int dy);
};

#endif // CHARACTER_H
