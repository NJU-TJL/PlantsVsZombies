#include "Game.h"
#include<iostream>
#include<ctime>
#include<conio.h>
using namespace std;

void Game::openFocus()
{
	map.grid[x][y].setSelected();
}

void Game::closeFocus()
{
	state = NORMAL; refreshHelpInfo = true;
	map.grid[x][y].setUnSelected();
}

void Game::weeding()
{
	//���̰���ʶ��
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case -32:
			map.grid[x][y].setUnSelected();
			ch = _getch();
			switch (ch)
			{
			case 72://��
				if (y > 0)
					y--;
				break;
			case 80://��
				if (y < GRID_NUM_Y - 1)
					y++;
				break;
			case 75://��
				if (x > 0)
					x--;
				break;
			case 77://��
				if (x < GRID_NUM_X - 1)
					x++;
				break;
			default:
				break;
			}
			map.grid[x][y].setSelected();
			break;
		case '\r':
			delPlant(x, y);
			//���ﲻ��break�����������رս����˳�
		case 27://ESC
			closeFocus();
			break;
		//�ո����ͣ
		case ' ':
			pause();
			break;

		case '+'://����ָ����Ǯ�������ڲ��ԣ�
			store.addSun(1000);
		case '*'://����ָ��˲�����������ȴ�����ڲ��ԣ�
			store.renew(); break;

		default:break;
		}
	}
	//����ʶ�����
}

void Game::shopping()
{
	//���̰���ʶ��
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case -32:
			map.grid[x][y].setUnSelected();
			ch = _getch();
			switch (ch)
			{
			case 72://��
				if (y > 0)
					y--;
				break;
			case 80://��
				if (y < GRID_NUM_Y - 1)
					y++;
				break;
			case 75://��
				if (x > 0)
					x--;
				break;
			case 77://��
				if (x < GRID_NUM_X - 1)
					x++;
				break;
			default:
				break;
			}
			map.grid[x][y].setSelected();
			break;
		case 27://ESC
			store.plants[planting_type].setUnSelect();
			closeFocus();
			break;
		case '\r':
			if (store.pay(planting_type, x, y, map)) { //�������ɹ�
				store.plants[planting_type].setUnSelect();
				closeFocus();
			}
			break;
		//�ո����ͣ
		case ' ':
			pause();
			break;

		case '+'://����ָ����Ǯ�������ڲ��ԣ�
			store.addSun(1000);
		case '*'://����ָ��˲�����������ȴ�����ڲ��ԣ�
			store.renew(); break;
		
		/*����ֲ��İ���ʶ��*/
		case 'a':case'A':
			store.plants[planting_type].setUnSelect();
			planting_type = 9;
			store.plants[planting_type].setSelect();
			break;
		case 'b':case'B':
			store.plants[planting_type].setUnSelect();
			planting_type = 10;
			store.plants[planting_type].setSelect();
			break;
		case 'c':case 'C':
			store.plants[planting_type].setUnSelect();
			planting_type = 11;
			store.plants[planting_type].setSelect();
			break;
		default:
			if (ch >= '1' && ch <= '9') {
				int key = ch - '0' - 1;
				if (key >= 0 && key < PLANT_TYPE_MAX) {
					store.plants[planting_type].setUnSelect();
					planting_type = key;
					store.plants[planting_type].setSelect();
				}
			}
			break;
		}
	}
	//����ʶ�����
}

void Game::delPlant(int ix, int iy)
{
	if (ix<0 || ix>GRID_NUM_X || iy<0 || iy>GRID_NUM_Y - 1) return;
	map.grid[ix][iy].delPlant();
}

