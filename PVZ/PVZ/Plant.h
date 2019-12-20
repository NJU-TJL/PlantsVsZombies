#pragma once

#include<string>
using namespace std;

#include"ui_tools.h"

class Game;
class Grid;

/* ����ֲ��Ļ��� */
class Plant {
protected:
	//ֲ����
	string name;
	//��������
	int x, y;
	//ֲ���;öȣ�Ĭ�϶���300��
	int HP;
	int maxHP;

	//�趨ֲ�����ԣ����֡�HP��Ĭ��300��
	void set(const string& str, int ilife = 300) {
		name = str; maxHP = HP = ilife; eatable = true; skipable = true; nameColor = DEFAULT_COLOR;
	}

	friend class Grid;
public:
	//ֲ���Ƿ���Ա��ԣ��磺�ش̲�����
	bool eatable;
	//ֲ���Ƿ�ɱ��������߼��ǿ���У�
	bool skipable;

	//����ֲ������
	const string& getName() const { return name; }
	//�趨��������
	void setXY(int ix, int iy) { x = ix; y = iy; }
	//������Ϊ��Ĭ���ޣ����磺�����㶹����������
	virtual void go(Game& nowGame) {}
	//���ֲ����
	void printName();
	//ֲ��������ɫ
	int nameColor;
	//���ʣ������ֵ��Ĭ�ϸ�ʽ���������д������ش�ʣ��HP��
	virtual void printLife();
	//������Ϣ�����Ĭ���ޣ����磺�����׵�װ����Ϣ
	virtual void printExtra() {}
};


/* ��������ֲ�� */

//�㶹����
class PeaShooter :public Plant {
	//�����ٶ�
	int speed;
	//ʱ�Ӽ���
	int counter;
public:
	PeaShooter() { 
		set("�㶹����"); //HPĬ��300
		speed = 14 * 1000 / 10 / (SLEEP_TIME); counter = 0; //1.4��
		nameColor = PLANT_ATTACK_COLOR;
	}
	void go(Game& nowGame);
};

//���տ�
class SunFlower :public Plant {
	//����������ٶ�
	int speed;
	//ʱ�Ӽ���
	int counter;
public:
	SunFlower() { 
		set("���տ�");//HPĬ��300
		speed = 80 * 1000 / 10 / (SLEEP_TIME); counter = 0;//8��
		nameColor = PLANT_STATIC_COLOR;
	}
	void go(Game& nowGame);
};

//�ѹ�
class Squash :public Plant {
	//������
	int attack;
	//��ֲʱ���Ӻ�ſ�ʼ����Ч��
	int speed;
	//ʱ�����
	int counter;

public:
	Squash() {
		set("�ѹ�"); nameColor = PLANT_BOMB_COLOR;
		eatable = false;
		speed = 8 * 1000 / 10 / (SLEEP_TIME); counter = 0; attack = 1800;
	}
	void go(Game& nowGame);
};

//ӣ��ը��
class CherryBomb :public Plant {
	//��ֲ�������ſ�ʼ����Ч��
	int speed;
	//ʱ�����
	int counter;
	//������
	int attack;

public:
	CherryBomb() {
		set("ӣ��ը��"); nameColor = PLANT_BOMB_COLOR;
		eatable = false;
		speed = 5 * 1000 / 10 / (SLEEP_TIME); counter = 0; attack = 1800;
	}
	void go(Game& nowGame);
};

//���ǽ
class WallNut :public Plant {
public:
	WallNut() { 
		set("���ǽ", 4000); nameColor = PLANT_STATIC_COLOR;
	}
};

//��������
class SnowPea :public Plant {
	//�����ٶ�
	int speed;
	//ʱ�Ӽ���
	int counter;
public:
	SnowPea() { 
		set("��������"); nameColor = PLANT_ATTACK_COLOR;
		speed = 14 * 1000 / 10 / (SLEEP_TIME); counter = 0; 
	}
	void go(Game& nowGame);
};

//˫������
class Repeater :public Plant {
	//�����ٶ�
	int speed;
	//ʱ�Ӽ���
	int counter;
public:
	Repeater() { 
		set("˫������"); nameColor = PLANT_ATTACK_COLOR;
		speed = 14 * 1000 / 10 / (SLEEP_TIME); counter = 0; 
	}
	void go(Game& nowGame);
};

//����
class Garlic :public Plant {
public:
	Garlic() { 
		set("����", 800); nameColor = PLANT_STATIC_COLOR;
	}
	void go(Game& nowGame);
};

//������
class Jalapeno :public Plant {
	//��ֲ�������ſ�ʼ����Ч��
	int speed;
	//ʱ�����
	int counter;
	//������
	int attack;

public:
	Jalapeno() {
		set("������"); nameColor = PLANT_BOMB_COLOR;
		eatable = false;
		speed = 6 * 1000 / 10 / (SLEEP_TIME); counter = 0; attack = 1800;
	}
	void go(Game& nowGame);
};

//��������
class PotatoMine :public Plant {
	//��ֲ�������ſ�ʼ����Ч��
	int speed;
	//ʱ�����
	int counter;
	//������
	int attack;
	//��¼�Ƿ���װ�����
	bool ready;

public:
	PotatoMine() {
		set("��������"); nameColor = PLANT_BOMB_COLOR;
		speed = 75 * 1000 / 10 / (SLEEP_TIME); counter = 0; attack = 1800;
		ready = false;
	}
	void go(Game& nowGame);
	void printExtra();
};

//�ش�
class Spikeweed :public Plant {
	//�����ٶ�
	int speed;
	//������
	int attack;
	//ʱ�Ӽ���
	int counter;
public:
	Spikeweed() { 
		set(" <�ش�>"); 
		attack = 20; eatable = false;
		speed = 10 * 1000 / 10 / (SLEEP_TIME); counter = 0; 
	}
	void go(Game& nowGame);
	void printLife() {}
};

//�߼��ǽ
class TallNut :public Plant {
public:
	TallNut() { 
		set("�߼��ǽ", 8000); nameColor = PLANT_STATIC_COLOR;
		skipable = false; }
};
