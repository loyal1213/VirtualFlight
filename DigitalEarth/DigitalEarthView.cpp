
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
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
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

//void CDigitalEarthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

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


int CDigitalEarthView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Now that the window is created setup OSG
	mOSG = new cOSG(m_hWnd);

	return 0;
}


void CDigitalEarthView::OnDestroy()
{
	delete mThreadHandle;
	if (mOSG != 0) delete mOSG;

	//WaitForSingleObject(mThreadHandle, 1000);

	CView::OnDestroy();
}


BOOL CDigitalEarthView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CDigitalEarthView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDigitalEarthView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CString csFileName = this->GetDocument()->GetFileName();

	// Init the osg class
	mOSG->InitOSG(csFileName.GetString());

	// Start the thread to do OSG Rendering
	//mThreadHandle = (HANDLE)_beginthread(&cOSG::Render, 0, mOSG); 
	mThreadHandle = new CRenderingThread(mOSG);
	mThreadHandle->start();
}
