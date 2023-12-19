#include "Block.h"
/*
 * Block: 初始化block
 * args
 *     x: 横坐标
 *     y: 纵坐标
 *     type: 类型
 *     isMultiPlayer: 是否为双人模式，区别在于显示坐标不同
 *
 * return
 *     symbol_t: the 'name' symbol
 *     NULL: not exist
 */

/*
 * Block: 初始化block
 * args
 *     x: 横坐标
 *     y: 纵坐标
 *     type: 类型
 *     isMultiPlayer: 是否为双人模式，区别在于显示坐标不同
 */
Block::Block(int x, int y, int type, bool isMultiPlayer) : QGraphicsPixmapItem(), x(x), y(y), type(type), state(State::normal), proxyWidget(nullptr), isMultiPlayer(isMultiPlayer) {
    // 设置显示的图片
    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);

    // 设置显示的位置
    if (!isMultiPlayer) setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
    else setPos(X_OFFSET_MULTI + x * BLOCK_INTERVAL, Y_OFFSET_MULTI + y * BLOCK_INTERVAL);
}

/*
 * reset: 恢复为normal状态
 */
void Block::reset() {
    if (this->state == State::selected) return;

    //恢复显示初始图片
    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);

    // 恢复state为正常状态
    this->state = State::normal;
}

/*
 * resetFromSelect: 从select状态恢复为normal状态
 */
void Block::resetFromSelect() {
    if (state != State::selected) return;
    //取消动态图片
    delete proxyWidget;
    proxyWidget = nullptr;

    // Reset the state and set the pixmap
    this->state = State::normal;
    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);
    setPixmap(pixmap);
}


/*
 * near：靠近方块
 */
void Block::near() {
    if (this->state == State::selected) return;

    // 显示靠近状态下的图片
    QPixmap pixmap(images_near[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);
    this->state = State::near;
}

/*
 * select：选中方块
 */
bool Block::select() {
    if (this->state != State::near) return false;
    QString gifPath = images_select[type]; // 替换为你的GIF动图路径
    QMovie* movie = new QMovie(gifPath);
    movie->setCacheMode(QMovie::CacheAll);
    movie->setScaledSize(QSize(BLOCK_SIZE, BLOCK_SIZE));

    QLabel* label = new QLabel();
    label->setMovie(movie);

    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(label);

    movie->start();

    this->state = State::selected;

    std::cout<<x<<", "<<y<<":"<<"select"<<std::endl;
    return true;
}

/*
 * selectByHint：由Hint道具选中方块
 */
void Block::selectByHint() {
    this->state = State::near;
    select();
}

/*
 * link：显示link特效
 */
void Block::link() {
    if (this->state != State::selected) return;

    QString gifPath = ":/Effect/image/effect/explode.gif"; // GIF动图路径
    QMovie* movie = new QMovie(gifPath);
    movie->setCacheMode(QMovie::CacheAll);
    movie->setScaledSize(QSize(EXPLODE_EFFECT_SIZE, EXPLODE_EFFECT_SIZE));

    // 背景为透明
    QLabel* label = new QLabel();
    label->setMovie(movie);
    label->setStyleSheet("background-color: transparent;");

    // 显示动图
    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(label);
    proxyWidget->setPos(proxyWidget->pos().x() + EXPLODE_OFFSET, proxyWidget->pos().y() + EXPLODE_OFFSET);

    movie->start();
}

/*
 * setNewPos：设置新的坐标
 * args
 *     x: 新的横坐标
 *     y: 新的纵坐标
 */
void Block::setNewPos(int x, int y) {
    this->x = x;
    this->y = y;
    if (!isMultiPlayer) setPos(X_OFFSET + x * BLOCK_INTERVAL, Y_OFFSET + y * BLOCK_INTERVAL);
    else setPos(X_OFFSET_MULTI + x * BLOCK_INTERVAL, Y_OFFSET_MULTI + y * BLOCK_INTERVAL);
}

int Block::getType() {
    return this->type;
}

int Block::getX() {
    return this->x;
}

int Block::getY() {
    return this->y;
}

void Block::setType(int type) {
    this->type = type;
    QPixmap pixmap(images[type]);
    pixmap = pixmap.scaled(BLOCK_SIZE, BLOCK_SIZE);

    setPixmap(pixmap);
}
