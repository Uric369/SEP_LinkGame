#include "CountDownClock.h"

CountDownClock::CountDownClock(QWidget *parent) : QWidget(parent), seconds(0), isPaused(false) {
    timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &CountDownClock::updateSeconds);
    timer->start(1000); // 每隔1秒触发一次计时器

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 96px; color: white;");
//    label->setGeometry(rect().center().x() + 50, rect().center().y() + 80, 100, 100);
    label->setGeometry(rect().center().x() + 30, rect().center().y() + 60, 140, 140);

    setGeometry(CLOCK_X_OFFSET, CLOCK_Y_OFFSET, CLOCK_SIZE, CLOCK_SIZE);
}

void CountDownClock::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制外边框圆环
    painter.setPen(QPen(QColor(236, 111, 116), ANNULUS_THICKNESS / 2));
    painter.drawEllipse(rect().center(), CLOCK_EXRADIUS - ANNULUS_THICKNESS / 2, CLOCK_EXRADIUS - ANNULUS_THICKNESS / 2);

    painter.setPen(QPen(QColor(198, 49, 63), ANNULUS_THICKNESS / 2));
    painter.drawEllipse(rect().center(), CLOCK_EXRADIUS - ANNULUS_THICKNESS, CLOCK_EXRADIUS - ANNULUS_THICKNESS);

    // 绘制内部填充圆环
    QColor fillColor(QColor(255, 255, 255, 200));
    painter.setPen(Qt::NoPen);
    painter.setBrush(fillColor);

    // 计算内圆环填充区域的半径和角度
    int innerRadius = CLOCK_EXRADIUS - ANNULUS_THICKNESS;
    int startAngle = 90; // 圆环起始角度（以x轴正方向为0度逆时针旋转）
    int spanAngle = (360 - seconds * 360 / COUNTDOWN_TIME) * 16; // 扇形角度（乘以16是因为QPainter中的角度单位为1/16度）

    QRectF pieRect(rect().center() - QPointF(innerRadius, innerRadius), QSizeF(innerRadius * 2, innerRadius * 2));
    painter.drawPie(pieRect, startAngle * 16, spanAngle);

    // 绘制倒计时秒数
    QString text = QString::number(COUNTDOWN_TIME - seconds);
    label->setText(text);
    label->setStyleSheet("font-size: 96px; color: black;");
}

void CountDownClock::updateSeconds() {
    if (!isPaused) seconds++;
    if (!isPaused && seconds >= COUNTDOWN_TIME)
    {
        timer->stop();
        emit countdownFinished(); // Emit the countdownFinished() signal
        return;
    }
    update(); // 触发重绘事件，更新界面
}

void CountDownClock::countdownFinished() {
    std::cout<<"SIGNAL: countdownFinished"<<std::endl;
}

void CountDownClock::toggleCountDown() {
    isPaused = !isPaused;
}

void CountDownClock::stopCountDown() {
    isPaused = true;
}

void CountDownClock::addTime() {
    this->seconds -= ADD_TIME;
}
