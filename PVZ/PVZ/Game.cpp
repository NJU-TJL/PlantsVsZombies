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
	//键盘按键识别
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
			case 72://上
				if (y > 0)
					y--;
				break;
			case 80://下
				if (y < GRID_NUM_Y - 1)
					y++;
				break;
			case 75://左
				if (x > 0)
					x--;
				break;
			case 77://右
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
			//这里不用break，接下来，关闭焦点退出
		case 27://ESC
			closeFocus();
			break;
		//空格键暂停
		case ' ':
			pause();
			break;

		case '+'://金手指：加钱！（便于测试）
			store.addSun(1000);
		case '*'://金手指：瞬间完成所有冷却（便于测试）
			store.renew(); break;

		default:break;
		}
	}
	//按键识别结束
}

void Game::shopping()
{
	//键盘按键识别
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
			case 72://上
				if (y > 0)
					y--;
				break;
			case 80://下
				if (y < GRID_NUM_Y - 1)
					y++;
				break;
			case 75://左
				if (x > 0)
					x--;
				break;
			case 77://右
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
			if (store.pay(planting_type, x, y, map)) { //如果购买成功
				store.plants[planting_type].setUnSelect();
				closeFocus();
			}
			break;
		//空格键暂停
		case ' ':
			pause();
			break;

		case '+'://金手指：加钱！（便于测试）
			store.addSun(1000);
		case '*'://金手指：瞬间完成所有冷却（便于测试）
			store.renew(); break;
		
		/*购买植物的按键识别*/
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
	//按键识别结束
}

void Game::delPlant(int ix, int iy)
{
	if (ix<0 || ix>GRID_NUM_X || iy<0 || iy>GRID_NUM_Y - 1) return;
	map.grid[ix][iy].delPlant();
}

