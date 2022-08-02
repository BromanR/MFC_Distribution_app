
// MFC_Distribution_appView.h : interface of the CMFCDistributionappView class
//

#pragma once


class CMFCDistributionappView : public CView
{
protected: // create from serialization only
	CMFCDistributionappView() noexcept;
	DECLARE_DYNCREATE(CMFCDistributionappView)

// Attributes
public:
	CMFCDistributionappDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCDistributionappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	void PrintHist();
	void PrintPValue();
};

#ifndef _DEBUG  // debug version in MFC_Distribution_appView.cpp
inline CMFCDistributionappDoc* CMFCDistributionappView::GetDocument() const
   { return reinterpret_cast<CMFCDistributionappDoc*>(m_pDocument); }
#endif

