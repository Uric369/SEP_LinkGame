#include "MainWindow.h"

/*
 * MainWindow: 初始化MainWindow
 * args
 *     parent: 横坐标
 *     isResume: 是否载入游戏
 */
MainWindow::MainWindow(QWidget* parent, bool isResume) : QGraphicsView(parent) {
    // 设置窗口标题
    setWindowTitle("Main Window");

    // 设置窗口大小
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

    // 播放bgm
    bgm = new QSoundEffect(this);
    bgm->setLoopCount(QSoundEffect::Infinite); // 设置为无限循环
    bgm->setSource(QUrl::fromLocalFile(":/Sound/sounds/bgm.wav"));
    bgm->play();

    // 创建特效
    effect = new Effect(this);

    // 如果是载入游戏，读取文件并初始化
    if (isResume) loadGame();
    else {
    createMap(scene);     //生成所有方块
    createCharacter(scene);    //生成角色
    createComponents();    //生成零件（按钮计分板等）
    }

    // 将场景设置到视图中
    setScene(scene);

    // 将主窗口设置为焦点，以便接收键盘事件
    setFocus();
}

/*
 * createComponents: 生成零件
 */
void MainWindow::createComponents() {
    // 初始化参数
    residue = NUM_HORIZONTAL_BLOCKS * NUM_VERTICAL_BLOCKS;
    seconds = 0;
    isPaused = false;
    isSaved = false;
    linkPair[0] = nullptr;
    linkPair[1] = nullptr;

    // 启动计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSeconds);
    timer->start(1000); // 每隔1秒触发一次计时器

    // 创建暂停按钮
    pauseButton = new Button(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, 0, this);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pauseGame);

    // 创建存档按钮
    saveButton = new Button(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 200, 1, this);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveGame);

    // 创建倒计时
    countDownClock = new CountDownClock(this);
    connect(countDownClock, SIGNAL(countdownFinished()), this, SLOT(this->handleCountdownFinished()));

    // 创建计分板
    scoreboard = new ScoreBoard();
    scoreboard->setScore(0);
    scene->addItem(scoreboard);
}

/*
 * createCharacter: 创建角色
 * args
 *     scene: 当前窗口场景
 */
void MainWindow::createCharacter(QGraphicsScene* scene) {
    // 创建角色
    srand(static_cast<unsigned>(time(0)));
    // 随机角色位置
    int seed1 = rand() % 4;
    if (seed1 == 0 || seed1 == 2) {
        int seed2 = rand() % (NUM_VERTICAL_BLOCKS + 2);
        if (seed1 == 0) character = new Character(nullptr, -1, seed2 - 1, CHARACTER1_TYPE);
        if (seed1 == 2) character = new Character(nullptr, NUM_HORIZONTAL_BLOCKS, seed2 - 1, CHARACTER1_TYPE);
    }
    if (seed1 == 1 || seed1 == 3) {
        int seed2 = rand() % (NUM_HORIZONTAL_BLOCKS + 2);
        if (seed1 == 1) character = new Character(nullptr, seed2 - 1, -1, CHARACTER1_TYPE);
        if (seed1 == 3) character = new Character(nullptr, seed2 - 1, NUM_VERTICAL_BLOCKS, CHARACTER1_TYPE);
    }
    // 添加角色至场景
    scene->addItem(character);
}

/*
 * createMap: 创建block地图
 * args
 *     scene: 当前窗口场景
 */
void MainWindow::createMap(QGraphicsScene* scene) {
    // 生成有序的typeMap
    int typeMap[NUM_HORIZONTAL_BLOCKS][NUM_VERTICAL_BLOCKS];
    for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
        for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++){
            typeMap[i][j] = (j * NUM_HORIZONTAL_BLOCKS + i) % NUM_BLOCK_TYPE;
            std::cout<<"index: "<<j * NUM_HORIZONTAL_BLOCKS + i<<std::endl;
            std::cout<<typeMap[i][j]<<std::endl;
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

    createMapBound();

    for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
        for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++) {
            Block* block = blockMap[i][j];
            if (block != nullptr) {
                std::cout << "Type of block at (" << i << ", " << j << "): " << block->getType() << std::endl;
            }
        }
    }

}

/*
 * keyPressEvent: 处理键盘输入
 * args
 *     event：键盘事件
 */
