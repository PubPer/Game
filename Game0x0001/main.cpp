#include <graphics.h>
#include <string>

#include"animation.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include "atlas.h"
#include"startGameButton.h"
#include"quitGameButton.h"


const int WINDOW_WIDTH = 1280;	//画面宽度
const int WINDOW_HEIGHT = 720;	//画面高度

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

Atlas* atlasPlayerLeft;
Atlas* atlasPlayerRight;
Atlas* atlasEnemyLeft;
Atlas* atlasEnemyRight;

bool isGameStarted = false;
bool isGameRunning = true;

#pragma comment(lib, "Winmm.lib")

//生成敌人
void tryGenerateEnemy(std::vector<Enemy*>& enemyList)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemyList.push_back(new Enemy(atlasEnemyLeft, atlasEnemyRight));
}

//更新子弹位置
void updateBulllets(std::vector<Bullet>& bulletList, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;							//径向波动速度
	const double TANGENT_SPEED = 0.0055;						//切向波动速度
	double radian_interval = 2 * 3.14159 / bulletList.size();	//子弹之间的弧度间隔
	POINT playerPosition = player.getPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bulletList.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;	//当前子弹所在的弧度
		bulletList[i].position.x = playerPosition.x + player.getPlayerWidth() / 2 + (int)(radius * sin(radian));
		bulletList[i].position.y = playerPosition.y + player.getPlayerHeight() / 2 + (int)(radius * cos(radian));
	}
}

void drawPlayerScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d"), score);

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

	//背景音乐加入
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

	//游戏主循环
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
			//尝试生成新敌人
			tryGenerateEnemy(enemyList);
			//玩家移动
			player.move();
			//更新子弹位置
			updateBulllets(bulletList, player);

			//更新敌人位置
			for (Enemy* enemy : enemyList)
				enemy->move(player);

			//检测敌人和玩家的碰撞
			for (Enemy* enemy : enemyList)
			{
				if (enemy->checkPlayerCollision(player))
				{
					static TCHAR text[128];
					_stprintf_s(text, _T("最终得分：%d"), score);
					MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
					isGameRunning = false;
					break;
				}
			}
			//检测子弹和敌人的碰撞
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
			//移除生命归零的敌人
			for (size_t i = 0; i < enemyList.size(); i++)
			{
				Enemy* enemy = enemyList[i];
				if (!enemy->checkAlive())
				{
					std::swap(enemyList[i], enemyList.back());	//换到队列尾，将其去除
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

		//进行优化
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
