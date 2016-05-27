
// Prj70_A.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj70_AApp:
// See Prj70_A.cpp for the implementation of this class
//

class CPrj70_AApp : public CWinApp
{
public:
	CPrj70_AApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj70_AApp theApp;