void MainWindow::keyPressEvent(QKeyEvent *event) {
    // 如果暂停，则直接返回
    if (isPaused) return;

    // 如果已存当，恢复为未存档状态
    if (isSaved) {
        isSaved = false;
        saveButton->toggleImage();
    }

    // 获取Character位置
    int x_pos, y_pos;

    x_pos = character->getX();
    y_pos = character->getY();

    // 判断角色在(x_pos, y_pos)位置，键盘输入为event的情况下，是否有选中block的动作
    if (!isSelect(x_pos, y_pos, event)) {
        // 还原当前时刻被选中的block
        resetBlocks(x_pos, y_pos);

        character->keyPressEvent(event);

        x_pos = character->getX();
        y_pos = character->getY();
        // 处理被角色靠近的方块
        nearBlocks(x_pos, y_pos);
    }
    // 触发道具
    triggerProp(x_pos, y_pos);
}

/*
 * keyPressEvent: 处理键盘输入
 * args
 *     x：当前角色横坐标
 *     y：当前角色纵坐标
 */
void MainWindow::triggerProp(int x, int y) {
    if(props.empty()) {
        return; // Return immediately if props is uninitialized or empty
    }

    for (auto it = props.begin(); it != props.end(); ++it) {
        Prop* prop = *it;
        std::cout << "PropType: ";
        if (prop->getX() == x && prop->getY() == y) {
            std::cout << "PropType: " << prop->getType() << std::endl;
//            blockMap[x][y]->hide();
//            delete blockMap[x][y];
//            blockMap[x][y] = nullptr;
            // 触发不同的道具效果
            switch (prop->getType()) {
                case 0: seconds -= ADD_TIME;
                countDownClock->addTime();
                break;
                case 1:
                resetBlocks(character->getX(), character->getY());
                shuffle();
                if (!blockMap[character->getX()][character->getY()]) nearBlocks(character->getX(), character->getY());
                break;
                case 2: hint(); break;
                //case 3: flash(); break;
                default: break;
            }
            // 显示触发道具特效
            // 0.3秒后再从scene中删掉道具
            prop->trigger();
            QTimer::singleShot(300, [=]() {
                scene->removeItem(prop);
            });
            // Remove the prop from the props vector
            props.erase(it);
            break;
        }
    }
}

/*
 * Shuffle: 打乱方块
 */
void MainWindow::shuffle() {
    // 打乱typeMap
    srand(static_cast<unsigned>(time(0))); // 在合适位置种下随机数种子
    for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
        for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++){
            int randomX = rand() % NUM_HORIZONTAL_BLOCKS;
            int randomY = rand() % NUM_VERTICAL_BLOCKS;

            if (blockMap[i][j]) blockMap[i][j]->setNewPos(randomX, randomY);
            if (blockMap[randomX][randomY]) blockMap[randomX][randomY]->setNewPos(i, j);
            std::swap(blockMap[i][j], blockMap[randomX][randomY]);
        }
    }

    if (!props.empty()) {
        // 将空位置存入一个容器
        std::vector<std::pair<int, int>> emptyPositions;
        for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
            for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++) {
                if (blockMap[i][j] == nullptr) {
                    emptyPositions.emplace_back(i, j);
                }
            }
        }

        // 从内部空位置选择四个坐标
        std::vector<std::pair<int, int>> coordinates;
        for (int i = 0; i < props.size(); i++) {
            int index = std::rand() % emptyPositions.size();
            coordinates.push_back(emptyPositions[index]);
            emptyPositions.erase(emptyPositions.begin() + index);
        }

        for (int i = 0; i < props.size(); i++) {
            int x = coordinates[i].first;
            int y = coordinates[i].second;

            // 使用x和y进行操作或打印输出
            props[i]->setNewPos(x, y);
        }
    }
}

/*
 * hint：提示10s并自动消去方块
 */
void MainWindow::hint() {
    QTimer *hintTimer = new QTimer(this);
    connect(hintTimer, &QTimer::timeout, this, &MainWindow::findLinkPair_certainAmount);
    hintTimer->start(2000);  // 每隔1秒触发一次timeout信号
}

/*
 * findLinkPair_certainAmount：hint的辅助函数
 */
void MainWindow::findLinkPair_certainAmount() {
    std::cout<<"findLinkPair_certainAmount"<<std::endl;
    static int count = 0;
    if (count < 7) {
        std::cout<<"count:"<<count<<std::endl;
        findLinkPair(true);
        count++;
    }
}


