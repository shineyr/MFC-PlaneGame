
// PlanGameView.h : CPlanGameView 类的接口
//

#pragma once
#include "GameObject.h"
#include "MyPlane.h"
#include "EnemyPlane.h"
#include "MyBullet.h"
#include "EnemyBullet.h"
#include "Explosion.h"

#define TIME1 30
#define TIME2 300
#define TIME3 600

class CPlanGameView : public CView
{
protected: // 仅从序列化创建
	CPlanGameView();
	DECLARE_DYNCREATE(CPlanGameView)

// 特性
public:
	CPlanGameDoc* GetDocument() const;

	/*创建各个游戏对象*/
	MyPlane *myPlane;
	EnemyPlane *enemyPlane;
	MyBullet *myBullet;
	EnemyBullet *enemyBullet;
	Explosion *explosion;

	/*创建游戏对象存储链表*/
	CObList myPlaneList;
	CObList enemyPlaneList;
	CObList myBulletList;
	CObList enemyBulletList;
	CObList explosionList;

	/*战机速度*/
	int myPlaneSpeed;	/*战机飞行速度*/
	int myLifeTime;		/*战机生命值*/
	int myScore;	/*战机得分*/
	int myLifeCount;	/*生命值变化值*/
	int myPass;		/*当前关卡*/
	int is_pass;	/*是否通关*/
	int is_pause;	/*是否暂停*/

// 操作
public:
	int GetSpeed()	const{
		return myPlaneSpeed;
	}

	void SetSpeed(int s)
	{
		myPlaneSpeed = s;
	}

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	/*绘制画布*/
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
// 实现
public:
	virtual ~CPlanGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	/*重启应用程序*/
	afx_msg void OnRestart();
	/*暂停应用*/
	afx_msg void OnPause();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PlanGameView.cpp 中的调试版本
inline CPlanGameDoc* CPlanGameView::GetDocument() const
   { return reinterpret_cast<CPlanGameDoc*>(m_pDocument); }
#endif

