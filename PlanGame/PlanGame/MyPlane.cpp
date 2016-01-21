#include "stdafx.h"
#include "MyPlane.h"

CImageList MyPlane::m_Images;
MyPlane::MyPlane()
{
	/*设置战机的初始位置*/
	m_ptPos.x = 400;
	m_ptPos.y = 500;
}


MyPlane::~MyPlane()
{
}

BOOL MyPlane::Draw(CDC *pDC, BOOL bPause)
{
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL MyPlane::LoadImageW()
{
	return GameObject::LoadImage(m_Images, IDB_MYPLANE, RGB(0, 0, 0), 50, 60, 1);
}

BOOL MyPlane::isFired()
{
	return TRUE;
}