/*
 * findLinkPair: 寻找可以消除的方块对
 * args
 *     isLink：找到之后是否消除。判断游戏是否结束调用findLinkPair时设置isLink是false
 */
bool MainWindow::findLinkPair(bool isLink) {
    std::cout<<"findLinkPair"<<std::endl;
    for (int i = 0; i < NUM_VERTICAL_BLOCKS * NUM_HORIZONTAL_BLOCKS; i++) {
        if (blockMap[i % NUM_HORIZONTAL_BLOCKS][i / NUM_HORIZONTAL_BLOCKS] == nullptr) continue;
        int x1 = i % NUM_HORIZONTAL_BLOCKS;
        int y1 = i / NUM_HORIZONTAL_BLOCKS;
        std::cout<<"check i ("<<x1<<", "<<y1<<")";
        for (int j = i + 1; j < NUM_VERTICAL_BLOCKS * NUM_HORIZONTAL_BLOCKS; j++) {
            std::cout<<"check j ("<<j % NUM_HORIZONTAL_BLOCKS<<", "<<j / NUM_HORIZONTAL_BLOCKS<<")";
            if (isLinkable(i % NUM_HORIZONTAL_BLOCKS, i / NUM_HORIZONTAL_BLOCKS, j % NUM_HORIZONTAL_BLOCKS, j / NUM_HORIZONTAL_BLOCKS)) {
                // 如果无需link，直接返回true
                if (!isLink) return true;
                int x2 = j % NUM_HORIZONTAL_BLOCKS;
                int y2 = j / NUM_HORIZONTAL_BLOCKS;
                blockMap[x1][y1]->selectByHint();
                blockMap[x2][y2]->selectByHint();
                QTimer::singleShot(1000, [=]() {
                    blockMap[x1][y1]->link();
                    blockMap[x2][y2]->link();
                    linkEffect();
                    effect->excellentEffect();
                    QTimer::singleShot(300, [=]() {
                        eraseLinkEffect();
                        scene->removeItem(blockMap[x1][y1]);
                        scene->removeItem(blockMap[x2][y2]);
                        delete blockMap[x1][y1];
                        delete blockMap[x2][y2];
                        blockMap[x1][y1] = nullptr;
                        blockMap[x2][y2] = nullptr;
                        residue -= 2;
                        scoreboard->setScore(NUM_VERTICAL_BLOCKS * NUM_HORIZONTAL_BLOCKS - residue);
                        judger();
                    });
                });
                return true;
                break;
            }
        }
    }
    return false;
}

/*
 * isSelect: 判断select是否被触发
 * args
 *     x， y：character当前的位置
 *     event：键盘动作
 * return
 *     0，未触发；1，触发
 */
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

/*
 * resetBlocks: 重置character周围的block
 * args
 *     x， y：character当前的位置
 */
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

/*
 * resetBlocks: 重置单个block
 * args
 *     x， y：block的位置
 */
void MainWindow::resetBlock(int x, int y) {
    if (x >= 0 && x < NUM_HORIZONTAL_BLOCKS && y >= 0 && y < NUM_VERTICAL_BLOCKS && blockMap[x][y])
        blockMap[x][y]->reset();
}


/*
 * nearBlocks: 设置character周围为靠近状态
 * args
 *     x， y：character当前的位置
 */
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

/*
 * nearBlock: 靠近单个block
 * args
 *     x， y：block的位置
 */
void MainWindow::nearBlock(int x, int y) {
    if (x >= 0 && x < NUM_HORIZONTAL_BLOCKS && y >= 0 && y <NUM_VERTICAL_BLOCKS && blockMap[x][y])
        blockMap[x][y]->near();
}

/*
 * linkBlock: 链接block
 * args
 *     x， y：block的位置
 */
