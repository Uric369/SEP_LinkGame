#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QSoundEffect>
#include "Config.h"
#include <QMediaPlayer>


class Effect : public QObject
{
    Q_OBJECT

public:
    explicit Effect(QWidget *parent = nullptr); // 修改构造函数参数为 QWidget*

    void excellentEffect();
    void missEffect();

private slots:
    void hideLabel();

private:
    QLabel *label;
};

#endif // EFFECT_H

