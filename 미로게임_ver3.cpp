#include <iostream>
#include <conio.h> // console input output
#include <time.h>
using namespace std;

/*
규칙
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
4 : 폭탄
5 : 파워아이템
6 : 벽밀기 아이템
7 : 투명아이템
8 : 웜홀

숙제 : 벽을 깨면 일정 확률로아이템이 나온다.
아이템종류 : 폭탄 반경 1칸 증가. 벽 밀기 아이템. 투명아이템(벽통과)
3종류가 랜덤하게 등장한다. 등장하지 않을 수도 있다.

아이템을 먹게되면 해당 아이템 효과를 부여받게 된다.

벽을 깨면 랜덤하게 웜홀을 만든다. 웜홀에 들어가게 되면 다른 웜홀의 위치로 이동한다.
웜홀은 맵 중간마다 몇개씩 만들어본다. 웜홀이 1개일 경우 다른곳으로 이동하지 않는다.
Score system도 만들 수 있다.

F9를 누르면 break point(중단점)을 설정할 수 있다. 설정하고 F5를 누르면 실행되고
프로그램을 실행하고 중단점에 설정된 기능을 실행하면 설정한 중단점에 들어온다.
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : 타입을 재정의 하는 기능이다.
typedef _tagPoint	 POINT;
typedef _tagPoint * PPOINT;

typedef struct _tagPlayer
{
	_tagPoint	tPos;
	bool		bWallPush;
	bool		bTransparency;
	int			iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos,
	PPOINT pEndPos) // 포인터 구조체이므로 *없음
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;
	/*
	pPlayerPos->x = 0;
	pPlayerPos->y = 0;
	*/
	// StartPos와 PlayerPos는 같은 위치
	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111100000000");
	strcpy_s(Maze[2], "00100010000111111100");
	strcpy_s(Maze[3], "01100010000000000100");
	strcpy_s(Maze[4], "01000011110001111100");
	strcpy_s(Maze[5], "01000000001111000000");
	strcpy_s(Maze[6], "01100000001000000000");
	strcpy_s(Maze[7], "00100000001111111000");
	strcpy_s(Maze[8], "00001110000000001000");
	strcpy_s(Maze[9], "01111011111111111000");
	strcpy_s(Maze[10], "01000000000000000000");
	strcpy_s(Maze[11], "01111100111111100000");
	strcpy_s(Maze[12], "00000111100000111110");
	strcpy_s(Maze[13], "01111100000000000010");
	strcpy_s(Maze[14], "01000000001111111110");
	strcpy_s(Maze[15], "01111110011000000000");
	strcpy_s(Maze[16], "00000010010000000000");
	strcpy_s(Maze[17], "01111110011111000000");
	strcpy_s(Maze[18], "01000000000001100000");
	strcpy_s(Maze[19], "11000000000000111113");
}

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	// 2차원 배열 반복을 돌리기 위해 2중 for문 이용
	for (int i = 0; i < 20; ++i) // 세로
	{
		for (int j = 0; j < 20; ++j) // 가로
		{
			if (Maze[i][j] == '4')
				cout << "♨";
			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "☆";
			else if (Maze[i][j] == '0') // 벽
				cout << "■"; // 한글폰트이므로 2byte
			else if (Maze[i][j] == '1') // 길
				cout << "  "; // 2byte이므로 space bar 2개
			else if (Maze[i][j] == '2') // 출발점
				cout << "★";
			else if (Maze[i][j] == '3') // 도착점
				cout << "◎";
			else if (Maze[i][j] == '5') // Power
				cout << "＠";
			else if (Maze[i][j] == '6') // Push
				cout << "※";
			else if (Maze[i][j] == '7') // Trans
				cout << "▷";

		}
		cout << endl;
	}

	cout << "폭탄파워 : " << pPlayer->iBombPower << endl;
	cout << "벽통과 : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";
	cout << "벽밀기 : ";
	if (pPlayer->bWallPush)
		cout << "ON" << endl;
	else
		cout << "OFF" << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		// Power Item
		// Power 최대치 아이템을 먹어도 Power는 올라가지 않도록
		if (pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;
		return true;
	}
	else if (cItemType == '6')
	{
		// Push a wall
		pPlayer->bWallPush = true;
		return true;
	}
	else if (cItemType == '7')
	{
		// Transparency
		pPlayer->bTransparency = true;
		return true;
	}
	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	// 예외처리
	if (pPlayer->tPos.y - 1 >= 0) // 위로 올라가는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}
		// 벽이나 폭탄을 만나도 투명화면 통과할 수 있다.
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		// 아이템
		if(AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	// 예외처리
	if (pPlayer->tPos.y + 1 < 20) // 아래로 내려가는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0'&&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}
		// 벽이나 폭탄을 만나도 투명화면 통과할 수 있다.
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		// 아이템
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	// 예외처리
	if (pPlayer->tPos.x + 1 < 20) // 오른쪽으로 이동하는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0'&&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}
		// 벽이나 폭탄을 만나도 투명화면 통과할 수 있다.
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		// 아이템
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	// 예외처리
	if (pPlayer->tPos.x - 1 >= 0) // 왼쪽으로 이동하는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0'&&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}
		// 벽이나 폭탄을 만나도 투명화면 통과할 수 있다.
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		// 아이템
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
		// 대소문자 지원
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

// 포인터 변수를 const로 생성하면 가리키는 대상의 값을 변경할 수 없다.
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer,
	PPOINT pBombArr, int* pBombCount)
{
	// 폭탄을 5개 전부 놓으면 리턴
	if (*pBombCount == 5)
		return;
	// 벽이 위에 있으면 폭탄생성하지 못하게 막는다.
	// 예외처리
	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; ++i)
	{
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr,
	int *pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		// 폭탄이 터지면 사라진다.
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
		// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}
		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			// 위 체크
			if (pBombArr[i].y - j >= 0)
			{
				// 벽일 경우에 길로 바꾼다.
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20) // 0 ~ 99 20%확률
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%확률로 Power
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else // 나머지 20%
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';

				}

				// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
			// 아래 체크
			if (pBombArr[i].y + j < 20)
			{
				// 벽일 경우에 길로 바꾼다.
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20) // 0 ~ 99 20%확률
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%확률로 Power
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else // 나머지 20%
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}

				// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
			// 왼쪽 체크
			if (pBombArr[i].x - j >= 0)
			{
				// 벽일 경우에 길로 바꾼다.
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20) // 0 ~ 99 20%확률
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%확률로 Power
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else // 나머지 20%
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}

				// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}

			}
			// 오른쪽 체크
			if (pBombArr[i].x + j < 20)
			{
				// 벽일 경우에 길로 바꾼다.
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20) // 0 ~ 99 20%확률
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%확률로 Power
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else // 나머지 20%
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

				// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	// 모든 폭탄이 터지기 때문에 0으로 초기화
	*pBombCount = 0;

}


int main()
{
	srand((unsigned int)time(0));
	// 20 x 20 미로를 만들어준다.
	char strMaze[21][21] = {};

	PLAYER	tPlayer = {};
	POINT	tStartPos;
	POINT	tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT	tBombPos[5];
	// 미로를 설정한다.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// 미로를 출력한다.
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "t : 폭탄설치 u : 폭탄 터트리기 i : 벽밀기" << endl;
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
		char cInput = _getch(); // _getch()를 이용해서 바로 반응하도록!

		if (cInput == 'q' || cInput == 'Q')
			break;
		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		else if (cInput == 'u' || cInput == 'U')
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}
		else
			MovePlayer(strMaze, &tPlayer, cInput);
	}

	return 0;
}