#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QtTest>
#include "MainWindow.h"
#include <QObject>
//#include "tst_linkgametest.moc"

// add necessary includes here

class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    TestMainWindow();
    ~TestMainWindow();

private slots:
    void test_case1();
    void test_case2();
};

#endif // TESTMAINWINDOW_H
