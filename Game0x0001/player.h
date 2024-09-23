#pragma once
#ifndef ___GAME0X0001_PLAYER_H__
#define ___GAME0X0001_PLAYER_H__

// -------------------------------------------------------
// player.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� �����
// �汾��
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
	const int PLAYER_SPEED = 5;		//����ƶ��ٶ�
	const int PLAYER_WIDTH = 80;	//��ҿ��
	const int PLAYER_HEIGHT = 80;	//��Ҹ߶�
	const int SHADOW_WIDTH = 32;	//��Ӱ���

	const int WINDOW_WIDTH = 1280;	//������
	const int WINDOW_HEIGHT = 720;	//����߶�

private:
	IMAGE m_imgShadow;				//ͼƬ��Ӱ
	Animation* m_animLeft;			//������Ҷ���
	Animation* m_animRight;			//������Ҷ���
	POINT m_playerPos = { 500, 500 };	//���λ��
	bool m_isMoveUp;
	bool m_isMoveDown;
	bool m_isMoveLeft;
	bool m_isMoveRight;
};

#endif // ___GAME0X0001_PLAYER_H__
