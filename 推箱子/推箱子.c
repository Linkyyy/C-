#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "������.h"

/*��Ϸ���˼·
1.���һ�ŵ�ͼ
2.��ʼ����Ϸ����(InitDate):�˵ĳ�λ��X,Y ��ͼ�е�������(�ж��Ƿ������Ϸ)
3.���Ƶ�ͼ(ShowUI):
4.��ʼ��Ϸ(Playgame):ͨ�����̿��Ƶ��ú������жϸı��ͼԪ��,Ȼ�����»��Ƶ�ͼ
5.���ڹؿ���� �������
*/

int map[High][Wide] ;
int X;
int Y;
int boxs=0;
int degree = 1;

int main()
{
	//ȥ������̨���
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
	//ѡ���ͼ
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
		printf("��ϲ�㣡ȫ��ͨ�أ�\n");
		return 0;
	}
	printf("��Ϸ������...\n");*/
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
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			case 4:
				printf("��");
				break;
			case 5:
				printf("��");
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
		printf("��ϲ��ȫ��ͨ�أ�\n");
	}
	else
	{
	printf("��ɹؿ�\n");
	printf("��N������һ�أ��������˳�\n");

	}

}

void Move_up()
{

	int uX, uY;
	uX = X;
	uY = Y - 1;

	//����Ϸ�Ϊǽ,�����ﲻ��
	if (map[uY][uX] == 1)
	{
		return;
	}
	//����Ϸ�Ϊ���������,�����ﲻ��
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

	//����·�Ϊǽ,�����ﲻ��
	if (map[uY][uX] == 1)
	{
		return;
	}
	//����·�Ϊ���������,�����ﲻ��
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

	//������Ϊǽ,�����ﲻ��
	if (map[uY][uX] == 1)
	{
		return;
	}
	//������Ϊ���������,�����ﲻ��
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

	//����ұ�Ϊǽ,�����ﲻ��
	if (map[uY][uX] == 1)
	{
		return;
	}
	//����ұ�Ϊ���������,�����ﲻ��
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
