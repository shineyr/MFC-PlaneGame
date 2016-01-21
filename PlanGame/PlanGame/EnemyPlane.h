#pragma once
#include "GameObject.h"

/************************************************************************/
/*                         敌机对象
						  2016/01/18  yrr
*/
/************************************************************************/

class EnemyPlane :
	public GameObject
{
public:
	EnemyPlane(int motion);
	~EnemyPlane();

	BOOL Draw(CDC *pDC, BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYPLANE_HEIGHT, m_ptPos.y + ENEMYPLANE_HEIGHT));
	}

	int GetDirection()	const
	{
		return m_direction;
	}

	void SetDirection(int dir)
	{
		m_direction = dir;
	}

	void SetSpeed(int s)
	{
		m_speed = s;
	}

	BOOL isFired();
private:
	/*敌机的宽度、高度*/
	static const int ENEMYPLANE_HEIGHT = 35;
	static CImageList m_Images;

	/*敌机运行方向 1*/
	int m_direction;

	/*敌机图像索引*/
	int m_nImgIdx;

	/*敌机速度*/
	int m_speed;

	/*发射延时*/
	int m_wait;
};

