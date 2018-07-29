#include <iostream>
#include <conio.h> // console input output
using namespace std;

/*
규칙
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
4 : 폭탄
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : 타입을 재정의 하는 기능이다.
typedef _tagPoint	 POINT;
typedef _tagPoint * PPOINT;

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos,
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
	*pPlayerPos = *pStartPos;

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

void Output(char Maze[21][21], PPOINT pPlayerPos)
{
	// 2차원 배열 반복을 돌리기 위해 2중 for문 이용
	for (int i = 0; i < 20; ++i) // 세로
	{
		for (int j = 0; j < 20; ++j) // 가로
		{
			if (Maze[i][j] == '4')
				cout << "♨";
			else if (pPlayerPos->x == j && pPlayerPos->y == i)
				cout << "☆";
			else if (Maze[i][j] == '0') // 벽
				cout << "■"; // 한글폰트이므로 2byte
			else if (Maze[i][j] == '1') // 길
				cout << "  "; // 2byte이므로 space bar 2개
			else if (Maze[i][j] == '2') // 출발점
				cout << "★";
			else if (Maze[i][j] == '3') // 도착점
				cout << "◎";
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos)
{
	// 예외처리
	if (pPlayerPos->y - 1 >= 0) // 위로 올라가는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0' &&
			Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4')
		{
			--pPlayerPos->y;
		}
	}
}

void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	// 예외처리
	if (pPlayerPos->y + 1 < 20) // 아래로 내려가는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0'&&
			Maze[pPlayerPos->y + 1][pPlayerPos->x] != '4')
		{
			++pPlayerPos->y;
		}
	}
}

void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	// 예외처리
	if (pPlayerPos->x + 1 < 20) // 오른쪽으로 이동하는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0'&&
			Maze[pPlayerPos->y][pPlayerPos->x + 1] != '4')
		{
			++pPlayerPos->x;
		}
	}
}

void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	// 예외처리
	if (pPlayerPos->x - 1 >= 0) // 왼쪽으로 이동하는 커맨드
	{
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0'&&
			Maze[pPlayerPos->y][pPlayerPos->x - 1] != '4')
		{
			--pPlayerPos->x;
		}
	}
}

void MovePlayer(char Maze[21][21], PPOINT pPlayerPos, char cInput)
{
	switch (cInput)
	{
		// 대소문자 지원
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayerPos);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayerPos);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayerPos);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayerPos);
		break;
	}
}

// 포인터 변수를 const로 생성하면 가리키는 대상의 값을 변경할 수 없다.
void CreateBomb(char Maze[21][21], const PPOINT pPlayer,
	PPOINT pBombArr, int* pBombCount)
{
	// 폭탄을 5개 전부 놓으면 리턴
	if (*pBombCount == 5)
		return;

	for (int i = 0; i < *pBombCount; ++i)
	{
		if (pPlayer->x == pBombArr[i].x &&
			pPlayer->y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = *pPlayer;
	++(*pBombCount);

	Maze[pPlayer->y][pPlayer->x] = '4';
}

void Fire(char Maze[21][21], PPOINT pPlayer, PPOINT pBombArr,
	int *pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		// 폭탄이 터지면 사라진다.
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
		// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
		if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y)
		{
			pPlayer->x = 0;
			pPlayer->y = 0;
		}
		// 위 체크
		if (pBombArr[i].y - 1 >= 0)
		{
			// 벽일 경우에 길로 바꾼다.
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';

			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y - 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		// 아래 체크
		if (pBombArr[i].y + 1 < 20)
		{
			// 벽일 경우에 길로 바꾼다.
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';

			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		// 왼쪽 체크
		if (pBombArr[i].x - 1 >= 0)
		{
			// 벽일 경우에 길로 바꾼다.
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';

			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}

		}
		// 오른쪽 체크
		if (pBombArr[i].x + 1 < 20)
		{
			// 벽일 경우에 길로 바꾼다.
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';

			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
	}

	// 모든 폭탄이 터지기 때문에 0으로 초기화
	*pBombCount = 0;

}


int main()
{
	// 20 x 20 미로를 만들어준다.
	char strMaze[21][21] = {};

	POINT	tPlayerPos;
	POINT	tStartPos;
	POINT	tEndPos;

	int iBombCount = 0;

	POINT	tBombPos[5];
	// 미로를 설정한다.
	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// 미로를 출력한다.
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "t : 폭탄설치 u : 폭탄 터트리기" << endl;
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
		char cInput = _getch(); // _getch()를 이용해서 바로 반응하도록!

		if (cInput == 'q' || cInput == 'Q')
			break;
		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayerPos, tBombPos, &iBombCount);
		else if (cInput == 'u' || cInput == 'U')
		{
			Fire(strMaze, &tPlayerPos, tBombPos, &iBombCount);
		}
		else
			MovePlayer(strMaze, &tPlayerPos, cInput);
	}

	return 0;
}
