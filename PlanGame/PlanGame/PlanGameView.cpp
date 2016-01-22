
// PlanGameView.cpp : CPlanGameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlanGame.h"
#endif

#include "PlanGameDoc.h"
#include "PlanGameView.h"

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanGameView

IMPLEMENT_DYNCREATE(CPlanGameView, CView)

BEGIN_MESSAGE_MAP(CPlanGameView, CView)
	/*标准打印命令*/
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_UPDATEUISTATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_RESTART, &CPlanGameView::OnRestart)
	ON_COMMAND(ID_PAUSE , &CPlanGameView::OnPause)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPlanGameView 构造/析构
//战机生命值、战机得分、战机增加生命值数、关卡、是否过关、是否暂停
CPlanGameView::CPlanGameView():
myLifeTime(10), myScore(0), myLifeCount(1), myPass(1), is_pass(0), is_pause(0)
{
	// TODO:  在此处添加构造代码
	/*默认战机飞行速度*/
	myPlaneSpeed = 30;

	/*加载各个游戏对象的图片*/
	MyPlane::LoadImageW();
	EnemyPlane::LoadImageW();
	MyBullet::LoadImageUp();
	MyBullet::LoadImageDown();
	EnemyBullet::LoadImageW();
	Explosion::LoadImageW();
}

CPlanGameView::~CPlanGameView()
{
}

BOOL CPlanGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlanGameView 绘制

void CPlanGameView::OnDraw(CDC* /*pDC*/)
{
	CPlanGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}

/*CPlaneGameView 打印*/
BOOL CPlanGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	/*默认准备*/
	return DoPreparePrinting(pInfo);
}

void CPlanGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanGameView 诊断

#ifdef _DEBUG
void CPlanGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanGameDoc* CPlanGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanGameDoc)));
	return (CPlanGameDoc*)m_pDocument;
}
#endif //_DEBUG

// CPlanGameView 消息处理程序
int CPlanGameView::OnCreate(LPCREATESTRUCT lpcs)
{
	/*视图创建失败*/
	if (CView::OnCreate(lpcs) == -1)
	{
		return -1;
	}//if

	/*TODO: 应用程序专用代码 2016/01/11*/
	//（1）创建战机对象
	myPlane = new MyPlane;
	//（2）设置说明对话框 (其中#define IDYES 6 #define IDNO 7)
	if (AfxMessageBox(L"查看游戏说明请点击“是”，若直接进入游戏请点击“否”！", MB_YESNO) == 6)
	{
		AfxMessageBox(L"方向键控制战机方向，空格键射击，鼠标均可控制。初始生命值为10,消灭一个敌机加1分，如果分数达到要求即可进入下一关。随着关卡增多，敌机速度和数量均增加，通过3关即可通关！");
		/*设置睡眠时间，单位毫秒*/
		Sleep(1000);
	}//if
	/*进入主界面，设置刷新定时*/
	SetTimer(1, TIME1, NULL);
	SetTimer(2, TIME2, NULL);
	SetTimer(3, TIME3, NULL);
	return 0;
}

