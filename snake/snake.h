#define High 20
#define Wide 60


struct BODY
{
	int X;
	int Y;
};
struct SNAKE
{
	int size;
	struct BODY body[High*Wide];
}snake;

int Food[2];//0表示x,1表示y
int score=0;
int dx = 0;
int dy = 0;
int lx = 0;
int ly = 0;


void InitFood();
void InitSnake();
void showUI();
void Playgame();
void InitWall();



