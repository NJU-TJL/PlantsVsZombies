#pragma once
#include"ui_tools.h"
#include<string>
using namespace std;

class Game;
class Store;
class Map;

//用于商店展示的植物卡牌
class PlantCard{
	//植物编号
	int index;
	//植物名字
	string name;
	//价格
	int price;
	//冷却时间
	int CD;
	//是否选中
	bool flag;

	//时间计数
	int counter;
	
	friend class Store;
public:
	//设定参数
	void set(int i, const string& iname, int iprice, int iCD) {
		index = i;
		name = iname;
		price = iprice;
		CD = iCD * 1000 / 10 / SLEEP_TIME; //(iCD/10)的值表示多少秒的CD时间
		counter = CD;
		flag = false;
	}
	//输出植物购买信息（名字、价格，以及冷却进度）
	void print();
	//切换选中/非选中
	void setSelect() { flag = true; print(); }
	void setUnSelect() { flag = false; print(); }
	//冷却
	void cooling();
	//是否冷却结束
	bool coolingDone();
};

class Store
{
	//阳光数量
	int sun;
	//自然生产阳光的速度
	int speed;
	//可种植的植物
	PlantCard plants[PLANT_TYPE_MAX];
	
	//时间计数
	int counter;
public:
	Store() {
		plants[0].set(0, "向日葵  ", 50, 75);
		plants[1].set(1, "豌豆射手", 100, 75);
		plants[2].set(2, "窝瓜    ", 50, 200);
		plants[3].set(3, "樱桃炸弹", 150, 200);
		plants[4].set(4, "坚果墙  ", 50, 200);
		plants[5].set(5, "寒冰射手", 175, 75);
		plants[6].set(6, "双发射手", 200, 75);
		plants[7].set(7, "大蒜    ", 50, 75);
		plants[8].set(8, "火爆辣椒", 125, 300);
		plants[9].set(9, "土豆地雷", 25, 200);
		plants[10].set(10, "地刺    ", 100, 75);
		plants[11].set(11, "高坚果墙", 125, 200);
	}

	//商店初始化
	void init();
	//刷新阳光数量的输出
	void refreshSun();
	//增加阳光
	void addSun(int isun=50) { sun += isun; refreshSun(); }
	//购买，扣除阳光，返回是否购买成功
	bool pay(int choice, int x, int y, Map &map);
	//商店运行(周期增加阳光、冷却植物等)
	void run();
	//金手指：瞬间完成所有冷却（便于测试）
	void renew();

	friend class Game;
};

