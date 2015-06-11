
// ultra_piDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ultra_pi.h"
#include "ultra_piDlg.h"
#include "Calculate.h"
#include "cpuinfo.h"
#include "MyLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cultra_piDlg dialog




Cultra_piDlg::Cultra_piDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cultra_piDlg::IDD, pParent)
	, m_1(_T(""))
	, m_2(_T(""))
	, m_3(_T(""))
	, m_4(_T(""))
	, m_5(_T(""))
	, m_6(_T(""))
	, m_7(_T(""))
	, m_8(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	if(!MyLoader::load_all())			//false if cannot load anything
		MyLoader::init();

	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
}

void Cultra_piDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_1);
	DDX_Text(pDX, IDC_EDIT2, m_2);
	DDX_Text(pDX, IDC_EDIT3, m_3);
	DDX_Text(pDX, IDC_EDIT4, m_4);
	DDX_Text(pDX, IDC_EDIT5, m_5);
	DDX_Text(pDX, IDC_EDIT6, m_6);
	DDX_Text(pDX, IDC_EDIT7, m_7);
	DDX_Text(pDX, IDC_EDIT8, m_8);
}

BEGIN_MESSAGE_MAP(Cultra_piDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &Cultra_piDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_C1, &Cultra_piDlg::OnBnClickedC1)
	ON_BN_CLICKED(IDC_C2, &Cultra_piDlg::OnBnClickedC2)
	ON_BN_CLICKED(IDC_C3, &Cultra_piDlg::OnBnClickedC3)
	ON_BN_CLICKED(IDC_C4, &Cultra_piDlg::OnBnClickedC4)
	ON_BN_CLICKED(IDC_C5, &Cultra_piDlg::OnBnClickedC5)
	ON_BN_CLICKED(IDC_C6, &Cultra_piDlg::OnBnClickedC6)
	ON_BN_CLICKED(IDC_C7, &Cultra_piDlg::OnBnClickedC7)
	ON_BN_CLICKED(IDC_C8, &Cultra_piDlg::OnBnClickedC8)
	ON_BN_CLICKED(IDC_CPU, &Cultra_piDlg::OnBnClickedCpu)
	ON_BN_CLICKED(IDC_About, &Cultra_piDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_MYHELP, &Cultra_piDlg::OnBnClickedMyhelp)
END_MESSAGE_MAP()


// Cultra_piDlg message handlers

BOOL Cultra_piDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void Cultra_piDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cultra_piDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cultra_piDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cultra_piDlg::OnBnClickedCancel()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnCancel();
}

void Cultra_piDlg::OnBnClickedC1()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 4000 digits of Pi!");
	dlg.m_digits = 4000;
	dlg.m_position = 0;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC2()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 8000 digits of Pi!");
	dlg.m_digits = 8000;
	dlg.m_position = 1;
	dlg.DoModal();
	
	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC3()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 16000 digits of Pi!");
	dlg.m_digits = 16000;
	dlg.m_position = 2;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC4()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 32000 digits of Pi!");
	dlg.m_digits = 32000;
	dlg.m_position = 3;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC5()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 64000 digits of Pi!");
	dlg.m_digits = 64000;
	dlg.m_position = 4;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC6()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 128000 digits of Pi!");
	dlg.m_digits = 128000;
	dlg.m_position = 5;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC7()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 256000 digits of Pi!");
	dlg.m_digits = 256000;
	dlg.m_position = 6;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedC8()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CCalculate dlg;
	dlg.m_text = _T("Press \"Start\" to calculate 512000 digits of Pi!");
	dlg.m_digits = 512000;
	dlg.m_position = 7;
	dlg.DoModal();

	MyLoader::load_all();
	m_1 = MyLoader::getNextCalcTime();
	m_2 = MyLoader::getNextCalcTime();
	m_3 = MyLoader::getNextCalcTime();
	m_4 = MyLoader::getNextCalcTime();
	m_5 = MyLoader::getNextCalcTime();
	m_6 = MyLoader::getNextCalcTime();
	m_7 = MyLoader::getNextCalcTime();
	m_8 = MyLoader::getNextCalcTime();
	UpdateData(false);
}

void Cultra_piDlg::OnBnClickedCpu()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	Ccpuinfo dlg;
	dlg.DoModal();
}

void Cultra_piDlg::OnBnClickedAbout()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.

	CString about_str = L"Ultra Pi (Beta)\n(c) 2008 Raphael M. Kuchta";
		 about_str += L"\n\nThis benchmark program is designed to calculate the number Pi on";
		 about_str += L" many-/multicore systems.\nThe Bailey-Borwein-Plouffe formula (BBP formula) is used for the calculation, because";
		 about_str += L" it allows extracting any individual digit of Pi without calculating the preceding ones.";

	MessageBox(about_str, _T("Ultra Pi - Info"));

}

void Cultra_piDlg::OnBnClickedMyhelp()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	
	CString helpstr;
	helpstr = L"To test speed and stability of your cpu and calculate some digits of Pi click on the \"Calculate\" button";
	helpstr += L", and new dialog will appear where you begin the calculation by clicking on the \"start\" button.";
	helpstr += L"\r\nA progress bar informs you about the calculation status.";
	helpstr += L"\r\nWhen all threads have finished their calculations a dialog box will appear informing you about the calculated digits and the time needed.";
	helpstr += L"\r\nIf you want to cancel the running calculation, or go back to the main dialog click on the \"Stop / Close\" button";
	helpstr += L"\r\nThe computed digits of Pi are saved to the file \"ultra_pi_result.txt\".";
	helpstr += L"\r\nYou can also see the shortest time needed for every amount of digits in the main dialog next to the accordant digits.";
	helpstr += L"\r\nClick on the \"CPU info\" button to see some features of your CPU.";
	helpstr += L"\r\n\r\nAttention: Ultra Pi ist not designed to calculate the number pi as fast as possible on a single core CPU, but to do it on multicore / manycore CPUs.";
	helpstr += L" Every CPU core can calculate independently different digits of Pi.";
	helpstr += L" So calculation speed not only scales with CPU speed but also (and even more) with the number of cores available!";
	helpstr += L"\r\nFurthermore Ultra Pi don´t consider how many physical CPUs your system have, but how many logical CPUs are there.";
	helpstr += L" Some CPUs can handle 2 or more threads parallel on every core, so for example a CPU with 4 physical cores that can all";
	helpstr += L" handle 2 thread at a time will have 8 logical CPUs (hopefully).";

	MessageBox(helpstr, _T("Ultra Pi - Help"));
}
