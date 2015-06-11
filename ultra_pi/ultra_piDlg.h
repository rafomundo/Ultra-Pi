
// ultra_piDlg.h : header file
//

#pragma once


// Cultra_piDlg dialog
class Cultra_piDlg : public CDialog
{
// Construction
public:
	Cultra_piDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ULTRA_PI_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedC1();
	afx_msg void OnBnClickedC2();
	afx_msg void OnBnClickedC3();
	afx_msg void OnBnClickedC4();
	afx_msg void OnBnClickedC5();
	afx_msg void OnBnClickedC6();
	afx_msg void OnBnClickedC7();
	afx_msg void OnBnClickedC8();
	afx_msg void OnBnClickedCpu();
	CString m_1;
	CString m_2;
	CString m_3;
	CString m_4;
	CString m_5;
	CString m_6;
	CString m_7;
	CString m_8;
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedMyhelp();
};
