#pragma once

#include "Zombie.h"
#include<vector>

class Map;
class Bullet
{
protected:
	//�ӵ���ǰ��λ��
	int x, y;
	//�ƶ��ٶȣ�speed��ʱ�������ƶ�һ���ַ����ӣ�
	int speed;
	//��������ÿ�λ��н�ʬ���۳���Ѫ����
	int attack;

	//�����ƶ��ļ���
	int counter;

public:
	Bullet();
	//���㲢�����ӵ�����ʼ���꣨(dx,dy)λ�õ�ֲ�﷢���ӵ���
	void setXY(int dx, int dy);
	//��ǰ�ƶ�
	void move(Map &map);
	//�����ӵ�
	virtual void paint();
	//������ʬ
	virtual void hitZombie(vector<Zombie*> &zombie);
	//�Ƿ����
	bool hit;
};

//�������ֵ��ӵ�
class SnowBullet :public Bullet {
	void hitZombie(vector<Zombie*> &zombie);
	void paint();
};