#pragma once
#include "GameObject.h"

/************************************************************************/
/*                        战机子弹对象
						2016/01/18  yrr
*/
/************************************************************************/

class MyBullet :
	public GameObject
{
public:
	MyBullet(int x, int y, int direction);
	~MyBullet();

	BOOL Draw(CDC *pDC, BOOL bPause);
	static BOOL LoadImageUp();
	static BOOL LoadImageDown();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + MYBULLET_HEIGHT));
	}

	int GetHeight()		const
	{
		return MYBULLET_HEIGHT;
	}

	void SetDirection(int dir)
	{
		m_direction = dir;
	}

	int GetDirection()		const
	{
		return m_direction;
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
	static const int MYBULLET_HEIGHT = 200;
	static CImageList m_Images_Down;
	static CImageList m_Images_UP;

	int m_direction;
	int m_speed;
};

