#pragma once
#include<cstdlib>
#include<Windows.h>
#include<string>
using namespace std;

/* UI��� - �ߴ���Ϣ */
const int GRID_WIDTH = 11; //��ƺ��ÿ�����ӵĿ�ȣ��ַ�����
const int GRID_HEIGHT = 5; //��ƺ��ÿ�����ӵĸ߶ȣ��ַ�����
const int GRID_NUM_X = 7;  //��ƺ�ߴ�Ϊ��GRID_NUM_X�� 
const int GRID_NUM_Y = 5;  //            GRID_NUM_Y��
//�̵�UI����ĸ߶ȣ����ͬ���ڿ�ȣ�
const int STORE_HEIGHT = 7;
//����-��
const int WINDOWS_WIDTH = (GRID_WIDTH + 1)*GRID_NUM_X + GRID_WIDTH * 3 / 2;
//����-��
const int WINDOWS_HEIGHT = (GRID_HEIGHT + 1)*GRID_NUM_Y + STORE_HEIGHT + 2;
//�̵괰�ڵ��ϱ߽� - y��ֵ
const int STORE_UP_BOUND = (GRID_HEIGHT + 1)*GRID_NUM_Y + 1;
//�̵괰����ֲ��չʾ��Ϣ�Ŀ��
const int PLANT_CARD_WIDTH = 24;
//������ | �÷֡���'|'��λ��
const int RIGHT_LINE_X = WINDOWS_WIDTH - 20;
//������Ϣ������λ��
const int HELP_INFO_Y = WINDOWS_HEIGHT - 1;

/* UI��� - ��ɫ��Ϣ */
//Ĭ��ɫ - �ڵ�������
const int DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//����ʱ��ѡ��
const int SELECTED_COLOR = BACKGROUND_GREEN | BACKGROUND_BLUE | DEFAULT_COLOR;
//��ͨ�㶹��ɫ
const int BULLET_COLOR = FOREGROUND_GREEN;
//�����㶹��ɫ
const int SNOWBULLET_COLOR = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//��ʬ�䶳Ч��ʱ���������
const int FREEZING_COLOR = SNOWBULLET_COLOR;
//��ը��Ч����ɫ
const int BOOM_COLOR = FOREGROUND_RED | FOREGROUND_INTENSITY;
//��ֽ��ʬû��ֽ��ĺ���״̬��ɫ
const int RED_EYE_COLOR = FOREGROUND_RED | FOREGROUND_INTENSITY;
//������Ϣ����ɫ(�׵׺���)
const int HELP_COLOR = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
//��Ϸ״̬
const int STATE_COLOR = BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//ֲ������
const int PLANT_ATTACK_COLOR = BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int PLANT_STATIC_COLOR = BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int PLANT_BOMB_COLOR =  BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;


/* ȫ���Թ��ܺ������� */
// ���ù��λ��
void Goto_XY(const int x, const int y);
// ���ع��
void HideCursor();
// ����0~n-1�������
inline int RANDOM(int n) { return rand() % n; }
// ���ô��ڴ�С
void SetWindowSize(int cols, int lines);
// �����ı���ɫ
void SetColor(int colorID);
// ����ɫ���ı������Ĭ��Ϊ�ڵװ���
void PrintWithColor(const string& str, int colorID = DEFAULT_COLOR);
void PrintWithColor(int num, int colorID = DEFAULT_COLOR);



/* һЩȫ�ֳ��� */
//ʱ�����ڣ����룩
const int SLEEP_TIME = 100;
//ֲ��������
const int PLANT_TYPE_MAX = 12;
enum PlantType { SUNFLOWER, PEASHOOTER, SQUASH, CHERRYBOMB, WALLNUT, SNOWPEA, REPEATER, GARLIC, JALAPENO, POTATOMINE, SPIKEWEED, TALLNUT };
//��ʬ������
const int ZOMBIE_TYPE_MAX = 11;
enum ZombieType { 
	ZOMBIE, CONEHEAD_ZOMBIE, BUCKET_ZOMBIE, FOOTBALL_ZOMBIE, DOOR_ZOMBIE, NEWSPAPER_ZOMBIE, POLE_ZOMBIE, DANCING_ZOMBIE, BOX_ZOMBIE, FLAG_ZOMBIE, BACKUP_DANCER
};