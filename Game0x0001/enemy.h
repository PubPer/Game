#pragma once
#ifndef ___GAME0X0001_ENEMY_H__
#define ___GAME0X0001_ENEMY_H__

// -------------------------------------------------------
// enemy.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 敌人类
// 版本：
// --------------------------------------------------------

#include <graphics.h>
#include "animation.h"
#include "bullet.h"
#include "player.h"
#include"atlas.h"

class Enemy
{
public:
	Enemy(Atlas* const atlasLeft, Atlas* const atlasRight);
	~Enemy();
	bool checkPlayerCollision(const Player& player);
	bool checkBulletCollision(const Bullet& bullet);
	bool checkAlive();
	void move(const Player& player);
	void draw(int delta);
	void hurt();					//受到攻击
	
private:
	const int FRAME_SPEED = 2;		//敌人移动速度
	const int FRAME_WIDTH = 80;		//敌人宽度
	const int FRAME_HEIGHT = 80;	//敌人高度
	const int SHADOW_WIDTH = 48;	//阴影宽度

	const int WINDOW_WIDTH = 1280;	//画面宽度
	const int WINDOW_HEIGHT = 720;	//画面高度

private:
	IMAGE m_imgShadow;				//图片阴影
	Animation* m_animLeft;			//左向敌人动画
	Animation* m_animRight;			//右向敌人动画
	POINT m_framePosition = {500, 500};			//敌人位置
	bool m_facingLeft;
	bool m_alive;					//是否存活标记
};


#endif // ___GAME0X0001_ENEMY_H__

