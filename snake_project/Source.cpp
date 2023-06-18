#include<iostream>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#include<fstream>
#include<ctime>
#include<string.h>
using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define purple 5
#define BROWN 6
#define GRAY 8
#define LGreen 10
#define LBlue 11
#define Yellow 14
#define white 15
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}


enum DIRECTION { UP, DOWN, LEFT, RIGHT };
struct Position
{
	int ri, ci;
};
struct Snake
{
	Position* ps;
	string pname;
	DIRECTION dir;
	int size;
	char sym;
	int score;
	int UPKEY, DOWNKEY, LEFTKEY, RIGHTKEY;
};
struct Food
{
	Position fpos;
	bool isAlive;
	int score;
	char sym;
};



bool isLegalCoord(Position p, Snake*& S, int NOS)
{
	for (int j = 0; j < NOS; j++)
	{
		for (int i = 0; i < S[j].size; i++)
		{
			if (S[j].ps[i].ri == p.ri && S[j].ps[i].ci == p.ci)
				return false;
		}
	}
	return true;
}
void genFood(Snake*& S, Food& f, int h, int w, int nos)
{
	SetClr(RED);
	bool p = false;
	for (int n = 0; n < nos; n++)
	{
		for (int i = 0; i < h; i++)
		{
			if (f.fpos.ri == 15 && f.fpos.ci == 20 + i)
			{
				p = false;
			}
			if (f.fpos.ri == 15 && f.fpos.ci == 50 + i)
			{
				p = false;
			}
			if (f.fpos.ri == 45 && f.fpos.ci == 20 + i)
			{
				p = false;
			}
			if (f.fpos.ri == 45 && f.fpos.ci == 50 + i)
			{
				p = false;
			}
		}

	}
	p = true;
	do {
		do
		{
			f.fpos.ri = rand() % (h - 2);
			f.fpos.ci = rand() % (w - 2);
		} while (!isLegalCoord(f.fpos, S, nos) && (f.fpos.ri != 0 || f.fpos.ci != 0 || f.fpos.ri != h || f.fpos.ci != w));
	} while (p = false);
	f.isAlive = true;
	f.score = 1;
}
void init(Snake*& Sn, Food& f, int h, int w, int& nos)
{
	gotoRowCol(19, 81);
	SetClr(white);
	cin >> nos;
	Sn[0].ps = new Position[3];

	Sn[0].ps[0].ri = h / 3;
	Sn[0].ps[0].ci = w / 2;

	Sn[0].ps[1].ri = h / 3;
	Sn[0].ps[1].ci = w / 2 - 1;

	Sn[0].ps[2].ri = h / 3;
	Sn[0].ps[2].ci = w / 2 - 2;

	Sn[1].ps = new Position[3];

	Sn[1].ps[0].ri = 3 * (h / 4);
	Sn[1].ps[0].ci = w / 2;

	Sn[1].ps[1].ri = 3 * (h / 4);
	Sn[1].ps[1].ci = w / 2 - 1;

	Sn[1].ps[2].ri = 3 * (h / 4);
	Sn[1].ps[2].ci = w / 2 - 2;

	Sn[2].ps = new Position[3];

	Sn[2].ps[0].ri = h / 2;
	Sn[2].ps[0].ci = w / 4;

	Sn[2].ps[1].ri = h / 2;
	Sn[2].ps[1].ci = w / 4 - 1;

	Sn[2].ps[2].ri = h / 2;
	Sn[2].ps[2].ci = w / 4 - 2;

	Sn[3].ps = new Position[3];

	Sn[3].ps[0].ri = h / 3;
	Sn[3].ps[0].ci = w / 3;

	Sn[3].ps[1].ri = h / 3;
	Sn[3].ps[1].ci = w / 3 - 1;

	Sn[3].ps[2].ri = h / 3;
	Sn[3].ps[2].ci = w / 3 - 2;

	for (int i = 0; i < nos; i++)
	{
		Sn[i].size = 3;
		Sn[i].score = 1;
		Sn[i].sym = -37;
	}
	int i = 0;
	for (int n = 0; n < nos; n++)
	{
		gotoRowCol(40, i + 17);
		SetClr(white);
		cin >> Sn[n].pname;
		i += 40;
	}
	Sn[0].dir = RIGHT;
	Sn[1].dir = UP;
	Sn[2].dir = DOWN;
	Sn[3].dir = RIGHT;
	Sn[0].RIGHTKEY = 77, Sn[0].LEFTKEY = 75, Sn[0].DOWNKEY = 80, Sn[0].UPKEY = 72;
	Sn[1].RIGHTKEY = 100, Sn[1].LEFTKEY = 97, Sn[1].DOWNKEY = 115, Sn[1].UPKEY = 119;
	Sn[2].RIGHTKEY = 104, Sn[2].LEFTKEY = 102, Sn[2].DOWNKEY = 103, Sn[2].UPKEY = 116;
	Sn[3].RIGHTKEY = 108, Sn[3].LEFTKEY = 106, Sn[3].DOWNKEY = 107, Sn[3].UPKEY = 105;
	genFood(Sn, f, h, w, nos);
	f.sym = 'O';
}

