#include "stdafx.h"
#include "MyBullet.h"

CImageList MyBullet::m_Images_UP;
CImageList MyBullet::m_Images_Down;

MyBullet::MyBullet(int x, int y, int dir)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	/*战机子弹速度*/
	m_speed = 30;
	m_direction = dir;
}


MyBullet::~MyBullet()
{
}

BOOL MyBullet::Draw(CDC *pDC, BOOL bPause)
{
	m_ptPos.y -= (m_speed * (m_direction == DOWN ? -1 : 1));

	if (m_direction == UP)
	{
		if (m_Images_UP.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT))
			return TRUE;
		else
			return FALSE;
	}//if
	else{
		if (m_Images_Down.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT))
			return TRUE;
		else
			return FALSE;
	}//else
}

BOOL MyBullet::LoadImageUp()
{
	return GameObject::LoadImage(m_Images_UP, IDB_MYBULLET_UP, RGB(0, 0, 0), 10, 20, 1);
}


BOOL MyBullet::LoadImageDown()
{
	return GameObject::LoadImage(m_Images_Down, IDB_MYBULLET_DOWN, RGB(0, 0, 0), 10, 20, 1);
}