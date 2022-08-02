
// MFC_Distribution_appDoc.h : interface of the CMFCDistributionappDoc class
//


#pragma once
#include "ChiSq.h"
#include "Sample.h"
#include "Binomial.h"
#include "Geom.h"
#include "TheorGeom.h"
#include "TheorBinomial.h"
#include "TheorNegativeBinomial.h"
#include "NegativeBinomial.h"
#include "TheorPoisson.h"
#include "Poisson.h"
#include "R32M.h"


class CMFCDistributionappDoc : public CDocument
{
protected: // create from serialization only
	CMFCDistributionappDoc() noexcept;
	DECLARE_DYNCREATE(CMFCDistributionappDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCDistributionappDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
int print_mode;
int* emp_freq;
double* theor_freq;
double* cdf;
int n_pvalue_calc;
Sample* pSample;
Theor* pTheor;
Theor* pTheorH1;
int distr_type;
int sample_size;

COLORREF hist_colour_1;
COLORREF hist_colour_2;

void MakeHist();
void PvalueCDF();
void UpdateParams();

afx_msg void OnHistogram();
afx_msg void OnPValue();
afx_msg void OnSettings();

double lambda;
int n;
double p;

double lambda_h1;
int n_h1;
double p_h1;

};