void displaySnake1(Snake* S)
{
	for (int i = 0; i < S[0].size; i++)
	{
		if ((S[0].ps[i].ri + S[0].ps[i].ci) % 2 == 0)
		{
			gotoRowCol(S[0].ps[i].ri, S[0].ps[i].ci);
			SetClr(BROWN);
			cout << S[0].sym;
		}
		else
		{
			gotoRowCol(S[0].ps[i].ri, S[0].ps[i].ci);
			SetClr(white);
			cout << S[0].sym;
		}
	}
}
void displaySnake2(Snake* S)
{
	for (int i = 0; i < S[1].size; i++)
	{
		if ((S[1].ps[i].ri + S[1].ps[i].ci) % 2 == 0)
		{
			gotoRowCol(S[1].ps[i].ri, S[1].ps[i].ci);
			SetClr(RED);
			cout << S[1].sym;
		}
		else
		{
			gotoRowCol(S[1].ps[i].ri, S[1].ps[i].ci);
			SetClr(BLUE);
			cout << S[1].sym;
		}
	}
}
void displaySnake3(Snake* S)
{
	for (int i = 0; i < S[2].size; i++)
	{
		if ((S[2].ps[i].ri + S[2].ps[i].ci) % 2 == 0)
		{
			gotoRowCol(S[2].ps[i].ri, S[2].ps[i].ci);
			SetClr(purple);
			cout << S[2].sym;
		}
		else
		{
			gotoRowCol(S[2].ps[i].ri, S[2].ps[i].ci);
			SetClr(LBlue);
			cout << S[2].sym;
		}
	}
}
void displaySnake4(Snake* S)
{
	for (int i = 0; i < S[3].size; i++)
	{
		if ((S[3].ps[i].ri + S[3].ps[i].ci) % 2 == 0)
		{
			gotoRowCol(S[3].ps[i].ri, S[3].ps[i].ci);
			SetClr(GRAY);
			cout << S[3].sym;
		}
		else
		{
			gotoRowCol(S[3].ps[i].ri, S[3].ps[i].ci);
			SetClr(LGreen);
			cout << S[3].sym;
		}
	}
}
void removeSnake(Snake* S, int h, int w, int nos)
{
	for (int j = 0; j < nos; j++)
	{
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < w; c++)
			{
				if (r == 0 || r == h - 1 || c == 0 || c == w - 1)
				{
					gotoRowCol(r, c);
					SetClr(GREEN);
					cout << S[j].sym;
				}
			}
		}
		for (int i = 0; i < S[j].size; i++)
		{
			gotoRowCol(S[j].ps[i].ri, S[j].ps[i].ci);
			cout << " ";
		}
	}
}

void moveSnake(Snake*& S, int h, int w, int nos)
{
	for (int x = 0; x < nos; x++)
	{
		for (int i = S[x].size - 1; i - 1 >= 0; i--)
		{
			S[x].ps[i] = S[x].ps[i - 1];
		}
		switch (S[x].dir)
		{
		case UP:
		{
			S[x].ps[0].ri--;
			if (S[x].ps[0].ri == 0)
			{
				S[x].ps[0].ri = h - 2;
			}
			break;
		}
		case DOWN:
		{
			S[x].ps[0].ri++;
			if (S[x].ps[0].ri == h - 1)
			{
				S[x].ps[0].ri = 1;
			}
			break;
		}
		case LEFT:
		{
			S[x].ps[0].ci--;
			if (S[x].ps[0].ci == 0)
			{
				S[x].ps[0].ci = w - 2;
			}
			break;
		}
		case RIGHT:
		{
			S[x].ps[0].ci++;
			if (S[x].ps[0].ci == w - 1)
			{
				S[x].ps[0].ci = 1;
			}
			break;
		}
		}
	}

}
void changeDirection(Snake*& S, char key, int nos)
{
	for (int i = 0; i < nos; i++)
	{
		if (key == S[i].UPKEY)
		{
			if (S[i].dir != DOWN)
				S[i].dir = UP;

		}
		if (key == S[i].DOWNKEY)
		{
			if (S[i].dir != UP)
				S[i].dir = DOWN;
		}
		if (key == S[i].LEFTKEY)
		{
			if (S[i].dir != RIGHT)
				S[i].dir = LEFT;
		}
		if (key == S[i].RIGHTKEY)
		{
			if (S[i].dir != LEFT)
				S[i].dir = RIGHT;
		}
	}

}


