#include "Effect.h"
#include <QPixmap>
#include <QSound>

Effect::Effect(QWidget *parent, bool isMultiPlayer) : QObject(parent), isMultiPlayer(isMultiPlayer)
{
    label = new QLabel(parent); // 将 parent 作为父对象传递给 QLabel 构造函数
}

void Effect::excellentEffect()
{
    if (!isMultiPlayer) label->setGeometry(X_OFFSET + BLOCK_INTERVAL * NUM_HORIZONTAL_BLOCKS / 2 - 200, Y_OFFSET - 3 * BLOCK_INTERVAL, 400, 100);
    else label->setGeometry(X_OFFSET_MULTI + BLOCK_INTERVAL * NUM_HORIZONTAL_BLOCKS / 2 - 200, Y_OFFSET_MULTI - 3 * BLOCK_INTERVAL, 400, 100);

    QPixmap originalPixmap(":/Effect/image/effect/excellent.png");
    QPixmap scaledPixmap = originalPixmap.scaled(400, 100, Qt::KeepAspectRatio);
    label->setPixmap(scaledPixmap);
    label->show();

    QSound::play(":/Sound/sounds/excellent.wav");

    QTimer::singleShot(1000, this, &Effect::hideLabel);
}

void Effect::missEffect() {
    if (!isMultiPlayer) label->setGeometry(X_OFFSET + BLOCK_INTERVAL * NUM_HORIZONTAL_BLOCKS / 2 - 200, Y_OFFSET - 3 * BLOCK_INTERVAL, 400, 100);
    else label->setGeometry(X_OFFSET_MULTI + BLOCK_INTERVAL * NUM_HORIZONTAL_BLOCKS / 2 - 200, Y_OFFSET_MULTI - 3 * BLOCK_INTERVAL, 400, 100);

    QSound::play(":/Sound/sounds/miss.wav");

    QPixmap originalPixmap(":/Effect/image/effect/miss.png");
    QPixmap scaledPixmap = originalPixmap.scaled(400, 100, Qt::KeepAspectRatio);
    label->setPixmap(scaledPixmap);
    label->show();

    QTimer::singleShot(1000, this, &Effect::hideLabel);
}

void Effect::loseGame() {
    // 获取屏幕的宽度和高度
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    label->setGeometry(screenWidth / 2 - ENDGAME_LOGO_SIZE / 2, screenHeight / 2 - ENDGAME_LOGO_SIZE / 2, ENDGAME_LOGO_SIZE, ENDGAME_LOGO_SIZE);

    QSound::play(":/Sound/sounds/lose.wav");

    QPixmap originalPixmap(":/Effect/image/effect/failGame.png");
    QPixmap scaledPixmap = originalPixmap.scaled(ENDGAME_LOGO_SIZE, ENDGAME_LOGO_SIZE, Qt::KeepAspectRatio);
    label->setPixmap(scaledPixmap);
    label->show();

    // QTimer::singleShot(3000, this, &Effect::hideLabel);
}

void Effect::winGame() {
    // 获取屏幕的宽度和高度
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    label->setGeometry(screenWidth / 2 - ENDGAME_LOGO_SIZE / 2, screenHeight / 2 - ENDGAME_LOGO_SIZE / 2, ENDGAME_LOGO_SIZE, ENDGAME_LOGO_SIZE);

    QSound::play(":/Sound/sounds/win.wav");

    QPixmap originalPixmap(":/Effect/image/effect/winGame.png");
    QPixmap scaledPixmap = originalPixmap.scaled(ENDGAME_LOGO_SIZE, ENDGAME_LOGO_SIZE, Qt::KeepAspectRatio);
    label->setPixmap(scaledPixmap);
    label->show();

    // QTimer::singleShot(3000, this, &Effect::hideLabel);
}

void Effect::winGame(int charIdx) {
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    label->setGeometry(screenWidth / 2 - ENDGAME_LOGO_SIZE / 2, screenHeight / 2 - ENDGAME_LOGO_SIZE / 2, ENDGAME_LOGO_SIZE, ENDGAME_LOGO_SIZE);

    QSound::play(":/Sound/sounds/win.wav");

    QPixmap originalPixmap(":/Effect/image/effect/winGame_player.jpeg");
    QPixmap scaledPixmap = originalPixmap.scaled(ENDGAME_LOGO_SIZE, ENDGAME_LOGO_SIZE, Qt::KeepAspectRatio);

    // 创建一个新的QPixmap并绘制characterImages[charIdx]
    QPixmap characterPixmap(characterImages[charIdx]);
    QPainter painter(&scaledPixmap);
    // 调整位置和大小
    int x = (scaledPixmap.width() - characterPixmap.width()) / 2;
    int y = (scaledPixmap.height() - characterPixmap.height()) / 2;
    painter.drawPixmap(x, y, characterPixmap);

    label->setPixmap(scaledPixmap);
    label->show();
}



void Effect::hideLabel()
{
    label->hide();
//    delete label;
}