void Game::refreshScore()
{
	//先清空
	Goto_XY(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
	string str(15, ' ');
	cout << str;
	//输出得分
	Goto_XY(RIGHT_LINE_X + 4, STORE_UP_BOUND + 1);
	cout << "[分数：" << score<<"]";
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
		//清空
		string str(WINDOWS_WIDTH, ' ');
		Goto_XY(0, HELP_INFO_Y);
		cout << str;
		Goto_XY(0, HELP_INFO_Y);
		if (state == NORMAL) {
			PrintWithColor(" <游戏中> ", STATE_COLOR);
			PrintWithColor(" 种植：\"1-9\"数字键、\"a-c\"键 | 铲除：\"x\"键 | 暂停：空格键 （不区分大小写）", HELP_COLOR);
		}
		else if (state == STORE) {
			PrintWithColor(" <种植> ", STATE_COLOR);
			PrintWithColor(" 选择：\"1-9\"数字键、\"a-c\"键 | 确认：回车键 | 返回：Esc键 | 暂停：空格键", HELP_COLOR);
		}
		else if (state == SHOVEL) {
			PrintWithColor(" <铲除> ", STATE_COLOR);
			PrintWithColor(" 确认：回车键 | 返回：Esc键 | 暂停：空格键", HELP_COLOR);
		}
		else if (state == PAUSE) {
			PrintWithColor(" <暂停中> ", STATE_COLOR);
			PrintWithColor(" 退出暂停：空格键", HELP_COLOR);
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
			case ' '://空格结束暂停
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
	PrintWithColor("【游戏结束】", STATE_COLOR);
	//输出分数
	Goto_XY(WINDOWS_WIDTH / 2 - 8, WINDOWS_HEIGHT / 2 + 2);
	cout << "你的分数是： " << score << endl;
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

	//16秒产生一次僵尸
	make_speed = 160 * 1000 / 10 / SLEEP_TIME;
	make_counter = 0;
}

void Game::loop()
{	
	//TEST:（一开始就生成特定的僵尸，用于调试）
	//addZombie(GRID_NUM_X, 0, POLE_ZOMBIE);	
	//addZombie(GRID_NUM_X, 2, DANCING_ZOMBIE);
	addZombie(GRID_NUM_X, 2, BOX_ZOMBIE);
	//addZombie(GRID_NUM_X, 2, NEWSPAPER_ZOMBIE);
	//addZombie(GRID_NUM_X, 2, FLAG_ZOMBIE);
	//addZombie(GRID_NUM_X, 2, ZOMBIE);

	while (true) {

		if (state == NORMAL) {
			//键盘按键识别
			char ch;
			if (_kbhit())
			{
				ch = _getch();
				switch (ch)
				{
				case 'a':case 'A':
					planting_type = 9;
					store.plants[planting_type].setSelect();
					//开启商店选择
					state = STORE; refreshHelpInfo = true;
					openFocus();
					break;
				case 'b':case 'B':
					planting_type = 10;
					store.plants[planting_type].setSelect();
					//开启商店选择
					state = STORE; refreshHelpInfo = true;
					openFocus();
					break;
				case 'c':case 'C':
					planting_type = 11;
					store.plants[planting_type].setSelect();
					//开启商店选择
					state = STORE; refreshHelpInfo = true;
					openFocus();
					break;
				//按x/X进入铲除植物
				case 'x':case 'X':
					state = SHOVEL; refreshHelpInfo = true;
					openFocus();
					break;
				//空格键暂停
				case ' ':
					pause();
					break;

				case '+'://金手指：加钱！（便于测试）
					store.addSun(1000);
				case '*'://金手指：瞬间完成所有冷却（便于测试）
					store.renew(); break;

				default:
					//直接按下数字键的情况
					if (ch >= '1'&&ch <= '9') {
						planting_type = ch - '0' - 1;
						state = STORE; refreshHelpInfo = true;
						openFocus();
						//开启商店选择
						store.plants[planting_type].setSelect();
						break;
					}
				}
			}
			//按键识别结束
		}
		else if (state == STORE) {
			shopping();
		}
		else if (state == SHOVEL) {
			weeding();
		}

		//执行僵尸产生逻辑
		makeZombies();

		//遍历：植物
		if (!map.travGrid(*this)) {
			break;
		}
		
		//僵尸队列 - 行动
		if (moveZombie()) {
			gameover();//僵尸攻破，游戏结束
			break;
		}
		
		//商店运行
		store.run();

		//子弹移动
		moveBullet();
		
		//清除无效僵尸
		clearZombie();

		//刷新显示
		map.refresh();//草地的每个格子
		printBullet();//子弹

		//计分逻辑
		calScore();

		//下方帮助信息的输出显示
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
	//全部遍历，执行移动
	for (auto& var : bullets) {
		var->move(map);
	}
	//删除无效的子弹
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
	//全部遍历，执行输出
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
		//摇旗僵尸首先出现
		addZombie(GRID_NUM_X, RANDOM(GRID_NUM_Y), FLAG_ZOMBIE);
		//难度随分数增加，分数越高，僵尸产生速度越快
		for (int i = 0; i <= score / 2000; i++) {
			int type = RANDOM(ZOMBIE_TYPE_MAX - 2); //伴舞、摇旗僵尸不随机刷出
			int y = RANDOM(GRID_NUM_Y);
			addZombie(GRID_NUM_X, y, type);
		}
		make_counter = 0;
	}
}

bool Game::moveZombie()
{
	//全部遍历，执行移动
	for (auto& var : zombies) {
		if (var->move(map))
			return true;
		//部分僵尸存在的特殊效果
		var->go(*this);
	}
	return false;
}

void Game::clearZombie()
{
	//删除血量为零的僵尸
	for (auto itList = zombies.begin(); itList != zombies.end(); )
	{
		if ((*itList)->HP <= 0)
		{
			//击杀计分
			score += (*itList)->score;
			map.grid[(*itList)->x][(*itList)->y].delZombie(*itList);
			delete (*itList);
			itList = zombies.erase(itList);
		}
		else {
			//检测是否快被攻破
			if ((*itList)->x == 0) {
				//输出CHEATING信息
				Goto_XY(2 + 10, STORE_UP_BOUND + 1);
				PrintWithColor("【CHEATING】输入'+'号：增加阳光且刷新植物冷却时间", HELP_COLOR);
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
