#pragma once
#ifndef ___GAME0X0001_QUITGAMEBUTTON_H__
#define ___GAME0X0001_QUITGAMEBUTTON_H__

// -------------------------------------------------------
// quitGameButton.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 退出游戏按钮
// 版本：
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

