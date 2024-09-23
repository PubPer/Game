#pragma once
#ifndef ___GAME0X0001_ANIMATION_H__
#define ___GAME0X0001_ANIMATION_H__

// -------------------------------------------------------
// animation.h
// 创建者： SkySea
// 创建时间： 2024/09/11
// 功能描述： 动画类
// 版本：
// --------------------------------------------------------

#pragma comment(lib, "MSIMG32.LIB")

#include <graphics.h>
#include <vector>
#include"atlas.h"


class Animation
{
public:
	//路径，图片数量，帧间隔
	Animation(Atlas* const atlas, int interval);
	~Animation() = default; 

	static inline void putImageAlpha(int x, int y, IMAGE* img);
	void play(int x, int y, int delta);

private:
	int m_timer;			//动画计时器
	int m_idxFrame;			//动画帧索引
	int m_interval;
	Atlas* m_animAtlas;		//动画集
public:
	Atlas* m_atlas_left;
	Atlas* m_atlas_right;
};

#endif // ___GAME0X0001_ANIMATION_H__
