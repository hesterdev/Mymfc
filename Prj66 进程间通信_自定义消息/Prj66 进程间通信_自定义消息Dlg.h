
// Prj66 ���̼�ͨ��_�Զ�����ϢDlg.h : header file
//

#pragma once


// CPrj66���̼�ͨ��_�Զ�����ϢDlg dialog
class CPrj66���̼�ͨ��_�Զ�����ϢDlg : public CDialogEx
{
// Construction
public:
	CPrj66���̼�ͨ��_�Զ�����ϢDlg(CWnd* pParent = NULL);	// standard constructor

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
