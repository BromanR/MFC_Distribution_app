// CFormatDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_Distribution_app.h"
#include "CFormatDlg.h"
#include "afxdialogex.h"


// CFormatDlg dialog

IMPLEMENT_DYNAMIC(CFormatDlg, CDialog)

CFormatDlg::CFormatDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, distr_type(0)
	, parametr_int(0)
	, parametr_double(0)
	, parametr_int_h1(0)
	, parametr_double_h1(0)
	, sample_size(0)
	, n_pvalue_calc(0)
{
	ctr = NULL; 
}

CFormatDlg::~CFormatDlg()
{
}

void CFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_POISSON, distr_type);
	DDX_Text(pDX, IDC_EDIT1, parametr_int);
	DDX_Text(pDX, IDC_EDIT2, parametr_double);
	DDX_Text(pDX, IDC_EDIT3, parametr_int_h1);
	DDX_Text(pDX, IDC_EDIT4, parametr_double_h1);
	DDX_Text(pDX, IDC_EDIT5, sample_size);
	DDX_Text(pDX, IDC_EDIT6, n_pvalue_calc);
}


BEGIN_MESSAGE_MAP(CFormatDlg, CDialog)
	ON_BN_CLICKED(IDC_POISSON, &CFormatDlg::OnBnClickedPoisson)
	ON_BN_CLICKED(IDC_BINOMIAL, &CFormatDlg::OnBnClickedBinomial)
	ON_BN_CLICKED(IDC_NEGBINOMIAL, &CFormatDlg::OnBnClickedNegbinomial)
	ON_BN_CLICKED(IDC_GEOMETRIC, &CFormatDlg::OnBnClickedGeometric)
END_MESSAGE_MAP()


// CFormatDlg message handlers



void CFormatDlg::OnBnClickedPoisson()
{
	ctr = GetDlgItem(IDC_EDIT1);
	ctr->EnableWindow(0);
	ctr = GetDlgItem(IDC_EDIT3);
	ctr->EnableWindow(0);

	if (parametr_double < 1) {
		UpdateData(TRUE);
		parametr_double = 5;
		UpdateData(FALSE);
	}
	if (parametr_double_h1 < 1) {
		UpdateData(TRUE);
		parametr_double_h1 = 5;
		UpdateData(FALSE);
	}

}


void CFormatDlg::OnBnClickedBinomial()
{
	ctr = GetDlgItem(IDC_EDIT1);
	ctr->EnableWindow(1);
	ctr = GetDlgItem(IDC_EDIT3);
	ctr->EnableWindow(1);

	if (parametr_double > 1) {
		UpdateData(TRUE);
		parametr_double = 0.4;
		UpdateData(FALSE);
	}
	if (parametr_double_h1 > 1) {
		UpdateData(TRUE);
		parametr_double_h1 = 0.4;
		UpdateData(FALSE);
	}

}


void CFormatDlg::OnBnClickedNegbinomial()
{
	ctr = GetDlgItem(IDC_EDIT1);
	ctr->EnableWindow(1);
	ctr = GetDlgItem(IDC_EDIT3);
	ctr->EnableWindow(1);

	if (parametr_double > 1) {
		UpdateData(TRUE);
		parametr_double = 0.4;
		UpdateData(FALSE);
	}
	if (parametr_double_h1 > 1) {
		UpdateData(TRUE);
		parametr_double_h1 = 0.4;
		UpdateData(FALSE);
	}
}


void CFormatDlg::OnBnClickedGeometric()
{
	ctr = GetDlgItem(IDC_EDIT1);
	ctr->EnableWindow(0);
	ctr = GetDlgItem(IDC_EDIT3);
	ctr->EnableWindow(0);
	if (parametr_double > 1) {
		UpdateData(TRUE);
		parametr_double = 0.4;
		UpdateData(FALSE);
	}
	if (parametr_double_h1 > 1) {
		UpdateData(TRUE);
		parametr_double_h1 = 0.4;
		UpdateData(FALSE);
	}
}


