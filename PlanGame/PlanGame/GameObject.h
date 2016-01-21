#pragma once
#include "afx.h"
#include "Resource.h"
/************************************************************************/
/*                         游戏对象的父类
						 2016/01/18  yrr
*/
/************************************************************************/
/*游戏对象飞行方向*/
enum Direction{
	STOP,
	UP,
	DOWN
};

/*对象图像索引*/
enum ImageIdx{
	UP_IDX,
	DOWN_IDX
};

class GameObject :
	public CObject
{
public:
	GameObject(int x = 0, int y = 0);
	/*虚析构函数，正确释放子类对象资源*/
	virtual ~GameObject();

	/*绘制图像*/
	virtual BOOL Draw(CDC *pDC, BOOL bPause) = 0;
	/*获得矩形区域*/
	virtual CRect GetRect() = 0;

	/*获得游戏对象的左上角坐标*/
	CPoint GetPoint()
	{
		return m_ptPos;
	}

	/*设置游戏对象坐标*/
	void SetPoint(int x, int y)
	{
		m_ptPos.x = x;
		m_ptPos.y = y;
	}

protected:
	/*加载图像*/
	static BOOL LoadImage(CImageList &imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);

protected:
	/*游戏对象的坐标位置*/
	CPoint m_ptPos;
};
