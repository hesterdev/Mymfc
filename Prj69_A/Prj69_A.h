
// Prj69_A.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj69_AApp:
// See Prj69_A.cpp for the implementation of this class
//

class CPrj69_AApp : public CWinApp
{
public:
	CPrj69_AApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj69_AApp theApp;