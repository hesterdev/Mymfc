
// �߳̿���56Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "�߳̿���56.h"
#include "�߳̿���56Dlg.h"
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


// C�߳̿���56Dlg dialog

//CCriticalSection *g_pCS;
//CMutex *g_pMutex;
//CSemaphore *g_pSemaphore;
CEvent* g_pEvent;


C�߳̿���56Dlg::C�߳̿���56Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY56_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//g_pCS = new CCriticalSection();
	//g_pMutex = new CMutex();
	//g_pSemaphore = new CSemaphore();
	g_pEvent = new CEvent(TRUE/*����տ�ʼ�����źŵ�*/);
}

C�߳̿���56Dlg::~C�߳̿���56Dlg()
{

	//delete(g_pCS);
	//delete(g_pMutex);
	//delete(g_pSemaphore);
	delete(g_pEvent);
}

void C�߳̿���56Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C�߳̿���56Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C�߳̿���56Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C�߳̿���56Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C�߳̿���56Dlg message handlers

BOOL C�߳̿���56Dlg::OnInitDialog()
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

void C�߳̿���56Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�߳̿���56Dlg::OnPaint()
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
HCURSOR C�߳̿���56Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int k = 1;
int total = 0;		//�����̹߳���ͻᷢ�����ص�����

//�Թ�����ԴҪ���м����ͽ���
/*
//ʹ���ٽ����������ͬ��
for (int i = 1; i <= 100000000; i++) {

//����  (�ٽ���) �� �ؼ���
g_pCS->Lock();

k = k * 2;
k = k / 2;
total += k;

g_pCS->Unlock();
//����
}
*/
/*
//������
CSingleLock singleLock(g_pMutex);//����һ����	, ����������, ��ʾ,ÿ��ֻ��һ���߳��ڷ��ʸñ���
for (int i = 1; i <= 100000000; i++) {

//����
singleLock.Lock();
if (singleLock.IsLocked()) {
k = k * 2;
k = k / 2;
total += k;
singleLock.Unlock();
}
//����
}
*/
/*
//�ź�������
CSingleLock singleLock(g_pSemaphore);//����һ����
for (int i = 1; i <= 1000000; i++) {

//����
singleLock.Lock();
if (singleLock.IsLocked()) {

k = k * 2;
k = k / 2;
total += k;
singleLock.Unlock();
}
//����
}
*/
UINT ThreadProcA(LPVOID pParam) {
	CSingleLock singleLock(g_pEvent);//����һ����
	for (int i = 1; i <= 1000000; i++) {

		//����
		singleLock.Lock();
		if (singleLock.IsLocked()) {

			k = k * 2;
			k = k / 2;
			total += k;
			singleLock.Unlock();
			g_pEvent->SetEvent();//���źŸ������߳�,���ǿ��Լ�����,������
		}
		//����
	}
	::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_OUTPUT, total, false);
	return 0;
}
UINT ThreadProcB(LPVOID pParam) {
	CSingleLock singleLock(g_pEvent);//����һ����
	for (int i = 1; i <= 1000000; i++) {

		//����
		singleLock.Lock();
		if (singleLock.IsLocked()) {

			k = k * 2;
			k = k / 2;
			total += k;
			singleLock.Unlock();
			g_pEvent->SetEvent();//���źŸ������߳�,���ǿ��Լ�����,������
		}
		//����
	}
	::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_OUTPUT, total, false);
	return 0;
}



void C�߳̿���56Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(ThreadProcA, NULL);
}


void C�߳̿���56Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(ThreadProcB, NULL);
}