void displayFood(Food f)
{
	gotoRowCol(f.fpos.ri, f.fpos.ci);
	SetClr(RED);
	cout << f.sym;
}
bool foodIsEaten(Snake*& S, Food& f, int nos)
{
	for (int i = 0; i < nos; i++)
	{
		if (S[i].ps[0].ri == f.fpos.ri && S[i].ps[0].ci == f.fpos.ci)
			return true;
	}
	return false;
}
void expandSnake(Snake*& S, int nos, Food f)
{
	if (S[0].ps[0].ri == f.fpos.ri && S[0].ps[0].ci == f.fpos.ci)
	{
		S[0].score++;
		Position* HP = new Position[S[0].size + 1];
		for (int i = 0; i < S[0].size; i++)
		{
			HP[i] = S[0].ps[i];
		}
		HP[S[0].size] = S[0].ps[S[0].size - 1];
		S[0].size++;
		delete[]S[0].ps;
		S[0].ps = HP;
	}
	if (S[1].ps[0].ri == f.fpos.ri && S[1].ps[0].ci == f.fpos.ci)
	{
		S[1].score++;
		Position* HP = new Position[S[1].size + 1];
		for (int i = 0; i < S[1].size; i++)
		{
			HP[i] = S[1].ps[i];
		}
		HP[S[1].size] = S[1].ps[S[1].size - 1];
		S[1].size++;
		delete[]S[1].ps;
		S[1].ps = HP;

	}
	if (S[2].ps[0].ri == f.fpos.ri && S[2].ps[0].ci == f.fpos.ci)
	{
		S[2].score++;
		Position* HP = new Position[S[2].size + 1];
		for (int i = 0; i < S[2].size; i++)
		{
			HP[i] = S[2].ps[i];
		}
		HP[S[2].size] = S[2].ps[S[2].size - 1];
		S[2].size++;
		delete[]S[2].ps;
		S[2].ps = HP;
	}
	if (S[3].ps[0].ri == f.fpos.ri && S[3].ps[0].ci == f.fpos.ci)
	{
		S[3].score++;
		Position* HP = new Position[S[3].size + 1];
		for (int i = 0; i < S[3].size; i++)
		{
			HP[i] = S[3].ps[i];
		}
		HP[S[3].size] = S[3].ps[S[3].size - 1];
		S[3].size++;
		delete[]S[3].ps;
		S[3].ps = HP;
	}
}

void drawBoundry(Position& B, Snake* S, int h, int w, int nos)
{
	for (int i = 0; i < nos; i++)
	{
		gotoRowCol(19 + i * 2, 90);
		SetClr(white);
		cout << "SCORE of " << S[i].pname << ": ";
	}
	if (S[0].score == 1)
	{
		gotoRowCol(20, 106);
		SetClr(white);
		cout << "0";
	}
	if (S[1].score == 1)
	{
		gotoRowCol(22, 106);
		SetClr(white);
		cout << "0";
	}
	if (S[2].score == 1)
	{
		gotoRowCol(24, 106);
		SetClr(white);
		cout << "0";
	}
	if (S[3].score == 1)
	{
		gotoRowCol(26, 106);
		SetClr(white);
		cout << "0";
	}
	for (int r = 0; r < h; r++)
	{
		for (int c = 0; c < w; c++)
		{
			if (r == 0 || r == h - 1 || c == 0 || c == w - 1)
			{
				gotoRowCol(r, c);
				SetClr(GREEN);
				cout << char(-37);
			}
		}
	}
}
void displayScore(Snake*& S, Food f)
{
	if (S[0].ps[0].ri == f.fpos.ri && S[0].ps[0].ci == f.fpos.ci)
	{
		gotoRowCol(20, 106);
		SetClr(white);
		cout << S[0].score;
	}
	else if (S[1].ps[0].ri == f.fpos.ri && S[1].ps[0].ci == f.fpos.ci)
	{
		gotoRowCol(22, 106);
		SetClr(white);
		cout << S[1].score;
	}
	else if (S[2].ps[0].ri == f.fpos.ri && S[2].ps[0].ci == f.fpos.ci)
	{
		gotoRowCol(24, 106);
		SetClr(white);
		cout << S[2].score;
	}
	else if (S[3].ps[0].ri == f.fpos.ri && S[3].ps[0].ci == f.fpos.ci)
	{
		gotoRowCol(26, 106);
		SetClr(white);
		cout << S[3].score;
	}
}
void drawHurdles(int h, char syms)
{
	gotoRowCol(10, 20);
	int l;
	for (int sp = 1; sp <= h; sp++)
		cout << " ";
	cout << syms << endl;
	for (l = 2; l <= h - 1; l++)
	{
		gotoRowCol(10 + l - 1, 20);
		for (int sp = 1; sp <= h - l + 1; sp++)
			cout << " ";
		cout << syms;
		for (int sp = 1; sp <= 2 * l - 2 - 1; sp++)
			cout << " ";
		cout << syms << endl;
	}
	l--;
	cout << endl;
	l--;
	int i = 1;
	while (l >= 1 && i)
	{
		gotoRowCol(30 + i, 20);
		for (int sp = 1; sp <= h - l; sp++)
			cout << " ";
		cout << syms;
		for (int sp = 1; sp <= 2 * l - 1; sp++)
			cout << " ";
		cout << syms;
		l -= 1;
		cout << endl;
		i++;
	}
	gotoRowCol(49, 20);
	for (int sp = 1; sp <= h; sp++)
		cout << " ";
	cout << syms << endl;
}
void game_over(Snake* S, int h, int w, int nos, bool& gm)
{
	gm = false;
	for (int i = 0; i < nos; i++)
	{
		if (S[i].ps[0].ri == h || S[i].ps[0].ri == 1 || S[i].ps[0].ci == w || S[i].ps[0].ci == 1)
		{
			gm = true;
			break;
		}
	}
	for (int i = 1; i < S[0].size; i++)
	{
		if (S[0].ps[i].ri == S[0].ps[0].ri && S[0].ps[i].ci == S[0].ps[0].ci)
		{
			gm = true;
		}
	}
	for (int i = 1; i < S[1].size; i++)
	{
		if (S[1].ps[i].ri == S[1].ps[0].ri && S[1].ps[i].ci == S[1].ps[0].ci)
		{
			gm = true;
		}
	}
	for (int i = 1; i < S[2].size; i++)
	{
		if (S[2].ps[i].ri == S[2].ps[0].ri && S[2].ps[i].ci == S[2].ps[0].ci)
		{
			gm = true;
		}
	}
	for (int i = 1; i < S[3].size; i++)
	{
		if (S[3].ps[i].ri == S[3].ps[0].ri && S[3].ps[i].ci == S[3].ps[0].ci)
		{
			gm = true;
		}
	}
}
bool killOther(Snake* S, int nos)
{
	for (int n = 0; n < nos; n++)
	{
		for (int i = 0; i < nos; i++)
		{
			for (int j = 0; j < S[i].size; j++)
			{
				if (n != i)
				{
					if ((S[n].ps[0].ri == S[i].ps[j].ri && S[n].ps[0].ci == S[i].ps[j].ci))
					{
						return true;
					}
				}

			}
		}
	}

	return false;
}

