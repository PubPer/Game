#pragma once
#ifndef ___GAME0X0001_STARTGAMEBUTTON_H__
#define ___GAME0X0001_STARTGAMEBUTTON_H__

// -------------------------------------------------------
// startGameButton.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 开始游戏按钮
// 版本：
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

