
// Prj66 进程间通信_自定义消息Dlg.h : header file
//

#pragma once


// CPrj66进程间通信_自定义消息Dlg dialog
class CPrj66进程间通信_自定义消息Dlg : public CDialogEx
{
// Construction
public:
	CPrj66进程间通信_自定义消息Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRJ66__DIALOG };
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
	CString m_strUserMsg;
	CString m_strRegMsg;
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnSend2();
};
