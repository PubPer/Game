#include "bullet.h"

void Bullet::draw() const
{
	//�Ⱥ�ɫ�ӵ�
	setlinecolor(RGB(255, 155, 50));
	setfillcolor(RGB(200, 75, 10));
	fillcircle(position.x, position.y, RADIUS);
}
