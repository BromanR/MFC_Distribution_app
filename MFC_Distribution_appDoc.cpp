
// MFC_Distribution_appDoc.cpp : implementation of the CMFCDistributionappDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Distribution_app.h"
#endif

#include "MFC_Distribution_appDoc.h"

#include <propkey.h>
#include "CFormatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCDistributionappDoc

IMPLEMENT_DYNCREATE(CMFCDistributionappDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDistributionappDoc, CDocument)
	ON_COMMAND(ID_HISTOGRAM, &CMFCDistributionappDoc::OnHistogram)
	ON_COMMAND(ID_CDFPVALUE, &CMFCDistributionappDoc::OnPValue)
	ON_COMMAND(ID_SETTINGS, &CMFCDistributionappDoc::OnSettings)
END_MESSAGE_MAP()


// CMFCDistributionappDoc construction/destruction

CMFCDistributionappDoc::CMFCDistributionappDoc() noexcept :hist_colour_1(RGB(248, 118, 109)), hist_colour_2(RGB(0, 191, 196)),
print_mode(0), cdf(new double[21]{}), n_pvalue_calc(1000), distr_type(0), lambda(5), n(10), p(0.4), sample_size(100),
lambda_h1(5), n_h1(10), p_h1(0.4)
{
	rninit(13337);

	pTheor = new TheorPoisson(lambda);
	pTheorH1 = new TheorPoisson(lambda_h1);
	pSample = new Poisson(lambda_h1, sample_size);
	pSample->generateSample(pTheorH1);
	this->emp_freq = new int[pTheor->getTheorSize() + 1];
	this->theor_freq = new double[pTheor->getTheorSize() + 1];
}

CMFCDistributionappDoc::~CMFCDistributionappDoc()
{
	delete[] emp_freq;
	delete[] theor_freq;
	delete[] cdf;
	delete pTheorH1;
	delete pTheor;
	delete pSample;
}

BOOL CMFCDistributionappDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCDistributionappDoc serialization

void CMFCDistributionappDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCDistributionappDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCDistributionappDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDistributionappDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCDistributionappDoc diagnostics

#ifdef _DEBUG
void CMFCDistributionappDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDistributionappDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDistributionappDoc commands

void CMFCDistributionappDoc::MakeHist()
{
	pSample->generateSample(pTheorH1);
	ChiSq Chi(*pSample, *pTheor);
	memcpy(this->emp_freq, Chi.getEmpFreq(), sizeof(int) * (pTheor->getTheorSize() + 1));
	memcpy(this->theor_freq, Chi.getTheorFreq(), sizeof(double) * (pTheor->getTheorSize() + 1));
}

void CMFCDistributionappDoc::PvalueCDF() {
	for (int i = 0; i < 20; ++i) {
		this->cdf[i] = 0;
	}
	for (int i = 0; i < n_pvalue_calc; ++i) {
		pSample->generateSample(pTheorH1);
		ChiSq Chi(*pSample, *pTheor);
		Chi.calcPvalue();
		++this->cdf[int(Chi.getPvalue() * 20)];
	}
	for (int i = 1; i < 21; ++i) {
		this->cdf[i] += this->cdf[i - 1];
		this->cdf[i - 1] /= n_pvalue_calc;
	}
}


void CMFCDistributionappDoc::OnHistogram()
{
	print_mode = 1;
	MakeHist();
	UpdateAllViews(0);
}


void CMFCDistributionappDoc::OnPValue()
{
	print_mode = 2;
	PvalueCDF();
	UpdateAllViews(0);
}


void CMFCDistributionappDoc::OnSettings()
{
	CFormatDlg d;
	d.distr_type = distr_type;
	d.parametr_int = n;
	d.parametr_int_h1 = n_h1;
	if (distr_type == 0) {
		d.parametr_double = lambda;
		d.parametr_double_h1 = lambda_h1;
	}
	else {
		d.parametr_double = p;
		d.parametr_double_h1 = p_h1;
	}
	d.sample_size = sample_size;
	d.n_pvalue_calc = n_pvalue_calc;

	if (d.DoModal() == IDOK) {
		distr_type = d.distr_type;
		n=d.parametr_int;
		n_h1 = d.parametr_int_h1;
		if (distr_type == 0) {
			lambda = d.parametr_double;
			lambda_h1 = d.parametr_double_h1;
		}
		else {
			p = d.parametr_double;
			p_h1 = d.parametr_double_h1;
		}
		sample_size = d.sample_size;
		n_pvalue_calc =d.n_pvalue_calc;

		UpdateParams();
		if (print_mode == 1)
			OnHistogram();
		if (print_mode == 2)
			OnPValue();
	}
}

void CMFCDistributionappDoc::UpdateParams() {
	delete pSample;
	delete pTheor;
	delete pTheorH1;
	delete[] emp_freq;
	delete[] theor_freq;
	if (distr_type == 0) {
		pSample = new Poisson(lambda_h1, sample_size);
		pTheor = new TheorPoisson(lambda);
		pTheorH1 = new TheorPoisson(lambda_h1);
	}

	else if (distr_type == 1) {
		pTheor = new TheorBinomial(n, p);
		pSample = new Binomial(n, p, sample_size);
		pTheorH1 = new TheorBinomial(n_h1, p_h1);
	}
	else if (distr_type == 2) {
		pTheor = new TheorNegativeBinomial(n, p);
		pSample = new NegativeBinomial(n, p, sample_size);
		pTheorH1 = new TheorNegativeBinomial(n_h1, p_h1);
	}
	else if (distr_type == 3) {
		pTheor = new TheorGeom(p);
		pSample = new Geom(p, sample_size);
		pTheorH1 = new TheorGeom(p_h1);
	}
	this->emp_freq = new int[pTheor->getTheorSize() + 1];
	this->theor_freq = new double[pTheor->getTheorSize() + 1];
}

