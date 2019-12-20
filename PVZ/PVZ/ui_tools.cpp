#include<cstdio>
#include<iostream>

#include "ui_tools.h"

//设置光标位置
void Goto_XY(const int x, const int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//隐藏光标
void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
}

//设置窗口大小
void SetWindowSize(int cols, int lines)
{
	system("title \"植物大战僵尸（控制台版）- Plants vs. Zombies  | By NJU-Tang\"");//设置窗口标题
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
	system(cmd); //设置窗口宽度和高度
}

//设置文本颜色
void SetColor(int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

// 带颜色的文本输出，默认为黑底白字
void PrintWithColor(const string & str, int colorID)
{
	SetColor(colorID);
	cout << str;
	SetColor(DEFAULT_COLOR); //输出结束后设置回默认色
}

void PrintWithColor(int num, int colorID)
{
	SetColor(colorID);
	cout << num;
	SetColor(DEFAULT_COLOR); //输出结束后设置回默认色
}