void MainWindow::linkBlock(int x, int y) {
    //  如果之前未选择block，直接返回
    if (linkPair[0] == nullptr) {
        linkPair[0] = blockMap[x][y];
        return;
    }

    linkPair[1] = blockMap[x][y];
    if (isLinkable()) {
        std::cout << "success" << std::endl;

        linkPair[0]->link();
        linkPair[1]->link();
        linkEffect();
        effect->excellentEffect();

        QTimer::singleShot(300, [=]() {
            eraseLinkEffect();

            blockMap[linkPair[0]->getX()][linkPair[0]->getY()] = nullptr;
            blockMap[linkPair[1]->getX()][linkPair[1]->getY()] = nullptr;

            scene->removeItem(linkPair[0]);
            scene->removeItem(linkPair[1]);

            delete linkPair[0];
            delete linkPair[1];

            linkPair[0] = nullptr;
            linkPair[1] = nullptr;

            residue -= 2;

            scoreboard->setScore(NUM_VERTICAL_BLOCKS * NUM_HORIZONTAL_BLOCKS - residue);

            judger();
        });
    }
    else {
        std::cout<<"fail"<<std::endl;
        linkPair[0]->resetFromSelect();
        linkPair[1]->resetFromSelect();
        nearBlocks(character->getX(), character->getY());
        effect->missEffect();

        linkPair[0] = nullptr;
        linkPair[1] = nullptr;
    }
}

/*
 * linkEffect: 显示link特效
 */
void MainWindow::linkEffect() {
    if (linkPath.size() < 2) {
        // 链接路径上的点不足两个，无法绘制直线
        return;
    }

    QGraphicsScene* scene = this->scene;
    QPen linePen(QColor(101, 198, 254));  // 可以根据需要更改线条颜色和样式
    linePen.setWidth(4);

    for (size_t i = 0; i < linkPath.size() - 1; ++i) {
        int x1 = X_OFFSET + linkPath[i].first * BLOCK_INTERVAL + BLOCK_SIZE / 2;
        int y1 = Y_OFFSET + linkPath[i].second * BLOCK_INTERVAL + BLOCK_SIZE / 2;
        int x2 = X_OFFSET + linkPath[i + 1].first * BLOCK_INTERVAL + BLOCK_SIZE / 2;
        int y2 = Y_OFFSET + linkPath[i + 1].second * BLOCK_INTERVAL + BLOCK_SIZE / 2;

        scene->addLine(x1, y1, x2, y2, linePen);
    }
}

/*
 * eraselinkEffect: 擦除link特效
 */
void MainWindow::eraseLinkEffect() {
    QList<QGraphicsItem*> items = scene->items();

    for (QGraphicsItem* item : items) {
        if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
            delete item;
        }
    }
}

/*
 * isLinkable:判断当前linkPair里面的block是否可以被链接
 * return
 *  0，不可以；1，可以
 */
bool MainWindow::isLinkable() {
    if (linkPair[0] == nullptr || linkPair[1] == nullptr) return false;
    if (linkPair[0]->getType() != linkPair[1]->getType()) return false;

    int x1 = linkPair[0]->getX();
    int y1 = linkPair[0]->getY();
    int x2 = linkPair[1]->getX();
    int y2 = linkPair[1]->getY();

    if (isLinkable_zeroAngle(x1, y1, x2, y2, true, false) ||
    isLinkable_oneAngle(x1, y1, x2, y2) ||
    isLinkable_twoAngle(x1, y1, x2, y2)) return true;

    return false;
}

/*
 * isLinkable:判断当前坐标为(x1, y1)和(x2, y2)的block是否可以被链接
 * args
 *     x1, y1:第一个block的坐标
 *     x2, y2:第二个block的坐标
 * return
 *     0，不可以；1，可以
 */
bool MainWindow::isLinkable(int x1, int y1, int x2, int y2) {
    std::cout<<"isLinkable?"<<x1<<", "<<y1<<"; "<<x2<<", "<<y2<<std::endl;
    if (!blockMap[x1][y1] || !blockMap[x2][y2] || blockMap[x1][y1]->getType() != blockMap[x2][y2]->getType()) {
        std::cout<<"no!"<<std::endl;
        return false;
    }

    if (isLinkable_zeroAngle(x1, y1, x2, y2, true, false) ||
    isLinkable_oneAngle(x1, y1, x2, y2) ||
    isLinkable_twoAngle(x1, y1, x2, y2)) {
        std::cout<<"YEEES! type: "<<blockMap[x1][y1]->getType()<<","<<blockMap[x2][y2]->getType()<<std::endl;
        return true;
    }

    std::cout<<"no!"<<std::endl;
    return false;
}

