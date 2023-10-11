#include "Config.h"

const int BLOCK_SIZE = 60;
const int BLOCK_INTERVAL = 70;
const int NUM_BLOCK_TYPE = 10;

const int EXPLODE_EFFECT_SIZE = 100;
const int EXPLODE_OFFSET = -25;

const int X_OFFSET_MULTI = 900;
const int Y_OFFSET_MULTI = 400;

const int X_OFFSET = 1150;
const int Y_OFFSET = 400;


const int NUM_HORIZONTAL_BLOCKS = 12;
const int NUM_VERTICAL_BLOCKS = 10;

//const int X_OFFSET = 1220;
//const int Y_OFFSET = 470;

//const int NUM_HORIZONTAL_BLOCKS = 10;
//const int NUM_VERTICAL_BLOCKS = 2;

const int COUNTDOWN_TIME = 180;
const int CLOCK_EXRADIUS = 100;
const int ANNULUS_THICKNESS = 20;
//const int CLOCK_X_OFFSET = 680;
const int CLOCK_X_OFFSET = 250;
//const int CLOCK_Y_OFFSET = 550;
const int CLOCK_Y_OFFSET = 300;
const int CLOCK_SIZE = 300;

const int BUTTON_SIZE = 200;
const int BUTTON_WIDTH = 600;
const int BUTTON_HEIGHT = 150;
const int BUTTON_X_OFFSET = 300;
const int BUTTON_Y_OFFSET = 600;

const int ENDGAME_LOGO_SIZE = 800;

const int PROPS_TRIGGER_LIMIT = 6;//道具触发条件：消除了n个方块
//const int NUM_PROP_TYPE = 4;
const int NUM_PROP_TYPE = 3;
const int ADD_TIME = 30;
const int CHARACTER1_TYPE = 0;
const int CHARACTER2_TYPE = 1;

const int ENTRY_BUTTON_GAP = 130;
const int ENTRY_BUTTON_Y_OFFEST = 700;

const QString characterImages[2]= {
    ":/Character/image/character/whiteDog.PNG",
    ":/Character/image/character/brownDog.PNG",
};

const std::string savePath = "C:/coding/SEP-QT/LinkGame.txt";
