#pragma once
#ifndef ___GAME0X0001_BUTTON_H__
#define ___GAME0X0001_BUTTON_H__

// -------------------------------------------------------
// button.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 按钮类
// 版本：
// --------------------------------------------------------

#include <graphics.h>

class Button
{
public:
	Button(RECT rect, LPCTSTR pathImgIdle, LPCTSTR pathImgHovered, LPCTSTR pathImgPushed);
	~Button() = default;
	void processEvent(const ExMessage& msg, bool& jugeGame);
	void draw();

protected:
	virtual void onClick(bool& jugeGame) = 0;

private:
	//检测鼠标点击
	bool checkCursorHit(int x, int y);

private:
	enum class Status
	{
		Idel = 0,
		Hovered,
		Pushed
	};

private:
	RECT m_region;
	IMAGE m_imgIdle;
	IMAGE m_imgHovered;
	IMAGE m_imgPushed;
	Status m_status;
};

#endif // ___GAME0X0001_BUTTON_H__

