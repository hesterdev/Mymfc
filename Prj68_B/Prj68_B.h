
// Prj68_B.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj68_BApp:
// See Prj68_B.cpp for the implementation of this class
//

class CPrj68_BApp : public CWinApp
{
public:
	CPrj68_BApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj68_BApp theApp;