#pragma once

#include<string>
using namespace std;

#include"ui_tools.h"

class Map;
class Game;

//��ͨ��ʬ
class Zombie
{
protected:
	//��������
	int x, y;
	//��ʬ��
	string name;
	//�ƶ��ٶ�
	int speed;
	//Ѫ��
	int HP; //��ǰ
	int maxHP;
	//������
	int attack;
	//��ɱ�÷�
	int score;

	//���Բ����趨
	void set(const string& str, int iscore=50, int ilife = 200, int ispeed = 45, int iattack = 100) { 
		//���֡���ɱ�÷֡�HP
		name = str; score = iscore; maxHP = HP = ilife; 
		//�ٶȣ���ispeed/10����/��
		speed = ispeed * 1000 / 10 / SLEEP_TIME; 
		//����������iattack) ���˺�/��
		attack = iattack * SLEEP_TIME / 1000; 
	}
	
	//�����ƶ��ļ���
	int counter;
	//��Ǵ��ڳ�ֲ���״̬
	bool eating;

	//������Ч�����ƶ�/�����ٶȼ���
	bool freezing;
	//����Ч������ʱ��
	int freezing_time;
	//ʱ�����
	int freezing_counter;

	//��������
	bool scape_flag;
	//��������ƶ���������
	int scape_time;
	//ʱ�����
	int scape_counter;

	//�����ʬ���֣��磺����״̬���ֻ��ɫ��
	virtual void printName();
	//������Ϣ�������������/��ֽ����Ϣ��
	virtual void printExtra() {}

public:
	Zombie() { 
		counter = 0; eating = false; set("��ͨ��ʬ",50); 
		//����Ч��������ʼ��
		freezing = false; freezing_counter = 0;
		freezing_time = 8 * 1000 / SLEEP_TIME; //8��
		//����Ч��������ʼ��
		scape_flag = false; scape_counter = 0;
		scape_time = 8 * 1000 / 10 / SLEEP_TIME;//0.8��
	}
	//���ؽ�ʬ����
	const string& getName() const { return name; }

	//�趨��ʼλ��
	void setXY(int ix, int iy) { x = ix; y = iy; }
	//��ʬ�ж�������λ�ơ���ֲ��ȶ�����������ֵ�����Ƿ���
	virtual bool move(Map& map);
	//��ʬ����Ч����Ĭ���ޣ�
	virtual void go(Game &nowGame) {}
	//������
	virtual void hit(int attack) { HP -= attack; }
	//���������ٵ�Ч�������Ž�ʬ�ȿɷ�����
	virtual void setFreezing() { freezing = true; freezing_counter = 0; };
	//��������Ч����׼������е����ڵ��У�
	void setScape() { 
		if (!scape_flag) {
			scape_flag = true; scape_counter = 0;;
		}
	};

	friend class Game;
	friend class Bullet;
	friend class SnowBullet;
	friend class Grid;
};

/* ��������Ľ�ʬ */

class Flag_Zombie :public Zombie {
public:
	Flag_Zombie() { set("ҡ�콩ʬ", 50, 200, 30, 110); }
};

class Conehead_Zombie :public Zombie {
public:
	Conehead_Zombie() { set("·�Ͻ�ʬ", 75, 570, 45,120); }
};

class Bucket_Zombie :public Zombie {
public:
	Bucket_Zombie() { set("��Ͱ��ʬ", 125, 1300, 45,120); }
};

class Football_Zombie :public Zombie {
public:
	Football_Zombie() { set("�����ʬ", 175, 1600, 25, 120); }
};

class Door_Zombie :public Zombie {
	//�ٽ��
	int transHP;
public:
	Door_Zombie() { set("���Ž�ʬ", 125, 1300, 45, 120); transHP = 500; }
	void setFreezing();
	void printExtra();
};

class Newspaper_Zombie :public Zombie {
	//�ٽ��
	int transHP;
	//��ֽû�˺���ٶ� 1.2��/��
	int speed_Plus = 12 * 1000 / 10 / SLEEP_TIME;
	//��ֽû�˺�Ĺ�����
	int attack_Plus = 200;
public:
	Newspaper_Zombie() { set("������ʬ", 125, 300); transHP = 200; }
	void setFreezing();
	void printExtra();
	//��д��Ѫ��������ֽû��Ҫ���٣�
	void hit(int attack);
	//û��ֽ�˾ͺ�����ʾ������״̬��
	void printName();
};

class Pole_Zombie :public Zombie {
	//�ٽ�㣺�Ƿ��гŸ�
	bool hasPole;
	//����֮����ٶ� 4.5��/��
	int speed2 = 45 * 1000 / 10 / SLEEP_TIME;
public:
	Pole_Zombie() { set("�Ÿ˽�ʬ", 100, 430, 20); hasPole = true; }
	void printExtra();
	bool move(Map& map);
};

class Dancing_Zombie :public Zombie {
	//һ��ʱ��󴥷��ٻ�
	int call_time;
	//�Ա�ʱ�����
	int call_counter;
	//�ٽ�㣺�Ƿ��Ѵ����ٻ�
	bool hasCalled;
	//�ٻ�֮����ٶ� 5.5��/��
	int speed2 = 55 * 1000 / 10 / SLEEP_TIME;
public:
	Dancing_Zombie() { 
		set("������ʬ", 350, 500, 12); 
		hasCalled = false; 
		call_time = 40 * 1000 / 10 / SLEEP_TIME;
		call_counter = 0;
	}
	void go(Game &nowGame);
};

class Backup_Dancer :public Zombie {
public:
	Backup_Dancer() { set("���轩ʬ", 50, 200, 55); }
};

class Box_Zombie :public Zombie {
	//һ��ʱ��󴥷������Ա�
	int bomb_time;
	//�Ա�ʱ�����
	int bomb_counter;
	//�Ƿ�������ը
	bool bomb_flag;
public:
	Box_Zombie() {
		set("С��ʬ", 250, 800, 12); 
		bomb_time = 30 * 1000 / 10 / SLEEP_TIME;
		bomb_counter = 0;
		bomb_flag = false;
	}
	void go(Game &nowGame);
};
