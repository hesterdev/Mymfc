
// 创建线程MFC54Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "创建线程MFC54.h"
#include "创建线程MFC54Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinThread * g_PThreadA;
BOOL g_bRunning; //记录该线程有没有在运行


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


// C创建线程MFC54Dlg dialog



C创建线程MFC54Dlg::C创建线程MFC54Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC54_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_PThreadA = NULL;
	g_bRunning = false;
}

void C创建线程MFC54Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C创建线程MFC54Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C创建线程MFC54Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C创建线程MFC54Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C创建线程MFC54Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &C创建线程MFC54Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C创建线程MFC54Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_SUSPEND, &C创建线程MFC54Dlg::OnBnClickedSuspend)
END_MESSAGE_MAP()


// C创建线程MFC54Dlg message handlers

BOOL C创建线程MFC54Dlg::OnInitDialog()
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

void C创建线程MFC54Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C创建线程MFC54Dlg::OnPaint()
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
HCURSOR C创建线程MFC54Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C创建线程MFC54Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	// 使用主线程 ,一般用来做界面响应

	for (int i = 1; i <= 100; i++) {
		SetDlgItemInt(IDC_STATIC1, i);
		Sleep(1000);
	}


}
UINT DemoA(LPVOID pParam) {
	for (int m = 1; m <= 100; m++) {
		if (!g_bRunning)break;

		::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC2, m, false);
		Sleep(500);
	}
	g_PThreadA = NULL;
	g_bRunning = false;
	return 0;
}

UINT DemoB(LPVOID pParam) {
	for (int n = 100; n >= 1; n--) {
		::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_STATIC3, n, false);
		Sleep(1000);
	}
	return 0;
}



void C创建线程MFC54Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	if (g_PThreadA == NULL) {
		g_PThreadA = AfxBeginThread(DemoA, NULL);
		g_bRunning = TRUE;
	}
	else {
		AfxMessageBox(_T("已经启动了"));
	}
}


void C创建线程MFC54Dlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(DemoB, NULL);
}




// 暂停
void C创建线程MFC54Dlg::OnBnClickedSuspend()
{
	// TODO: Add your control notification handler code here
	if (g_PThreadA == NULL) {
		AfxMessageBox(_T("线程不存在"));
	}
	else {
		g_PThreadA->SuspendThread(); //暂停就是挂起 suspend
	}
}

//继续
void C创建线程MFC54Dlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	if (g_PThreadA == NULL) {
		AfxMessageBox(_T("线程不存在"));
	}
	else {
		g_PThreadA->ResumeThread(); //暂停就是挂起 suspend
	}
}



//停止
void C创建线程MFC54Dlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	if (g_PThreadA == NULL) {
		AfxMessageBox(_T("线程不存在"));
	}
	else {
		g_bRunning = FALSE;
	}
}


