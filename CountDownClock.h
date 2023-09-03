#ifndef COUNTDOWNCLOCK_H
#define COUNTDOWNCLOCK_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <iostream>
#include "Config.h"

class CountDownClock : public QWidget
{
public:
    CountDownClock(QWidget *parent);
    void toggleCountDown();
    void stopCountDown();
    void addTime();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateSeconds();

signals:
    void countdownFinished();

private:
    QTimer *timer;
    int seconds;
    bool isPaused;
    QLabel *label;
};

#endif // COUNTDOWNCLOCK_H