void Game::refreshScore()
{
	//�����
	Goto_XY(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
	string str(15, ' ');
	cout << str;
	//����÷�
	Goto_XY(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
	cout << "[������" << score<<"]";
}

void Game::calScore()
{
	score_counter++;
	if (score_counter >= score_speed) {
		score_counter = 0;
		score++;
		refreshScore();
	}
}

void Game::helpInfo()
{
	if (refreshHelpInfo) {
		//���
		string str(WINDOWS_WIDTH, ' ');
		Goto_XY(0, HELP_INFO_Y);
		cout << str;
		Goto_XY(0, HELP_INFO_Y);
		if (state == NORMAL) {
			PrintWithColor(" <��Ϸ��> ", STATE_COLOR);
			PrintWithColor(" ��ֲ��\"1-9\"���ּ���\"a-c\"�� | ������\"x\"�� | ��ͣ���ո�� �������ִ�Сд��", HELP_COLOR);
		}
		else if (state == STORE) {
			PrintWithColor(" <��ֲ> ", STATE_COLOR);
			PrintWithColor(" ѡ��\"1-9\"���ּ���\"a-c\"�� | ȷ�ϣ��س��� | ���أ�Esc�� | ��ͣ���ո��", HELP_COLOR);
		}
		else if (state == SHOVEL) {
			PrintWithColor(" <����> ", STATE_COLOR);
			PrintWithColor(" ȷ�ϣ��س��� | ���أ�Esc�� | ��ͣ���ո��", HELP_COLOR);
		}
		else if (state == PAUSE) {
			PrintWithColor(" <��ͣ��> ", STATE_COLOR);
			PrintWithColor(" �˳���ͣ���ո��", HELP_COLOR);
		}

		refreshHelpInfo = false;
	}
}

void Game::pause()
{
	int temp = state;
	state = PAUSE; refreshHelpInfo = true;
	helpInfo();
	while (true) {
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case ' '://�ո������ͣ
				state = temp; refreshHelpInfo = true;
				helpInfo();
				return;
				break;
			default:;
			}
		}
		Sleep(SLEEP_TIME);
	}
	
}

void Game::gameover()
{
	system("cls");
	Goto_XY(WINDOWS_WIDTH / 2 - 6, WINDOWS_HEIGHT / 2 - 1);
	PrintWithColor("����Ϸ������", STATE_COLOR);
	//�������
	Goto_XY(WINDOWS_WIDTH / 2 - 8, WINDOWS_HEIGHT / 2 + 2);
	cout << "��ķ����ǣ� " << score << endl;
	Goto_XY(0, WINDOWS_HEIGHT - 1);
	SetColor(HELP_COLOR);
	system("pause");
}

Game::Game()
{
	HideCursor();
	SetWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	srand(time(0));
}

void Game::init()
{
	map.init();
	store.init();

	state = NORMAL; refreshHelpInfo = true;
	x = y = 0;
	planting_type = 0;

	score = 0;
	score_speed = 1 * 1000 / SLEEP_TIME;
	score_counter = 0;
	refreshScore();

	//16�����һ�ν�ʬ
	make_speed = 160 * 1000 / 10 / SLEEP_TIME;
	make_counter = 0;
}

void Game::loop()
{	
	//TEST:��һ��ʼ�������ض��Ľ�ʬ�����ڵ��ԣ�
	//addZombie(GRID_NUM_X, 0, POLE_ZOMBIE);	
	//addZombie(GRID_NUM_X, 2, DANCING_ZOMBIE);
	addZombie(GRID_NUM_X, 2, BOX_ZOMBIE);
	//addZombie(GRID_NUM_X, 2, NEWSPAPER_ZOMBIE);
	//addZombie(GRID_NUM_X, 2, FLAG_ZOMBIE);
	//addZombie(GRID_NUM_X, 2, ZOMBIE);

	while (true) {

		if (state == NORMAL) {
			//���̰���ʶ��
			char ch;
			if (_kbhit())
			{
				ch = _getch();
				switch (ch)
				{
				case 'a':case 'A':
					planting_type = 9;
					store.plants[planting_type].setSelect();
					//�����̵�ѡ��
					state = STORE; refreshHelpInfo = true;
					openFocus();
					break;
				case 'b':case 'B':
					planting_type = 10;
					store.plants[planting_type].setSelect();
					//�����̵�ѡ��
					state = STORE; refreshHelpInfo = true;
					openFocus();
					break;
				case 'c':case 'C':
					planting_type = 11;
					store.plants[planting_type].setSelect();
					//�����̵�ѡ��
					state = STORE; refreshHelpInfo = true;
					openFocus();
					break;
				//��x/X�������ֲ��
				case 'x':case 'X':
					state = SHOVEL; refreshHelpInfo = true;
					openFocus();
					break;
				//�ո����ͣ
				case ' ':
					pause();
					break;

				case '+'://����ָ����Ǯ�������ڲ��ԣ�
					store.addSun(1000);
				case '*'://����ָ��˲�����������ȴ�����ڲ��ԣ�
					store.renew(); break;

				default:
					//ֱ�Ӱ������ּ������
					if (ch >= '1'&&ch <= '9') {
						planting_type = ch - '0' - 1;
						state = STORE; refreshHelpInfo = true;
						openFocus();
						//�����̵�ѡ��
						store.plants[planting_type].setSelect();
						break;
					}
				}
			}
			//����ʶ�����
		}
		else if (state == STORE) {
			shopping();
		}
		else if (state == SHOVEL) {
			weeding();
		}

		//ִ�н�ʬ�����߼�
		makeZombies();

		//������ֲ��
		if (!map.travGrid(*this)) {
			break;
		}
		
		//��ʬ���� - �ж�
		if (moveZombie()) {
			gameover();//��ʬ���ƣ���Ϸ����
			break;
		}
		
		//�̵�����
		store.run();

		//�ӵ��ƶ�
		moveBullet();
		
		//�����Ч��ʬ
		clearZombie();

		//ˢ����ʾ
		map.refresh();//�ݵص�ÿ������
		printBullet();//�ӵ�

		//�Ʒ��߼�
		calScore();

		//�·�������Ϣ�������ʾ
		helpInfo();

		Sleep(SLEEP_TIME);
	}

}



