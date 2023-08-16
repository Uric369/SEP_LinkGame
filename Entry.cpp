#include "Entry.h"

Entry::Entry(QWidget *parent) : QWidget(parent) {
    setWindowTitle("连连看");

    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    resize(screenWidth, screenHeight);

    initializeComponents();
}

void Entry::initializeComponents() {
    // 设置背景图片
    QPixmap backgroundImage(":/Entry/Entry_background_2.jpg");

    // 调整背景图片的缩放模式为按比例缩放，并且保持纵横比例不变
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
    this->setPalette(palette);

    titleLabel = new QLabel(this);
    titleLabel->setText("连连看");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 30));
    titleLabel->setGeometry(width() / 2 - 100, height() / 2 - 300, 200, 50);

    startButton = new QPushButton("开始游戏", this);
    startButton->setGeometry(width() / 2 - 200, height() / 2 - 60, 400, 120); // 居中设置开始游戏按钮位置
    startButton->setStyleSheet("font-size: 50px"); // 设置字体大小为 24 像素
    startButton->setStyleSheet("QPushButton:hover { background-color: yellow; } QPushButton:pressed { background-color: green; }");

    connect(startButton, &QPushButton::clicked, this, &Entry::startGame);
}

void Entry::startGame() {
    MainWindow *m = new MainWindow();
    m->show();
    this->hide();
}