/************************************************************************/
/*nIDEvent来自于上步中 SetTimer函数*/
void CPlanGameView::OnTimer(UINT nIDEvent)
{
	/*获取矩形区域*/
	CDC *pDC = GetDC();
	CRect cRect;
	GetClientRect(&cRect);

	/*设备环境对象类 ---- CDC类*/
	CDC cdc;
	/*内存中承载临时图位图*/
	CBitmap bitMap1;

	//该函数创建一个与指定设备兼容的内存设备上下文环境（DC）
	cdc.CreateCompatibleDC(pDC);
	//该函数创建与指定的设备环境相关的设备兼容的位图
	bitMap1.CreateCompatibleBitmap(pDC, cRect.Width(), cRect.Height());
	//该函数选择一对象到指定的设备上下文环境中，该新对象替换先前的相同类型的对象。
	CBitmap *pOldBit = cdc.SelectObject(&bitMap1);
	//用固定的固体色填充文本矩形框
	cdc.FillSolidRect(cRect, RGB(51, 255, 255));
	//添加背景图片
	CBitmap bgBitMap;
	bgBitMap.LoadBitmap(IDB_BACKGROUND);

	/*位图2*/
	BITMAP bitMap2;
	bgBitMap.GetBitmap(&bitMap2);

	/*定义一个兼容的CDC*/
	CDC bgCdc;
	bgCdc.CreateCompatibleDC(&cdc);

	CBitmap *old = bgCdc.SelectObject(&bgBitMap);
	cdc.StretchBlt(0, 0, cRect.Width(), cRect.Height(), &bgCdc, 0, 0, bitMap2.bmWidth, bitMap2.bmHeight, SRCCOPY);

	/*==================================添加战机,键盘手动控制战机======================================*/
	if (myPlane != NULL)
	{
		myPlane->Draw(&cdc, TRUE);
	}//if
	/*获得用户按下的键盘消息，战机位置做出响应*/
	if ((GetKeyState(VK_UP) < 0 || GetKeyState('W') < 0) && is_pause == 0)
	{
		/*战机坐标超过了上边界*/
		if (myPlane->GetPoint().y < cRect.top)
			myPlane->SetPoint(myPlane->GetPoint().x, cRect.bottom);
		else
			myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y - myPlaneSpeed);
	}//if
	if ((GetKeyState(VK_DOWN) < 0 || GetKeyState('S') < 0) && is_pause == 0)//下方向键
	{
		if (myPlane->GetPoint().y>cRect.bottom)
			myPlane->SetPoint(myPlane->GetPoint().x, cRect.top);
		else
			myPlane->SetPoint(myPlane->GetPoint().x, (myPlane->GetPoint().y + myPlaneSpeed));
	}//if
	if ((GetKeyState(VK_LEFT) < 0 || GetKeyState('A') < 0) && is_pause == 0)//左方向键
	{
		if (myPlane->GetPoint().x < cRect.left)
			myPlane->SetPoint(cRect.right, myPlane->GetPoint().y);
		else
			myPlane->SetPoint((myPlane->GetPoint().x - myPlaneSpeed), myPlane->GetPoint().y);
	}//if
	if ((GetKeyState(VK_RIGHT) < 0 || GetKeyState('D') < 0) && is_pause == 0)//右方向键
	{
		if (myPlane->GetPoint().x > cRect.right)
			myPlane->SetPoint(cRect.left, myPlane->GetPoint().y);
		else
			myPlane->SetPoint((myPlane->GetPoint().x + myPlaneSpeed), myPlane->GetPoint().y);
	}//if
	/*空格键发射子弹（战机发射双列子弹）*/
	if (GetKeyState(VK_SPACE) < 0 && is_pause == 0)
	{
		MyBullet *bullet1 = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y, UP);
		myBulletList.AddTail(bullet1);
		MyBullet *bullet2 = new MyBullet(myPlane->GetPoint().x + 35, myPlane->GetPoint().y, UP);
		myBulletList.AddTail(bullet2);
		/*播放战机发射子弹声音*/
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	}//if

	/*Z键代表暂停*/
	if (GetKeyState('Z') < 0)
	{
		is_pause += 1;
		if (is_pause != 1)
			is_pause = 0;
	}//if

	/*=====随机添加敌机,敌机随机发射炸弹，此时敌机速度与数量和关卡有关 =======================*/
	if (myPlane != NULL && is_pause == 0)
	{
		switch (nIDEvent)
		{
		case 2:
			{
				  /*当前处于第一关卡*/
				  if (1 == myPass)
				  {
					  int dir = UP;
					  EnemyPlane *enemyPlane1 = new EnemyPlane(dir);
					  enemyPlaneList.AddTail(enemyPlane1);
				  }//if
				  /*当前处于第二以上关卡，敌机从上下两个方向飞出*/
				  else if (2 <= myPass)
				  {
					  int dir1 = UP;
					  EnemyPlane *enemyPlane1 = new EnemyPlane(dir1);
					  /*敌机的飞行速度根据关卡不同*/
					  enemyPlane1->SetSpeed((rand() % 5 + 1) * myPass);
					  enemyPlaneList.AddTail(enemyPlane1);

					  int dir2 = DOWN;
					  EnemyPlane *enemyPlane2 = new EnemyPlane(dir2);
					  enemyPlane2->SetSpeed((rand() % 5 + 1) * myPass);
					  enemyPlaneList.AddTail(enemyPlane2);
				  }//elif
			}//case
			break;

		default:
			break;
		}//switch

		/*删除在游戏界面之外的敌机*/
		POSITION epPos = NULL, epPosTmp = NULL;
		epPos = enemyPlaneList.GetHeadPosition();
		while (epPos != NULL)
		{
			epPosTmp = epPos;
			enemyPlane = (EnemyPlane *)enemyPlaneList.GetNext(epPos);
			/*判断敌机是否出界*/
			if (enemyPlane->GetPoint().x < cRect.left || enemyPlane->GetPoint().x > cRect.right ||
				enemyPlane->GetPoint().y < cRect.top || enemyPlane->GetPoint().y > cRect.bottom)
			{
				enemyPlaneList.RemoveAt(epPosTmp);
				delete enemyPlane;
			}//if
			else{
				enemyPlane->Draw(&cdc, TRUE);
				switch (nIDEvent)
				{
				//设置定时器产生敌机炸弹
				case 3:
					{
						  EnemyBullet *eb = new EnemyBullet(enemyPlane->GetPoint().x + 17, enemyPlane->GetPoint().y + 30, enemyPlane->GetDirection());
						  enemyBulletList.AddTail(eb);
						  /*敌机发射子弹*/
						  PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					}//case
					break;
				}//switch
			}//else
		}//while

		/*判断该敌机发射的子弹是否出界，若出界则删除*/
		POSITION ebPos = NULL, ebPosTmp = NULL;
		ebPos = enemyBulletList.GetHeadPosition();
		while (ebPos != NULL)
		{
			ebPosTmp = ebPos;
			enemyBullet = (EnemyBullet *)enemyBulletList.GetNext(ebPos);
			if (enemyBullet->GetPoint().x <cRect.left || enemyBullet->GetPoint().x > cRect.right ||
				enemyBullet->GetPoint().y < cRect.top || enemyBullet->GetPoint().y >cRect.bottom)
			{
				enemyBulletList.RemoveAt(ebPosTmp);
				delete enemyBullet;
			}//if
			else{
				enemyBullet->Draw(&cdc, TRUE);
			}//else
		}//while
	}//if

	/*=============================处理战机发射子弹======================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		/*声明子弹位置*/
		POSITION mbPos = NULL, mbPosTmp = NULL;
		mbPos = myBulletList.GetHeadPosition();
		while (mbPos != NULL)
		{
			mbPosTmp = mbPos;
			myBullet = (MyBullet *)myBulletList.GetNext(mbPos);
			/*删除越界的子弹*/
			if (myBullet->GetPoint().x < cRect.left || myBullet->GetPoint().x > cRect.right ||
				myBullet->GetPoint().y < cRect.top || myBullet->GetPoint().y > cRect.bottom)
			{
				myBulletList.RemoveAt(mbPosTmp);
				delete myBullet;
			}//if
			else
				myBullet->Draw(&cdc, TRUE);
		}//while
	}//if

	/*=================（1）添加爆炸效果，战机子弹打中敌机================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		POSITION explosionPos = NULL;
		explosionPos = explosionList.GetHeadPosition();
		/*检查爆炸列表，非空时在其所在位置显示*/
		while (explosionPos != NULL)
		{
			explosion = (Explosion *)explosionList.GetNext(explosionPos);
			explosion->Draw(&cdc, TRUE);
		}//while
		POSITION mbPos, mbPosTmp, epPos, epPosTmp;
		for (mbPos = myBulletList.GetHeadPosition(); (mbPosTmp = mbPos) != NULL;)
		{
			/*战机子弹*/
			myBullet = (MyBullet *)myBulletList.GetNext(mbPos);
			/*获得战机子弹的矩形区域*/
			CRect myBulletRect = myBullet->GetRect();
			/*遍历所有敌机，若有与战机子弹交叉者则爆炸，销毁敌机*/
			for (epPos = enemyPlaneList.GetHeadPosition(); (epPosTmp = epPos) != NULL;)
			{
				enemyPlane = (EnemyPlane *)enemyPlaneList.GetNext(epPos);
				/*获得敌机所在矩形区域*/
				CRect enemyPlaneRect = enemyPlane->GetRect();
				/*判断该敌机与战机子弹有没有交叉*/
				CRect tmpRect;
				if (tmpRect.IntersectRect(&myBulletRect, &enemyPlaneRect))
				{
					/*将爆炸对象加入爆炸列表*/
					Explosion *explosion = new Explosion((enemyPlane->GetPoint().x + 17), (enemyPlane->GetPoint().y + 17));
					explosionList.AddTail(explosion);
					/*播放爆炸声音*/
					PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					
					/*爆炸后删除子弹*/
					myBulletList.RemoveAt(mbPosTmp);
					delete myBullet;

					/*删除敌机*/
					enemyPlaneList.RemoveAt(epPosTmp);
					delete enemyPlane;

					/*打中一个敌机，战机积一分*/
					++myScore;
					break;
				}//if
			}
		}//for
	}//if

	/*=================（2）添加爆炸效果，敌机子弹打中战机================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		/*敌机子弹位置*/
		POSITION ebPos, ebPosTmp;
		for (ebPos = enemyBulletList.GetHeadPosition(); (ebPosTmp = ebPos) != NULL;)
		{
			enemyBullet = (EnemyBullet *)enemyBulletList.GetNext(ebPos);
			/*获得敌机子弹的矩形区域*/
			CRect enemyBulletRect = enemyBullet->GetRect();
			/*获得战机矩形区域*/
			CRect myPlaneRect = myPlane->GetRect();
			/*判断有无交叉*/
			CRect tmpRect;
			if (tmpRect.IntersectRect(&enemyBulletRect, &myPlaneRect))
			{
				/*将爆炸对象加入爆炸列表*/
				Explosion *explosion = new Explosion((enemyPlane->GetPoint().x + 17), (enemyPlane->GetPoint().y + 17));
				explosionList.AddTail(explosion);
				/*播放爆炸声音*/
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				/*删除敌机子弹*/
				enemyBulletList.RemoveAt(ebPosTmp);
				delete enemyBullet;

				/*生命值减一*/
				--myLifeTime;
				if (0 == myLifeTime)
				{
					/*删除战机*/
					delete myPlane;
					myPlane = NULL;
				}//if
				break;
			}//if
		}//for
	}//if
	/*=================（3）添加爆炸效果，战机与敌机相撞================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		POSITION epPos, epPosTmp;
		for (epPos = enemyPlaneList.GetHeadPosition(); (epPosTmp = epPos) != NULL;)
		{
			enemyPlane = (EnemyPlane *)enemyPlaneList.GetNext(epPos);
			/*获得敌机矩形区域*/
			CRect enemyPlaneRect = enemyPlane->GetRect();
			/*获得战机矩形区域*/
			CRect myPlaneRect = myPlane->GetRect();

			CRect tmpRect;
			if (tmpRect.IntersectRect(&enemyPlaneRect, &myPlaneRect))
			{
				Explosion *explosion = new Explosion((enemyPlane->GetPoint().x + 18), (enemyPlane->GetPoint().y + 18));
				explosionList.AddTail(explosion);
				/*播放爆炸声音*/
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				/*删除敌机*/
				enemyPlaneList.RemoveAt(epPosTmp);
				delete enemyPlane;

				/*战机生命值减一*/
				--myLifeTime;
				if (0 == myLifeTime)
				{
					/*删除战机对象*/
					delete myPlane;
					myPlane = NULL;
				}//if
				break;
			}//if
		}//for
	}//if
	/*=================（4）添加爆炸效果，战机子弹与敌机子弹相撞================================*/
	if (myPlane != NULL && is_pause == 0)
	{
		/*声明战机子弹、敌机子弹位置*/
		POSITION mbPos, mbPosTmp, ebPos, ebPosTmp;
		for (mbPos = myBulletList.GetHeadPosition(); (mbPosTmp = mbPos) != NULL;)
		{
			myBullet = (MyBullet *)myBulletList.GetNext(mbPos);
			/*获得战机子弹的矩形区域*/
			CRect myBulletRect = myBullet->GetRect();
			for (ebPos = enemyBulletList.GetHeadPosition(); (ebPosTmp = ebPos) != NULL;)
			{
				enemyBullet = (EnemyBullet *)enemyBulletList.GetNext(ebPos);
				/*获得敌机子弹的矩形区域*/
				CRect enemyBulletRect = enemyBullet->GetRect();
				/*判断有无交叉*/
				CRect tmpRect;
				if (tmpRect.IntersectRect(&myBulletRect, &enemyBulletRect))
				{
					//将爆炸对象添加到爆炸链表中
					Explosion *explosion = new Explosion((enemyBullet->GetPoint().x + 17), (enemyBullet->GetPoint().y + 17));
					explosionList.AddTail(explosion);

					/*播放爆炸声音*/
					PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					//爆炸后删除战机子弹
					myBulletList.RemoveAt(mbPosTmp);
					delete myBullet;

					/*删除敌机子弹*/
					enemyBulletList.RemoveAt(ebPosTmp);
					delete enemyBullet;

					/*战机积一分*/
					++myLifeTime;
					break;
				}//if
			}//for
		}//for
	}//if
	/*=================================游戏界面输出该游戏当前信息========================*/
	if (myPlane != NULL && is_pause == 0)
	{
		HFONT font;
		font = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(font);
		CString str;
		cdc.SetTextColor(RGB(255, 0, 0));
		str.Format(_T("当前关卡:%d"), myPass);
		cdc.TextOutW(10, 20, str);
		str.Format(_T("当前得分:%d"), myScore);
		cdc.TextOutW(10, 40, str);
		str.Format(_T("剩余生命:%d"), myLifeTime);
		cdc.TextOutW(10, 60, str);
	}//if
	/*按要求增加战机生命值*/
	if (myPlane != NULL && is_pause == 0)
	{
		if (myScore > 10 * myLifeCount * myPass)
		{
			myLifeTime++;
			myLifeCount++;
		}
	}//if
	/*=================================进入下一关界面========================*/
	if (myPlane != NULL && myScore > 50 * myPass && is_pause == 0)
	{
		delete myPlane;
		myPlane = NULL;
		/*这一关已经通过*/
		is_pass = 1;
	}//if
	/*进入下一关*/
	if (is_pass == 1)
	{
		/*过了第三关，则该游戏战机已通关*/
		if (3 == myPass)
		{
			/*关闭计时器*/
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			if (AfxMessageBox(L"哇，恭喜你已通关！是否重新开始？", MB_YESNO) == 6)
			{
				/*清空战机链表*/
				myPlaneList.RemoveAll();
				/*清空敌机链表*/
				enemyPlaneList.RemoveAll();
				/*清空战机子弹链表*/
				myBulletList.RemoveAll();
				/*清空敌机子弹链表*/
				enemyBulletList.RemoveAll();
				/*清空炸弹链表*/
				explosionList.RemoveAll();

				/*生成新的战机*/
				myPlane = new MyPlane;
				myScore = 0;
				myLifeCount = 1;
				myLifeTime = 10;
				myPass = 1;
				is_pass = 0;
				SetTimer(1, TIME1, NULL);
				SetTimer(2, TIME2, NULL);
				SetTimer(3, TIME3, NULL);
			}//if
			else
				exit(1);
		}//if
		else{
			/*关闭计时器*/
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			if (AfxMessageBox(L"哇，恭喜你已通过此关！是否进入下一关？", MB_YESNO) == 6)
			{
				/*清空战机链表*/
				myPlaneList.RemoveAll();
				/*清空敌机链表*/
				enemyPlaneList.RemoveAll();
				/*清空战机子弹链表*/
				myBulletList.RemoveAll();
				/*清空敌机子弹链表*/
				enemyBulletList.RemoveAll();
				/*清空炸弹链表*/
				explosionList.RemoveAll();
				/*生成新的战机*/
				myPlane = new MyPlane;
				myScore = 0;
				myLifeCount = 1;
				myLifeTime = 10;
				++myPass;
				is_pass = 0;
				SetTimer(1, TIME1, NULL);
				SetTimer(2, TIME2, NULL);
				SetTimer(3, TIME3, NULL);
			}//if
			else
				exit(1);
		}//else
	}//if
	/*=================================结束游戏的界面========================*/
	if (myPlane == NULL && is_pass == 0 && is_pause == 0)
	{
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		if (AfxMessageBox(L"GAME OVER！COME ON ！重新开始？", MB_YESNO) == 6)
		{
			/*清空战机链表*/
			myPlaneList.RemoveAll();
			/*清空敌机链表*/
			enemyPlaneList.RemoveAll();
			/*清空战机子弹链表*/
			myBulletList.RemoveAll();
			/*清空敌机子弹链表*/
			enemyBulletList.RemoveAll();
			/*清空炸弹链表*/
			explosionList.RemoveAll();

			/*生成新的战机*/
			myPlane = new MyPlane;
			myScore = 0;
			myLifeCount = 1;
			myLifeTime = 10;
			myPass = 1;
			is_pass = 0;
			SetTimer(1, TIME1, NULL);
			SetTimer(2, TIME2, NULL);
			SetTimer(3, TIME3, NULL);
		}//if
		else
			exit(1);
	}//if

	/*该函数对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境*/
	pDC->BitBlt(0, 0, cRect.Width(), cRect.Height(), &cdc, 0, 0, SRCCOPY);
	cdc.DeleteDC();
	bitMap1.DeleteObject();
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}//onTimer
/*===================================================================================*/
void CPlanGameView::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
}

