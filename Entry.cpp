#include "Entry.h"

Entry::Entry(QWidget *parent) : QWidget(parent) {
    setWindowTitle("连连看");

    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    resize(screenWidth, screenHeight);

    int x = (screenWidth - BUTTON_WIDTH) / 2;

    Button *singlePlayer = new Button(x, ENTRY_BUTTON_Y_OFFEST, 2, this);
    Button *twoPlayer = new Button(x, ENTRY_BUTTON_Y_OFFEST + ENTRY_BUTTON_GAP, 3, this);
    Button *loadGame = new Button(x, ENTRY_BUTTON_Y_OFFEST + 2 *ENTRY_BUTTON_GAP, 4, this);
    Button *exitGame = new Button(x, ENTRY_BUTTON_Y_OFFEST + 3 *ENTRY_BUTTON_GAP, 5, this);
    connect(singlePlayer, &QPushButton::clicked, this, &Entry::singlePlayerMode);
    connect(twoPlayer, &QPushButton::clicked, this, &Entry::twoPlayerMode);
    connect(loadGame, &QPushButton::clicked, this, &Entry::loadGameMode);
    connect(exitGame, &QPushButton::clicked, this, &Entry::exit);

    initializeComponents();

    bgm = new QSoundEffect(this);
    bgm->setLoopCount(QSoundEffect::Infinite); // 设置为无限循环
    bgm->setSource(QUrl::fromLocalFile(":/Sound/sounds/entry.wav"));
    bgm->play();
}

void Entry::initializeComponents() {
    // 设置背景图片
    QPixmap backgroundImage(":/Entry/image/entry.jpg");

    // 调整背景图片的缩放模式为按比例缩放，并且保持纵横比例不变
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
    this->setPalette(palette);
}

void Entry::singlePlayerMode() {
    bgm->stop();
    MainWindow *m = new MainWindow();
    m->show();
    this->hide();
}

void Entry::twoPlayerMode() {
    bgm->stop();
    MainWindow_m *m = new MainWindow_m();
    m->show();
    this->hide();
}

void Entry::loadGameMode() {
    bgm->stop();
    MainWindow_m *m = new MainWindow_m();
    m->show();
    this->hide();
}

void Entry::exit() {
    bgm->stop();
    this->hide();
}

