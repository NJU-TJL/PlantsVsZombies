#pragma once
#include"ui_tools.h"
#include<string>
using namespace std;

class Game;
class Store;
class Map;

//�����̵�չʾ��ֲ�￨��
class PlantCard{
	//ֲ����
	int index;
	//ֲ������
	string name;
	//�۸�
	int price;
	//��ȴʱ��
	int CD;
	//�Ƿ�ѡ��
	bool flag;

	//ʱ�����
	int counter;
	
	friend class Store;
public:
	//�趨����
	void set(int i, const string& iname, int iprice, int iCD) {
		index = i;
		name = iname;
		price = iprice;
		CD = iCD * 1000 / 10 / SLEEP_TIME; //(iCD/10)��ֵ��ʾ�������CDʱ��
		counter = CD;
		flag = false;
	}
	//���ֲ�ﹺ����Ϣ�����֡��۸��Լ���ȴ���ȣ�
	void print();
	//�л�ѡ��/��ѡ��
	void setSelect() { flag = true; print(); }
	void setUnSelect() { flag = false; print(); }
	//��ȴ
	void cooling();
	//�Ƿ���ȴ����
	bool coolingDone();
};

class Store
{
	//��������
	int sun;
	//��Ȼ����������ٶ�
	int speed;
	//����ֲ��ֲ��
	PlantCard plants[PLANT_TYPE_MAX];
	
	//ʱ�����
	int counter;
public:
	Store() {
		plants[0].set(0, "���տ�  ", 50, 75);
		plants[1].set(1, "�㶹����", 100, 75);
		plants[2].set(2, "�ѹ�    ", 50, 200);
		plants[3].set(3, "ӣ��ը��", 150, 200);
		plants[4].set(4, "���ǽ  ", 50, 200);
		plants[5].set(5, "��������", 175, 75);
		plants[6].set(6, "˫������", 200, 75);
		plants[7].set(7, "����    ", 50, 75);
		plants[8].set(8, "������", 125, 300);
		plants[9].set(9, "��������", 25, 200);
		plants[10].set(10, "�ش�    ", 100, 75);
		plants[11].set(11, "�߼��ǽ", 125, 200);
	}

	//�̵��ʼ��
	void init();
	//ˢ���������������
	void refreshSun();
	//��������
	void addSun(int isun=50) { sun += isun; refreshSun(); }
	//���򣬿۳����⣬�����Ƿ���ɹ�
	bool pay(int choice, int x, int y, Map &map);
	//�̵�����(�����������⡢��ȴֲ���)
	void run();
	//����ָ��˲�����������ȴ�����ڲ��ԣ�
	void renew();

	friend class Game;
};

