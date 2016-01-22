#include "stdafx.h"
#include "EnemyPlane.h"

CImageList EnemyPlane::m_Images;

EnemyPlane::EnemyPlane(int motion) :m_wait(0), m_speed(1)
{
	m_direction = motion;
	int random = rand();
	/*随机产生敌机的位置*/
	m_ptPos.x = rand() % 1000;
	/*敌机飞行方向为向下*/
	if (m_direction == DOWN)
	{
		m_ptPos.y = 600;
		m_nImgIdx = DOWN_IDX;
	}//if
	/*敌机飞行方向为向上*/
	else{
		m_ptPos.y = 0;
		m_nImgIdx = UP_IDX;
	}//else
}


EnemyPlane::~EnemyPlane()
{
}

BOOL EnemyPlane::Draw(CDC *pDC, BOOL bPause)
{
	/*敌机的位置随机变化*/
	/*敌机向上飞*/
	if (m_direction == UP)
		m_ptPos.y += (m_speed + rand() % 10);
	/*敌机向下飞*/
	else
		m_ptPos.y -= (m_speed + rand() % 10);
	m_Images.Draw(pDC, m_nImgIdx, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL EnemyPlane::LoadImageW()
{
	return GameObject::LoadImage(m_Images, IDB_ENEMYPLANE, RGB(0, 0, 0), 35, 35, 1);
}

BOOL EnemyPlane::isFired()
{
	return TRUE;
}