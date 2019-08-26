#pragma once

#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>

using namespace std;

class ScreenC
{
public:
	bool isScreenBuilt;
	SHORT rowsOfConsole , colsOfConsole;
	SHORT PLayArea_RightLimit;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ScreenC();
	void ClearScreen();
};

class Item : public ScreenC
{
public:
	int m_X;
	int m_Y;
	enum Shape { SQUARE = 0, LSHAPE = 1 ,ISHAPE = 2 };
	int X[4];
	int Y[4];
	int orientation_type;
	int current_Shape;
	string orientation[4];
	int orientationHeight[4];
	int orientationBreadth[4];
	bool isDown;
	void redef(int Shape);
	void getMap();
	Item();
	Item(int Shape);
};


class PlayArena :public ScreenC
{
public:
	vector<string> play_arena;
	int GameInfoPosX;
	int GameInfoPosY;
	int maxStackHeight;
	int score;
	string insert_Blank_Row;
	vector<int> stackHeight;
	vector<string> dump;
	PlayArena();
};
