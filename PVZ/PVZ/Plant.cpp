#include "Plant.h"
#include "Game.h"
#include<iostream>
using namespace std;

void PeaShooter::go(Game & nowGame)
{
	/*先判断右侧是否存在僵尸，不存在则不攻击*/
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
		/*开启爆炸特效*/
		//上侧一列的三个格子
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].setBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].setBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].setBombFlag();
		}
		//中间一列的三个格子
		nowGame.map.grid[x][y].setBombFlag();
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].setBombFlag();
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].setBombFlag();
		//下侧一列的三个格子
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].setBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].setBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].setBombFlag();
		}
	}

	if (counter < speed) {
		counter++;
		/*闪烁*/
		//上侧一列的三个格子
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].flipBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].flipBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].flipBombFlag();
		}
		//中间一列的三个格子
		nowGame.map.grid[x][y].flipBombFlag();
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].flipBombFlag();
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].flipBombFlag();
		//下侧一列的三个格子
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].flipBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].flipBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].flipBombFlag();
		}
	}
	else {
		//上侧一列的三个格子
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].hitZombies(attack);
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].hitZombies(attack);
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].hitZombies(attack);
		}
		//中间一列的三个格子
		nowGame.map.grid[x][y].hitZombies(attack);
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].hitZombies(attack);
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].hitZombies(attack);
		//下侧一列的三个格子
		if (y + 1 <= GRID_NUM_Y - 1) {
			nowGame.map.grid[x][y + 1].hitZombies(attack);
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y + 1].hitZombies(attack);
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y + 1].hitZombies(attack);
		}

		/*取消爆炸特效*/
		//上侧一列的三个格子
		if (y - 1 >= 0) {
			nowGame.map.grid[x][y - 1].clearBombFlag();
			if (x - 1 >= 0) nowGame.map.grid[x - 1][y - 1].clearBombFlag();
			if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y - 1].clearBombFlag();
		}
		//中间一列的三个格子
		nowGame.map.grid[x][y].clearBombFlag();
		if (x - 1 >= 0) nowGame.map.grid[x - 1][y].clearBombFlag();
		if (x + 1 <= GRID_NUM_X) nowGame.map.grid[x + 1][y].clearBombFlag();
		//下侧一列的三个格子
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
	/*先判断右侧是否存在僵尸，不存在则不攻击*/
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
	/*先判断右侧是否存在僵尸，不存在则不攻击*/
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
		/*开启爆炸特效*/
		for (int i = 0; i <= GRID_NUM_X; i++) {
			nowGame.map.grid[i][y].setBombFlag();
		}
	}

	if (counter < speed) {
		counter++;
		/*闪烁*/
		for (int i = 0; i <= GRID_NUM_X; i++) {
			nowGame.map.grid[i][y].flipBombFlag();
		}
	}
	else {
		for (int i = 0; i <= GRID_NUM_X; i++) {
			nowGame.map.grid[i][y].hitZombies(attack);
			/*取消爆炸特效*/
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
		cout << "(蓄力" << counter * 100 / speed << "%)";
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
	//输出HP
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
