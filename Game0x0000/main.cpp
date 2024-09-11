#include <graphics.h>
#include <iostream>
/*
	作者：SkySea
	时间：2024.09.11
	功能描述：使用Easy图形库简单实现井字棋小游戏
	版本：模仿Voidmatrix老师的

*/

//棋盘数据，‘-’代表空
char boardData[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'},
};

char currentPiece = 'O';

//检测指定棋子的玩家是否获胜
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

//检测当前是否出现平局
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

//绘制棋盘
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//绘制棋子
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

//绘制提示信息
void DrawTipText()
{
	//定义TCHAR类型的字符数组作为格式化的缓冲区
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型是:%c"), currentPiece);

	//设置提示信息文本字体颜色
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
		//处理消息队列
		while (peekmessage(&msg))
		{
			//检查鼠标左键按下消息

			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;

				int indexX = x / 200;
				int indexY = y / 200;


				//尝试落子
				if (boardData[indexY][indexX] == '-')
				{
					boardData[indexY][indexX] = currentPiece;
					//切换棋子类型
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
			MessageBox(GetHWnd(), _T("X玩家胜利"), _T("游戏结束"), MB_OK);
			juageRunning = false;
		}
		else if (CheckWin('O'))
		{
			MessageBox(GetHWnd(), _T("O玩家胜利"), _T("游戏结束"), MB_OK);
			juageRunning = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
			juageRunning = false;
		}
		//计算耗时，进行性能优化
		DWORD endTime = GetTickCount();
		DWORD useTime = endTime - starTime;
		//实现60帧的优化
		if (useTime < 1000 / 60)
		{
			Sleep(1000 / 60 - useTime);
		}
	}
	EndBatchDraw();

	return 0;
}