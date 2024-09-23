#pragma once
#ifndef ___GAME0X0001_ATLAS_H__
#define ___GAME0X0001_ATLAS_H__

// -------------------------------------------------------
// atlas.h
// 创建者： SkySea
// 创建时间： 2024/09/13
// 功能描述： 动画图集类
// 版本：
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

