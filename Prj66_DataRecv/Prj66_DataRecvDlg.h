
// Prj66_DataRecvDlg.h : header file
//

#pragma once


// CPrj66_DataRecvDlg dialog
class CPrj66_DataRecvDlg : public CDialogEx
{
// Construction
public:
	CPrj66_DataRecvDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRJ66_DATARECV_DIALOG };
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

	afx_msg LRESULT OnUserReceiveMsg(WPARAM, LPARAM);
	afx_msg LRESULT OnRegReceiveMsg(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	CString m_str_Reg;
	CString m_str_User;
};
