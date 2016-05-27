
// Prj69_B.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj69_BApp:
// See Prj69_B.cpp for the implementation of this class
//

class CPrj69_BApp : public CWinApp
{
public:
	CPrj69_BApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj69_BApp theApp;