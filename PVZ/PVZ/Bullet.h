#pragma once

#include "Zombie.h"
#include<vector>

class Map;
class Bullet
{
protected:
	//子弹当前的位置
	int x, y;
	//移动速度（speed个时钟周期移动一个字符格子）
	int speed;
	//攻击力（每次击中僵尸，扣除的血量）
	int attack;

	//用于移动的计数
	int counter;

public:
	Bullet();
	//计算并设置子弹的起始坐标（(dx,dy)位置的植物发射子弹）
	void setXY(int dx, int dy);
	//向前移动
	void move(Map &map);
	//绘制子弹
	virtual void paint();
	//攻击僵尸
	virtual void hitZombie(vector<Zombie*> &zombie);
	//是否击中
	bool hit;
};

//寒冰射手的子弹
class SnowBullet :public Bullet {
	void hitZombie(vector<Zombie*> &zombie);
	void paint();
};