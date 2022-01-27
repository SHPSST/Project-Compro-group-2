#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define SCREEN_WIDTH 100 // **
#define SCREEN_HEIGHT 50 // **
#define WIN_HEIGHT 40	 // **

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int DDposx, DDposy;
int baseposx[4];
int baseposy[4];

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder()
{

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		gotoxy(i, 0);
		cout << "±";
		gotoxy(i, SCREEN_HEIGHT);
		cout << "±";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << "±";
		gotoxy(SCREEN_WIDTH, i);
		cout << "±";
	}
	for (int i = 0; i < SCREEN_WIDTH - 2; i++)
	{
		gotoxy(i + 1, WIN_HEIGHT);
		cout << "±";
	}
}

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 10;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

char dookdik[2][6] = {'/', '-', '-', 'o', '\\', ' ', // น้องdookdik  **
					  '|', '_', '_', '_', ' ', '>'};

//     ___
//    (o>o)
// 	  /___\
//	   ll
//
//    dookdik

/*void drawDD(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+6); cout<<dookdik[i][j];
		}
	}
}*/

char control() //เช็คการกดปุ่ม ตอนเล่น
{
	if (kbhit())
	{
		char ch = getch();
		if (ch == 'w')
		{
			return 'w';
		}
		if (ch == 'a')
		{
			return 'a';
		}
		if (ch == 's')
		{
			return 's';
		}
		if (ch == 'd')
		{
			return 'd';
		}
		if (ch == 27)
		{
			return 'x';
		} //ESC
	}
	return '-'; // non
}
void drawDD() //แสดงDD
{
	gotoxy(DDposx, DDposy);
	cout << '*';
}
void eraseDD() //ลบDD
{
	gotoxy(DDposx, DDposy);
	cout << ' ';
}

void genbase(int i, int j) //genbase[i][j]  i=[0-3] , j=[0-3]
{
	baseposx[i] = (i + 1) * 20 - rand() % 8; // **
	baseposy[j] = (j + 1) * 8 + rand() % 4;	 // **
}

void drawbase(int i, int j) //แสดงDD
{
	gotoxy(baseposx[i], baseposy[j]);
	cout << "==========";
}
void erasebase(int i, int j) //ลบDD
{
	gotoxy(baseposx[i], baseposy[j]);
	cout << "          ";
}

void play()
{
	double fps = 30, ptime = time(0) - 2;
	int countfps = 0;

	DDposx = 50;
	DDposy = 40; //ตำแหน่ง X Y  เริ่มต้น( Y-G )( บนน้อย , ล่างมาก )  **

	int dx;		//ตำแหน่ง X ในอนาคต
	int vx = 2; //ความเร็ว X  **

	double dy = DDposy; //ตำแหน่ง Y ในอนาคต
	double G = 13;		//ความสูงที่กระโดดได้  **
	double vy = -G;		//ความเร็ว Y
	int slow = 5;		//gravity น้อย=ตกเร็ว  **

	for (int i = 0; i < 4; i++)
	{ //genbase 4x4
		for (int j = 0; j < 4; j++)
		{
			genbase(i, j);
		}
	}

	while (1)
	{
		char CT = control();
		if (CT == 'x')
		{
			break;
		} //exit ( esc )
		if (CT == 'w')
		{
		}
		if (CT == 's')
		{
		}
		if (CT == 'a')
		{
			dx = -vx;
		}
		if (CT == 'd')
		{
			dx = vx;
		}

		gotoxy(70, 45);
		cout << " vy = " << vy << "  ";
		gotoxy(70, 46);
		cout << " dy= " << dy << "  ";

		if (vy > 0)
		{
			dy += vy / slow;
			vy++;
			if (vy == G)
				vy = -G + 1;
		}
		if (vy < 0)
		{
			dy += vy / slow;
			vy++;
			if (vy == 0)
				vy = 1;
		}

		DDposx += dx;
		DDposy = dy;

		if (DDposx < 2)
		{
			DDposx = SCREEN_WIDTH - 2;
		}
		if (DDposx > SCREEN_WIDTH - 2)
		{
			DDposx = 2;
		} //ชนขอบ X
		if (DDposy < 1)
		{
			DDposy = 1;
		}
		if (DDposy > WIN_HEIGHT - 1)
		{
			DDposy = WIN_HEIGHT - 1;
		} //ชนขอบ Y

		gotoxy(40, 45);
		cout << "  CT = " << CT; //Show data ปุ่มกด wasd
		gotoxy(50, 45);
		cout << "  X = " << DDposx << " "; //Show data posX
		gotoxy(60, 45);
		cout << "  Y = " << DDposy << " "; //Show data posY
		gotoxy(10, 45);
		cout << "  FPS = "; //Show data FPS

		if (time(0) - ptime == 2)
		{
			ptime = time(0);
			gotoxy(18, 45);
			fps = countfps / 2;
			cout << (fps) << "   ";
			countfps = 0;
		} //update data FPS every 2sec
		else
		{
			countfps++;
		}

		{ //draw
			drawDD();
			for (int i = 0; i < 4; i++)
			{ // drawbase
				for (int j = 0; j < 4; j++)
				{
					drawbase(i, j);
				}
			}
		}
		Sleep(20);
		{ //erase
			eraseDD();
			for (int i = 0; i < 4; i++)
			{ //erasebase
				for (int j = 0; j < 4; j++)
				{
					erasebase(i, j);
				}
			}
		}
	}
}

int main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do
	{
		system("cls");
		drawBorder();
		gotoxy(10, 5);
		cout << " -------------------------- ";
		gotoxy(10, 6);
		cout << " |      test.exe       | ";
		gotoxy(10, 7);
		cout << " --------------------------";
		gotoxy(10, 9);
		cout << "1. Start Game";
		gotoxy(10, 10);
		cout << "2. Instructions";
		gotoxy(10, 11);
		cout << "3. Quit";
		gotoxy(10, 13);
		cout << "Select option: ";

		char op = getche();
		if (op == '1')
		{
			system("cls");
			drawBorder();
			play();
		}
		else if (op == '2')
		{
			drawDD();
			getche();
		}
		else if (op == '3')
			exit(0);

	} while (1);
}