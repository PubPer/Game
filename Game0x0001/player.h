#pragma once
#ifndef ___GAME0X0001_PLAYER_H__
#define ___GAME0X0001_PLAYER_H__

// -------------------------------------------------------
// player.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 玩家类
// 版本：
// --------------------------------------------------------

#include <graphics.h>
#include"animation.h"

class Player
{
public:
	Player(Atlas* const atlasLeft, Atlas* const atlasRight);
	~Player();
	void processEnent(const ExMessage& msg);
	void move();
	void draw(int delta);
	const POINT& getPosition() const;
	int getPlayerWidth() const;
	int getPlayerHeight() const;

private:
	const int PLAYER_SPEED = 5;		//玩家移动速度
	const int PLAYER_WIDTH = 80;	//玩家宽度
	const int PLAYER_HEIGHT = 80;	//玩家高度
	const int SHADOW_WIDTH = 32;	//阴影宽度

	const int WINDOW_WIDTH = 1280;	//画面宽度
	const int WINDOW_HEIGHT = 720;	//画面高度

private:
	IMAGE m_imgShadow;				//图片阴影
	Animation* m_animLeft;			//左向玩家动画
	Animation* m_animRight;			//右向玩家动画
	POINT m_playerPos = { 500, 500 };	//玩家位置
	bool m_isMoveUp;
	bool m_isMoveDown;
	bool m_isMoveLeft;
	bool m_isMoveRight;
};

#endif // ___GAME0X0001_PLAYER_H__
