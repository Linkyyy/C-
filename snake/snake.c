#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "snake.h"
#include <conio.h>

void InitFood()
{
	Food[0] = rand() % Wide;
	Food[1] = rand() % High;

}

void InitSnake()
{
	snake.size = 3;
	snake.body[0].X = Wide / 2;
	snake.body[1].X = Wide / 2;
	snake.body[2].X = Wide / 2;
	snake.body[0].Y = High / 2;
	snake.body[1].Y = High / 2 - 1;
	snake.body[2].Y = High / 2 - 2;
}

void showUI()
{
	//清除蛇尾位置
	COORD coord;
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('  ');
	
	for (int i = 0; i < snake.size;i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		//移动光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 0)
		{
			printf("◆");
		}
		else
		{
			printf("●");
		}

	}
	coord.X = Food[0];
	coord.Y = Food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("★");

}

void Playgame()
{
	//初始化速度
	char key = 'D';
	//平衡误差
	unsigned int sp = 300;
	unsigned int sp1 = 150;
	unsigned int sp2 = 150;
	

	
	while (snake.body[0].X >=0 && snake.body[0].X<=Wide && snake.body[0].Y>=0 && snake.body[0].Y<=High)
	{

		//显示分数
		COORD coord;
		coord.X = Wide / 2 - 5;
		coord.Y = High + 5;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printf("当前分数:%d", score);
		
		//更新界面
		showUI();
		
		//蛇尾位置记录
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;
		
     
		if (_kbhit())//判断是否有键盘输入
		{
			key = _getch();//不显示键盘输入
		}//需要include <conio.h>
		
		//判断蛇速度
		if (score >= 50)
		{
			sp1 = 100;
			sp2 = 100;
		}
		else if (score >= 100)
		{
			sp1 = 50;
			sp2 = 50;
		}
		else if (score >= 200)
		{
			sp1 = 30;
			sp2 = 30;
		}
			
		else
		{
			sp1 = 150;
			sp2 = 150;
		}

		//方向控制
		switch (key)
		{
		case 'd':case'D':dx = 2; dy = 0; sp=sp1; break;
		case 'a':case'A':dx = -2; dy = 0; sp=sp1; break;
		case 'w':case'W':dx = 0; dy = -1; sp=sp2; break;
		case 's':case'S':dx = 0; dy = 1; sp=sp2; break;
		}

		
			

		//蛇是否和自身碰撞
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.body[i].X == snake.body[0].X && snake.body[i].Y == snake.body[0].Y)
			{
				return;//结束游戏
			}
		}

		//蛇和食物碰撞
		if (snake.body[0].X == Food[0] && snake.body[0].Y == Food[1])
		{
			//随机新食物
			InitFood();
			//蛇身体增长
			snake.size++;
			//分数增长
			score += 10;
			//关卡 速度 障碍物
		}
		else if (snake.body[0].X == Food[0] + 1 && snake.body[0].Y == Food[1])
		{
			//随机新食物
			InitFood();
			//蛇身体增长
			snake.size++;
			//分数增长
			score += 10;
			//关卡 速度 障碍物
		}


		//蛇位置更新  **
		for (int i = snake.size-1; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += dx;
		snake.body[0].Y += dy;
		Sleep(sp);
		//system("cls");
		
	}
}

void InitWall()
{
	for (int i = 0; i <= Wide; i++)
	{
		COORD coord;
		coord.X = i;
		coord.Y = High+1;
		//移动光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		putchar('=');
	}
	for (int i = 0; i <= High+1; i++)
	{
		COORD coord;
		coord.X = Wide+2;
		coord.Y = i;
		//移动光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		putchar('=');
	}


	
	/*for (int i = 0; i <= High; i++)
	{
		for (int j = 0; j <= Wide; j++)
		{
			if (i == High)
			{
				putchar('=');
			}
			else if (j == Wide)
			{
				printf("‖");
			}
			else
			{
				putchar(' ');
			}
			
		}
		putchar('\n');
	}*/
}

int main()
{
	srand((unsigned int)time(NULL));

	char key = 'q';
	//去除控制台光标
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	while(1)
	{
		InitWall();
	
		InitFood();
	
		InitSnake();
	
		showUI();
	
		Playgame();

		COORD coord;
		coord.X = Wide/2-9;
		coord.Y = High/2;
		//移动光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printf("游戏结束");

		coord.X = Wide / 2 - 8;
		coord.Y = High / 2+1;
		//移动光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printf("分数:%d",score);

		coord.X = Wide / 2 - 18;
		coord.Y = High / 2+2;
		//移动光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printf("按s继续游戏，按其他键退出游戏");

		key = _getch();//不显示键盘输入
		if (key == 's')
		{
			score = 0;
			system("cls");
			continue;
		}
		else
		{
			break;
		}

	}

	return 0;


}