#include "atlas.h"

Atlas::Atlas(LPCTSTR path, int num)
{
	TCHAR pathFile[256];
	for (size_t i = 0; i < num; i++)
	{
		_stprintf_s(pathFile, path, i);

		IMAGE* frame = new IMAGE();
		loadimage(frame, pathFile);
		m_frameList.push_back(frame);
	}
}

Atlas::~Atlas()
{
	for (size_t i = 0; i < m_frameList.size(); i++)
		delete m_frameList[i];
}
