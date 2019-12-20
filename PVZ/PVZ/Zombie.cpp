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
	//�䶳Ч����ʱ
	if (freezing) {
		freezing_counter++;
		if (freezing_counter >= freezing_time) {
			freezing = false;
		}
	}

	//�ƶ���ʱ
	if (!eating) {
		if (freezing) //�ƶ��ٶȼ���
			counter += 5;
		else
			counter += 10;
		if (counter >= 10*speed) {
			map.grid[x][y].delZombie(this);
			x--;
			if (x < 0) //��ʬ����
				return true;
			map.grid[x][y].addZombie(this);
			counter = 0;
		}
	}
	else {
		//��ֲ�ֹͣ�ƶ���
		if (freezing) //�����ٶȼ���
			map.grid[x][y].eatPlant(attack / 2);
		else
			map.grid[x][y].eatPlant(attack);
		
	}

	//����Ч����ʱ
	if (scape_flag) {
		scape_counter++;
		if (scape_counter >= scape_time) {
			scape_flag = false;
			map.grid[x][y].delZombie(this);
			if (y == 0) y++;
			else if (y == GRID_NUM_Y - 1) y--;
			else {
				y = RANDOM(2) ? y - 1 : y + 1; //����ƶ���������
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
		cout << "(������)";
	}else{
		cout << "(������)";
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
		cout << "(�ޱ�ֽ)";
	}
	else {
		cout << "(�б�ֽ)";
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
		cout << "(�гŸ�)";
	}
	else {
		cout << "(�޳Ÿ�)";
	}
}

bool Pole_Zombie::move(Map & map)
{
	//�гŸˡ��˴���ֲ�ֲ���Խ������Խ��һ��
	if (hasPole && eating && map.grid[x][y].plant->skipable) {
		map.grid[x][y].delZombie(this);
		x--;
		if (x < 0) //��ʬ����
			return true;
		map.grid[x][y].addZombie(this);
		//��������¸��ӣ����״̬
		hasPole = false; eating = false;
		counter = 0; scape_flag = 0; 
		speed = speed2;//�����ٶ�Ϊ����֮����ٶ�
		return false;

	}
	else { //���򣬵�����ͨ��ʬ�����ࣩ���н��߼�����
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
			//�ڲ�����Խ���飬�������ﲻ�ü��x��y�Ƿ�Խ��
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
			//�ر���˸
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
			if (coin) { //�Ա�
				bomb_flag = true; counter = 0;
				nowGame.map.setBombFlag(x, y);
				//�ڲ�����Խ���飬�������ﲻ�ü��x��y�Ƿ�Խ��
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
			else { //���Ա�
				bomb_counter = 0;
			}
		}
	}
	else {
		HP = -1; //�Լ�Ҳ����
		nowGame.map.clearBombFlag(x, y);
		//�ڲ�����Խ���飬�������ﲻ�ü��x��y�Ƿ�Խ��
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
