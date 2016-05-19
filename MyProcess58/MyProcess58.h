
// MyProcess58.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyProcess58App:
// See MyProcess58.cpp for the implementation of this class
//

class CMyProcess58App : public CWinApp
{
public:
	CMyProcess58App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyProcess58App theApp;