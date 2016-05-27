
// Prj69_BDlg.h : header file
//

#pragma once


// CPrj69_BDlg dialog
class CPrj69_BDlg : public CDialogEx
{
// Construction
public:
	CPrj69_BDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRJ69_B_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HANDLE m_hMapObject;
	LPTSTR m_pszMapView;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
