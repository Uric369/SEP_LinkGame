#include "Effect.h"
#include <QPixmap>
#include <QSound>

Effect::Effect(QWidget *parent) : QObject(parent)
{
    label = new QLabel(parent); // 将 parent 作为父对象传递给 QLabel 构造函数
}

void Effect::excellentEffect()
{
    label->setGeometry(X_OFFSET + BLOCK_INTERVAL * NUM_HORIZONTAL_BLOCKS / 2 - 200, Y_OFFSET - 3 * BLOCK_INTERVAL, 400, 100);

    QPixmap originalPixmap(":/Effect/image/effect/excellent.png");
    QPixmap scaledPixmap = originalPixmap.scaled(400, 100, Qt::KeepAspectRatio);
    label->setPixmap(scaledPixmap);
    label->show();

    QSound::play(":/Sound/sounds/excellent.wav");

    QTimer::singleShot(1000, this, &Effect::hideLabel);
}

void Effect::missEffect() {
    label->setGeometry(X_OFFSET + BLOCK_INTERVAL * NUM_HORIZONTAL_BLOCKS / 2 - 200, Y_OFFSET - 3 * BLOCK_INTERVAL, 400, 100);

    QSound::play(":/Sound/sounds/miss.wav");

    QPixmap originalPixmap(":/Effect/image/effect/miss.png");
    QPixmap scaledPixmap = originalPixmap.scaled(400, 100, Qt::KeepAspectRatio);
    label->setPixmap(scaledPixmap);
    label->show();

    QTimer::singleShot(1000, this, &Effect::hideLabel);
}

void Effect::hideLabel()
{
    label->hide();
//    delete label;
}
