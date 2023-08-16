#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QGraphicsView(parent) {
    setWindowTitle("Main Window");

    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    resize(screenWidth, screenHeight);

    // 创建场景
    scene = new QGraphicsScene(this);

    // 设置背景图片
    QPixmap background(":/MainWindow/MainWindow_Background_2.jpg");
    background = background.scaled(screenWidth, screenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(background);
    scene->setSceneRect(0, 0, screenWidth, screenHeight);

    linkPair[0] = nullptr;
    linkPair[1] = nullptr;

    //生成所有方块
    createMap(scene);

    // 创建角色
    Character* character = new Character();
    scene->addItem(character);

    // 将场景设置到视图中
    setScene(scene);

    // 将主窗口设置为焦点，以便接收键盘事件
    setFocus();
}

void MainWindow::createMap(QGraphicsScene* scene) {
    // 生成有序的typeMap
    int typeMap[NUM_HORIZONTAL_BLOCKS][NUM_VERTICAL_BLOCKS];
    for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
        for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++){
            typeMap[i][j] = (i * NUM_HORIZONTAL_BLOCKS + j) % 10;
        }
    }

    // 打乱typeMap
    srand(static_cast<unsigned>(time(0))); // 在合适位置种下随机数种子
    for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
        for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++){
            int randomX = rand() % NUM_HORIZONTAL_BLOCKS;
            int randomY = rand() % NUM_VERTICAL_BLOCKS;

            std::swap(typeMap[randomX][randomY],typeMap[i][j]);
        }
    }

    //生成所有方块
    //一定要初始化分配空间啊！！！
    blockMap.resize(NUM_HORIZONTAL_BLOCKS, std::vector<Block*>(NUM_VERTICAL_BLOCKS, nullptr));

    for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
        for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++){
            Block* block = new Block(i, j, typeMap[i][j]);
            blockMap[i][j] = block;
            scene->addItem(block);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // 获取Character位置
    int x_pos, y_pos;

    // 获取当前场景中的所有项
    QList<QGraphicsItem *> items = scene->items();

    // 查找Character项
    foreach (QGraphicsItem *item, items) {
        Character *character = qgraphicsitem_cast<Character *>(item);
        if (character) {
            // 调用Character的keyPressEvent处理函数
            x_pos = character->getX();
            y_pos = character->getY();

            if (!isSelect(x_pos, y_pos, event)) {
                resetBlocks(x_pos, y_pos);

                character->keyPressEvent(event);

                x_pos = character->getX();
                y_pos = character->getY();
                nearBlocks(x_pos, y_pos);
            }
            break;
        }
    }
}

bool MainWindow::isSelect(int x, int y, QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            if (x >= 0 && x < NUM_HORIZONTAL_BLOCKS
            && y - 1 >= 0 && y - 1 <NUM_VERTICAL_BLOCKS
            && blockMap[x][y - 1]) {
                if (blockMap[x][y - 1]->select()) linkBlock(x, y - 1);
                return true;
            }
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            if (x >= 0 && x < NUM_HORIZONTAL_BLOCKS
            && y + 1 >= 0 && y + 1 <NUM_VERTICAL_BLOCKS
            && blockMap[x][y + 1]) {
                if (blockMap[x][y + 1]->select()) linkBlock(x, y + 1);
                return true;
            }
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            if (x - 1 >= 0 && x - 1 < NUM_HORIZONTAL_BLOCKS
            && y >= 0 && y <NUM_VERTICAL_BLOCKS
            && blockMap[x - 1][y]) {
                if (blockMap[x - 1][y]->select()) linkBlock(x - 1, y);
                return true;
            }
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            if (x + 1 >= 0 && x + 1 < NUM_HORIZONTAL_BLOCKS
            && y >= 0 && y <NUM_VERTICAL_BLOCKS
            && blockMap[x + 1][y]) {
                if (blockMap[x + 1][y]->select()) linkBlock(x + 1, y);
                return true;
            }
            break;
        default:
            return true;
    }
    return false;
}

void MainWindow::resetBlocks(int x, int y) {
    if ((x == -1 && y == -1) ||
    (x == -1 && y == NUM_VERTICAL_BLOCKS) ||
    (x == NUM_HORIZONTAL_BLOCKS && y == -1) ||
    (x == NUM_HORIZONTAL_BLOCKS && y == NUM_VERTICAL_BLOCKS)) return;

    resetBlock(x - 1, y);
    resetBlock(x, y + 1);
    resetBlock(x + 1, y);
    resetBlock(x, y - 1);
}

void MainWindow::resetBlock(int x, int y) {
    if (x >= 0 && x < NUM_HORIZONTAL_BLOCKS && y >= 0 && y < NUM_VERTICAL_BLOCKS && blockMap[x][y])
        blockMap[x][y]->reset();
}

void MainWindow::nearBlocks(int x,int y) {
    if ((x == -1 && y == -1) ||
    (x == -1 && y == NUM_VERTICAL_BLOCKS) ||
    (x == NUM_HORIZONTAL_BLOCKS && y == -1) ||
    (x == NUM_HORIZONTAL_BLOCKS && y == NUM_VERTICAL_BLOCKS)) return;

    nearBlock(x - 1, y);
    nearBlock(x, y + 1);
    nearBlock(x + 1, y);
    nearBlock(x, y - 1);
}

void MainWindow::nearBlock(int x, int y) {
    if (x >= 0 && x < NUM_HORIZONTAL_BLOCKS && y >= 0 && y <NUM_VERTICAL_BLOCKS && blockMap[x][y])
        blockMap[x][y]->near();
}

void MainWindow::linkBlock(int x, int y) {
    if (linkPair[0] == nullptr) {
        linkPair[0] = blockMap[x][y];
        return;
    }

    linkPair[1] = blockMap[x][y];
    if (isLinkable()) {
        std::cout << "success" << std::endl;

        linkPair[0]->link();
        linkPair[1]->link();

        QTimer::singleShot(300, [=]() {
            blockMap[linkPair[0]->getX()][linkPair[0]->getY()] = nullptr;
            blockMap[linkPair[1]->getX()][linkPair[1]->getY()] = nullptr;

            scene->removeItem(linkPair[0]);
            scene->removeItem(linkPair[1]);

            delete linkPair[0];
            delete linkPair[1];

            linkPair[0] = nullptr;
            linkPair[1] = nullptr;
        });
    }
    else {
        std::cout<<"fail"<<std::endl;
        linkPair[0]->resetFromSelect();
        linkPair[1]->resetFromSelect();

        linkPair[0] = nullptr;
        linkPair[1] = nullptr;
    }
}

bool MainWindow::isLinkable() {
    if (linkPair[0]->getType() != linkPair[1]->getType()) return false;
    return true;
}
