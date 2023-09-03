#include "Prop.h"

Prop::Prop(int x, int y, int type) : QGraphicsPixmapItem(), x(x), y(y), type(type), proxyWidget(nullptr) {
    QPixmap pixmap(propImages[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);
    setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
}

void Prop::trigger() {
    QString gifPath = ":/Effect/image/effect/explode.gif"; // 替换为你的GIF动图路径
    // QString gifPath = ":/Prop/props/triggerProps.gif";
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

    QSound::play(":/Sound/sounds/triggerProps.wav");
}

int Prop::getType() {
    return this->type;
}

void Prop::setNewPos(int x, int y) {
    this->x = x;
    this->y = y;
    setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
}

int Prop::getX() {
    return this->x;
}

int Prop::getY() {
    return this->y;
}
