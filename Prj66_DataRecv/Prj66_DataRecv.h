
// Prj66_DataRecv.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj66_DataRecvApp:
// See Prj66_DataRecv.cpp for the implementation of this class
//

class CPrj66_DataRecvApp : public CWinApp
{
public:
	CPrj66_DataRecvApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj66_DataRecvApp theApp;