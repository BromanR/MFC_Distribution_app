
// MFC_Distribution_appView.cpp : implementation of the CMFCDistributionappView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Distribution_app.h"
#endif

#include "MFC_Distribution_appDoc.h"
#include "MFC_Distribution_appView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDistributionappView

IMPLEMENT_DYNCREATE(CMFCDistributionappView, CView)

BEGIN_MESSAGE_MAP(CMFCDistributionappView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCDistributionappView construction/destruction

CMFCDistributionappView::CMFCDistributionappView() noexcept
{
	// TODO: add construction code here

}

CMFCDistributionappView::~CMFCDistributionappView()
{
}

BOOL CMFCDistributionappView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDistributionappView drawing

void CMFCDistributionappView::OnDraw(CDC* pDC)
{
	CMFCDistributionappDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int print_mode = pDoc->print_mode;
	if (print_mode == 1)
		PrintHist();
	if (print_mode ==2)
		PrintPValue();
	// TODO: add draw code for native data here
}

void CMFCDistributionappView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDistributionappView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDistributionappView diagnostics

#ifdef _DEBUG
void CMFCDistributionappView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDistributionappView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDistributionappDoc* CMFCDistributionappView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDistributionappDoc)));
	return (CMFCDistributionappDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDistributionappView message handlers

void CMFCDistributionappView::PrintHist()
{
	CMFCDistributionappDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);

	COLORREF colour_1 = pDoc->hist_colour_1;
	COLORREF colour_2 = pDoc->hist_colour_2;
	CRect rc;
	GetClientRect(&rc);


	int* emp_freq = pDoc->emp_freq;
	double* theor_freq = pDoc->theor_freq;
	int n;

	int z = 0;
	int tmp = 0;
	while (emp_freq[z] < emp_freq[z + 1] || theor_freq[z] < theor_freq[z + 1]) ++z;
	while (emp_freq[z] > 1 || theor_freq[z] > 1) { 
		++z; 
	}

	if (z == 0) { n = 30; }
	n = z;


	int max = -1;
	for (int i = 0; i < n; ++i) {
		if (max < emp_freq[i]) max = emp_freq[i];
	}
	CBrush br;
	br.CreateHatchBrush(6, colour_1);
	CBrush* pOldBrush = (CBrush*)dc.SelectObject(&br);
	double emp_column_width = 7 * rc.Width() / (n * 11);
	for (int i = 0; i < n; ++i) {
		dc.Rectangle(rc.Width() / 20 + i * 7 * rc.Width() / (n * 10),
			(1 - double(emp_freq[i]) / (max + 20)) * rc.Height(),
			rc.Width() / 20 + i * 7 * rc.Width() / (n * 10)+emp_column_width,
			rc.Height());
	}


	dc.Rectangle(rc.Width() * 8.5 / 10, rc.Height() * 1.3 / 10, rc.Width() * 8.7 / 10, rc.Height() * 1.6 / 10);
	dc.TextOut(rc.Width() * 8.8 / 10, rc.Height() * 1.3 / 10, L"Empirical");

	br.DeleteObject();
	br.CreateHatchBrush(6, colour_2);
	pOldBrush = (CBrush*)dc.SelectObject(&br);
	for (int i = 0; i < n; ++i) {
		dc.Rectangle(rc.Width() / 20+emp_column_width/7 + i * 7 * rc.Width() / (n * 10),
			(1 - double(theor_freq[i]) / (max + 20)) * rc.Height(),
			rc.Width() / 20+ 6*emp_column_width / 7 + i * 7 * rc.Width() / (n * 10),
			rc.Height());
	}

	dc.Rectangle(rc.Width() * 8.5 / 10, rc.Height() * 1.3 / 10 + 50, rc.Width() * 8.7 / 10, rc.Height() * 1.6 / 10 + 50);
	dc.TextOut(rc.Width() * 8.8 / 10, rc.Height() * 1.3 / 10 + 50, L"Theoretical");

	dc.SelectObject(pOldBrush);
	br.DeleteObject();
}

void CMFCDistributionappView::PrintPValue() {
	CMFCDistributionappDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);


	COLORREF colour_1 = RGB(248, 118, 109);
	COLORREF colour_2 = RGB(0, 191, 196);
	CRect rc;
	GetClientRect(&rc);
	CPen pen;
	pen.CreatePen(3, 4, colour_2);
	CPen* pOldPen = (CPen*)dc.SelectObject(&pen);

	double* cdf = pDoc->cdf;

	double field_coors[4] = { rc.Width() / 10, rc.Height() / 10,
		rc.Width() * 8 / 10, rc.Height() * 8 / 10 };

	dc.MoveTo(field_coors[0], field_coors[3]);
	double step = 5;
	for (int i = 0; i < 100; i += step) {
		dc.LineTo(field_coors[0] + (i + step * 9 / 10) * (field_coors[2] - field_coors[0]) / 100,
			field_coors[3] * (1 - cdf[int(i / step)] * 87 / 100));
	}
	dc.MoveTo(rc.Width() * 8.5 / 10, rc.Height() * 1.3 / 10);
	dc.LineTo(rc.Width() * 9 / 10, rc.Height() * 1.3 / 10);
	dc.TextOut(rc.Width() * 8.5 / 10, rc.Height() * 0.8 / 10, L"P-value");

	dc.SelectObject(pOldPen);
	dc.MoveTo(field_coors[0], field_coors[3]);
	dc.LineTo(field_coors[0], field_coors[1]);
	dc.MoveTo(field_coors[0], field_coors[3]);
	dc.LineTo(field_coors[2], field_coors[3]);

	dc.SelectObject(pOldPen);
	pen.DeleteObject();
	pen.CreatePen(3, 4, colour_1);
	pOldPen = (CPen*)dc.SelectObject(&pen);
	dc.MoveTo(field_coors[0], field_coors[3]);
	dc.LineTo(field_coors[2], field_coors[1]);
	dc.TextOut(field_coors[0] * 9 / 10, field_coors[1], L"1");
	dc.TextOut(field_coors[2], field_coors[3], L"1");
	dc.TextOut(field_coors[0], field_coors[3], L"0");

	dc.MoveTo(rc.Width() * 8.5 / 10, rc.Height() * 3 / 10);
	dc.LineTo(rc.Width() * 9 / 10, rc.Height() * 3 / 10);
	dc.TextOut(rc.Width() * 8.5 / 10, rc.Height() * 2.5 / 10, L"CDF Uniform");


	dc.SelectObject(pOldPen);
	pen.DeleteObject();
}