/*
 * isLinkable_zeroAngle:判断当前坐标为(x1, y1)和(x2, y2)的block是否可以被直线链接
 * args
 *     x1, y1:第一个block的坐标
 *     x2, y2:第二个block的坐标
 *     isDirect: 是否直接修改linkPair
 *     examEndPoint: 是否检查结束点
 * return
 *     0，不可以；1，可以
 */
bool MainWindow::isLinkable_zeroAngle(int x1, int y1, int x2, int y2, bool isDirect, bool examEndPoint) {
    if (x1 != x2 && y1 != y2) return false;
    if (examEndPoint && x2 >= 0 && x2 < NUM_HORIZONTAL_BLOCKS && y2 >= 0
    && y2 <NUM_VERTICAL_BLOCKS && blockMap[x2][y2]) return false;

    if (x1 == x2) {
        if (x1 == -1 || x1 == NUM_HORIZONTAL_BLOCKS) return true;
        for (int i = std::min(y1, y2) + 1; i < std::max(y1, y2); i++){
            if (blockMap[x1][i]) return false;
        }
        if (!props.empty()) {
            for (Prop* prop : props) {
                if (prop->getX() == x1 && prop->getY() < std::max(y1, y2) && prop->getY() > std::min(y1, y2)) return false;
            }
        }
        if (isDirect) {
            linkPath.clear();
            linkPath.push_back(std::make_pair(x1, y1));
            linkPath.push_back(std::make_pair(x2, y2));
            std::cout<<"isLinkable_zeroAngle"<<std::endl;
            std::cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<std::endl;
        }
        return true;
    }

    if (y1 == y2) {
        if (y1 == -1 || y1 == NUM_VERTICAL_BLOCKS) return true;
        for (int i = std::min(x1, x2) + 1; i < std::max(x1, x2); i++){
            if (blockMap[i][y1]) return false;
        }
        if (!props.empty()) {
            for (Prop* prop : props) {
                if (prop->getY() == y1 && prop->getX() < std::max(x1, x2) && prop->getX() > std::min(x1, x2)) return false;
            }
        }
        if (isDirect) {
            linkPath.clear();
            linkPath.push_back(std::make_pair(x1, y1));
            linkPath.push_back(std::make_pair(x2, y2));
            std::cout<<"isLinkable_zeroAngle"<<std::endl;
            std::cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<std::endl;
        }
        return true;
    }

    return false;
}


/*
 * isLinkable_oneAngle:判断当前坐标为(x1, y1)和(x2, y2)的block是否可以被一个折角的直线链接
 * args
 *     x1, y1:第一个block的坐标
 *     x2, y2:第二个block的坐标
 * return
 *     0，不可以；1，可以
 */
bool MainWindow::isLinkable_oneAngle(int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) return false;

    if (isLinkable_zeroAngle(x1, y1, x2, y1, false, true) && isLinkable_zeroAngle(x2, y1, x2, y2, false, false)) {
        linkPath.clear();
        linkPath.push_back(std::make_pair(x1, y1));
        linkPath.push_back(std::make_pair(x2, y1));
        linkPath.push_back(std::make_pair(x2, y2));
        std::cout<<"isLinkable_oneAngle"<<std::endl;
        std::cout<<x1<<" "<<y1<<" "<<x2<<" "<<y1<<" "<<x2<<" "<<y2<<std::endl;
        return true;
    }

    if (isLinkable_zeroAngle(x1, y1, x1, y2, false, true) && isLinkable_zeroAngle(x1, y2, x2, y2, false, false)) {
        linkPath.clear();
        linkPath.push_back(std::make_pair(x1, y1));
        linkPath.push_back(std::make_pair(x1, y2));
        linkPath.push_back(std::make_pair(x2, y2));
        std::cout<<"isLinkable_oneAngle"<<std::endl;
        std::cout<<x1<<" "<<y1<<" "<<x1<<" "<<y2<<" "<<x2<<" "<<y2<<std::endl;
        return true;
    }

    return false;
}

/*
 * isLinkable_twoAngle:判断当前坐标为(x1, y1)和(x2, y2)的block是否可以被两个直角的折线链接
 * args
 *     x1, y1:第一个block的坐标
 *     x2, y2:第二个block的坐标
 * return
 *     0，不可以；1，可以
 */
