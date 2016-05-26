
// 创建线程MFC54.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C创建线程MFC54App:
// See 创建线程MFC54.cpp for the implementation of this class
//

class C创建线程MFC54App : public CWinApp
{
public:
	C创建线程MFC54App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C创建线程MFC54App theApp;