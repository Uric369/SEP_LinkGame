#include "Button.h"

Button::Button(int x, int y, int type, QWidget *parent)
    : QPushButton(parent), isImage1(true)
{
    if (type < 2) setGeometry(x, y, BUTTON_SIZE, BUTTON_SIZE);
    else setGeometry(x, y, BUTTON_WIDTH, BUTTON_HEIGHT);
    image1Path = image_before[type];
    image2Path = image_after[type];
    setImage(image1Path);
    connect(this, &QPushButton::clicked, this, &Button::toggleImage);

    // 设置按钮的样式表，将背景设置为透明，并在鼠标悬停时放大图标
    setStyleSheet("QPushButton { background-color: transparent; border: none; } \
                   QPushButton:hover { transform: scale(1.1); }");
}


void Button::toggleImage()
{
    if (isImage1) {
        setImage(image2Path);
        isImage1 = false;
    } else {
        setImage(image1Path);
        isImage1 = true;
    }
}

void Button::setImage(const QString& imagePath)
{
    QPixmap pixmap(imagePath);
    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(size());
    setFixedSize(size());
}
