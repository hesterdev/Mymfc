
// Prj67_B.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj67_BApp:
// See Prj67_B.cpp for the implementation of this class
//

class CPrj67_BApp : public CWinApp
{
public:
	CPrj67_BApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj67_BApp theApp;