bool MainWindow::isLinkable_twoAngle(int x1, int y1, int x2, int y2) {
    //借道x = -1
    for (int i = -1; i <= NUM_HORIZONTAL_BLOCKS; i++) {
        if (isLinkable_zeroAngle(x1, y1, i, y1, false, true) &&
        isLinkable_zeroAngle(i, y1, i, y2, false, true) &&
        isLinkable_zeroAngle(i, y2, x2, y2, false, false)) {
            linkPath.clear();
            linkPath.push_back(std::make_pair(x1, y1));
            linkPath.push_back(std::make_pair(i, y1));
            linkPath.push_back(std::make_pair(i, y2));
            linkPath.push_back(std::make_pair(x2, y2));
            std::cout<<"isLinkable_twoAngle"<<std::endl;
            std::cout<<x1<<" "<<y1<<" "<<i<<" "<<y1<<" "<<i<<" "<<y2<<" "<<x2<<" "<<y2<<std::endl;
            return true;
        }
    }

    for (int i = -1; i <= NUM_VERTICAL_BLOCKS; i++) {
        if (isLinkable_zeroAngle(x1, y1, x1, i, false, true) &&
        isLinkable_zeroAngle(x1, i, x2, i, false, true) &&
        isLinkable_zeroAngle(x2, i, x2, y2, false, false)) {
            linkPath.clear();
            linkPath.push_back(std::make_pair(x1, y1));
            linkPath.push_back(std::make_pair(x1, i));
            linkPath.push_back(std::make_pair(x2, i));
            linkPath.push_back(std::make_pair(x2, y2));
            std::cout<<"isLinkable_twoAngle"<<std::endl;
            std::cout<<x1<<" "<<y1<<" "<<x1<<" "<<i<<" "<<x2<<" "<<i<<" "<<x2<<" "<<y2<<std::endl;
            return true;
        }
    }

    return false;
}

/*
 * handleCountdownFinished:倒计时结束停止bgm
 */
void MainWindow::handleCountdownFinished()
{
    std::cout<<"SLOT: handleCountdownFinished"<<std::endl;
    bgm->stop();
}

/*
 * updateSeconds: 更新时间
 */
void MainWindow::updateSeconds()
{
    if (!isPaused) seconds++;
    if (seconds >= COUNTDOWN_TIME)
    {
        timer->stop();
        bgm->stop();
        blackMask();
        if (residue > 0) effect->loseGame();
        else effect->winGame();
        return;
    }
    update(); // 触发重绘事件，更新界面
}

/*
 * judger: 判断游戏是否结束/是否可解
 */
void MainWindow::judger() {
    if (residue == 0) {
        timer->stop();
        bgm->stop();
        blackMask();
        countDownClock->stopCountDown();
        effect->winGame();
        return;
    }

    if (residue == NUM_HORIZONTAL_BLOCKS * NUM_VERTICAL_BLOCKS - PROPS_TRIGGER_LIMIT) {
        createProps(this->scene);
    }

    if (!findLinkPair(false)) {
        timer->stop();
        bgm->stop();
        blackMask();
        effect->loseGame();
        return;
    }
}

/*
 * blackMask: 游戏结束黑色遮罩
 */
void MainWindow::blackMask() {
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();

    QGraphicsRectItem* blackMask = new QGraphicsRectItem(0, 0, screenWidth, screenHeight);
    blackMask->setBrush(QColor(0, 0, 0, 150)); // 设置为半透明黑色
    scene->addItem(blackMask);
}

/*
 * pauseGame: 暂停游戏
 */
void MainWindow::pauseGame() {
    if (seconds >= COUNTDOWN_TIME) return;
    if (isPaused) bgm->play();
    else bgm->stop();
    isPaused = !isPaused;
    countDownClock->toggleCountDown();
    pauseButton->toggleImage();
}

/*
 * createProps: 创建props
 */
void MainWindow::createProps(QGraphicsScene* scene) {
       std::srand(std::time(0)); // 使用时间作为随机数种子
       // 将空位置存入一个容器
       std::vector<std::pair<int, int>> emptyPositions;
       for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
           for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++) {
               if (blockMap[i][j] == nullptr) {
                   emptyPositions.emplace_back(i, j);
               }
           }
       }

       if (emptyPositions.size() < 4) {
           std::cout << "格子地图内部空位置数量不足！" << std::endl;
           return;
       }

       // 从内部空位置选择四个坐标
       std::vector<std::pair<int, int>> coordinates;
       for (int i = 0; i < 4; i++) {
           int index = std::rand() % emptyPositions.size();
           coordinates.push_back(emptyPositions[index]);
           emptyPositions.erase(emptyPositions.begin() + index);
       }

       for (int i = 0; i < NUM_PROP_TYPE; i++) {
           int x = coordinates[i].first;
           int y = coordinates[i].second;

           // 使用x和y进行操作或打印输出
           Prop *prop = new Prop(x, y, i);
//           blockMap[x][y] = new Block(x, y, 0);
           props.push_back(prop);
           scene->addItem(prop);
       }

