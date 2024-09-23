#include "player.h"

Player::Player(Atlas* const atlasLeft, Atlas* const atlasRight)
	:m_isMoveUp(false)
	,m_isMoveDown(false)
	,m_isMoveLeft(false)
	,m_isMoveRight(false)
{
	loadimage(&m_imgShadow, _T("resources/img/shadow_player.png"));
	m_animLeft = new Animation(atlasLeft, 45);
	m_animRight = new Animation(atlasRight, 45);
}

Player::~Player()
{
	delete m_animLeft;
	delete m_animRight;
}

void Player::processEnent(const ExMessage& msg)
{
		//键盘控制玩家移动逻辑，实现移动丝滑
	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
			{
			case VK_UP:
				m_isMoveUp = true;
				break;
			case VK_DOWN:
				m_isMoveDown = true;
				break;
			case VK_LEFT:
				m_isMoveLeft = true;
				break;
			case VK_RIGHT:
				m_isMoveRight = true;
				break;
			}
		break;

	case WM_KEYUP:
		switch (msg.vkcode)
			{
			case VK_UP:
				m_isMoveUp = false;
				break;
			case VK_DOWN:
				m_isMoveDown = false;
				break;
			case VK_LEFT:
				m_isMoveLeft = false;
				break;
			case VK_RIGHT:
				m_isMoveRight = false;
				break;
			}
		break;
	}
}

void Player::move()
{
	int dirX = m_isMoveRight - m_isMoveLeft;	//X方向上的变化量
	int dirY = m_isMoveDown - m_isMoveUp;		//Y方向上的变化量
	double lenDir = sqrt((double)(dirX * dirX + dirY * dirY));
	if (lenDir != 0)
	{
		double normalizedX = dirX / lenDir;
		double normalizedY = dirY / lenDir;
		m_playerPos.x += (int)(PLAYER_SPEED * normalizedX);
		m_playerPos.y += (int)(PLAYER_SPEED * normalizedY);
	}

	if (m_playerPos.x < 0) m_playerPos.x = 0;
	if (m_playerPos.y < 0) m_playerPos.y = 0;
	if (m_playerPos.y + PLAYER_HEIGHT > WINDOW_HEIGHT) m_playerPos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
	if (m_playerPos.x + PLAYER_WIDTH > WINDOW_WIDTH) m_playerPos.x = WINDOW_WIDTH - PLAYER_WIDTH;
}

void Player::draw(int delta)
{
	int posShadowX = m_playerPos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int posShadowY = m_playerPos.y + PLAYER_HEIGHT - 8;
	Animation::putImageAlpha(posShadowX, posShadowY, &m_imgShadow);

	static bool facingLeft = false;	//判断左右转向问题
	int dirX = m_isMoveRight - m_isMoveLeft;
	if (dirX < 0)
		facingLeft = true;
	else if (dirX > 0)
		facingLeft = false;

	if (facingLeft)
		m_animLeft->play(m_playerPos.x, m_playerPos.y, delta);
	else
		m_animRight->play(m_playerPos.x, m_playerPos.y, delta);
}

const POINT& Player::getPosition() const
{
	return m_playerPos;
}

int Player::getPlayerWidth() const
{
	return PLAYER_WIDTH;
}

int Player::getPlayerHeight() const
{
	return PLAYER_HEIGHT;
}
