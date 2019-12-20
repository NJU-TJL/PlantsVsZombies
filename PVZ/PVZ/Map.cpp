#include "Map.h"
#include"Zombie.h"
#include<iostream>
using namespace std;


void Grid::setXY(int x, int y)
{
	dx = x * (GRID_WIDTH + 1) + 1;
	dy = y * (GRID_HEIGHT + 1) + 1;
}

void Grid::paint()
{
	flag_refresh = false;

	//先清空整个格子
	string str(GRID_WIDTH,' ');
	for (int i = 0; i < GRID_HEIGHT; i++) {
		Goto_XY(dx, dy + i);
		PrintWithColor(str);
	}

	if (bomb_flag) { //爆炸特效
		string str(GRID_WIDTH, '*');
		Goto_XY(dx, dy);
		PrintWithColor(str, BOOM_COLOR);
		int i;
		for (i = 1; i < GRID_HEIGHT - 1; i++) {
			Goto_XY(dx, dy + i);
			PrintWithColor("*", BOOM_COLOR);
			Goto_XY(dx + GRID_WIDTH - 1, dy + i);
			PrintWithColor("*", BOOM_COLOR);
		}
		Goto_XY(dx, dy + i);
		PrintWithColor(str, BOOM_COLOR);
	}

	if (selected) { //选中状态 输出选择框
		string str(GRID_WIDTH - 2, '-');
		Goto_XY(dx, dy);
		PrintWithColor("+" + str + "+");
		int i;
		for (i = 1; i < GRID_HEIGHT - 1; i++) {
			Goto_XY(dx, dy + i);
			PrintWithColor("|");
			Goto_XY(dx + GRID_WIDTH - 1, dy + i);
			PrintWithColor("|");
		}
		Goto_XY(dx, dy + i);
		PrintWithColor("+" + str + "+");
	}

	//输出植物、僵尸等信息
	if (plant != nullptr && zombies.size() == 0) {
		//植物额外信息
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 - 1);
		plant->printExtra();
		//植物名字
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2);
		plant->printName();
		//植物剩余HP
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 + 1);
		plant->printLife();
	}
	else if (plant != nullptr && zombies.size() != 0) {
		//植物额外信息
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 - 2);
		plant->printExtra();
		//植物名
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 - 1);
		plant->printName();
		//植物剩余HP
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2);
		plant->printLife();
		//僵尸数量
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 + 1);
		PrintWithColor("僵尸×");
		PrintWithColor(zombies.size());
	}
	//以下的都是不存在植物的情况
	else if (zombies.size() == 0);
	else if (zombies.size() == 1) {
		//输出额外信息
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 - 1);
		zombies[0]->printExtra();
		//输出僵尸名字
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2);
		zombies[0]->printName();
		//输出耐久度百分比
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 + 1);
		PrintWithColor("( ");
		PrintWithColor(zombies[0]->HP * 100 / zombies[0]->maxHP);
		PrintWithColor("% )");
	}
	else if (selected == false && zombies.size() <= GRID_HEIGHT) {
		for (int i = 0; i < zombies.size(); i++) {
			Goto_XY(dx + 1, dy + i);
			zombies[i]->printName();
		}
	}
	else if (selected == true && zombies.size() + 2 <= GRID_HEIGHT) {
		for (int i = 0; i < zombies.size(); i++) {
			Goto_XY(dx + 1, dy + i + 1);
			zombies[i]->printName();
		}
	}
	else {
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2);
		PrintWithColor("僵尸×");
		PrintWithColor(zombies.size());
	}
}

bool Grid::setPlant(Plant * iPlant)
{
	if (plant != nullptr) return false;
	else {
		plant = iPlant;
		flag_refresh = true;
		return true;
	}
}

void Grid::eatPlant(int attack)
{
	if (plant != nullptr) {
		plant->HP -= attack;
		if (plant->HP <= 0) {
			delPlant();
		}
		flag_refresh = true;
	}
}

