#pragma once

#include<string>
using namespace std;

#include"ui_tools.h"

class Map;
class Game;

//普通僵尸
class Zombie
{
protected:
	//所在网格
	int x, y;
	//僵尸名
	string name;
	//移动速度
	int speed;
	//血量
	int HP; //当前
	int maxHP;
	//攻击力
	int attack;
	//击杀得分
	int score;

	//属性参数设定
	void set(const string& str, int iscore=50, int ilife = 200, int ispeed = 45, int iattack = 100) { 
		//名字、击杀得分、HP
		name = str; score = iscore; maxHP = HP = ilife; 
		//速度：（ispeed/10）秒/格
		speed = ispeed * 1000 / 10 / SLEEP_TIME; 
		//攻击力：（iattack) 点伤害/秒
		attack = iattack * SLEEP_TIME / 1000; 
	}
	
	//用于移动的计数
	int counter;
	//标记处于吃植物的状态
	bool eating;

	//冰减速效果：移动/攻击速度减半
	bool freezing;
	//减速效果持续时间
	int freezing_time;
	//时间计数
	int freezing_counter;

	//遇到大蒜
	bool scape_flag;
	//多少秒后移动到其他行
	int scape_time;
	//时间计数
	int scape_counter;

	//输出僵尸名字（如：冰冻状态名字会变色）
	virtual void printName();
	//额外信息输出（有无铁门/报纸等信息）
	virtual void printExtra() {}

public:
	Zombie() { 
		counter = 0; eating = false; set("普通僵尸",50); 
		//减速效果参数初始化
		freezing = false; freezing_counter = 0;
		freezing_time = 8 * 1000 / SLEEP_TIME; //8秒
		//大蒜效果参数初始化
		scape_flag = false; scape_counter = 0;
		scape_time = 8 * 1000 / 10 / SLEEP_TIME;//0.8秒
	}
	//返回僵尸名字
	const string& getName() const { return name; }

	//设定起始位置
	void setXY(int ix, int iy) { x = ix; y = iy; }
	//僵尸行动（包括位移、吃植物等动作），返回值代表是否攻破
	virtual bool move(Map& map);
	//僵尸特殊效果（默认无）
	virtual void go(Game &nowGame) {}
	//被攻击
	virtual void hit(int attack) { HP -= attack; }
	//开启被减速的效果（铁门僵尸等可防御）
	virtual void setFreezing() { freezing = true; freezing_counter = 0; };
	//开启大蒜效果（准备随机切到相邻的行）
	void setScape() { 
		if (!scape_flag) {
			scape_flag = true; scape_counter = 0;;
		}
	};

	friend class Game;
	friend class Bullet;
	friend class SnowBullet;
	friend class Grid;
};

/* 各类特殊的僵尸 */

class Flag_Zombie :public Zombie {
public:
	Flag_Zombie() { set("摇旗僵尸", 50, 200, 30, 110); }
};

class Conehead_Zombie :public Zombie {
public:
	Conehead_Zombie() { set("路障僵尸", 75, 570, 45,120); }
};

class Bucket_Zombie :public Zombie {
public:
	Bucket_Zombie() { set("铁桶僵尸", 125, 1300, 45,120); }
};

class Football_Zombie :public Zombie {
public:
	Football_Zombie() { set("橄榄球僵尸", 175, 1600, 25, 120); }
};

class Door_Zombie :public Zombie {
	//临界点
	int transHP;
public:
	Door_Zombie() { set("铁门僵尸", 125, 1300, 45, 120); transHP = 500; }
	void setFreezing();
	void printExtra();
};

class Newspaper_Zombie :public Zombie {
	//临界点
	int transHP;
	//报纸没了后的速度 1.2秒/格
	int speed_Plus = 12 * 1000 / 10 / SLEEP_TIME;
	//报纸没了后的攻击力
	int attack_Plus = 200;
public:
	Newspaper_Zombie() { set("读报僵尸", 125, 300); transHP = 200; }
	void setFreezing();
	void printExtra();
	//重写扣血函数（报纸没了要加速）
	void hit(int attack);
	//没报纸了就红名显示（红眼状态）
	void printName();
};

class Pole_Zombie :public Zombie {
	//临界点：是否有撑杆
	bool hasPole;
	//跳完之后的速度 4.5秒/格
	int speed2 = 45 * 1000 / 10 / SLEEP_TIME;
public:
	Pole_Zombie() { set("撑杆僵尸", 100, 430, 20); hasPole = true; }
	void printExtra();
	bool move(Map& map);
};

class Dancing_Zombie :public Zombie {
	//一定时间后触发召唤
	int call_time;
	//自爆时间计数
	int call_counter;
	//临界点：是否已触发召唤
	bool hasCalled;
	//召唤之后的速度 5.5秒/格
	int speed2 = 55 * 1000 / 10 / SLEEP_TIME;
public:
	Dancing_Zombie() { 
		set("舞王僵尸", 350, 500, 12); 
		hasCalled = false; 
		call_time = 40 * 1000 / 10 / SLEEP_TIME;
		call_counter = 0;
	}
	void go(Game &nowGame);
};

class Backup_Dancer :public Zombie {
public:
	Backup_Dancer() { set("伴舞僵尸", 50, 200, 55); }
};

class Box_Zombie :public Zombie {
	//一定时间后触发概率自爆
	int bomb_time;
	//自爆时间计数
	int bomb_counter;
	//是否启动爆炸
	bool bomb_flag;
public:
	Box_Zombie() {
		set("小丑僵尸", 250, 800, 12); 
		bomb_time = 30 * 1000 / 10 / SLEEP_TIME;
		bomb_counter = 0;
		bomb_flag = false;
	}
	void go(Game &nowGame);
};
