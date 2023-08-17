#include "Block.h"

Block::Block(int x, int y, int type) : QGraphicsPixmapItem(), x(x), y(y), type(type), state(State::normal), proxyWidget(nullptr) {
    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);
    setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
}

void Block::reset() {
    if (this->state == State::selected) return;

    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);

    this->state = State::normal;
}

void Block::resetFromSelect() {
    if (state != State::selected) return;

    delete proxyWidget;
    proxyWidget = nullptr;

    // Reset the state and set the pixmap
    this->state = State::normal;
    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);
    setPixmap(pixmap);
}



void Block::near() {
    if (this->state == State::selected) return;

    QPixmap pixmap(images_near[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);
//    std::cout<<x<<", "<<y<<":"<<"near"<<std::endl;
    this->state = State::near;
}

bool Block::select() {
    if (this->state != State::near) return false;
    QString gifPath = ":/Block_select/image/blocks_select/strawberry.gif"; // 替换为你的GIF动图路径
    QMovie* movie = new QMovie(gifPath);
    movie->setCacheMode(QMovie::CacheAll);
    movie->setScaledSize(QSize(BLOCK_SIZE, BLOCK_SIZE));

    QLabel* label = new QLabel();
    label->setMovie(movie);

    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(label);

    movie->start();

    this->state = State::selected;

    std::cout<<x<<", "<<y<<":"<<"select"<<std::endl;
    return true;
}

void Block::link() {
    if (this->state != State::selected) return;

    QString gifPath = ":/Effect/image/effect/explode.gif"; // 替换为你的GIF动图路径
    QMovie* movie = new QMovie(gifPath);
    movie->setCacheMode(QMovie::CacheAll);
    movie->setScaledSize(QSize(EXPLODE_EFFECT_SIZE, EXPLODE_EFFECT_SIZE));

    QLabel* label = new QLabel();
    label->setMovie(movie);
    label->setStyleSheet("background-color: transparent;");

    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(label);
    proxyWidget->setPos(proxyWidget->pos().x() + EXPLODE_OFFSET, proxyWidget->pos().y() + EXPLODE_OFFSET);

    movie->start();
}

int Block::getType() {
    return this->type;
}

int Block::getX() {
    return this->x;
}

int Block::getY() {
    return this->y;
}
