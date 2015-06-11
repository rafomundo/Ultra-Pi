#pragma once
#include "afxcmn.h"


// CCalculate-Dialogfeld


class CCalculate : public CDialog
{
	DECLARE_DYNAMIC(CCalculate)

public:
	CCalculate(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CCalculate();

// Dialogfelddaten
	enum { IDD = IDD_CALCULATE };

private:

	static UINT Control_Thread(LPVOID);
	//UINT Control_Thread(LPVOID);
	static UINT Calc_Threads(LPVOID);
	static int save_result(void);

	static double expm(double, double);			
	static double series (int, int);
	static void ihex(double, int);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnTimer(UINT);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_text;
	int m_digits;
	int m_position;

private:
	int nCPU;
};
