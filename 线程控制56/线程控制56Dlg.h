
// �߳̿���56Dlg.h : header file
//

#pragma once


UINT ThreadProcA(LPVOID pParam);
UINT ThreadProcB(LPVOID pParam);



// C�߳̿���56Dlg dialog
class C�߳̿���56Dlg : public CDialogEx
{
// Construction
public:
	C�߳̿���56Dlg(CWnd* pParent = NULL);	// standard constructor
	~C�߳̿���56Dlg();
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY56_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
