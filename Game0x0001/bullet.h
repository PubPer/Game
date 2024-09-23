#pragma once
#ifndef ___GAME0X0001_BULLET_H__
#define ___GAME0X0001_BULLET_H__

// -------------------------------------------------------
// bullet.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 子弹类
// 版本：
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

