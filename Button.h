#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include "Config.h"

const QString image_before[6] = {
    ":/Button/image/button/pause.png",
    ":/Button/image/button/pause.png",
    ":/Button/image/button/danren.png",
    ":/Button/image/button/shuangren.png",
    ":/Button/image/button/load.png",
    ":/Button/image/button/exit.png",
};

const QString image_after[6] = {
    ":/Button/image/button/restart.png",
    ":/Button/image/button/restart.png",
    ":/Button/image/button/danren.png",
    ":/Button/image/button/shuangren.png",
    ":/Button/image/button/load.png",
    ":/Button/image/button/exit.png",
};

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(int x, int y, int type, QWidget *parent = nullptr);

private slots:
    void toggleImage();

private:
    QString image1Path;
    QString image2Path;
    bool isImage1;

    void setImage(const QString& imagePath);
};


#endif // BUTTON_H
