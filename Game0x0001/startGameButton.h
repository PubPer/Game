#pragma once
#ifndef ___GAME0X0001_STARTGAMEBUTTON_H__
#define ___GAME0X0001_STARTGAMEBUTTON_H__

// -------------------------------------------------------
// startGameButton.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� ��ʼ��Ϸ��ť
// �汾��
// --------------------------------------------------------

#include <graphics.h>
#include "button.h"
class StartGameButton : public Button
{
public:
	StartGameButton(RECT rect, LPCTSTR pathImgIdle, LPCTSTR pathImgHovered, LPCTSTR pathImgPushed);
	~StartGameButton() = default;

protected:
	void onClick(bool& jugeGame) override;

};


#endif // ___GAME0X0001_STARTGAMEBUTTON_H__

