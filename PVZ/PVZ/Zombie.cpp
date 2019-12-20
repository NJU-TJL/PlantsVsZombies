#include "Zombie.h"
#include "Map.h"
#include "Game.h"

#include<iostream>
using namespace std;

void Zombie::printName()
{
	if (freezing)
		PrintWithColor(name, FREEZING_COLOR);
	else
		PrintWithColor(name);
}

bool Zombie::move(Map & map)
{
	//冷冻效果计时
	if (freezing) {
		freezing_counter++;
		if (freezing_counter >= freezing_time) {
			freezing = false;
		}
	}

	//移动计时
	if (!eating) {
		if (freezing) //移动速度减半
			counter += 5;
		else
			counter += 10;
		if (counter >= 10*speed) {
			map.grid[x][y].delZombie(this);
			x--;
			if (x < 0) //僵尸攻破
				return true;
			map.grid[x][y].addZombie(this);
			counter = 0;
		}
	}
	else {
		//吃植物（停止移动）
		if (freezing) //攻击速度减半
			map.grid[x][y].eatPlant(attack / 2);
		else
			map.grid[x][y].eatPlant(attack);
		
	}

	//大蒜效果计时
	if (scape_flag) {
		scape_counter++;
		if (scape_counter >= scape_time) {
			scape_flag = false;
			map.grid[x][y].delZombie(this);
			if (y == 0) y++;
			else if (y == GRID_NUM_Y - 1) y--;
			else {
				y = RANDOM(2) ? y - 1 : y + 1; //随机移动到相邻行
			}
			map.grid[x][y].addZombie(this);
		}
	}
	return false;
}

void Door_Zombie::setFreezing()
{
	if (HP <= transHP) {
		freezing = true; freezing_counter = 0;
	}
}

void Door_Zombie::printExtra()
{
	if (HP <= transHP) {
		cout << "(无铁门)";
	}else{
		cout << "(有铁门)";
	}
}

void Newspaper_Zombie::setFreezing()
{
	if (HP <= transHP) {
		freezing = true; freezing_counter = 0;
	}
}

void Newspaper_Zombie::printExtra()
{
	if (HP <= transHP) {
		cout << "(无报纸)";
	}
	else {
		cout << "(有报纸)";
	}
}

void Newspaper_Zombie::hit(int iattack)
{
	HP -= iattack;
	if (HP <= transHP) {
		speed = speed_Plus;
		attack = attack_Plus;
	}
}

void Newspaper_Zombie::printName()
{
	if (freezing)
		PrintWithColor(name, FREEZING_COLOR);
	else if (HP <= transHP)
		PrintWithColor(name, RED_EYE_COLOR);
	else
		PrintWithColor(name);
}

void Pole_Zombie::printExtra()
{
	if (hasPole) {
		cout << "(有撑杆)";
	}
	else {
		cout << "(无撑杆)";
	}
}

bool Pole_Zombie::move(Map & map)
{
	//有撑杆、此处有植物、植物可越过：则越过一格
	if (hasPole && eating && map.grid[x][y].plant->skipable) {
		map.grid[x][y].delZombie(this);
		x--;
		if (x < 0) //僵尸攻破
			return true;
		map.grid[x][y].addZombie(this);
		//到了左侧新格子，清空状态
		hasPole = false; eating = false;
		counter = 0; scape_flag = 0; 
		speed = speed2;//设置速度为跳完之后的速度
		return false;

	}
	else { //否则，调用普通僵尸（父类）的行进逻辑即可
		return Zombie::move(map);
	}
}

void Dancing_Zombie::go(Game & nowGame)
{

	if (!hasCalled) {
		call_counter++;
		if (call_counter >= call_time) {
			hasCalled = true;
			speed = speed2; counter = 0;
			nowGame.map.setBombFlag(x, y);
			//内部会有越界检查，所以这里不用检查x、y是否越界
			nowGame.map.setBombFlag(x - 1, y);
			nowGame.map.setBombFlag(x + 1, y);
			nowGame.map.setBombFlag(x, y - 1);
			nowGame.map.setBombFlag(x, y + 1);
			nowGame.addZombie(x - 1, y, BACKUP_DANCER);
			nowGame.addZombie(x + 1, y, BACKUP_DANCER);
			nowGame.addZombie(x, y - 1, BACKUP_DANCER);
			nowGame.addZombie(x, y + 1, BACKUP_DANCER);
		}
	}
	else {
		if (call_counter >= call_time) {
			//关闭闪烁
			nowGame.map.clearBombFlag(x, y);
			nowGame.map.clearBombFlag(x - 1, y);
			nowGame.map.clearBombFlag(x + 1, y);
			nowGame.map.clearBombFlag(x, y - 1);
			nowGame.map.clearBombFlag(x, y + 1);
			call_counter = 0;
		}
	}
}

void Box_Zombie::go(Game & nowGame)
{
	if (!bomb_flag) {
		bomb_counter++;
		if (bomb_counter >= bomb_time) {
			int coin = RANDOM(3);
			if (coin) { //自爆
				bomb_flag = true; counter = 0;
				nowGame.map.setBombFlag(x, y);
				//内部会有越界检查，所以这里不用检查x、y是否越界
				nowGame.map.setBombFlag(x - 1, y - 1);
				nowGame.map.setBombFlag(x - 1, y);
				nowGame.map.setBombFlag(x - 1, y + 1);
				nowGame.map.setBombFlag(x, y - 1);
				nowGame.map.setBombFlag(x, y);
				nowGame.map.setBombFlag(x, y + 1);
				nowGame.map.setBombFlag(x + 1, y - 1);
				nowGame.map.setBombFlag(x + 1, y);
				nowGame.map.setBombFlag(x + 1, y + 1);
			}
			else { //不自爆
				bomb_counter = 0;
			}
		}
	}
	else {
		HP = -1; //自己也死亡
		nowGame.map.clearBombFlag(x, y);
		//内部会有越界检查，所以这里不用检查x、y是否越界
		nowGame.map.clearBombFlag(x - 1, y - 1);
		nowGame.map.clearBombFlag(x - 1, y);
		nowGame.map.clearBombFlag(x - 1, y + 1);
		nowGame.map.clearBombFlag(x, y - 1);
		nowGame.map.clearBombFlag(x, y);
		nowGame.map.clearBombFlag(x, y + 1);
		nowGame.map.clearBombFlag(x + 1, y - 1);
		nowGame.map.clearBombFlag(x + 1, y);
		nowGame.map.clearBombFlag(x + 1, y + 1);
		nowGame.delPlant(x - 1, y - 1);
		nowGame.delPlant(x - 1, y);
		nowGame.delPlant(x - 1, y + 1);
		nowGame.delPlant(x, y - 1);
		nowGame.delPlant(x, y);
		nowGame.delPlant(x, y + 1);
		nowGame.delPlant(x + 1, y - 1);
		nowGame.delPlant(x + 1, y);
		nowGame.delPlant(x + 1, y + 1);
	}
}
