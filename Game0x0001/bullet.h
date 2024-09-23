#pragma once
#ifndef ___GAME0X0001_BULLET_H__
#define ___GAME0X0001_BULLET_H__

// -------------------------------------------------------
// bullet.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� �ӵ���
// �汾��
// --------------------------------------------------------

#include <graphics.h>

class Bullet
{
public:
	POINT position = { 0, 0 };
public:
	Bullet() = default;
	~Bullet() = default;

	void draw() const;

private:
	const int RADIUS = 10;
};

#endif // ___GAME0X0001_BULLET_H__

