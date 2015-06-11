#pragma once


// Ccpuinfo-Dialogfeld

class Ccpuinfo : public CDialog
{
	DECLARE_DYNAMIC(Ccpuinfo)

public:
	Ccpuinfo(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Ccpuinfo();

	static int get_num_cpu();

// Dialogfelddaten
	enum { IDD = IDD_CPUINFO };

private:
	CString ShowInfo();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString m_text;
	afx_msg void OnBnClickedOk();
};
