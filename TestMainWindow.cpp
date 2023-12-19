#include "TestMainWindow.h"

TestMainWindow::TestMainWindow()
{
qDebug("Called before everything else.");
}

TestMainWindow::~TestMainWindow()
{
qDebug("Stop After everything else.");
}

//测试isSelect函数
void TestMainWindow::test_case1()
{
    MainWindow mainWindow(nullptr, false);

    //select成功测试
    QVERIFY(mainWindow.isSelectTest(0, -1, new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier)));
    QVERIFY(mainWindow.isSelectTest(-1, 0, new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier)));
    QVERIFY(mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS, 0, new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier)));
    QVERIFY(mainWindow.isSelectTest(0, NUM_VERTICAL_BLOCKS, new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier)));

    // selected block超出范围
    QVERIFY(!mainWindow.isSelectTest(0, -1, new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(-1, 0, new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS, 0, new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(0, NUM_VERTICAL_BLOCKS, new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS, -1, new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(-1, NUM_VERTICAL_BLOCKS, new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS, NUM_VERTICAL_BLOCKS, new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS, NUM_VERTICAL_BLOCKS, new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier)));

    //select空block
    mainWindow.setBlockInMap(0, 0, nullptr);
    mainWindow.setBlockInMap(NUM_HORIZONTAL_BLOCKS - 1, NUM_VERTICAL_BLOCKS - 1, nullptr);
    delete mainWindow.getBlockFromMap(0, 0);
    delete mainWindow.getBlockFromMap(NUM_HORIZONTAL_BLOCKS - 1, NUM_VERTICAL_BLOCKS - 1);
    QVERIFY(!mainWindow.isSelectTest(0, -1, new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(-1, 0, new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS, NUM_VERTICAL_BLOCKS - 1, new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier)));
    QVERIFY(!mainWindow.isSelectTest(NUM_HORIZONTAL_BLOCKS - 1, NUM_VERTICAL_BLOCKS, new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier)));
}



//测试isLinkable函数
void TestMainWindow::test_case2()
{
    MainWindow mainWindow(nullptr, false);

    //linkPair为空
    QVERIFY(!mainWindow.isLinkableTest());

    //直线link测试
    Block* block1 = mainWindow.getBlockFromMap(0, 0);
    mainWindow.setLinkPair(0, block1);
    Block* block2 = mainWindow.getBlockFromMap(0, 1);
    block2->setType(block1->getType());
    mainWindow.setLinkPair(1, block2);
    QVERIFY(mainWindow.isLinkableTest());

    //两折角link测试
    mainWindow.setLinkPair(0, block1);
    block2 = mainWindow.getBlockFromMap(0, 3);
    block2->setType(block1->getType());
    mainWindow.setLinkPair(1, block2);
    QVERIFY(mainWindow.isLinkableTest());

    //无法link
    mainWindow.setLinkPair(0, block1);
    block2 = mainWindow.getBlockFromMap(1, 1);
    block2->setType(block1->getType());
    mainWindow.setLinkPair(1, block2);
    QVERIFY(!mainWindow.isLinkableTest());

    //单个折角link测试
    mainWindow.setBlockInMap(0, 0, nullptr);
    block1 = mainWindow.getBlockFromMap(0, 1);
    mainWindow.setLinkPair(0, block1);
    block2 = mainWindow.getBlockFromMap(1, 0);
    block2->setType(block1->getType());
    mainWindow.setLinkPair(1, block2);
    QVERIFY(mainWindow.isLinkableTest());



    //种类不同不可以link
    block1 = mainWindow.getBlockFromMap(0, 1);
    block1->setType(1);
    mainWindow.setLinkPair(0, block1);
    block2 = mainWindow.getBlockFromMap(1, 0);
    block2->setType(2);
    mainWindow.setLinkPair(1, block2);
    QVERIFY(!mainWindow.isLinkableTest());

 }
