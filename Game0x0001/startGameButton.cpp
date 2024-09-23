#include "startGameButton.h"

StartGameButton::StartGameButton(RECT rect, LPCTSTR pathImgIdle, LPCTSTR pathImgHovered, LPCTSTR pathImgPushed)
	:Button(rect, pathImgIdle, pathImgHovered, pathImgPushed)
{
}

void StartGameButton::onClick(bool& jugeGame)
{
	jugeGame = true;
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	
}
