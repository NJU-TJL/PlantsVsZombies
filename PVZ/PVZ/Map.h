#pragma once
#include"ui_tools.h"
#include "Plant.h"
#include<vector>
using namespace std;

class Game;
class Zombie;
class Bullet;
class Grid {
	//格子左上角的坐标，用于绘制时加上的偏移量
	int dx, dy;
	//此格子中的植物
	Plant* plant;
	//格子中的僵尸
	vector<Zombie*> zombies;
	
	/*其他辅助信息*/
	//是否选中
	bool selected;
	//用于标记是否需要刷新显示
	bool flag_refresh;
	void setRefresh() { flag_refresh = true; }
	//用于标记本格子是否处于爆炸特效（樱桃炸弹等）
	bool bomb_flag;

public:
	Grid() { plant = nullptr; selected = false; flag_refresh = false; bomb_flag = false; }
	//根据格子的坐标来设定dx,dy
	void setXY(int x, int y);
	//绘制格子中的显示内容
	void paint();
	//设定植物
	bool setPlant(Plant* iPlant);
	//清空植物
	void delPlant() { delete plant; plant = nullptr; flag_refresh = true; clearBombFlag(); }
	//加入一个僵尸
	void addZombie(Zombie* iZombie);
	//清除一个特定的僵尸
	void delZombie(Zombie* iZombie);
	//格子内的所有僵尸扣除attack的血量
	void hitZombies(int attack);

	//植物被吃
	void eatPlant(int attack);
	//判断僵尸是否吃植物
	void judgeEating();

	//设定选中、非选中状态
	void setSelected() { selected = true; flag_refresh = true; }
	void setUnSelected() { selected = false; flag_refresh = true;}
	
	//设置/取消爆炸特效标记
	void setBombFlag() { bomb_flag = true; setRefresh(); }
	void clearBombFlag() { bomb_flag = false; setRefresh(); }
	void flipBombFlag() { bomb_flag = !bomb_flag; setRefresh(); }

	~Grid() { delete plant; }

	friend class Map;
	friend class Bullet;
	friend class Store;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class PotatoMine;
	friend class Garlic;
	friend class Pole_Zombie;
};

class Map {
	Grid grid[GRID_NUM_X+1][GRID_NUM_Y];
public:
	//地图的初始化
	void init();
	//网格线（草地块的边界）的绘制
	void paintGridLine();
	//遍历网格：处理植物、僵尸
	bool travGrid(Game &game);
	//种植某类植物
	bool setPlant(int ix, int iy, int type);
	//遍历所有格子，检查是否需要刷新显示
	void refresh();
	//(x,y)格子开启/关闭爆炸特效
	void setBombFlag(int x, int y);
	void clearBombFlag(int x, int y);


	friend class Game;
	friend class Bullet;
	friend class Zombie;
	friend class Pole_Zombie;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class PotatoMine;
	friend class CherryBomb;
	friend class Jalapeno;
	friend class Garlic;
	friend class Spikeweed;
};
