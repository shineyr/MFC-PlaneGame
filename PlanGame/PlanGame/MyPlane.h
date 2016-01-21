#pragma once
#include "GameObject.h"

/************************************************************************/
/*                         战机对象
						  2016/01/18  yrr
*/
/************************************************************************/
class MyPlane :
	public GameObject
{
public:
	MyPlane();
	~MyPlane();

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImage();

	/*得到战机所在的矩形区域*/
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + PLANE_WIDTH, m_ptPos.y + PLANE_HEIGHT));
	}

	/*战机是否可以发射子弹*/
	BOOL isFired();

public:
	/*设置战机的长度和宽度*/
	static const int PLANE_WIDTH = 50;
	static const int PLANE_HEIGHT = 60;

private:
	static CImageList m_Images;/*存储战机图片*/
};

