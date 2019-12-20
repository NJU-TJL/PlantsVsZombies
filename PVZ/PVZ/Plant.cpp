#include "Plant.h"
#include "Game.h"
#include<iostream>
using namespace std;

void PeaShooter::go(Game & nowGame)
{
	/*���ж��Ҳ��Ƿ���ڽ�ʬ���������򲻹���*/
	bool isAttacking = false;
	for (int i = x; i <= GRID_NUM_X; i++) {
		if (nowGame.map.grid[i][y].zombies.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet *p = new Bullet;
			p->setXY(x, y);
			nowGame.addBullet(p);
		}
	}
}

void SunFlower::go(Game & nowGame)
{
	counter++;
	if (counter >= speed) {
		counter = 0;
		nowGame.store.addSun(50);
	}
}

void Squash::go(Game & nowGame)
{
	if (counter == 0) {
		nowGame.map.grid[x][y].setBombFlag();
	}

	if (counter < speed) {
		counter++;
		nowGame.map.grid[x][y].flipBombFlag();
	}
	else {
		if (nowGame.map.grid[x][y].zombies.size() != 0) {
			nowGame.map.grid[x][y].hitZombies(attack);
			nowGame.map.grid[x][y].clearBombFlag();
			nowGame.delPlant(x, y);
		}
		else if (x + 1 <= GRID_NUM_X && nowGame.map.grid[x + 1][y].zombies.size() != 0) {
			nowGame.map.grid[x + 1][y].hitZombies(attack);
			nowGame.map.grid[x][y].clearBombFlag();
			nowGame.delPlant(x, y);
		}
		else if (x - 1 >= 0 && nowGame.map.grid[x - 1][y].zombies.size() != 0) {
			nowGame.map.grid[x - 1][y].hitZombies(attack);
			nowGame.map.grid[x][y].clearBombFlag();
			nowGame.delPlant(x, y);
		}
	}
}

void CherryBomb::go(Game & nowGame)
{
	if (counter == 0) {
		/*������ը��Ч*/
		//�ϲ�һ�е���������
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].setBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].setBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].setBombFlag();
		}
		//�м�һ�е���������
		nowGame.map.grid[x][y].setBombFlag();
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].setBombFlag();
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].setBombFlag();
		//�²�һ�е���������
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].setBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].setBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].setBombFlag();
		}
	}

	if (counter < speed) {
		counter++;
		/*��˸*/
		//�ϲ�һ�е���������
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].flipBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].flipBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].flipBombFlag();
		}
		//�м�һ�е���������
		nowGame.map.grid[x][y].flipBombFlag();
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].flipBombFlag();
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].flipBombFlag();
		//�²�һ�е���������
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].flipBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].flipBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].flipBombFlag();
		}
	}
	else {
		//�ϲ�һ�е���������
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].hitZombies(attack);
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].hitZombies(attack);
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].hitZombies(attack);
		}
		//�м�һ�е���������
		nowGame.map.grid[x][y].hitZombies(attack);
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].hitZombies(attack);
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].hitZombies(attack);
		//�²�һ�е���������
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].hitZombies(attack);
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].hitZombies(attack);
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].hitZombies(attack);
		}

		/*ȡ����ը��Ч*/
		//�ϲ�һ�е���������
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].clearBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].clearBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].clearBombFlag();
		}
		//�м�һ�е���������
		nowGame.map.grid[x][y].clearBombFlag();
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].clearBombFlag();
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].clearBombFlag();
		//�²�һ�е���������
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].clearBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].clearBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].clearBombFlag();
		}

		nowGame.delPlant(x, y);
	}
}

void SnowPea::go(Game & nowGame)
{
	/*���ж��Ҳ��Ƿ���ڽ�ʬ���������򲻹���*/
	bool isAttacking = false;
	for (int i = x; i <= GRID_NUM_X; i++) {
		if (nowGame.map.grid[i][y].zombies.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet *p = new SnowBullet;
			p->setXY(x, y);
			nowGame.addBullet(p);
		}
	}
}

void Repeater::go(Game & nowGame)
{
	/*���ж��Ҳ��Ƿ���ڽ�ʬ���������򲻹���*/
	bool isAttacking = false;
	for (int i = x; i <= GRID_NUM_X; i++) {
		if (nowGame.map.grid[i][y].zombies.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet *p = new Bullet;
			p->setXY(x, y);
			nowGame.addBullet(p);
		}
		else if (counter == speed - speed * 25 / 100) {
			Bullet *p = new Bullet;
			p->setXY(x, y);
			nowGame.addBullet(p);
		}
	}
}

void Garlic::go(Game & nowGame)
{
	vector<Zombie*> &zombie = nowGame.map.grid[x][y].zombies;
	for (auto& var : zombie) {
		var->setScape();
	}
}

void Jalapeno::go(Game & nowGame)
{
	if (counter == 0) {
		/*������ը��Ч*/
		for (int i = 0; i <= GRID_NUM_X; i++) {
			nowGame.map.grid[i][y].setBombFlag();
		}
	}

	if (counter < speed) {
		counter++;
		/*��˸*/
		for (int i = 0; i <= GRID_NUM_X; i++) {
			nowGame.map.grid[i][y].flipBombFlag();
		}
	}
	else {
		for (int i = 0; i <= GRID_NUM_X; i++) {
			nowGame.map.grid[i][y].hitZombies(attack);
			/*ȡ����ը��Ч*/
			nowGame.map.grid[i][y].clearBombFlag();
		}
		nowGame.delPlant(x, y);
	}
}

void PotatoMine::go(Game & nowGame)
{
	if (counter < speed) {
		counter++;
		nowGame.map.grid[x][y].setRefresh();
	}
	else {
		if (!ready) {
			ready = true;
			eatable = false;
			nowGame.map.grid[x][y].setBombFlag();
		}
		else {
			nowGame.map.grid[x][y].flipBombFlag();
		}

		if (nowGame.map.grid[x][y].zombies.size() != 0) {
			nowGame.map.grid[x][y].hitZombies(attack);
			nowGame.map.grid[x][y].clearBombFlag();
			nowGame.delPlant(x, y);
		}
		else if (x + 1 <= GRID_NUM_X && nowGame.map.grid[x + 1][y].zombies.size() != 0) {
			nowGame.map.grid[x + 1][y].hitZombies(attack);
			nowGame.map.grid[x][y].clearBombFlag();
			nowGame.delPlant(x, y);
		}
		else if (x - 1 >= 0 && nowGame.map.grid[x - 1][y].zombies.size() != 0) {
			nowGame.map.grid[x - 1][y].hitZombies(attack);
			nowGame.map.grid[x][y].clearBombFlag();
			nowGame.delPlant(x, y);
		}
	}
}

void PotatoMine::printExtra()
{
	if (!ready) {
		cout << "(����" << counter * 100 / speed << "%)";
	}
	else {
		cout << " (Ready)";
	}
	
}

void Plant::printName()
{
	PrintWithColor(name, nameColor);
}

void Plant::printLife()
{
	//���HP
	cout << "<HP-" << HP * 100 / maxHP << "%>";
}

void Spikeweed::go(Game & nowGame)
{
	if (counter == 0) {
		nowGame.map.grid[x][y].clearBombFlag();
	}
	counter++;
	if (counter >= speed) {
		counter = 0;
		nowGame.map.grid[x][y].setBombFlag();
		nowGame.map.grid[x][y].hitZombies(attack);
	}
}
