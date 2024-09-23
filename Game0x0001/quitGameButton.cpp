#include "quitGameButton.h"

QuitGameButton::QuitGameButton(RECT rect, LPCTSTR pathImgIdle, LPCTSTR pathImgHovered, LPCTSTR pathImgPushed)
	:Button(rect, pathImgIdle, pathImgHovered, pathImgPushed)
{
}

void QuitGameButton::onClick(bool& jugeGame)
{
	jugeGame = false;
}
