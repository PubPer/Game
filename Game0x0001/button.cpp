#include "button.h"

Button::Button(RECT rect, LPCTSTR pathImgIdle, LPCTSTR pathImgHovered, LPCTSTR pathImgPushed)
	:m_region(rect)
	,m_status(Status::Idel)
{
	loadimage(&m_imgIdle, pathImgIdle);
	loadimage(&m_imgHovered, pathImgHovered);
	loadimage(&m_imgPushed, pathImgPushed);
}

void Button::processEvent(const ExMessage& msg, bool& jugeGame)
{
	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		if (m_status == Status::Idel && checkCursorHit(msg.x, msg.y))
			m_status = Status::Hovered;
		else if (m_status == Status::Hovered && !checkCursorHit(msg.x, msg.y))
			m_status = Status::Idel;
		break;
	case WM_LBUTTONDOWN:
		if (checkCursorHit(msg.x, msg.y))
			m_status = Status::Pushed;
		break;
	case WM_LBUTTONUP:
		if (m_status == Status::Pushed)
			onClick(jugeGame);
		break;
	default:
		break;
	}
}

void Button::draw()
{
	switch (m_status)
	{
	case Status::Idel:
		putimage(m_region.left, m_region.top, &m_imgIdle);
		break;
	case Status::Hovered:
		putimage(m_region.left, m_region.top, &m_imgHovered);
		break;
	case Status::Pushed:
		putimage(m_region.left, m_region.top, &m_imgPushed);
		break;
	}
}

bool Button::checkCursorHit(int x, int y)
{
	return x>=m_region.left && x<= m_region.right && y<= m_region.bottom && y>= m_region.top;
}
