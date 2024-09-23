#pragma once
#ifndef ___GAME0X0001_QUITGAMEBUTTON_H__
#define ___GAME0X0001_QUITGAMEBUTTON_H__

// -------------------------------------------------------
// quitGameButton.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� �˳���Ϸ��ť
// �汾��
// --------------------------------------------------------

#include <graphics.h>
#include "button.h"
class QuitGameButton : public Button
{
public:
	QuitGameButton(RECT rect, LPCTSTR pathImgIdle, LPCTSTR pathImgHovered, LPCTSTR pathImgPushed);
	~QuitGameButton() = default;

protected:
	void onClick(bool& jugeGame) override;

};


#endif // ___GAME0X0001_QUITGAMEBUTTON_H__