void Game::addBullet(Bullet * p)
{
	bullets.push_back(p);
}


void Game::moveBullet()
{
	//ȫ��������ִ���ƶ�
	for (auto& var : bullets) {
		var->move(map);
	}
	//ɾ����Ч���ӵ�
	for (auto itList = bullets.begin(); itList != bullets.end(); )
	{
		if ((*itList)->hit)
		{
			delete (*itList);
			itList = bullets.erase(itList);
		}
		else
			itList++;
	}
}

void Game::printBullet()
{
	//ȫ��������ִ�����
	for (auto& var : bullets) {
		var->paint();
	}
}

void Game::addZombie(int x, int y, int type)
{
	if (x<0 || x>GRID_NUM_X || y<0 || y>GRID_NUM_Y - 1) return;
	Zombie* newZombie = nullptr;
	switch (type)
	{
	case ZOMBIE:
		newZombie = new Zombie();
		break;
	case CONEHEAD_ZOMBIE:
		newZombie = new Conehead_Zombie();
		break;
	case BUCKET_ZOMBIE:
		newZombie = new Bucket_Zombie();
		break;
	case FLAG_ZOMBIE:
		newZombie = new Flag_Zombie();
		break;
	case FOOTBALL_ZOMBIE:
		newZombie = new Football_Zombie();
		break;
	case DOOR_ZOMBIE:
		newZombie = new Door_Zombie();
		break;
	case NEWSPAPER_ZOMBIE:
		newZombie = new Newspaper_Zombie();
		break;
	case POLE_ZOMBIE:
		newZombie = new Pole_Zombie();
		break;
	case DANCING_ZOMBIE:
		newZombie = new Dancing_Zombie();
		break;
	case BACKUP_DANCER:
		newZombie = new Backup_Dancer();
		break;
	case BOX_ZOMBIE:
		newZombie = new Box_Zombie();
		break;
	
	
	default:
		break;
	}
	if (newZombie != nullptr) {
		newZombie->setXY(x, y);
		map.grid[x][y].addZombie(newZombie);
		zombies.push_back(newZombie);
	}
}

void Game::makeZombies()
{
	make_counter++;
	if (make_counter >= make_speed) {
		//ҡ�콩ʬ���ȳ���
		addZombie(GRID_NUM_X, RANDOM(GRID_NUM_Y), FLAG_ZOMBIE);
		//�Ѷ���������ӣ�����Խ�ߣ���ʬ�����ٶ�Խ��
		for (int i = 0; i <= score / 2000; i++) {
			int type = RANDOM(ZOMBIE_TYPE_MAX - 2); //���衢ҡ�콩ʬ�����ˢ��
			int y = RANDOM(GRID_NUM_Y);
			addZombie(GRID_NUM_X, y, type);
		}
		make_counter = 0;
	}
}

bool Game::moveZombie()
{
	//ȫ��������ִ���ƶ�
	for (auto& var : zombies) {
		if (var->move(map))
			return true;
		//���ֽ�ʬ���ڵ�����Ч��
		var->go(*this);
	}
	return false;
}

void Game::clearZombie()
{
	//ɾ��Ѫ��Ϊ��Ľ�ʬ
	for (auto itList = zombies.begin(); itList != zombies.end(); )
	{
		if ((*itList)->HP <= 0)
		{
			//��ɱ�Ʒ�
			score += (*itList)->score;
			map.grid[(*itList)->x][(*itList)->y].delZombie(*itList);
			delete (*itList);
			itList = zombies.erase(itList);
		}
		else {
			//����Ƿ�챻����
			if ((*itList)->x == 0) {
				//���CHEATING��Ϣ
				Goto_XY(2 + 10, STORE_UP_BOUND + 1);
				PrintWithColor("��CHEATING������'+'�ţ�����������ˢ��ֲ����ȴʱ��", HELP_COLOR);
			}
			itList++;
		}
	}
}

Game::~Game()
{
	for (auto& var : bullets) {
		delete var;
	}
	for (auto& var : zombies) {
		delete var;
	}
	SetColor(DEFAULT_COLOR);
}
