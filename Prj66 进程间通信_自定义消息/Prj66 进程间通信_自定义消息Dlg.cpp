
// Prj66 ���̼�ͨ��_�Զ�����ϢDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Prj66 ���̼�ͨ��_�Զ�����Ϣ.h"
#include "Prj66 ���̼�ͨ��_�Զ�����ϢDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_COMM WM_USER+100	//ֻҪ����΢������ظ��ͺ�
const UINT wm_nRegMsg = RegisterWindowMessage(_T("reg_data"));

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


// CPrj66���̼�ͨ��_�Զ�����ϢDlg dialog



CPrj66���̼�ͨ��_�Զ�����ϢDlg::CPrj66���̼�ͨ��_�Զ�����ϢDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRJ66__DIALOG, pParent)
	, m_strUserMsg(_T(""))
	, m_strRegMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrj66���̼�ͨ��_�Զ�����ϢDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERMESSAGE, m_strUserMsg);
	DDX_Text(pDX, IDC_EDIT_REG_MESSAGE, m_strRegMsg);
}

BEGIN_MESSAGE_MAP(CPrj66���̼�ͨ��_�Զ�����ϢDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SEND2, &CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnBnClickedBtnSend2)
END_MESSAGE_MAP()


// CPrj66���̼�ͨ��_�Զ�����ϢDlg message handlers

BOOL CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnInitDialog()
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

void CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnPaint()
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
HCURSOR CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnBnClickedBtnSend()
{
	// TODO: Add your control notification handler code here
	UpdateData();//�������� �õ�998��������

	CWnd *pWnd = CWnd::FindWindowW(NULL, _T("Prj66_DataRecv")); // ���ݴ��ڵı����ҵ�

	if (!pWnd) {
		AfxMessageBox(_T("û�ҵ� ���ն�"));
		return;
	}

	UINT uMsg;
	uMsg = _ttoi(m_strUserMsg);//�������
	pWnd->SendMessage(WM_COMM, NULL, (LPARAM)uMsg);

}


void CPrj66���̼�ͨ��_�Զ�����ϢDlg::OnBnClickedBtnSend2()
{
	// TODO: Add your control notification handler code here
	UpdateData();//�������� �õ�998��������

	CWnd *pWnd = CWnd::FindWindowW(NULL, _T("Prj66_DataRecv")); // ���ݴ��ڵı����ҵ�

	if (!pWnd) {
		AfxMessageBox(_T("û�ҵ� ���ն�"));
		return;
	}

	UINT uMsg;
	uMsg = _ttoi(m_strRegMsg);//�������
	pWnd->SendMessage(wm_nRegMsg, NULL, (LPARAM)uMsg);
}
