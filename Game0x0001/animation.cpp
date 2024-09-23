#include "animation.h"

Animation::Animation(Atlas* const atlas, int interval)
	:m_timer(0)
	,m_idxFrame(0)
	,m_interval(0)
{
	m_animAtlas = atlas;
	m_interval = interval;
}

void inline Animation::putImageAlpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void Animation::play(int x, int y, int delta)
{
	m_timer += delta;
	if (m_timer >= m_interval)
	{
		m_idxFrame = (m_idxFrame + 1) %m_animAtlas->m_frameList.size();
		m_timer = 0;
	}
	putImageAlpha(x, y,m_animAtlas->m_frameList[m_idxFrame]);

}