//       std::cout<<"?"<<props.size()<<std::endl;
//       for (Prop* prop : props) {
//           std::cout << "Prop x: " << prop->getX() << ", y: " << prop->getY() << ", type: " << prop->getType() << std::endl;
//       }

}

/*
 * saveGame: 存档游戏
 */
void MainWindow::saveGame() {
    std::ofstream file(savePath); // 创建文件，并指定路径和文件名

    if (file.is_open()) // 检查文件是否成功打开
    {
        file.seekp(0, std::ios::beg); // 将写入位置设置为文件开头

        // 输出一系列信息到文件
//        file << 0 << " //单人模式"<< std::endl;
//        file << character->getX() << " " <<character->getY() << " //角色位置"<< std::endl;
//        file << seconds << " //时间" << std::endl;
//        file << residue << " //剩余方块个数" << std::endl;
//        file << isPaused << " //是否暂停" << std::endl;
        file << 0 << std::endl;
        file << character->getX() << " " <<character->getY() << std::endl;
        file << seconds << std::endl;
        file << residue << std::endl;
        file << isPaused << std::endl;

        file << "props:x y type" << std::endl;
        if (!props.empty()) {
            for (Prop* prop : props) {
                file << prop->getX() << " " << prop->getY() << " " << prop->getType() << std::endl;
            }
        }

        file << "blocks:x y type" << std::endl;
        if (residue > 0) {
            for (int i = 0; i < NUM_HORIZONTAL_BLOCKS; i++) {
                for (int j = 0; j < NUM_VERTICAL_BLOCKS; j++) {
                    if (blockMap[i][j])  file << blockMap[i][j]->getX() << " "  << blockMap[i][j]->getY() << " "  << blockMap[i][j]->getType() << std::endl;
                }
            }
        }

        file << "linkPair:x y" << std::endl;
        if (linkPair[0]) file << linkPair[0]->getX() << " "  << linkPair[0]->getY() << std::endl;
        if (linkPair[1]) file << linkPair[1]->getY() << " "  << linkPair[1]->getY() << std::endl;

        file.close(); // 关闭文件
        saveButton->toggleImage();
        isSaved = true;
    }
    else
    {
        // 文件打开失败，处理错误
    }
}

/*
 * loadGame: 载入游戏
 */
