#include "enemy.h"

Enemy::Enemy(Atlas* const atlasLeft, Atlas* const atlasRight)
	:m_facingLeft(false)
	,m_alive(true)
{
	loadimage(&m_imgShadow, _T("resources/img/shadow_enemy.png"));
	m_animLeft = new Animation(atlasLeft, 45);
	m_animRight = new Animation(atlasRight, 45);

	//敌人生成边界
	enum class SpawnEdge
	{
		Up = 0,
		Down,
		Left,
		Right
	};

	//将敌人放置在地图外边界处的随机位置
	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::Up:
		m_framePosition.x = rand() % WINDOW_WIDTH;
		m_framePosition.y = -FRAME_HEIGHT;
		break;
	case SpawnEdge::Down:
		m_framePosition.x = rand() % WINDOW_WIDTH;
		m_framePosition.y = WINDOW_HEIGHT;
		break;
	case SpawnEdge::Left:
		m_framePosition.x = -FRAME_WIDTH;
		m_framePosition.y = rand() % WINDOW_HEIGHT;
		break;
	case SpawnEdge::Right:
		m_framePosition.x = WINDOW_WIDTH;
		m_framePosition.y = rand() % WINDOW_HEIGHT;
		break;
	default:
		break;
	}
}

Enemy::~Enemy()
{
	delete m_animLeft;
	delete m_animRight;
}

//暂时有问题，未检测
bool Enemy::checkPlayerCollision(const Player& player)
{
	//将敌人中心位置等效为点，判断点是否在玩家矩形内
	POINT checkPosition = { m_framePosition.x + FRAME_WIDTH / 2, m_framePosition.y + FRAME_HEIGHT / 2 };
	POINT playerPosition = player.getPosition();
	bool isOverlapX = checkPosition.x >= playerPosition.x && checkPosition.x <= playerPosition.x + FRAME_WIDTH;
	bool isOverlapY = checkPosition.y >= playerPosition.y && checkPosition.y <= playerPosition.y + FRAME_HEIGHT;
	return isOverlapX && isOverlapY;
}

bool Enemy::checkBulletCollision(const Bullet& bullet)
{
	//将子弹等效为点，判断点是否在敌人矩形内
	bool isOverlapX = bullet.position.x >= m_framePosition.x && bullet.position.x <= m_framePosition.x + FRAME_WIDTH;
	bool isOverlapY = bullet.position.y >= m_framePosition.y && bullet.position.y <= m_framePosition.y + FRAME_HEIGHT;
	return isOverlapX && isOverlapY;
}

bool Enemy::checkAlive()
{
	return m_alive;
}

void Enemy::move(const Player& player)
{
	const POINT& playerPosition = player.getPosition();
	int dirX = playerPosition.x - m_framePosition.x;
	int dirY = playerPosition.y - m_framePosition.y;
	double lenDir = sqrt(dirX * dirX + dirY * dirY);
	if (lenDir != 0)
	{
		double normalizedX = dirX / lenDir;
		double normalizedY = dirY / lenDir;
		m_framePosition.x += (int)(FRAME_SPEED * normalizedX);
		m_framePosition.y += (int)(FRAME_SPEED * normalizedY);
	}

	if (dirX < 0)
		m_facingLeft = true;
	else if (dirX > 0)
		m_facingLeft = false;
}

void Enemy::draw(int delta)
{
	int posShadowX = m_framePosition.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
	int posShadowY = m_framePosition.y + FRAME_HEIGHT - 35;
	Animation::putImageAlpha(posShadowX, posShadowY, &m_imgShadow);

	if (m_facingLeft)
		m_animLeft->play(m_framePosition.x, m_framePosition.y, delta);
	else
		m_animRight->play(m_framePosition.x, m_framePosition.y, delta);
}

void Enemy::hurt()
{
	m_alive = false;
}