void Grid::judgeEating()
{
	//处理：检测僵尸是否该吃植物
	if (plant != nullptr && plant->eatable && zombies.size() != 0) {
		for (auto&var : zombies) {
			var->eating = true;
		}
	}
	else if (plant == nullptr && zombies.size() != 0) {
		for (auto&var : zombies) {
			var->eating = false;
		}
	}
}

void Grid::addZombie(Zombie * iZombie)
{
	zombies.push_back(iZombie);
	flag_refresh = true;
}

void Grid::delZombie(Zombie * iZombie)
{
	//删除特定的僵尸
	for (auto itList = zombies.begin(); itList != zombies.end(); )
	{
		if ((*itList)==iZombie)
		{
			itList = zombies.erase(itList);
		}
		else
			itList++;
	}
	flag_refresh = true;
}

void Grid::hitZombies(int attack)
{
	for (int i = 0; i < zombies.size(); i++) {
		zombies[i]->hit(attack);
	}
}

void Map::paintGridLine()
{
	//网格线（草地块的边界）的绘制
	for (int i = 0; i < GRID_NUM_Y; i++) {
		string str(WINDOWS_WIDTH, '#');
		Goto_XY(0, i*(GRID_HEIGHT + 1));
		PrintWithColor(str);
		for (int j = 1; j <= GRID_HEIGHT; j++) {
			for (int k = 0; k <= GRID_NUM_X; k++) {
				Goto_XY(k*(GRID_WIDTH + 1), i*(GRID_HEIGHT + 1) + j);
				PrintWithColor("#");
			}
		}
	}
	string str(WINDOWS_WIDTH, '#');
	Goto_XY(0, GRID_NUM_Y*(GRID_HEIGHT + 1));
	PrintWithColor(str);
}

bool Map::travGrid(Game &game)
{
	for (int i = 0; i < GRID_NUM_X + 1; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i][j].judgeEating();
			if (grid[i][j].plant != nullptr) {
				grid[i][j].plant->go(game);
			}
		}
	}
	
	return true;
}

bool Map::setPlant(int ix, int iy, int type)
{
	Plant *newPlant = nullptr;
	switch (type)
	{
	case PEASHOOTER:
		newPlant = new PeaShooter;
		break;
	case SUNFLOWER:
		newPlant = new SunFlower;
		break;
	case SQUASH:
		newPlant = new Squash;
		break;
	case CHERRYBOMB:
		newPlant = new CherryBomb;
		break;
	case WALLNUT:
		newPlant = new WallNut;
		break;
	case SNOWPEA:
		newPlant = new SnowPea;
		break;
	case REPEATER:
		newPlant = new Repeater;
		break;
	case GARLIC:
		newPlant = new Garlic;
		break;
	case JALAPENO:
		newPlant = new Jalapeno;
		break;
	case POTATOMINE:
		newPlant = new PotatoMine;
		break;
	case SPIKEWEED:
		newPlant = new Spikeweed;
		break;
	case TALLNUT:
		newPlant = new TallNut;
		break;
		
	default:
		break;
	}
	newPlant->setXY(ix, iy);
	if (!grid[ix][iy].setPlant(newPlant)) { //种植失败（格子已有植物）
		delete newPlant;
		return false;
	}
	else
		return true;
}

void Map::refresh()
{
	for (int i = 0; i < GRID_NUM_X + 1; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			if (grid[i][j].flag_refresh) {
				grid[i][j].paint();
			}
		}
	}
}

void Map::setBombFlag(int x, int y)
{
	//越界检查
	if (x<0 || x>GRID_NUM_X || y<0 || y>GRID_NUM_Y - 1) return;
	grid[x][y].setBombFlag();
}

void Map::clearBombFlag(int x, int y)
{
	//越界检查
	if (x<0 || x>GRID_NUM_X || y<0 || y>GRID_NUM_Y - 1) return;
	grid[x][y].clearBombFlag();
}

void Map::init()
{
	system("cls");
	//网格线（草地块的边界）的绘制
	paintGridLine();
	//每个格子初始化
	for (int i = 0; i < GRID_NUM_X + 1; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i][j].setXY(i, j);
		}
	}
}
