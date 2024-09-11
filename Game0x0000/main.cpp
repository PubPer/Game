#include <graphics.h>
#include <iostream>
/*
	���ߣ�SkySea
	ʱ�䣺2024.09.11
	����������ʹ��Easyͼ�ο��ʵ�־�����С��Ϸ
	�汾��ģ��Voidmatrix��ʦ��

*/

//�������ݣ���-�������
char boardData[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'},
};

char currentPiece = 'O';

//���ָ�����ӵ�����Ƿ��ʤ
bool CheckWin(char c)
{
	if (boardData[0][0] == c && boardData[0][1] == c && boardData[0][2] == c)
		return true;
	if (boardData[1][0] == c && boardData[1][1] == c && boardData[1][2] == c)
		return true;
	if (boardData[2][0] == c && boardData[2][1] == c && boardData[2][2] == c)
		return true;
	if (boardData[0][0] == c && boardData[1][0] == c && boardData[2][0] == c)
		return true;
	if (boardData[0][1] == c && boardData[1][1] == c && boardData[2][1] == c)
		return true;
	if (boardData[0][2] == c && boardData[1][2] == c && boardData[2][2] == c)
		return true;
	if (boardData[0][0] == c && boardData[1][1] == c && boardData[2][2] == c)
		return true;
	if (boardData[0][2] == c && boardData[1][1] == c && boardData[2][0] == c)
		return true;

	return false;

}

//��⵱ǰ�Ƿ����ƽ��
bool CheckDraw()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (boardData[i][j] == '-')
			{
				return false;
			}

		}
	}
	return true;
}

//��������
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//��������
void DrawPiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (boardData[i][j])
			{
			case 'O':
				circle(200 * j + 100, 200 * i + 100, 95);
				break;
			case 'X':
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
				line(200 * (j + 1), 200 * i, 200 * j, 200 * (i + 1));
			case '-':
				break;
			}

		}
	}
}

//������ʾ��Ϣ
void DrawTipText()
{
	//����TCHAR���͵��ַ�������Ϊ��ʽ���Ļ�����
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ����������:%c"), currentPiece);

	//������ʾ��Ϣ�ı�������ɫ
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}
int main()
{
	initgraph(600, 600);

	bool juageRunning = true;

	ExMessage msg;

	BeginBatchDraw();

	while (juageRunning)
	{
		DWORD starTime = GetTickCount();
		//������Ϣ����
		while (peekmessage(&msg))
		{
			//���������������Ϣ

			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;

				int indexX = x / 200;
				int indexY = y / 200;


				//��������
				if (boardData[indexY][indexX] == '-')
				{
					boardData[indexY][indexX] = currentPiece;
					//�л���������
					if (currentPiece == 'O')
					{
						currentPiece = 'X';
					}
					else
					{
						currentPiece = 'O';
					}
				}
			}

		}
		cleardevice();

		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();

		if (CheckWin('X'))
		{
			MessageBox(GetHWnd(), _T("X���ʤ��"), _T("��Ϸ����"), MB_OK);
			juageRunning = false;
		}
		else if (CheckWin('O'))
		{
			MessageBox(GetHWnd(), _T("O���ʤ��"), _T("��Ϸ����"), MB_OK);
			juageRunning = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("ƽ��"), _T("��Ϸ����"), MB_OK);
			juageRunning = false;
		}
		//�����ʱ�����������Ż�
		DWORD endTime = GetTickCount();
		DWORD useTime = endTime - starTime;
		//ʵ��60֡���Ż�
		if (useTime < 1000 / 60)
		{
			Sleep(1000 / 60 - useTime);
		}
	}
	EndBatchDraw();

	return 0;
}