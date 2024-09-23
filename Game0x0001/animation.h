#pragma once
#ifndef ___GAME0X0001_ANIMATION_H__
#define ___GAME0X0001_ANIMATION_H__

// -------------------------------------------------------
// animation.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/11
// ���������� ������
// �汾��
// --------------------------------------------------------

#pragma comment(lib, "MSIMG32.LIB")

#include <graphics.h>
#include <vector>
#include"atlas.h"


class Animation
{
public:
	//·����ͼƬ������֡���
	Animation(Atlas* const atlas, int interval);
	~Animation() = default; 

	static inline void putImageAlpha(int x, int y, IMAGE* img);
	void play(int x, int y, int delta);

private:
	int m_timer;			//������ʱ��
	int m_idxFrame;			//����֡����
	int m_interval;
	Atlas* m_animAtlas;		//������
public:
	Atlas* m_atlas_left;
	Atlas* m_atlas_right;
};

#endif // ___GAME0X0001_ANIMATION_H__
