#pragma once
#ifndef ___GAME0X0001_ATLAS_H__
#define ___GAME0X0001_ATLAS_H__

// -------------------------------------------------------
// atlas.h
// �����ߣ� SkySea
// ����ʱ�䣺 2024/09/13
// ���������� ����ͼ����
// �汾��
// --------------------------------------------------------

#include <graphics.h>
#include <vector>

class Atlas
{
public: 
	Atlas(LPCTSTR path, int num);
	~Atlas();

public:
	std::vector<IMAGE*> m_frameList;
};

#endif // ___GAME0X0001_ATLAS_H__

