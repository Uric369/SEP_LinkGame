#include "Character.h"
#include <QPixmap>
#include <QKeyEvent>

Character::Character(QGraphicsItem *parent, int x, int y, int type, bool isMultiPlayer) : QGraphicsPixmapItem(parent), x(x), y(y), type(type), isMultiPlayer(isMultiPlayer) {
    QPixmap pixmap(characterImages[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);
    if (!isMultiPlayer) setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
    else setPos(X_OFFSET_MULTI + x * BLOCK_INTERVAL, Y_OFFSET_MULTI + y * BLOCK_INTERVAL);
}

void Character::keyPressEvent(QKeyEvent *event) {
    int dx = 0;
    int dy = 0;
//    std::cout<<"here3"<<std::endl;

    // Check pressed key or arrow key
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            dy = -1;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            dy = 1;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            dx = -1;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            dx = 1;
            break;
        default:
            QGraphicsItem::keyPressEvent(event);
            return;
    }

    moveCharacter(dx, dy);
}

void Character::moveCharacter(int dx, int dy) {
    // Update character position
    x += dx;
    y += dy;

    // Boundary check and wrap around if necessary
    if (x < -1)
        x = NUM_HORIZONTAL_BLOCKS;
    else if (x > NUM_HORIZONTAL_BLOCKS)
        x = -1;

    if (y < -1)
        y = NUM_VERTICAL_BLOCKS;
    else if (y > NUM_VERTICAL_BLOCKS)
        y = -1;

    if (!isMultiPlayer) setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
    else setPos(X_OFFSET_MULTI + x * BLOCK_INTERVAL, Y_OFFSET_MULTI + y * BLOCK_INTERVAL);
}

int Character::getX() {
    return x;
}

int Character::getY() {
    return y;
}
