
// MyProcess58Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyProcess58.h"
#include "MyProcess58Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyProcess58Dlg dialog



CMyProcess58Dlg::CMyProcess58Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYPROCESS58_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyProcess58Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyProcess58Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyProcess58Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyProcess58Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyProcess58Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyProcess58Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyProcess58Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyProcess58Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyProcess58Dlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMyProcess58Dlg message handlers

BOOL CMyProcess58Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyProcess58Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyProcess58Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyProcess58Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyProcess58Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));


	if (!(CreateProcess(TEXT("C:\\Windows\\System32\\calc.exe"), NULL, NULL, NULL, FALSE/*不继承句柄*/, 0, NULL, NULL, &si, &pi)))
	{
		CString s;
		s.Format(TEXT("创建进程失败： %d"), GetLastError());
		MessageBox(s);
		return;
	}
}

STARTUPINFO si;
PROCESS_INFORMATION pi;
void CMyProcess58Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));


	if (!(CreateProcess(TEXT("C:\\Users\\Jerry\\Source\\Repos\\Mymfc\\Debug\\CPChild.exe"), NULL, NULL, NULL, FALSE/*不继承句柄*/, 0, NULL, NULL, &si, &pi)))
	{
		CString s;
		s.Format(TEXT("创建进程失败： %d"), GetLastError());
		MessageBox(s);
		return;
	}
	
}


void CMyProcess58Dlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	TerminateProcess(pi.hProcess, 0);
}


void CMyProcess58Dlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	CString s;
	s.Format(_T("父进程: %x"), GetCurrentProcessId());
	MessageBox(s);
}



void CMyProcess58Dlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here

	CString s;
	s.Format(_T("子进程: %d"),pi.dwProcessId);
	MessageBox(s);
}


void CMyProcess58Dlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));


	if (!(CreateProcess(TEXT("C:\\Windows\\System32\\notepad.exe"), /*可以有参数*/_T("C:\\Users\\Jerry\\Desktop\\搜狗截图20160518164843.png"), NULL, NULL, FALSE/*不继承句柄*/, 0, NULL, NULL, &si, &pi)))
	{
		CString s;
		s.Format(TEXT("创建进程失败： %d"), GetLastError());
		MessageBox(s);
		return;
	}
}


void CMyProcess58Dlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));


	if (!(CreateProcess(TEXT("C:\\Users\\Jerry\\Source\\Repos\\Mymfc\\Debug\\CPChild.exe"), _T("C:\\Users\\Jerry\\Desktop\\搜狗截图20160518164843.png"), NULL, NULL, FALSE/*不继承句柄*/, 0, NULL, NULL, &si, &pi)))
	{
		CString s;
		s.Format(TEXT("创建进程失败： %d"), GetLastError());
		MessageBox(s);
		return;
	}

}
