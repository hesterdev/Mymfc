
// �����߳�MFC54.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// C�����߳�MFC54App:
// See �����߳�MFC54.cpp for the implementation of this class
//

class C�����߳�MFC54App : public CWinApp
{
public:
	C�����߳�MFC54App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern C�����߳�MFC54App theApp;