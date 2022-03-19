
// MFC_OSG_MDIView.h: CMFCOSGMDIView 类的接口
//

#pragma once
#include "MFC_OSG.h"

class CMFCOSGMDIView : public CView
{
protected: // 仅从序列化创建
	CMFCOSGMDIView() noexcept;
	DECLARE_DYNCREATE(CMFCOSGMDIView)

// 特性
public:
	CMFCOSGMDIDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFCOSGMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	cOSG* mOSG;
	//HANDLE mThreadHandle;
	CRenderingThread* mThreadHandle;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnFileNew();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFC_OSG_MDIView.cpp 中的调试版本
inline CMFCOSGMDIDoc* CMFCOSGMDIView::GetDocument() const
   { return reinterpret_cast<CMFCOSGMDIDoc*>(m_pDocument); }
#endif

