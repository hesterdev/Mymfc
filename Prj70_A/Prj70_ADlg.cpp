
// Prj70_ADlg.cpp : implementation file
//

#include "stdafx.h"
#include "Prj70_A.h"
#include "Prj70_ADlg.h"
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


// CPrj70_ADlg dialog



CPrj70_ADlg::CPrj70_ADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRJ70_A_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrj70_ADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrj70_ADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPrj70_ADlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPrj70_ADlg message handlers

BOOL CPrj70_ADlg::OnInitDialog()
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

void CPrj70_ADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPrj70_ADlg::OnPaint()
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
HCURSOR CPrj70_ADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPrj70_ADlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	HANDLE hPWrite, hPRead;
	SECURITY_ATTRIBUTES sa = { 0 };
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	BOOL bCreate = CreatePipe(&hPRead, &hPWrite, &sa, 0/*用默认的大小,管道是一段共享的内存*/);
	if (!bCreate) {
		MessageBox(_T("创建管道失败"));
		return;
	}


	PROCESS_INFORMATION pi = { 0 };

	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	si.wShowWindow = TRUE;
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = si.hStdError = hPWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	TCHAR szCmd[MAX_PATH * 2] = { 0 };// = _T("cmd"); //用cmd能够创建出 cmd
	GetDlgItemText(IDC_EDIT1, szCmd, MAX_PATH * 2);


	bCreate = CreateProcess(NULL, szCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (!bCreate) {
		CloseHandle(hPWrite);
		CloseHandle(hPRead);

		MessageBox(_T("创建进程失败"));
		return;
	}
	CString str;
	CloseHandle(hPWrite);
	TCHAR szBuff[4096];
	DWORD dwRead;
	while (TRUE) {
		memset(szBuff, 0, sizeof(szBuff));
		if (!ReadFile(hPRead, szBuff, 4096, &dwRead, NULL)) {
			break;
		}
		str += szBuff;
		SetDlgItemText(IDC_EDIT2, str);
	}
	CloseHandle(hPRead);
	

}
