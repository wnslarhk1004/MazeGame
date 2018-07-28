#include <iostream>
#include <conio.h> // console input output
using namespace std;

/*
��Ģ
0 : ��
1 : ��
2 : ������
3 : ������
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : Ÿ���� ������ �ϴ� ����̴�.
typedef _tagPoint	 POINT;
typedef _tagPoint * PPOINT;

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos,
	PPOINT pEndPos) // ������ ����ü�̹Ƿ� *����
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;
	/*
	pPlayerPos->x = 0;
	pPlayerPos->y = 0;
	*/
	// StartPos�� PlayerPos�� ���� ��ġ
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
	// 2���� �迭 �ݺ��� ������ ���� 2�� for�� �̿�
	for (int i = 0; i < 20; ++i) // ����
	{
		for (int j = 0; j < 20; ++j) // ����
		{
			if (pPlayerPos->x == j && pPlayerPos->y == i)
				cout << "��";
			else if (Maze[i][j] == '0') // ��
				cout << "��"; // �ѱ���Ʈ�̹Ƿ� 2byte
			else if (Maze[i][j] == '1') // ��
				cout << "  "; // 2byte�̹Ƿ� space bar 2��
			else if (Maze[i][j] == '2') // �����
				cout << "��";
			else if (Maze[i][j] == '3') // ������
				cout << "��";
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos)
{
	// ����ó��
	if (pPlayerPos->y - 1 >= 0) // ���� �ö󰡴� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0')
		{
			--pPlayerPos->y;
		}
	}
}

void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	// ����ó��
	if (pPlayerPos->y + 1 < 20) // �Ʒ��� �������� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0')
		{
			++pPlayerPos->y;
		}
	}
}

void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	// ����ó��
	if (pPlayerPos->x + 1 < 20) // ���������� �̵��ϴ� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0')
		{
			++pPlayerPos->x;
		}
	}
}

void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	// ����ó��
	if (pPlayerPos->x - 1 >= 0) // �������� �̵��ϴ� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
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
		// ��ҹ��� ����
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
	// 20 x 20 �̷θ� ������ش�.
	char strMaze[21][21] = {};

	POINT	tPlayerPos;
	POINT	tStartPos;
	POINT	tEndPos;

	// �̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// �̷θ� ����Ѵ�.
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�." << endl;
			break;
		}

		cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ���� : ";
		char cInput = _getch(); // _getch()�� �̿��ؼ� �ٷ� �����ϵ���!

		if (cInput == 'q' || cInput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cInput);
	}

	return 0;
}