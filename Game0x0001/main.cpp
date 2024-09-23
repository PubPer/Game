#include <graphics.h>
#include <string>

#include"animation.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include "atlas.h"
#include"startGameButton.h"
#include"quitGameButton.h"


const int WINDOW_WIDTH = 1280;	//������
const int WINDOW_HEIGHT = 720;	//����߶�

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

Atlas* atlasPlayerLeft;
Atlas* atlasPlayerRight;
Atlas* atlasEnemyLeft;
Atlas* atlasEnemyRight;

bool isGameStarted = false;
bool isGameRunning = true;

#pragma comment(lib, "Winmm.lib")

//���ɵ���
void tryGenerateEnemy(std::vector<Enemy*>& enemyList)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemyList.push_back(new Enemy(atlasEnemyLeft, atlasEnemyRight));
}

//�����ӵ�λ��
void updateBulllets(std::vector<Bullet>& bulletList, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;							//���򲨶��ٶ�
	const double TANGENT_SPEED = 0.0055;						//���򲨶��ٶ�
	double radian_interval = 2 * 3.14159 / bulletList.size();	//�ӵ�֮��Ļ��ȼ��
	POINT playerPosition = player.getPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bulletList.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;	//��ǰ�ӵ����ڵĻ���
		bulletList[i].position.x = playerPosition.x + player.getPlayerWidth() / 2 + (int)(radius * sin(radian));
		bulletList[i].position.y = playerPosition.y + player.getPlayerHeight() / 2 + (int)(radius * cos(radian));
	}
}

void drawPlayerScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("��ǰ��ҵ÷֣�%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	atlasPlayerLeft = new Atlas(_T("resources/img/player_left_%d.png"), 6);
	atlasPlayerRight = new Atlas(_T("resources/img/player_right_%d.png"), 6);
	atlasEnemyLeft = new Atlas(_T("resources/img/enemy_left_%d.png"), 6);
	atlasEnemyRight = new Atlas(_T("resources/img/enemy_right_%d.png"), 6);

	//�������ּ���
	mciSendString(_T("open resources/mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open resources/mus/hit.wav alias hit"), NULL, 0, NULL);

	int score = 0;
	Player player(atlasPlayerLeft, atlasPlayerRight);
	ExMessage msg;
	IMAGE imgMenu;
	IMAGE imagBackground;
	std::vector<Enemy*> enemyList;
	std::vector<Bullet> bulletList(3);

	RECT regionBtnStartGame, regionBtnQuitGame;

	regionBtnStartGame.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	regionBtnStartGame.right = regionBtnStartGame.left + BUTTON_WIDTH;
	regionBtnStartGame.top = 430;
	regionBtnStartGame.bottom = regionBtnStartGame.top + BUTTON_HEIGHT;

	regionBtnQuitGame.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	regionBtnQuitGame.right = regionBtnQuitGame.left + BUTTON_WIDTH;
	regionBtnQuitGame.top = 550;
	regionBtnQuitGame.bottom = regionBtnQuitGame.top + BUTTON_HEIGHT;

	StartGameButton btnStartGame = StartGameButton(regionBtnStartGame, 
		_T("resources/img/ui_start_idle.png"), _T("resources/img/ui_start_hovered.png"), _T("resources/img/ui_start_pushed.png"));

	QuitGameButton btnQuitGame = QuitGameButton(regionBtnQuitGame,
		_T("resources/img/ui_quit_idle.png"), _T("resources/img/ui_quit_hovered.png"), _T("resources/img/ui_quit_pushed.png"));

	loadimage(&imgMenu, _T("resources/img/menu.png"));
	loadimage(&imagBackground, _T("resources/img/background.png"));
	
	BeginBatchDraw();

	//��Ϸ��ѭ��
	while (isGameRunning)
	{
		DWORD startTime = GetTickCount();
		while (peekmessage(&msg))
		{
			if (isGameStarted)
				player.processEnent(msg);
			else
			{
				btnStartGame.processEvent(msg, isGameStarted);
				btnQuitGame.processEvent(msg, isGameRunning);
			}
		}
		if (isGameStarted) 
		{
			//���������µ���
			tryGenerateEnemy(enemyList);
			//����ƶ�
			player.move();
			//�����ӵ�λ��
			updateBulllets(bulletList, player);

			//���µ���λ��
			for (Enemy* enemy : enemyList)
				enemy->move(player);

			//�����˺���ҵ���ײ
			for (Enemy* enemy : enemyList)
			{
				if (enemy->checkPlayerCollision(player))
				{
					static TCHAR text[128];
					_stprintf_s(text, _T("���յ÷֣�%d"), score);
					MessageBox(GetHWnd(), text, _T("��Ϸ����"), MB_OK);
					isGameRunning = false;
					break;
				}
			}
			//����ӵ��͵��˵���ײ
			for (Enemy* enemy : enemyList)
			{
				for (const Bullet& bullet : bulletList)
				{
					if (enemy->checkBulletCollision(bullet))
					{
						enemy->hurt();
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						score++;
					}
				}
			}
			//�Ƴ���������ĵ���
			for (size_t i = 0; i < enemyList.size(); i++)
			{
				Enemy* enemy = enemyList[i];
				if (!enemy->checkAlive())
				{
					std::swap(enemyList[i], enemyList.back());	//��������β������ȥ��
					enemyList.pop_back();
					delete enemy;
				}
			}
		}
		cleardevice();
		if (isGameStarted)
		{
			putimage(0, 0, &imagBackground);
			player.draw(1000 / 144);
			for (Enemy* enemy : enemyList)
				enemy->draw(1000 / 144);
			for (const Bullet& bullet : bulletList)
				bullet.draw();
			drawPlayerScore(score);
		}
		else
		{
			putimage(0, 0, &imgMenu);
			btnStartGame.draw();
			btnQuitGame.draw();
		}
		FlushBatchDraw();

		//�����Ż�
		DWORD endTime = GetTickCount();
		DWORD useTime = endTime - startTime;
		DWORD frameTime = 1000 / 144;
		if (frameTime > useTime)
		{
			Sleep(frameTime - useTime);
		}
	} 
	
	delete atlasPlayerLeft;
	delete atlasPlayerRight;
	delete atlasEnemyLeft;
	delete atlasEnemyRight;

	EndBatchDraw();

	return 0;
}
