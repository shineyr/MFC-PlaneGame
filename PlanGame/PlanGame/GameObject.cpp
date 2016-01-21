#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(int x, int y) :m_ptPos(x,y)
{
}


GameObject::~GameObject()
{
}

/*加载游戏对象图像*/
BOOL GameObject::LoadImageW(CImageList &imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial)
{
	CBitmap bmp;
	if (!bmp.LoadBitmap(bmpID))
		return FALSE;

	if (!imgList.Create(cx, cy, ILC_COLOR24 | ILC_MASK, nInitial, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度

	imgList.Add(&bmp, crMask);

	return TRUE;
}
