#include "stdafx.h"
#include "EnemyBullet.h"


CImageList EnemyBullet::m_Images;
EnemyBullet::EnemyBullet(int x , int y,int dir)
{
	m_ptPos.x = x;
	m_ptPos.y = y;

	m_direction = dir;
	m_speed = 20;
}


EnemyBullet::~EnemyBullet()
{
}

BOOL EnemyBullet::Draw(CDC *pDC, BOOL bPause)
{
	int direction = rand() % 2;
	if (direction == 0)
		direction = DOWN;
	m_ptPos.x += (rand() % 10) * (m_speed - 20) *m_direction;
	m_ptPos.y += m_speed * m_direction;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL EnemyBullet::LoadImageW()
{
	return GameObject::LoadImage(m_Images, IDB_ENEMYBULLET, RGB(0, 0, 0), 8, 8, 1);
}