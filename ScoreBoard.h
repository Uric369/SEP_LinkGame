#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsPixmapItem>
#include <QFont>
#include "Config.h"

const QString scoreBoardImages[2] = {
    ":/Effect/image/effect/scoreBoard.jpg",
    ":/Effect/image/effect/scoreBoard.jpg",
};


class ScoreBoard : public QGraphicsPixmapItem {
public:
    ScoreBoard(QGraphicsItem *parent = nullptr, int type = 0, int x = 0, int y = 0);

    void setScore(int score);

private:
    QGraphicsTextItem* scoreText;
};

#endif // SCOREBOARD_H
