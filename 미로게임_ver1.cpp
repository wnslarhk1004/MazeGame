#include <iostream>
#include <conio.h> // console input output
using namespace std;

/*
규칙
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
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
			if (pPlayerPos->x == j && pPlayerPos->y == i)
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
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0')
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
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0')
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
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0')
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
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0')
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

int main()
{
	// 20 x 20 미로를 만들어준다.
	char strMaze[21][21] = {};

	POINT	tPlayerPos;
	POINT	tStartPos;
	POINT	tEndPos;

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

		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
		char cInput = _getch(); // _getch()를 이용해서 바로 반응하도록!

		if (cInput == 'q' || cInput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cInput);
	}

	return 0;
}