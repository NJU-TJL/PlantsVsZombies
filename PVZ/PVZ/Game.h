#pragma once
#include "Map.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Store.h"

#include<list>
using namespace std;

class Plant;

class Game {
	Map map;
	Store store;

	//�ӵ����У��㶹���ֵȷ����ģ�
	list<Bullet*> bullets;
	//��ʬ����
	list<Zombie*> zombies;

	//��ǰ����״̬����ѡ���ֵ�����������ö��������
	int state;
	//״̬������������״̬������ֲ���Ϸ��ͣ
	enum GAME_STATE { NORMAL, STORE, SHOVEL, PAUSE };
	//ѡ�����ֲ����
	void weeding();
	//ѡ����ֲ����
	void shopping();

	//��ǰ����λ��
	int x, y; 
	//��ǰ׼����ֲ��ֲ������
	int planting_type;
	//����ѡ�񽹵�
	void openFocus();
	//�ر�ѡ�񽹵�
	void closeFocus();
	
	//����ĳ��λ�õ�ֲ��
	void delPlant(int ix, int iy);
	//�ӵ��ƶ�
	void moveBullet();
	//�ӵ�����ʾ���
	void printBullet();
	//ָ��λ������ĳ�����͵Ľ�ʬ
	void addZombie(int x, int y, int type);
	//��ʬ�����ٶ�
	int make_speed;
	int make_counter;
	//��ʬ�����߼�
	void makeZombies();
	//��ʬ�ƶ�
	bool moveZombie();
	//�����Ч��ʬ��Ѫ��<=0��
	void clearZombie();

	//�÷�
	int score;
	//ˢ�µ÷���ʾ
	void refreshScore();
	//���������ٶ�
	int score_speed;
	int score_counter;
	//�Ʒ�
	void calScore();

	//������Ϣ�����
	void helpInfo();
	//ָʾ�Ƿ���Ҫ���°�����Ϣ��״̬�л�����Ҫ��
	bool refreshHelpInfo;

	//��ͣ
	void pause();
	//��Ϸ����
	void gameover();

public:
	Game();

	//��Ϸ������ʼ��
	void init();
	//��Ϸ��ѭ��
	void loop();

	//�ӵ�����������һ���ӵ�
	void addBullet(Bullet* p);
	
	~Game();


	friend class SunFlower;
	friend class PeaShooter;
	friend class SnowPea;
	friend class Repeater;
	friend class Squash;
	friend class PotatoMine;
	friend class CherryBomb;
	friend class Jalapeno;
	friend class Garlic;
	friend class Spikeweed;
	friend class Dancing_Zombie;
	friend class Box_Zombie;
};

