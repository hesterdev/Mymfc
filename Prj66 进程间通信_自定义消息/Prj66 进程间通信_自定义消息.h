
// Prj66 进程间通信_自定义消息.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj66进程间通信_自定义消息App:
// See Prj66 进程间通信_自定义消息.cpp for the implementation of this class
//

class CPrj66进程间通信_自定义消息App : public CWinApp
{
public:
	CPrj66进程间通信_自定义消息App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj66进程间通信_自定义消息App theApp;