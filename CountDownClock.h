#ifndef COUNTDOWNCLOCK_H
#define COUNTDOWNCLOCK_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "Config.h"

class CountDownClock : public QWidget
{
public:
    CountDownClock(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateSeconds();

private:
    QTimer *timer;
    int seconds;
    QLabel *label;
};

#endif // COUNTDOWNCLOCK_H