BOOL CPlanGameView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}
/*重启应用程序*/
void CPlanGameView::OnRestart()
{
	/*清空战机链表*/
	myPlaneList.RemoveAll();
	/*清空敌机链表*/
	enemyPlaneList.RemoveAll();
	/*清空战机子弹链表*/
	myBulletList.RemoveAll();
	/*清空敌机子弹链表*/
	enemyBulletList.RemoveAll();
	/*清空炸弹链表*/
	explosionList.RemoveAll();

	/*生成新的战机*/
	myPlane = new MyPlane;
	myScore = 0;
	myLifeCount = 1;
	myLifeTime = 10;
	myPass = 1;
	is_pass = 0;

	SetTimer(1, TIME1, NULL);
	SetTimer(2, TIME2, NULL);
	SetTimer(3, TIME3, NULL);
}
/*暂停应用*/
void CPlanGameView::OnPause()
{
	// TODO: 在此添加命令处理程序代码
	Sleep(1000);
}
void CPlanGameView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnMouseMove(nFlags, point);
	if (is_pause == 0)
		myPlane->SetPoint(point.x, point.y);
}

void CPlanGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnLButtonDown(nFlags, point);
	if (is_pause == 0)
	{
		MyBullet *myBullet1 = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y, UP);
		/*发射子弹声音*/
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		myBulletList.AddTail(myBullet1);
		MyBullet *myBullet2 = new MyBullet(myPlane->GetPoint().x + 35, myPlane->GetPoint().y, UP);
		myBulletList.AddTail(myBullet2);
	}//if
}