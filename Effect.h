#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QSoundEffect>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QDesktopWidget>
#include "Config.h"
#include <QPainter>
#include <QMediaPlayer>
#include <QGraphicsProxyWidget>

class Effect : public QObject
{
    Q_OBJECT

public:
    explicit Effect(QWidget *parent = nullptr, bool isMultiPlayer = false); // 修改构造函数参数为 QWidget*

    void excellentEffect();
    void missEffect();
    void loseGame();
    void winGame();
    void winGame(int charIdx);

private slots:
    void hideLabel();

private:
    QLabel *label;
    bool isMultiPlayer;
};

#endif // EFFECT_H

