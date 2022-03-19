
// MFC_OSG_MDIView.cpp: CMFCOSGMDIView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_OSG_MDI.h"
#endif

#include "MFC_OSG_MDIDoc.h"
#include "MFC_OSG_MDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCOSGMDIView

IMPLEMENT_DYNCREATE(CMFCOSGMDIView, CView)

BEGIN_MESSAGE_MAP(CMFCOSGMDIView, CView)
//	ON_COMMAND(ID_FILE_NEW, &CMFCOSGMDIView::OnFileNew)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCOSGMDIView 构造/析构

CMFCOSGMDIView::CMFCOSGMDIView() noexcept
	:mOSG(0L)
{
	// TODO: 在此处添加构造代码

}

CMFCOSGMDIView::~CMFCOSGMDIView()
{
}

BOOL CMFCOSGMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCOSGMDIView 绘图

void CMFCOSGMDIView::OnDraw(CDC* /*pDC*/)
{
	CMFCOSGMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCOSGMDIView 诊断

#ifdef _DEBUG
void CMFCOSGMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOSGMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOSGMDIDoc* CMFCOSGMDIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOSGMDIDoc)));
	return (CMFCOSGMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCOSGMDIView 消息处理程序


//void CMFCOSGMDIView::OnFileNew()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CMFCOSGMDIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// Get Filename from DocumentOpen Dialog
	CString csFileName = GetDocument()->GetFileName();

	// Init the osg class
	mOSG->InitOSG(csFileName.GetString());

	// Start the thread to do OSG Rendering
	//mThreadHandle = (HANDLE)_beginthread(&cOSG::Render, 0, mOSG); 
	mThreadHandle = new CRenderingThread(mOSG);
	mThreadHandle->start();
}


int CMFCOSGMDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Let MFC create the window before OSG
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Now that the window is created setup OSG
	mOSG = new cOSG(m_hWnd);

	return 1;
}


void CMFCOSGMDIView::OnDestroy()
{
	delete mThreadHandle;
	if (mOSG != 0) delete mOSG;

	//WaitForSingleObject(mThreadHandle, 1000);

	CView::OnDestroy();
}


void CMFCOSGMDIView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// CView::OnKeyDown(nChar, nRepCnt, nFlags);

		// Close Window on Escape Key
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SendMessage(WM_CLOSE);
	}
}


BOOL CMFCOSGMDIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	// return CView::OnEraseBkgnd(pDC);
}
