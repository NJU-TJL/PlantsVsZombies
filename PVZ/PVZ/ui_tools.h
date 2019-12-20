#pragma once
#include<cstdlib>
#include<Windows.h>
#include<string>
using namespace std;

/* UI设计 - 尺寸信息 */
const int GRID_WIDTH = 11; //草坪中每个格子的宽度（字符数）
const int GRID_HEIGHT = 5; //草坪中每个格子的高度（字符数）
const int GRID_NUM_X = 7;  //草坪尺寸为：GRID_NUM_X列 
const int GRID_NUM_Y = 5;  //            GRID_NUM_Y行
//商店UI界面的高度（宽度同窗口宽度）
const int STORE_HEIGHT = 7;
//窗口-宽
const int WINDOWS_WIDTH = (GRID_WIDTH + 1)*GRID_NUM_X + GRID_WIDTH * 3 / 2;
//窗口-高
const int WINDOWS_HEIGHT = (GRID_HEIGHT + 1)*GRID_NUM_Y + STORE_HEIGHT + 2;
//商店窗口的上边界 - y的值
const int STORE_UP_BOUND = (GRID_HEIGHT + 1)*GRID_NUM_Y + 1;
//商店窗口中植物展示信息的宽度
const int PLANT_CARD_WIDTH = 24;
//“阳光 | 得分”中'|'的位置
const int RIGHT_LINE_X = WINDOWS_WIDTH - 20;
//帮助信息的所在位置
const int HELP_INFO_Y = WINDOWS_HEIGHT - 1;

/* UI设计 - 颜色信息 */
//默认色 - 黑底亮白字
const int DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//购买时，选中
const int SELECTED_COLOR = BACKGROUND_GREEN | BACKGROUND_BLUE | DEFAULT_COLOR;
//普通豌豆颜色
const int BULLET_COLOR = FOREGROUND_GREEN;
//寒冰豌豆颜色
const int SNOWBULLET_COLOR = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//僵尸冷冻效果时的名字输出
const int FREEZING_COLOR = SNOWBULLET_COLOR;
//爆炸特效的颜色
const int BOOM_COLOR = FOREGROUND_RED | FOREGROUND_INTENSITY;
//报纸僵尸没报纸后的红眼状态颜色
const int RED_EYE_COLOR = FOREGROUND_RED | FOREGROUND_INTENSITY;
//帮助信息的颜色(白底黑字)
const int HELP_COLOR = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//游戏状态
const int STATE_COLOR = BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//植物名字
const int PLANT_ATTACK_COLOR = BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int PLANT_STATIC_COLOR = BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int PLANT_BOMB_COLOR =  BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;


/* 全局性功能函数声明 */
// 设置光标位置
void Goto_XY(const int x, const int y);
// 隐藏光标
void HideCursor();
// 产生0~n-1的随机数
inline int RANDOM(int n) { return rand() % n; }
// 设置窗口大小
void SetWindowSize(int cols, int lines);
// 设置文本颜色
void SetColor(int colorID);
// 带颜色的文本输出，默认为黑底白字
void PrintWithColor(const string& str, int colorID = DEFAULT_COLOR);
void PrintWithColor(int num, int colorID = DEFAULT_COLOR);



/* 一些全局常量 */
//时钟周期（毫秒）
const int SLEEP_TIME = 100;
//植物种类数
const int PLANT_TYPE_MAX = 12;
enum PlantType { SUNFLOWER, PEASHOOTER, SQUASH, CHERRYBOMB, WALLNUT, SNOWPEA, REPEATER, GARLIC, JALAPENO, POTATOMINE, SPIKEWEED, TALLNUT };
//僵尸种类数
const int ZOMBIE_TYPE_MAX = 11;
enum ZombieType { 
	ZOMBIE, CONEHEAD_ZOMBIE, BUCKET_ZOMBIE, FOOTBALL_ZOMBIE, DOOR_ZOMBIE, NEWSPAPER_ZOMBIE, POLE_ZOMBIE, DANCING_ZOMBIE, BOX_ZOMBIE, FLAG_ZOMBIE, BACKUP_DANCER
};