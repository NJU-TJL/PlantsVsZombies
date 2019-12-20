#pragma once
#include "Map.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Store.h"

#include<list>
using namespace std;

class Plant;

class Game {
	Map map;
	Store store;

	//子弹队列（豌豆射手等发出的）
	list<Bullet*> bullets;
	//僵尸队列
	list<Zombie*> zombies;

	//当前动作状态，可选择的值包括在下面的枚举类型中
	int state;
	//状态：正常、购买状态、铲除植物、游戏暂停
	enum GAME_STATE { NORMAL, STORE, SHOVEL, PAUSE };
	//选择铲除植物中
	void weeding();
	//选择购买植物中
	void shopping();

	//当前焦点位置
	int x, y; 
	//当前准备种植的植物类型
	int planting_type;
	//开启选择焦点
	void openFocus();
	//关闭选择焦点
	void closeFocus();
	
	//铲除某个位置的植物
	void delPlant(int ix, int iy);
	//子弹移动
	void moveBullet();
	//子弹的显示输出
	void printBullet();
	//指定位置增加某个类型的僵尸
	void addZombie(int x, int y, int type);
	//僵尸产生速度
	int make_speed;
	int make_counter;
	//僵尸产生逻辑
	void makeZombies();
	//僵尸移动
	bool moveZombie();
	//清除无效僵尸（血量<=0）
	void clearZombie();

	//得分
	int score;
	//刷新得分显示
	void refreshScore();
	//分数增长速度
	int score_speed;
	int score_counter;
	//计分
	void calScore();

	//帮助信息的输出
	void helpInfo();
	//指示是否需要更新帮助信息（状态切换后需要）
	bool refreshHelpInfo;

	//暂停
	void pause();
	//游戏结束
	void gameover();

public:
	Game();

	//游戏参数初始化
	void init();
	//游戏主循环
	void loop();

	//子弹队列中增加一个子弹
	void addBullet(Bullet* p);
	
	~Game();


	friend class SunFlower;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class PotatoMine;
	friend class CherryBomb;
	friend class Jalapeno;
	friend class Garlic;
	friend class Spikeweed;
	friend class Dancing_Zombie;
	friend class Box_Zombie;
};

