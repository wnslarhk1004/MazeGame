#include <iostream>
#include <conio.h> // console input output
#include <time.h>
using namespace std;

/*
��Ģ
0 : ��
1 : ��
2 : ������
3 : ������
4 : ��ź
5 : �Ŀ�������
6 : ���б� ������
7 : ���������
8 : ��Ȧ

���� : ���� ���� ���� Ȯ���ξ������� ���´�.
���������� : ��ź �ݰ� 1ĭ ����. �� �б� ������. ���������(�����)
3������ �����ϰ� �����Ѵ�. �������� ���� ���� �ִ�.

�������� �԰ԵǸ� �ش� ������ ȿ���� �ο��ް� �ȴ�.

���� ���� �����ϰ� ��Ȧ�� �����. ��Ȧ�� ���� �Ǹ� �ٸ� ��Ȧ�� ��ġ�� �̵��Ѵ�.
��Ȧ�� �� �߰����� ��� ������. ��Ȧ�� 1���� ��� �ٸ������� �̵����� �ʴ´�.
Score system�� ���� �� �ִ�.

F9�� ������ break point(�ߴ���)�� ������ �� �ִ�. �����ϰ� F5�� ������ ����ǰ�
���α׷��� �����ϰ� �ߴ����� ������ ����� �����ϸ� ������ �ߴ����� ���´�.
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : Ÿ���� ������ �ϴ� ����̴�.
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
	// 2���� �迭 �ݺ��� ������ ���� 2�� for�� �̿�
	for (int i = 0; i < 20; ++i) // ����
	{
		for (int j = 0; j < 20; ++j) // ����
		{
			if (Maze[i][j] == '4')
				cout << "��";
			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "��";
			else if (Maze[i][j] == '0') // ��
				cout << "��"; // �ѱ���Ʈ�̹Ƿ� 2byte
			else if (Maze[i][j] == '1') // ��
				cout << "  "; // 2byte�̹Ƿ� space bar 2��
			else if (Maze[i][j] == '2') // �����
				cout << "��";
			else if (Maze[i][j] == '3') // ������
				cout << "��";
			else if (Maze[i][j] == '5') // Power
				cout << "��";
			else if (Maze[i][j] == '6') // Push
				cout << "��";
			else if (Maze[i][j] == '7') // Trans
				cout << "��";

		}
		cout << endl;
	}

	cout << "��ź�Ŀ� : " << pPlayer->iBombPower << endl;
	cout << "����� : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";
	cout << "���б� : ";
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
		// Power �ִ�ġ �������� �Ծ Power�� �ö��� �ʵ���
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
	// ����ó��
	if (pPlayer->tPos.y - 1 >= 0) // ���� �ö󰡴� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}
		// ���̳� ��ź�� ������ ����ȭ�� ����� �� �ִ�.
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		// ������
		if(AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	// ����ó��
	if (pPlayer->tPos.y + 1 < 20) // �Ʒ��� �������� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0'&&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}
		// ���̳� ��ź�� ������ ����ȭ�� ����� �� �ִ�.
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		// ������
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	// ����ó��
	if (pPlayer->tPos.x + 1 < 20) // ���������� �̵��ϴ� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0'&&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}
		// ���̳� ��ź�� ������ ����ȭ�� ����� �� �ִ�.
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		// ������
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	// ����ó��
	if (pPlayer->tPos.x - 1 >= 0) // �������� �̵��ϴ� Ŀ�ǵ�
	{
		// ������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0'&&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}
		// ���̳� ��ź�� ������ ����ȭ�� ����� �� �ִ�.
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		// ������
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
		// ��ҹ��� ����
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

// ������ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer,
	PPOINT pBombArr, int* pBombCount)
{
	// ��ź�� 5�� ���� ������ ����
	if (*pBombCount == 5)
		return;
	// ���� ���� ������ ��ź�������� ���ϰ� ���´�.
	// ����ó��
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
		// ��ź�� ������ �������.
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
		// �÷��̾ ��ź�� �¾��� �� ���������� ������.
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}
		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			// �� üũ
			if (pBombArr[i].y - j >= 0)
			{
				// ���� ��쿡 ��� �ٲ۴�.
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) // 0 ~ 99 20%Ȯ��
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%Ȯ���� Power
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else // ������ 20%
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';

				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
			// �Ʒ� üũ
			if (pBombArr[i].y + j < 20)
			{
				// ���� ��쿡 ��� �ٲ۴�.
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) // 0 ~ 99 20%Ȯ��
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%Ȯ���� Power
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else // ������ 20%
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
			// ���� üũ
			if (pBombArr[i].x - j >= 0)
			{
				// ���� ��쿡 ��� �ٲ۴�.
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) // 0 ~ 99 20%Ȯ��
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%Ȯ���� Power
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else // ������ 20%
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}

			}
			// ������ üũ
			if (pBombArr[i].x + j < 20)
			{
				// ���� ��쿡 ��� �ٲ۴�.
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) // 0 ~ 99 20%Ȯ��
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 70) // 70%Ȯ���� Power
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						else if (iPercent < 80) // 10%
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else // ������ 20%
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	// ��� ��ź�� ������ ������ 0���� �ʱ�ȭ
	*pBombCount = 0;

}


int main()
{
	srand((unsigned int)time(0));
	// 20 x 20 �̷θ� ������ش�.
	char strMaze[21][21] = {};

	PLAYER	tPlayer = {};
	POINT	tStartPos;
	POINT	tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT	tBombPos[5];
	// �̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// �̷θ� ����Ѵ�.
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�." << endl;
			break;
		}

		cout << "t : ��ź��ġ u : ��ź ��Ʈ���� i : ���б�" << endl;
		cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ���� : ";
		char cInput = _getch(); // _getch()�� �̿��ؼ� �ٷ� �����ϵ���!

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