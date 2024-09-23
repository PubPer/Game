#pragma once
#ifndef ___GAME0X0001_ENEMY_H__
#define ___GAME0X0001_ENEMY_H__

// -------------------------------------------------------
// enemy.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� ������
// �汾��
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
	void hurt();					//�ܵ�����
	
private:
	const int FRAME_SPEED = 2;		//�����ƶ��ٶ�
	const int FRAME_WIDTH = 80;		//���˿��
	const int FRAME_HEIGHT = 80;	//���˸߶�
	const int SHADOW_WIDTH = 48;	//��Ӱ���

	const int WINDOW_WIDTH = 1280;	//������
	const int WINDOW_HEIGHT = 720;	//����߶�

private:
	IMAGE m_imgShadow;				//ͼƬ��Ӱ
	Animation* m_animLeft;			//������˶���
	Animation* m_animRight;			//������˶���
	POINT m_framePosition = {500, 500};			//����λ��
	bool m_facingLeft;
	bool m_alive;					//�Ƿ�����
};


#endif // ___GAME0X0001_ENEMY_H__

