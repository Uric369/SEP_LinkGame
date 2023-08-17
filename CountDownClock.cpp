#include "CountDownClock.h"

CountDownClock::CountDownClock(QWidget *parent) : QWidget(parent), seconds(0)
{
    timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, this, &CountDownClock::updateSeconds);
    timer->start(1000); // 每隔1秒触发一次计时器

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 96px; color: white;");
    label->setGeometry(rect().center().x() + 50, rect().center().y() + 80, 100, 100);

    setGeometry(CLOCK_X_OFFSET, CLOCK_Y_OFFSET, CLOCK_SIZE, CLOCK_SIZE);
}

void CountDownClock::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制外边框圆环
    QColor borderColor(Qt::yellow);
    painter.setPen(QPen(borderColor, ANNULUS_THICKNESS));
    painter.drawEllipse(rect().center(), CLOCK_EXRADIUS - ANNULUS_THICKNESS / 2, CLOCK_EXRADIUS - ANNULUS_THICKNESS / 2);

    // 绘制内部填充圆环
    QColor fillColor(Qt::blue); // 这里用蓝色作为填充颜色，你可以根据需要修改
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
}

void CountDownClock::updateSeconds() {
    seconds++;
    if (seconds > COUNTDOWN_TIME)
    {
        timer->stop();
    }
    update(); // 触发重绘事件，更新界面
}
