#ifndef ENTRY_H
#define ENTRY_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QDesktopWidget>
#include "MainWindow.h"
#include "Block.h"

class Entry : public QWidget {
public:
    Entry(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QPushButton *startButton;

    void initializeComponents();
    void startGame();

};

#endif // ENTRY_H
