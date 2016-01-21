#include "stdafx.h"
#include "Explosion.h"

CImageList Explosion::m_Images;
Explosion::Explosion(int x, int y) :m_nProcess(0)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
}


Explosion::~Explosion()
{
}

BOOL Explosion::Draw(CDC *pDC, BOOL bPause)
{
	while (m_nProcess < 8)
	{
		m_Images.Draw(pDC, m_nProcess, m_ptPos, ILD_TRANSPARENT);
		++m_nProcess;
	}//while
	return TRUE;
}

BOOL Explosion::LoadImageW()
{
	return GameObject::LoadImage(m_Images, IDB_EXPLOSION, RGB(0, 0, 0), 66, 66, 8);
}