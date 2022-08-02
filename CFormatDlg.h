#pragma once


// CFormatDlg dialog

class CFormatDlg : public CDialog
{
	DECLARE_DYNAMIC(CFormatDlg)

public:
	CFormatDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFormatDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_method;
	// distribution type
	int distr_type;
	afx_msg void OnBnClickedPoisson();
	afx_msg void OnBnClickedBinomial();
	afx_msg void OnBnClickedNegbinomial();
	afx_msg void OnBnClickedGeometric();

	CWnd* ctr;
	// parametr with int type
	int parametr_int;
	// parametr with type double
	double parametr_double;
	int parametr_int_h1;
	double parametr_double_h1;
	int sample_size;
	int n_pvalue_calc;
};
