#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(QGraphicsItem *parent, int type, int xPos, int yPos)
    : QGraphicsPixmapItem(parent), scoreText(new QGraphicsTextItem(this))
{
    QPixmap pixmap(scoreBoardImages[type]);
    pixmap = pixmap.scaled(500, 250);  // 将底图大小设置为400x100

    // 设置背景图片位置
    setPos(xPos, yPos);
    setPixmap(pixmap);

    // 创建角色图片项
    QGraphicsPixmapItem* characterPixmapItem = new QGraphicsPixmapItem(this);
    characterPixmapItem->setPos(50, 50); // 调整角色图片的位置
    QPixmap characterPixmap(characterImages[type]);
    int width = 150;  // 设置宽度
    int height = 150; // 设置高度
    QPixmap scaledPixmap = characterPixmap.scaled(width, height);
    characterPixmapItem->setPixmap(scaledPixmap);

    scoreText->setFont(QFont("Arial", 40));
    scoreText->setDefaultTextColor(Qt::black);

    // 计算文本位置使其居中
    int textWidth = scoreText->boundingRect().width();
    int textHeight = scoreText->boundingRect().height();
    int centerX = 250;
    int centerY = pixmap.height() / 2 - textHeight / 2;

    scoreText->setPos(centerX, centerY);
}

void ScoreBoard::setScore(int score) {
    // 更新分数文本
//    scoreText->setPlainText(QString("Score: ") + QString::number(score));
    scoreText->setPlainText(QString::number(score));
}



