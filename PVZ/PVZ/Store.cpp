#include "Store.h"
#include "Map.h"

#include<conio.h>
#include<iostream>
using namespace std;

void PlantCard::print()
{
	//参考位置设定
	int Dx = 2 + index * PLANT_CARD_WIDTH;
	int Dy = STORE_UP_BOUND + STORE_HEIGHT - 4;//第一行
	if (index >= 8) {
		Dx = 2 + (index - 8) * PLANT_CARD_WIDTH;
		Dy = Dy + 2;
	}
	else if (index >= 4) {
		Dx = 2 + (index - 4) * PLANT_CARD_WIDTH;
		Dy = Dy + 1;
	}

	Goto_XY(Dx, Dy);
	string str(PLANT_CARD_WIDTH, ' ');
	cout << str;
	Goto_XY(Dx, Dy);
	if (flag) {
		SetColor(SELECTED_COLOR);
	}
	if (index <= 8)
		cout << index + 1 << "." << name << " - " << price << "$";
	else
		cout << (char)(index - 9 + 'a') << "." << name << " - " << price << "$";
	if (counter < CD) {
		cout << "(" << counter * 100 / CD << "%)";
	}
	SetColor(DEFAULT_COLOR);
}

void PlantCard::cooling()
{
	if (counter >= CD) return; //无需冷却
	else {
		counter++;
		print();
	}
}

bool PlantCard::coolingDone()
{
	if (counter >= CD)
		return true;
	else
		return false;
}

void Store::init()
{
	//一些变量的初始化
	sun = 200;
	counter = 0;
	//每6秒生成阳光
	speed = 60 * 1000 / 10 / SLEEP_TIME;


	//固定不变的UI部分
	Goto_XY(2, STORE_UP_BOUND + 1);
	PrintWithColor("【商店】");
	Goto_XY(RIGHT_LINE_X, STORE_UP_BOUND + 1);
	PrintWithColor("|");
	Goto_XY(0, STORE_UP_BOUND + 2);
	string str(WINDOWS_WIDTH, '-');
	PrintWithColor(str);
	

	//可变的UI部分的首次输出
	refreshSun();
	for (int i = 0; i < PLANT_TYPE_MAX; i++) {
		plants[i].print();
	}
}

void Store::refreshSun()
{
	//先清空
	Goto_XY(RIGHT_LINE_X - 17, STORE_UP_BOUND + 1);
	string str(16, ' ');
	cout << str;
	//输出阳光数
	Goto_XY(RIGHT_LINE_X - 17, STORE_UP_BOUND + 1);
	PrintWithColor("阳光：");
	PrintWithColor(sun);
	PrintWithColor(" $");
}

bool Store::pay(int choice, int x, int y, Map &map)
{
	if (sun >= plants[choice].price && plants[choice].coolingDone()) {
		if (map.setPlant(x, y, choice)) {
			sun -= plants[choice].price;
			refreshSun();
			plants[choice].counter = 0;
			return true;
		}
	}
	return false;
}

void Store::run()
{
	counter++;
	if (counter >= speed) {
		counter = 0;
		addSun();
	}

	//冷却植物
	for (int i = 0; i < PLANT_TYPE_MAX; i++) {
		plants[i].cooling();
	}
}

void Store::renew()
{
	for (int i = 0; i < PLANT_TYPE_MAX; i++) {
		plants[i].counter = plants[i].CD;
		plants[i].print();
	}
}
