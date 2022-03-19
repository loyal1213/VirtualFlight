﻿
// DigitalEarthView.cpp: CDigitalEarthView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DigitalEarth.h"
#endif

#include "DigitalEarthDoc.h"
#include "DigitalEarthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalEarthView

IMPLEMENT_DYNCREATE(CDigitalEarthView, CView)

BEGIN_MESSAGE_MAP(CDigitalEarthView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDigitalEarthView 构造/析构

CDigitalEarthView::CDigitalEarthView() noexcept
{
	// TODO: 在此处添加构造代码

}

CDigitalEarthView::~CDigitalEarthView()
{
}

BOOL CDigitalEarthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDigitalEarthView 绘图

void CDigitalEarthView::OnDraw(CDC* /*pDC*/)
{
	CDigitalEarthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDigitalEarthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDigitalEarthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDigitalEarthView 诊断

#ifdef _DEBUG
void CDigitalEarthView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalEarthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalEarthDoc* CDigitalEarthView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalEarthDoc)));
	return (CDigitalEarthDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalEarthView 消息处理程序
