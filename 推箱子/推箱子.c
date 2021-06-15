#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "推箱子.h"

/*游戏设计思路
1.设计一张地图
2.初始化游戏数据(InitDate):人的初位置X,Y 地图中的箱子数(判断是否继续游戏)
3.绘制地图(ShowUI):
4.开始游戏(Playgame):通过键盘控制调用函数，判断改变地图元素,然后重新绘制地图
5.后期关卡设计 分数设计
*/

int map[High][Wide] ;
int X;
int Y;
int boxs=0;
int degree = 1;

int main()
{
	//去除控制台光标
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	InitDate();
	ShowUI();
	Playgame();
	while (1)
	{
		char key = _getch();
		if (key == 'n')
		{
			InitDate();
			ShowUI();
			Playgame();
		}
		else
		{
			break;
		}
		
	}
	return 0;
}

int InitDate()
{
	//选择地图
	if (degree == 1)
	{
		int map1[High][Wide]= 
		{
			{ 0,0,1,1,1,0,0,0 },
			{ 0,0,1,4,1,0,0,0 },
			{ 0,0,1,0,1,1,1,1 },
			{ 1,1,1,3,0,3,4,1 },
			{ 1,4,0,3,2,1,1,1 },
			{ 1,1,1,1,3,1,0,0 },
			{ 0,0,0,1,4,1,0,0 },
			{ 0,0,0,1,1,1,0,0 }
		};
		memcpy(map, map1, sizeof(map1));

	}
	else if (degree == 2)
	{
		int map2[High][Wide] =
		{
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,1,1,2,0,1,0,0 },
			{ 0,1,4,3,3,1,1,0 },
			{ 0,1,1,0,0,4,1,0 },
			{ 0,0,1,1,1,1,1,0 },
			{ 0,0,0,0,0,0,0,0 }
		};
		memcpy(map, map2, sizeof(map2));
	}
	/*else
	{
		printf("恭喜你！全部通关！\n");
		return 0;
	}
	printf("游戏加载中...\n");*/
	for (int i = 0; i < High; i++)
	{
		for (int j = 0; j < Wide; j++)
		{
			if (map[i][j] == 2)
			{
				X = j, Y = i;
			}
			if (map[i][j]==3)
			{
				boxs++;
			}
		}
	}

}

void ShowUI()
{
	for (int i = 0; i < High; i++)
	{
		for (int j = 0; j < Wide; j++)
		{
			switch (map[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("■");
				break;
			case 2:
				printf("♀");
				break;
			case 3:
				printf("◆");
				break;
			case 4:
				printf("●");
				break;
			case 5:
				printf("★");
				break;
			}
		}
		printf("\n");
	}
}

void Playgame()
{
	while (boxs)
	{
		system("cls");
		ShowUI();

		char key = _getch();

		switch (key)
		{
		case 'W':case 'w': Move_up(); break;
		case 'S':case 's': Move_down(); break;
		case 'A':case 'a': Move_left(); break;
		case 'D':case 'd': Move_right(); break;
		}

    }
	degree++;
	if (degree == 3)
	{
		printf("恭喜你全部通关！\n");
	}
	else
	{
	printf("完成关卡\n");
	printf("按N进入下一关，其他键退出\n");

	}

}

void Move_up()
{

	int uX, uY;
	uX = X;
	uY = Y - 1;

	//如果上方为墙,则人物不动
	if (map[uY][uX] == 1)
	{
		return;
	}
	//如果上方为已完成箱子,则人物不动
	if (map[uY][uX] == 5)
	{
		return;
	}
	if (map[uY][uX] == 3)
	{
		if (map[uY - 1][uX] == 1)
		{
			return;
		}
		if (map[uY - 1][uX] == 4)
		{
			map[uY - 1][uX] = 5;
			map[uY][uX] = 0;
			boxs--;
		}
		else if (map[uY - 1][uX] == 0)
		{
			map[uY - 1][uX] = 3;
		}

	}
	map[Y][X] = 0;
	map[uY][uX] = 2;
	X = X;
	Y = Y - 1;

}

void Move_down()
{
	int uX, uY;
	uX = X;
	uY = Y + 1;

	//如果下方为墙,则人物不动
	if (map[uY][uX] == 1)
	{
		return;
	}
	//如果下方为已完成箱子,则人物不动
	if (map[uY][uX] == 5)
	{
		return;
	}
	if (map[uY][uX] == 3)
	{
		if (map[uY + 1][uX] == 1)
		{
			return;
		}
		if (map[uY + 1][uX] == 4)
		{
			map[uY + 1][uX] = 5;
			map[uY][uX] = 0;
			boxs--;
		}
		else if (map[uY + 1][uX] == 0)
		{
			map[uY + 1][uX] = 3;
		}

	}
	map[Y][X] = 0;
	map[uY][uX] = 2;
	X = X;
	Y = Y + 1;
}

void Move_left()
{
	int uX, uY;
	uX = X-1;
	uY = Y;

	//如果左边为墙,则人物不动
	if (map[uY][uX] == 1)
	{
		return;
	}
	//如果左边为已完成箱子,则人物不动
	if (map[uY][uX] == 5)
	{
		return;
	}
	if (map[uY][uX] == 3)
	{
		if (map[uY][uX-1] == 1)
		{
			return;
		}
		if (map[uY][uX-1] == 4)
		{
			map[uY][uX-1] = 5;
			map[uY][uX] = 0;
			boxs--;
		}
		else if (map[uY][uX-1] == 0)
		{
			map[uY][uX-1] = 3;
		}

	}
	map[Y][X] = 0;
	map[uY][uX] = 2;
	X = X-1;
	Y = Y ;
}

void Move_right()
{
	int uX, uY;
	uX = X + 1;
	uY = Y;

	//如果右边为墙,则人物不动
	if (map[uY][uX] == 1)
	{
		return;
	}
	//如果右边为已完成箱子,则人物不动
	if (map[uY][uX] == 5)
	{
		return;
	}
	if (map[uY][uX] == 3)
	{
		if (map[uY][uX + 1] == 1)
		{
			return;
		}
		if (map[uY][uX + 1] == 4)
		{
			map[uY][uX + 1] = 5;
			map[uY][uX] = 0;
			boxs--;
		}
		else if (map[uY][uX + 1] == 0)
		{
			map[uY][uX + 1] = 3;
		}

	}
	map[Y][X] = 0;
	map[uY][uX] = 2;
	X = X + 1;
	Y = Y;
}
