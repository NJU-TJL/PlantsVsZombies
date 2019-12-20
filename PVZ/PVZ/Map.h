#pragma once
#include"ui_tools.h"
#include "Plant.h"
#include<vector>
using namespace std;

class Game;
class Zombie;
class Bullet;
class Grid {
	//�������Ͻǵ����꣬���ڻ���ʱ���ϵ�ƫ����
	int dx, dy;
	//�˸����е�ֲ��
	Plant* plant;
	//�����еĽ�ʬ
	vector<Zombie*> zombies;
	
	/*����������Ϣ*/
	//�Ƿ�ѡ��
	bool selected;
	//���ڱ���Ƿ���Ҫˢ����ʾ
	bool flag_refresh;
	void setRefresh() { flag_refresh = true; }
	//���ڱ�Ǳ������Ƿ��ڱ�ը��Ч��ӣ��ը���ȣ�
	bool bomb_flag;

public:
	Grid() { plant = nullptr; selected = false; flag_refresh = false; bomb_flag = false; }
	//���ݸ��ӵ��������趨dx,dy
	void setXY(int x, int y);
	//���Ƹ����е���ʾ����
	void paint();
	//�趨ֲ��
	bool setPlant(Plant* iPlant);
	//���ֲ��
	void delPlant() { delete plant; plant = nullptr; flag_refresh = true; clearBombFlag(); }
	//����һ����ʬ
	void addZombie(Zombie* iZombie);
	//���һ���ض��Ľ�ʬ
	void delZombie(Zombie* iZombie);
	//�����ڵ����н�ʬ�۳�attack��Ѫ��
	void hitZombies(int attack);

	//ֲ�ﱻ��
	void eatPlant(int attack);
	//�жϽ�ʬ�Ƿ��ֲ��
	void judgeEating();

	//�趨ѡ�С���ѡ��״̬
	void setSelected() { selected = true; flag_refresh = true; }
	void setUnSelected() { selected = false; flag_refresh = true;}
	
	//����/ȡ����ը��Ч���
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
	//��ͼ�ĳ�ʼ��
	void init();
	//�����ߣ��ݵؿ�ı߽磩�Ļ���
	void paintGridLine();
	//�������񣺴���ֲ���ʬ
	bool travGrid(Game &game);
	//��ֲĳ��ֲ��
	bool setPlant(int ix, int iy, int type);
	//�������и��ӣ�����Ƿ���Ҫˢ����ʾ
	void refresh();
	//(x,y)���ӿ���/�رձ�ը��Ч
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