void letterA1(int l, char sym, int h, int w)
{
	int A1 = l + 2, A2 = l / 2, A3 = A2 + 1;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < A1; j++)
		{
			if (j == A2)
			{
				gotoRowCol(h + i + 1, w + j);
				cout << sym;
				A2--;
			}
			else if ((j > A2) && (j < A3) && (i == l / 4))
			{
				gotoRowCol(h + i + 1, w + j);
				cout << sym;
			}
			else if (j == A3)
			{
				gotoRowCol(h + i + 1, w + j);
				cout << sym;
				A3++;
				break;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterA2(int l, char sym, int h, int w)
{
	int A1 = l + 2, A2 = l / 2, A3 = A2 + 1;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < A1; j++)
		{
			if (j == A2)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
				A2--;
			}
			else if ((j > A2) && (j < A3) && (i == l / 4))
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else if (j == A3)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
				A3++;
				break;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterG(int l, char sym, int h, int w)
{
	int A1 = l / 2;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			if (j == 0 && i != 0 && i != l - 1)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else if ((i == 0 || i == l - 1) && j != 0 && j != l - 1)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else if (i == A1 && j > A1 - 1)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else if (i > A1 && j == l - 1 && i != l - 1)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterN(int l, char sym, int h, int w)
{
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (j == 1 || j == i)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		for (int j = l; j > i; j--)
		{
			cout << " ";
		}
		for (int j = 1; j <= l; j++)
		{
			if (j == l)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
		}
		cout << endl;
	}
}
void letterM(int l, char sym, int h, int w)
{
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (j == 1 || j == i)
			{
				gotoRowCol(h + i - 1, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		for (int j = l; j >= i + 1; j--)
		{
			//gotoRowCol(35 + i - 1, 95 + j);
			cout << " ";
		}
		for (int j = l; j >= i + 1; j--)
		{
			//gotoRowCol(35 + i - 1, 101 + j);
			cout << " ";
		}
		for (int j = 1; j <= i; j++)
		{
			if (j == 1 || j == i)
			{
				//gotoRowCol(35 + i-1, 106 + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterS(int l, char sym, int h, int w)
{
	int S1 = l / 2;
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= l; j++)
		{
			if ((i == 1 && j == 1) || i == S1 && (j == 1 || j == l) || i == l && j == l)
			{
				cout << " ";
			}
			else if ((i == 1 || i == S1 || i == l) || (j == 1 && i <= S1) || j == l && i >= S1)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterE1(int l, char sym, int h, int w)
{
	int E1 = l / 2;
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= E1 + 2; j++)
		{
			if (i == 1 && j == 1)
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else if ((i == 1 || j == 1) || i == l || (i == E1 + 1 && j <= E1))
			{
				gotoRowCol(h + i, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterE2(int l, char sym, int h, int w)
{
	int E1 = l / 2;
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= E1 + 2; j++)
		{
			if (i == 1 && j == 1)
			{
				gotoRowCol(h + i - 1, w + j);
				cout << sym;
			}
			else if ((i == 1 || j == 1) || i == l || (i == E1 + 1 && j <= E1))
			{
				gotoRowCol(h + i - 1, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void letterK(int l, char sym, int h, int w)
{
	int K1 = l, K2 = l / 2;
	for (int i = 0; i <= l; i++)
	{
		for (int j = 0; j <= l; j++)
		{
			if (j == K2 - 1 || j == K1)
			{
				gotoRowCol(h + i + 1, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		if (i - 1 < K2 - 1)
		{
			K1--;
		}
		else
			K1++;
		cout << endl;
	}
}
void letterR(int l, char sym, int h, int w)
{
	int R1 = l / 2, R2 = 1;
	for (int i = 1; i <= R1; i++)
	{
		gotoRowCol(h + i, w);
		cout << sym;
		for (int j = 1; j <= R1 + 2; j++)
		{
			if (i == 1 || i == R1 || (j == R1 + 2 && i <= R1))
			{
				if (!((i == 1 && j == R1 + 2) || (i == R1 && j == R1 + 2)))
				{
					gotoRowCol(h + i, w + j);
					cout << sym;
				}
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	for (int i = 1; i <= R1 + 1; i++)
	{
		gotoRowCol(h + i + R1, w);
		cout << sym;
		for (int j = 1; j <= i; j++)
		{
			if (R2 == j)
			{
				if (i == 1 && j == 1 && j == 2)
				{
					cout << " ";
				}
				//gotoRowCol(h + i, w+j);
				cout << sym; R2++;
				break;
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void letterV(int l, char sym, int h, int w)
{
	int V1 = l * 2;
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (i == j)
			{
				gotoRowCol(h + i + 1, w + j);
				cout << sym;
			}
			else
				cout << " ";
		}
		for (int j = 1; j <= V1 - i * 2; j++)
		{
			cout << " ";
		}
		cout << sym;
		cout << endl;
	}
}
void letterO(int l, char sym, int h, int w)
{
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= l; j++)
		{
			if (j == 1 || j == l || i == 1 || i == l)
			{
				if ((i == 1 && j <= 2) || (i == 1 && j >= l - 1))
				{
					cout << " ";
				}
				else if ((i == l && j <= 2) || (i == l && j >= l - 1))
				{
					cout << " ";
				}
				else
				{
					gotoRowCol(h + i, w + j);
					cout << sym;
				}
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void welcome(int hOfLetter, int h, int w, char sym)
{
	SetClr(Yellow);
	for (int i = 13; i <= h; i++)
	{
		for (int j = 35; j <= w; j++)
		{
			if (i == 13 || j == 35 || i == h || j == w)
			{
				gotoRowCol(i, j);
				cout << sym;
			}
		}
	}
	SetClr(BROWN);
	letterS(hOfLetter, sym, 15, 40);
	letterN(hOfLetter, sym, 15, 57);
	letterA1(hOfLetter * 2 - 2, sym, 15, 75);
	letterK(hOfLetter - 1, sym, 15, 101);
	letterE1(hOfLetter, sym, 15, 117);
	letterG(hOfLetter, sym, 35, 40);
	letterA2(hOfLetter * 2 - 2, sym, 35, 56);
	letterM(hOfLetter, sym, 35, 86);
	letterE2(hOfLetter, sym, 35, 118);



}
void end(int hOfLetter, int h, int w, char sym)
{
	SetClr(Yellow);
	for (int i = 13; i <= h; i++)
	{
		for (int j = 35; j <= w; j++)
		{
			if (i == 13 || j == 35 || i == h || j == w)
			{
				gotoRowCol(i, j);
				cout << sym;
			}
		}
	}
	SetClr(BROWN);
	letterG(hOfLetter, sym, 15, 40);
	letterA1(hOfLetter * 2 - 2, sym, 14, 56);
	letterM(hOfLetter, sym, 15, 86);
	letterE1(hOfLetter, sym, 14, 118);
	letterO(hOfLetter, sym, 34, 48);
	letterV(hOfLetter, sym, 33, 65);
	letterE2(hOfLetter, sym, 35, 97);
	letterR(hOfLetter, sym, 34, 110);
}

void mediumHurdles(int h, char syms)
{
	SetClr(GREEN);
	gotoRowCol(15, 20);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	gotoRowCol(15, 50);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	gotoRowCol(45, 20);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	gotoRowCol(45, 50);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
}
bool killWithMediumHurdle(Snake* S, int nos, int h)
{
	for (int n = 0; n < nos; n++)
	{
		for (int i = 0; i < h; i++)
		{
			if (S[n].ps[0].ri == 15 && S[n].ps[0].ci == 20 + i)
			{
				return true;
			}
			if (S[n].ps[0].ri == 15 && S[n].ps[0].ci == 50 + i)
			{
				return true;
			}
			if (S[n].ps[0].ri == 45 && S[n].ps[0].ci == 20 + i)
			{
				return true;
			}
			if (S[n].ps[0].ri == 45 && S[n].ps[0].ci == 50 + i)
			{
				return true;
			}
		}

	}

	return false;
}


void hardHurdles(int h, char syms)
{
	SetClr(GREEN);
	gotoRowCol(15, 20);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	gotoRowCol(15, 50);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	gotoRowCol(45, 20);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	gotoRowCol(45, 50);
	for (int i = 0; i < h; i++)
	{
		cout << syms;
	}
	for (int i = 0; i < h * 2; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			gotoRowCol(21 + i, 40 + j);
			cout << syms;
		}
		cout << endl;
	}
}
bool killWithHardHurdle(Snake* S, int nos, int h)
{
	for (int n = 0; n < nos; n++)
	{
		for (int i = 0; i < h; i++)
		{
			if (S[n].ps[0].ri == 15 && S[n].ps[0].ci == 20 + i)
			{
				return true;
			}
			if (S[n].ps[0].ri == 15 && S[n].ps[0].ci == 50 + i)
			{
				return true;
			}
			if (S[n].ps[0].ri == 45 && S[n].ps[0].ci == 20 + i)
			{
				return true;
			}
			if (S[n].ps[0].ri == 45 && S[n].ps[0].ci == 50 + i)
			{
				return true;
			}
		}
	}
	for (int n = 0; n < nos; n++)
	{
		for (int i = 0; i < h * 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				if (S[n].ps[0].ri == 21 + i && S[n].ps[0].ci == 40 + j)
				{
					return true;
				}
			}
		}
	}
	return false;
}

//int main()
//{
//	srand(time(0));
//	char c;
//	int height = 60, width = 80, nos;
//	Position Pos;
//	Food f;
//	Snake* S = new Snake[4];
//	bool gameover = false;
//	/*PlaySound(TEXT("naagin.wav"), NULL, SND_ASYNC);
//	welcome(15, 56, 132, -37);
//	_getch();
//	system("cls");*/
//	init(S, f, height, width, nos);
//	system("cls");
//	drawBoundry(Pos, S, height, width, nos);
//	hardHurdles(10, -37);
//	mediumHurdles(10, -37);
//	displayFood(f);
//	game_over(S, height, width, nos, gameover);
//	while (!gameover)
//	{
//		if (_kbhit())
//		{
//			c = _getch();
//			if (c == -32)
//			{
//				c = _getch();
//			}
//			changeDirection(S, c, nos);
//		}
//		for (int i = 0; i < nos; i++)
//		{
//			if (i == 0)
//			{
//				displaySnake1(S);
//			}
//			if (i == 1)
//			{
//				displaySnake2(S);
//			}
//			if (i == 2)
//			{
//				displaySnake3(S);
//			}
//			if (i == 3)
//			{
//				displaySnake4(S);
//			}
//		}
//		Sleep(1);
//		removeSnake(S, height, width, nos);
//		moveSnake(S, height, width, nos);
//		if (foodIsEaten(S, f, nos))
//		{
//			PlaySound(TEXT("eatingFood.wav"), NULL, SND_ASYNC);
//			displayScore(S, f);
//			expandSnake(S, nos, f);
//			genFood(S, f, height, width, nos);
//			displayFood(f);
//		}
//
//		game_over(S, height, width, nos, gameover);
//		for (int i = 0; i < nos; i++)
//		{
//			if (i == 0)
//			{
//				displaySnake1(S);
//			}
//			else if (i == 1)
//			{
//				displaySnake2(S);
//			}
//			else if (i == 2)
//			{
//				displaySnake3(S);
//			}
//			else if (i == 3)
//			{
//				displaySnake4(S);
//			}
//		}
//		/*if (killOther(S, nos))
//		{
//			for (int i = 0; i < nos; i++)
//			{
//				if (i == 0)
//				{
//					displaySnake(S);
//				}
//				if (i == 1)
//				{
//					displaySnake1(S);
//				}
//			}
//			_getch();
//			break;
//		}*/
//		if (killOther(S, nos) || killWithHardHurdle(S, nos, 10))
//		{
//			for (int i = 0; i < nos; i++)
//			{
//				if (i == 0)
//				{
//					displaySnake1(S);
//				}
//				if (i == 1)
//				{
//					displaySnake2(S);
//				}
//				if (i == 2)
//				{
//					displaySnake3(S);
//				}
//				if (i == 3)
//				{
//					displaySnake4(S);
//				}
//			}
//			break;
//		}
//	}
//	PlaySound(TEXT("EndMusic.wav"), NULL, SND_ASYNC);
//	system("cls");
//	end(15, 56, 132, -37);
//	Sleep(1000);
//	_getch();
//	return 0;
//}

int easyMode(Snake* S, Position& Pos, Food f, int height, int width, int nos)
{
	char c;
	bool gameover = false;
	drawBoundry(Pos, S, height, width, nos);
	displayFood(f);
	game_over(S, height, width, nos, gameover);
	while (!gameover)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();
			}
			changeDirection(S, c, nos);
		}
		for (int i = 0; i < nos; i++)
		{
			if (i == 0)
			{
				displaySnake1(S);
			}
			if (i == 1)
			{
				displaySnake2(S);
			}
			if (i == 2)
			{
				displaySnake3(S);
			}
			if (i == 3)
			{
				displaySnake4(S);
			}
		}
		///Sleep(1);
		removeSnake(S, height, width, nos);
		moveSnake(S, height, width, nos);
		if (foodIsEaten(S, f, nos))
		{
			PlaySound(TEXT("eatingFood.wav"), NULL, SND_ASYNC);
			displayScore(S, f);
			expandSnake(S, nos, f);
			genFood(S, f, height, width, nos);
			displayFood(f);
		}
		game_over(S, height, width, nos, gameover);
		for (int i = 0; i < nos; i++)
		{
			if (i == 0)
			{
				displaySnake1(S);
			}
			else if (i == 1)
			{
				displaySnake2(S);
			}
			else if (i == 2)
			{
				displaySnake3(S);
			}
			else if (i == 3)
			{
				displaySnake4(S);
			}
		}
	}

	PlaySound(TEXT("EndMusic.wav"), NULL, SND_ASYNC);
	system("cls");
	end(15, 56, 132, -37);
	Sleep(1000);
	_getch();
	return 0;
}
int mediumMode(Snake* S, Position& Pos, Food f, int height, int width, int nos)
{
	char c;
	bool gameover = false;
	mediumHurdles(10, -37);
	drawBoundry(Pos, S, height, width, nos);
	displayFood(f);
	game_over(S, height, width, nos, gameover);
	while (!gameover)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();
			}
			changeDirection(S, c, nos);
		}
		for (int i = 0; i < nos; i++)
		{
			if (i == 0)
			{
				displaySnake1(S);
			}
			if (i == 1)
			{
				displaySnake2(S);
			}
			if (i == 2)
			{
				displaySnake3(S);
			}
			if (i == 3)
			{
				displaySnake4(S);
			}
		}
		///Sleep(1);
		removeSnake(S, height, width, nos);
		moveSnake(S, height, width, nos);
		if (foodIsEaten(S, f, nos))
		{
			PlaySound(TEXT("eatingFood.wav"), NULL, SND_ASYNC);
			displayScore(S, f);
			expandSnake(S, nos, f);
			genFood(S, f, height, width, nos);
			displayFood(f);
		}
		game_over(S, height, width, nos, gameover);
		for (int i = 0; i < nos; i++)
		{
			if (i == 0)
			{
				displaySnake1(S);
			}
			else if (i == 1)
			{
				displaySnake2(S);
			}
			else if (i == 2)
			{
				displaySnake3(S);
			}
			else if (i == 3)
			{
				displaySnake4(S);
			}
		}
		if (killOther(S, nos) || killWithMediumHurdle(S, nos, 10))
		{
			for (int i = 0; i < nos; i++)
			{
				if (i == 0)
				{
					displaySnake1(S);
				}
				if (i == 1)
				{
					displaySnake2(S);
				}
				if (i == 2)
				{
					displaySnake3(S);
				}
				if (i == 3)
				{
					displaySnake4(S);
				}
			}
			break;
		}
	}
	PlaySound(TEXT("EndMusic.wav"), NULL, SND_ASYNC);
	system("cls");
	end(15, 56, 132, -37);
	Sleep(1000);
	_getch();
	return 0;
}
int hardMode(Snake* S, Position& Pos, Food f, int height, int width, int nos)
{
	char c;
	bool gameover = false;
	hardHurdles(10, -37);
	drawBoundry(Pos, S, height, width, nos);
	displayFood(f);
	game_over(S, height, width, nos, gameover);
	while (!gameover)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();
			}
			changeDirection(S, c, nos);
		}
		for (int i = 0; i < nos; i++)
		{
			if (i == 0)
			{
				displaySnake1(S);
			}
			if (i == 1)
			{
				displaySnake2(S);
			}
			if (i == 2)
			{
				displaySnake3(S);
			}
			if (i == 3)
			{
				displaySnake4(S);
			}
		}
		///Sleep(1);
		removeSnake(S, height, width, nos);
		moveSnake(S, height, width, nos);
		if (foodIsEaten(S, f, nos))
		{
			PlaySound(TEXT("eatingFood.wav"), NULL, SND_ASYNC);
			displayScore(S, f);
			expandSnake(S, nos, f);
			genFood(S, f, height, width, nos);
			displayFood(f);
		}
		game_over(S, height, width, nos, gameover);
		for (int i = 0; i < nos; i++)
		{
			if (i == 0)
			{
				displaySnake1(S);
			}
			else if (i == 1)
			{
				displaySnake2(S);
			}
			else if (i == 2)
			{
				displaySnake3(S);
			}
			else if (i == 3)
			{
				displaySnake4(S);
			}
		}
		if (killOther(S, nos) || killWithHardHurdle(S, nos, 10))
		{
			for (int i = 0; i < nos; i++)
			{
				if (i == 0)
				{
					displaySnake1(S);
				}
				if (i == 1)
				{
					displaySnake2(S);
				}
				if (i == 2)
				{
					displaySnake3(S);
				}
				if (i == 3)
				{
					displaySnake4(S);
				}
			}
			break;
		}
	}
	PlaySound(TEXT("EndMusic.wav"), NULL, SND_ASYNC);
	system("cls");
	end(15, 56, 132, -37);
	Sleep(1000);
	_getch();
	return 0;
}


void playerBox(int row, int col, int brows, int bcols, int clr, char c1, char c2, char c3, char c4, char c5, char c6, char c7, int lclr, char sym)
{
	for (int r = 0; r < brows; r++)
	{
		for (int c = 0; c < bcols; c++)
		{
			SetClr(clr);
			gotoRowCol(row + r, col + c);
			if (r == brows / 2 && c == bcols / 2 - 3)
			{
				SetClr(lclr);
				cout << c1;
			}
			if (r == brows / 2 && c == bcols / 2 - 2)
			{
				SetClr(lclr);
				cout << c2;
			}
			if (r == brows / 2 && c == bcols / 2 - 1)
			{
				SetClr(lclr);
				cout << c3;
			}
			if (r == brows / 2 && c == bcols / 2)
			{
				SetClr(lclr);
				cout << c4;
			}
			if (r == brows / 2 && c == bcols / 2 + 1)
			{
				SetClr(lclr);
				cout << c5;
			}
			if (r == brows / 2 && c == bcols / 2 + 2)
			{
				SetClr(lclr);
				cout << c6;
			}
			if (r == brows / 2 && c == bcols / 2 + 3)
			{
				SetClr(lclr);
				cout << c7;
			}
			else
			{
				cout << sym;
				SetClr(clr);
			}
		}
	}
}
void players()
{
	playerBox(10, 75, 7, 19, 6, 'P', 'L', 'A', 'Y', 'E', 'R', 'S', 111, -37);
	playerBox(30, 15, 7, 19, 6, 'P', 'L', 'A', 'Y', 'E', 'R', '1', 111, -37);
	playerBox(30, 55, 7, 19, 6, 'P', 'L', 'A', 'Y', 'E', 'R', '2', 111, -37);
	playerBox(30, 95, 7, 19, 6, 'P', 'L', 'A', 'Y', 'E', 'R', '3', 111, -37);
	playerBox(30, 135, 7, 19, 6, 'P', 'L', 'A', 'Y', 'E', 'R', '4', 111, -37);
}

void Drawbox1(int row, int col, int brows, int bcols, int clr, char c1, char c2, char c3, char c4, char c5, char c6, int lclr, char sym)
{
	for (int r = 0; r < brows; r++)
	{
		for (int c = 0; c < bcols; c++)
		{
			SetClr(clr);
			gotoRowCol(row + r, col + c);
			if (r == brows / 2 && c == bcols / 2 - 3)
			{
				SetClr(lclr);
				cout << c1;
			}
			if (r == brows / 2 && c == bcols / 2 - 2)
			{
				SetClr(lclr);
				cout << c2;
			}
			if (r == brows / 2 && c == bcols / 2 - 1)
			{
				SetClr(lclr);
				cout << c3;
			}
			if (r == brows / 2 && c == bcols / 2)
			{
				SetClr(lclr);
				cout << c4;
			}
			if (r == brows / 2 && c == bcols / 2 + 1)
			{
				SetClr(lclr);
				cout << c5;
			}
			if (r == brows / 2 && c == bcols / 2 + 2)
			{
				SetClr(lclr);
				cout << c6;
			}
			else
			{
				cout << sym;
				SetClr(clr);
			}
		}
	}
}
void Drawbox(int row, int col, int brows, int bcols, int clr, char c1, char c2, char c3, char c4, int lclr, char sym)
{
	for (int r = 0; r < brows; r++)
	{
		for (int c = 0; c < bcols; c++)
		{
			SetClr(clr);
			gotoRowCol(row + r, col + c);
			if (r == brows / 2 && c == bcols / 2 - 2)
			{
				SetClr(lclr);
				cout << c1;
			}
			if (r == brows / 2 && c == bcols / 2 - 1)
			{
				SetClr(lclr);
				cout << c2;
			}
			if (r == brows / 2 && c == bcols / 2)
			{
				SetClr(lclr);
				cout << c3;
			}
			if (r == brows / 2 && c == bcols / 2 + 1)
			{
				SetClr(lclr);
				cout << c4;
			}
			else
			{
				cout << sym;
				SetClr(clr);
			}
		}
	}
}
void mode()
{
	Drawbox(10, 75, 7, 19, 6, 'M', 'O', 'D', 'E', 111, -37);
	Drawbox(30, 35, 7, 19, 6, 'E', 'A', 'S', 'Y', 111, -37);
	Drawbox1(30, 75, 7, 19, 6, 'M', 'E', 'D', 'I', 'U', 'M', 111, -37);
	Drawbox(30, 115, 7, 19, 6, 'H', 'A', 'R', 'D', 111, -37);
}


int main()
{
	srand(time(0));
	char c;
	int height = 60, width = 80, nos;
	Position Pos;
	Food f;
	Snake* S = new Snake[4];
	PlaySound(TEXT("naagin.wav"), NULL, SND_ASYNC);
	welcome(15, 56, 132, -37);
	_getch();
	system("cls");
	players();
	init(S, f, height, width, nos);
	system("cls");
	char ch;
	mode();
	gotoRowCol(40, 75);
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case 'e':
	case 'E':
	{
		easyMode(S, Pos, f, height, width, nos);
	}
	case 'm':
	case 'M':
	{
		mediumMode(S, Pos, f, height, width, nos);
	}
	case 'h':
	case 'H':
	{
		hardMode(S, Pos, f, height, width, nos);
	}
	}
	return 0;
}

