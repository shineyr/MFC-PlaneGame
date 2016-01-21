#pragma once
#include "GameObject.h"


/************************************************************************/
/*                        敌机子弹对象
						2016/01/18  yrr
*/
/************************************************************************/


class EnemyBullet :
	public GameObject
{
public:
	EnemyBullet(int x, int y,int dir);
	~EnemyBullet();

	BOOL Draw(CDC *pDC, BOOL bPause);
	static BOOL LoadImage();
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMYBULLET_HEIGHT, m_ptPos.y + ENEMYBULLET_HEIGHT));
	}

	void SetSpeed(int s)
	{
		m_speed = s;
	}

	int GetSpeed()		const
	{
		return m_speed;
	}
private:
	static const int ENEMYBULLET_HEIGHT = 8;
	static CImageList m_Images;

	int m_direction;
	int m_speed;
};

