#pragma once
#ifndef ___GAME0X0001_BUTTON_H__
#define ___GAME0X0001_BUTTON_H__

// -------------------------------------------------------
// button.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� ��ť��
// �汾��
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
	//��������
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

