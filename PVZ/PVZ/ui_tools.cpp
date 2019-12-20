#include<cstdio>
#include<iostream>

#include "ui_tools.h"

//���ù��λ��
void Goto_XY(const int x, const int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//���ع��
void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
}

//���ô��ڴ�С
void SetWindowSize(int cols, int lines)
{
	system("title \"ֲ���ս��ʬ������̨�棩- Plants vs. Zombies  | By NJU-Tang\"");//���ô��ڱ���
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
	system(cmd); //���ô��ڿ�Ⱥ͸߶�
}

//�����ı���ɫ
void SetColor(int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

// ����ɫ���ı������Ĭ��Ϊ�ڵװ���
void PrintWithColor(const string & str, int colorID)
{
	SetColor(colorID);
	cout << str;
	SetColor(DEFAULT_COLOR); //������������û�Ĭ��ɫ
}

void PrintWithColor(int num, int colorID)
{
	SetColor(colorID);
	cout << num;
	SetColor(DEFAULT_COLOR); //������������û�Ĭ��ɫ
}