void MainWindow::loadGame() {
    std::ifstream file(savePath); // 打开文件，并指定路径和文件名

    if (!file) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    int mode;
    file >> mode;
    std::cout << "mode: " << mode << std::endl;
    if (mode != 0) {
        std::cout << "MODE DOESN'T MATCH" << mode << std::endl;
        file.close();
        return;
    }

    createMapBound();

    int x, y;
    file >> x >> y;
    std::cout << "x y: " << x << " " << y << std::endl;
    character = new Character(nullptr, x, y, CHARACTER1_TYPE);
    scene->addItem(character);

    file >> this->seconds;
    std::cout << "seconds: " << this->seconds << std::endl;
    file >> this->residue;
    std::cout << "residue: " << this->residue << std::endl;
    file >> this->isPaused;
    std::cout << "isPaused: " << this->isPaused << std::endl;

    std::string line;
    std::getline(file, line);
    std::cout << "SKIPLINE: " << line << std::endl;
    while (std::getline(file, line)) {
        std::cout << "props: " << line << std::endl;
                std::istringstream iss(line);
                int type;
                if (iss >> x >> y >> type) {
                    // 在这里使用 x 和 y 进行相应的操作
                    std::cout << "x: " << x << ", y: " << y << ", type: " << type << std::endl;
                    Prop *prop = new Prop(x, y, type);
                    props.push_back(prop);
                    scene->addItem(prop);
                } else {
                    // 处理无效的输入行
                    std::cout << "无效的输入行: " << line << std::endl;
                    break;
                }
            }

    std::getline(file, line);
    std::cout << "SKIPLINE: " << line << std::endl;
    blockMap.resize(NUM_HORIZONTAL_BLOCKS, std::vector<Block*>(NUM_VERTICAL_BLOCKS, nullptr));

    while (std::getline(file, line)) {
        std::cout << "blocks: " << line << std::endl;
                std::istringstream iss(line);
                int type;
                if (iss >> x >> y >> type) {
                    // 在这里使用 x 和 y 进行相应的操作
                    std::cout << "x: " << x << ", y: " << y << ", type: " << type << std::endl;
                    blockMap[x][y] = new Block(x, y, type);
                    scene->addItem(blockMap[x][y]);
                } else {
                    // 处理无效的输入行
                    std::cout << "无效的输入行: " << line << std::endl;
                    break;
                }
            }

    nearBlocks(character->getX(), character->getY());

    linkPair[0] = nullptr;
    linkPair[1] = nullptr;
//    std::getline(file, line);
//    std::cout << "SKIPLINE: " << line << std::endl;
    std::getline(file, line);
    std::cout << "linkpair: " << line << std::endl;
    if (!line.empty()) {
        std::istringstream iss(line);
        iss >> x >> y;
        std::cout << "x: " << x << ", y: " << y << std::endl;
        linkPair[0] = blockMap[x][y];
        linkPair[0]->select();
    }
    std::getline(file, line);
    if (!line.empty()) {
        std::istringstream iss(line);
        iss >> x >> y;
        std::cout << "x: " << x << ", y: " << y << std::endl;
        linkPair[1] = blockMap[x][y];
        linkPair[1]->select();
    }

    isSaved = true;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSeconds);
    timer->start(1000); // 每隔1秒触发一次计时器

    pauseButton = new Button(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, 0, this);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pauseGame);

    saveButton = new Button(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 200, 1, this);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveGame);
    saveButton->toggleImage();

    countDownClock = new CountDownClock(this);
    connect(countDownClock, SIGNAL(countdownFinished()), this, SLOT(this->handleCountdownFinished()));
    countDownClock->setTime(seconds);

    scoreboard = new ScoreBoard();
    scoreboard->setScore(NUM_HORIZONTAL_BLOCKS * NUM_VERTICAL_BLOCKS - residue);
    scene->addItem(scoreboard);

    if (isPaused == 1) pauseGame();
}

/*
 * createMapBound: 创建地图边界
 */
void MainWindow::createMapBound() {
    int y_top = Y_OFFSET - BLOCK_INTERVAL;
    int y_bottom = Y_OFFSET + NUM_VERTICAL_BLOCKS * BLOCK_INTERVAL;
    int x_top = X_OFFSET - BLOCK_INTERVAL;
    int x_bottom = X_OFFSET + NUM_HORIZONTAL_BLOCKS * BLOCK_INTERVAL;
    for (int i = -1; i <= NUM_HORIZONTAL_BLOCKS; i++) {
        QGraphicsRectItem* rectItem1 = new QGraphicsRectItem(X_OFFSET + i * BLOCK_INTERVAL, y_top, BLOCK_SIZE, BLOCK_SIZE);
        QGraphicsRectItem* rectItem2 = new QGraphicsRectItem(X_OFFSET + i * BLOCK_INTERVAL, y_bottom, BLOCK_SIZE, BLOCK_SIZE);
        QBrush brush(QColor(255, 255, 255, 128));  // 设置白色的半透明颜色
        rectItem1->setBrush(brush);
        rectItem2->setBrush(brush);

        scene->addItem(rectItem1);
        scene->addItem(rectItem2);
    }

    for (int i = 0; i < NUM_VERTICAL_BLOCKS; i++) {
        QGraphicsRectItem* rectItem1 = new QGraphicsRectItem(x_top, Y_OFFSET + i * BLOCK_INTERVAL, BLOCK_SIZE, BLOCK_SIZE);
        QGraphicsRectItem* rectItem2 = new QGraphicsRectItem(x_bottom, Y_OFFSET + i * BLOCK_INTERVAL, BLOCK_SIZE, BLOCK_SIZE);
        QBrush brush(QColor(255, 255, 255, 128));  // 设置白色的半透明颜色
        rectItem1->setBrush(brush);
        rectItem2->setBrush(brush);

        scene->addItem(rectItem1);
        scene->addItem(rectItem2);
    }


}
