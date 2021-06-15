
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "俄罗斯方块.h"
#define PATH "D:/Info.txt"

/*游戏思路:
1.建立25*15游戏界面，上面5*15为方块生成区
2.建立7种基本方块的生成位置(三维数组),建立由7种方块变形产生位置偏移的数组(四维数组)
3.Init函数,随机数生成随机方块;变量:随机产生的方块int Picture,方块状态int Shape,移动方块位置记录int Graph[][],键盘指令char key
4.ShowUI函数,规定0为空位"  ",1为正在移动方块"■",2为已经落地方块"□",3为底墙，4为边墙"|"
5.Playgame：
a.Move函数,判断左右是否为边界,是否为已经完成方块
b.Down函数,方块下落
c.Change函数,改变图形状态,判断左右是否为边界
d.IsbottomTop函数,判断是否到底；
e.New函数,产生新的方块
f.Clear函数,消除同一行的方块
*/


int main()
{
	FILE* fp1 = fopen(PATH, "rb");
	if (!fp1)
	{
		FILE* fp2 = fopen(PATH, "wb");
		fwrite(&MaxScore, 4, 1, fp2);
	}
	fread(&MaxScore, sizeof(int), 1, fp1);
	//去除控制台光标
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	key = 'x';
	srand((unsigned int)time(NULL));
	Init();
	Playgame();


	getchar();
	fclose(fp1);
}

void Playgame()
{
	while (1)
	{
		Speed = 400;
		system("cls");
		Clear();
		if (IsbottomTop() == 1) New();
		else if (IsbottomTop() == 0)
		{
			End();
			break;
		}
		if (_kbhit())//判断是否有键盘输入
		{
			key = _getch();//不显示键盘输入
		}//需要include <conio.h>
		if (key == 'w')Change();
		else if (key == 's') Speed = 10;

		else Move(key);

		key = 'x';
		Down();
		Clear();

		ShowUI();
		ShowScore();
		Sleep(Speed);
	}
}
void End()
{
	FILE* fp2 = fopen(PATH, "wb");
	COORD coord;
	coord.X = 10;
	coord.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	printf("游戏结束");

	coord.X = 10;
	coord.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("最终分数:%d", Score);
	if (Score > MaxScore)
	{
		MaxScore = Score;
	}
	fwrite(&MaxScore, 4, 1, fp2);
	coord.X = 10;
	coord.Y = 12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("历史最高分数:%d", MaxScore);
	fclose(fp2);
}
void Init()
{
	Picture = rand() % 6 ;
	Shape = -1;
	for (int i = 0; i < 4; i++)
	{
		Graph[i][1] = InitP[Picture][i][0];
		Graph[i][0] = InitP[Picture][i][1];
	}
	for (int i = 0; i < 4; i++)
	{
		map[Graph[i][1]][Graph[i][0]] = 1;
	}
	ShowUI();
}

void ShowUI()
{
	for (int i = 5; i < High; i++)
	{
		for (int j = 0; j < Wide; j++)
		{
			switch (map[i][j])
			{
			case 0:printf("  "); break;
			case 1:printf("■"); break;
			case 2:printf("■"); break;
			case 3:printf("__"); break;
			case 4:printf("|"); break;
			}
		}
		printf("\n");
	}
}



void Move(char key)
{
	if (key == 'a' || key == 'A')
	{
		if (Graph[0][0] - 1 != -1 && Graph[1][0] - 1 != -1 && Graph[2][0] - 1 != -1 && Graph[3][0] - 1 != -1)
		{
			if (map[Graph[0][1]][Graph[0][0] - 1] != 2 && map[Graph[1][1]][Graph[1][0] - 1] != 2 && map[Graph[2][1]][Graph[2][0] - 1] != 2 && map[Graph[3][1]][Graph[3][0] - 1] != 2)
			{
		for (int i = 0; i < 4; i++)
		{
			map[Graph[i][1]][Graph[i][0]] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			Graph[i][0] = Graph[i][0] - 1;
		}
		for (int i = 0; i < 4; i++)
		{
			map[Graph[i][1]][Graph[i][0]] = 1;
		}
			}
		}
	}
	else if (key == 'd' || key == 'D')
	{
		if (Graph[0][0] + 1 != Wide-1 && Graph[1][0] + 1 != Wide-1 && Graph[2][0] + 1 != Wide-1 && Graph[3][0] + 1 != Wide-1)
		{
			if (map[Graph[0][1]][Graph[0][0] + 1] != 2 && map[Graph[1][1]][Graph[1][0] + 1] != 2 && map[Graph[2][1]][Graph[2][0] + 1] != 2 && map[Graph[3][1]][Graph[3][0] + 1] != 2)
			{

		for (int i = 0; i < 4; i++)
		{
			map[Graph[i][1]][Graph[i][0]] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			Graph[i][0] = Graph[i][0] + 1;
		}
		for (int i = 0; i < 4; i++)
		{
			map[Graph[i][1]][Graph[i][0]] = 1;
		}
			}
		}
	}
}

void Down()
{
	for (int i = 0; i < 4; i++)
	{
		map[Graph[i][1]][Graph[i][0]] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		Graph[i][1] = Graph[i][1] + 1;
	}
	for (int i = 0; i < 4; i++)
	{
		map[Graph[i][1]][Graph[i][0]] = 1;
	}
}

void Change()
{
	Shape++;
	Shape = Shape % 4;
	for (int i = 0; i < 4; i++)
	{
		map[Graph[i][1]][Graph[i][0]] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		Graph[i][0] += ChangeP[Picture][Shape][i][1];
		Graph[i][1] += ChangeP[Picture][Shape][i][0];
	}
	for (int i = 0; i < 4; i++)
	{
		map[Graph[i][1]][Graph[i][0]] = 1;
	}

}

int IsbottomTop()
{
	for (int i = 0; i < 4; i++)
	{
		if (map[Graph[i][1]+1][Graph[i][0]] == 2 || map[Graph[i][1]+1][Graph[i][0]] == 3)
		{
			for (int i = 0; i < 4; i++)
			{
			map[Graph[i][1]][Graph[i][0]] = 2;
			if (Graph[0][1] <= 5 || Graph[1][1] <= 5 || Graph[2][1] <= 5 || Graph[3][1] <= 5)
			{
				return 0;
			}
			}
			return 1;
		}
	}
}


void New()
{
	Picture = rand() % 6 + 1;
	Shape = -1;
	for (int i = 0; i < 4; i++)
	{
		Graph[i][1] = InitP[Picture][i][0];
		Graph[i][0] = InitP[Picture][i][1];
	}
	for (int i = 0; i < 4; i++)
	{
		map[Graph[i][1]][Graph[i][0]] = 1;
	}
}

void Clear()
{
	for (int i = 0; i < High; i++)
	{
		if (map[i][0] == 2 && map[i][1] == 2 && map[i][2] == 2 && map[i][3] == 2 && map[i][4] == 2 && map[i][5] == 2 && map[i][6] == 2 && map[i][7] == 2 && map[i][8] == 2 && map[i][9] == 2 && map[i][10] == 2 && map[i][11] == 2 && map[i][12] == 2 && map[i][13] == 2)
		{
			for (int k = i; k >5; k--)
			{
				for (int j = 0; j < 14; j++)
				{
				map[k][j]=map[k-1][j];
				}
			}
				Score+=10;
		}
	}
}

void ShowScore()
{
	//移动光标位置
	COORD coord;
	coord.X = 30 ;
	coord.Y = 9 ;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	printf("历史最高分:%d", MaxScore);

	coord.X = 30;
	coord.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("当前分数:%d\n", Score);
}
