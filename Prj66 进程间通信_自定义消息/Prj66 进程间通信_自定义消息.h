
// Prj66 ���̼�ͨ��_�Զ�����Ϣ.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPrj66���̼�ͨ��_�Զ�����ϢApp:
// See Prj66 ���̼�ͨ��_�Զ�����Ϣ.cpp for the implementation of this class
//

class CPrj66���̼�ͨ��_�Զ�����ϢApp : public CWinApp
{
public:
	CPrj66���̼�ͨ��_�Զ�����ϢApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPrj66���̼�ͨ��_�Զ�����ϢApp theApp;