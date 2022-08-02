
// MFC_Distribution_app.h : main header file for the MFC_Distribution_app application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCDistributionappApp:
// See MFC_Distribution_app.cpp for the implementation of this class
//

class CMFCDistributionappApp : public CWinAppEx
{
public:
	CMFCDistributionappApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCDistributionappApp theApp;
