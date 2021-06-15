
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "����˹����.h"
#define PATH "D:/Info.txt"

/*��Ϸ˼·:
1.����25*15��Ϸ���棬����5*15Ϊ����������
2.����7�ֻ������������λ��(��ά����),������7�ַ�����β���λ��ƫ�Ƶ�����(��ά����)
3.Init����,����������������;����:��������ķ���int Picture,����״̬int Shape,�ƶ�����λ�ü�¼int Graph[][],����ָ��char key
4.ShowUI����,�涨0Ϊ��λ"  ",1Ϊ�����ƶ�����"��",2Ϊ�Ѿ���ط���"��",3Ϊ��ǽ��4Ϊ��ǽ"|"
5.Playgame��
a.Move����,�ж������Ƿ�Ϊ�߽�,�Ƿ�Ϊ�Ѿ���ɷ���
b.Down����,��������
c.Change����,�ı�ͼ��״̬,�ж������Ƿ�Ϊ�߽�
d.IsbottomTop����,�ж��Ƿ񵽵ף�
e.New����,�����µķ���
f.Clear����,����ͬһ�еķ���
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
	//ȥ������̨���
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
		if (_kbhit())//�ж��Ƿ��м�������
		{
			key = _getch();//����ʾ��������
		}//��Ҫinclude <conio.h>
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

	printf("��Ϸ����");

	coord.X = 10;
	coord.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("���շ���:%d", Score);
	if (Score > MaxScore)
	{
		MaxScore = Score;
	}
	fwrite(&MaxScore, 4, 1, fp2);
	coord.X = 10;
	coord.Y = 12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("��ʷ��߷���:%d", MaxScore);
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
			case 1:printf("��"); break;
			case 2:printf("��"); break;
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
	//�ƶ����λ��
	COORD coord;
	coord.X = 30 ;
	coord.Y = 9 ;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	printf("��ʷ��߷�:%d", MaxScore);

	coord.X = 30;
	coord.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("��ǰ����:%d\n", Score);
}
