﻿
// DigitalEarthView.h: CDigitalEarthView 类的接口
//

#pragma once

#include "MFC_OSG.h"
class CDigitalEarthView : public CView
{
protected: // 仅从序列化创建
	CDigitalEarthView() noexcept;
	DECLARE_DYNCREATE(CDigitalEarthView)

// 特性
public:
	CDigitalEarthDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CDigitalEarthView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DigitalEarthView.cpp 中的调试版本
inline CDigitalEarthDoc* CDigitalEarthView::GetDocument() const
   { return reinterpret_cast<CDigitalEarthDoc*>(m_pDocument); }
#endif

