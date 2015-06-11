// Calculate.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ultra_pi.h"
#include "Calculate.h"
#include <time.h>
#include <sys/timeb.h>
#include <windows.h>
#include <afxwin.h>
#include "cpuinfo.h"
#include "ultra_piDlg.h"
#include "MyLoader.h"
#include <math.h>



const int MAX_CPU = 64;
const int MAX_CHAR = 50;
const wchar_t *PI_RESULT_FILE = L"ultra_pi_result.txt";

#define EPS 1e-17
const int NTP = 25;
const int TRUSTED = 8;					//we trust 8 hex digits	
const int NHX = TRUSTED + 1;			//8 hex numbers + '\0' for char array


int pi_digits = 0;
int num_cpu = 0;
int timelist_position = 0;

int myThreadId = 0;						//a thread picks an id and increses the value for next thread
double diff = 0.0;						//the difference between start nad stop (the calculation time)

//CCriticalSection cs_id_lock;				//variable for CSingleLock (locking myThreadId)			
CCriticalSection cs_mem_lock;				//variable for CSingleLock (locking memsave)
CCriticalSection cs_pos_lock;				//variable for CCingleLock (locking position)

char (*memsave)[NHX];					//allocated memory to save results
int position = 0;						//curent position in memsave

bool isRunning = false;					//not running yet
bool isFinished[MAX_CPU];				//have ALL threads finished?
bool canClose = true;					//no threads are running, you can close
bool isError = false;					//an error occur; special approach needed;


UINT_PTR myTimer;						//handler for the Timer

// CCalculate-Dialogfeld

IMPLEMENT_DYNAMIC(CCalculate, CDialog)

CCalculate::CCalculate(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculate::IDD, pParent)
	, m_text(_T(""))
	, m_digits(0)
	, m_position(0)
	, nCPU(0)
{

}

CCalculate::~CCalculate()
{
}

void CCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}


BEGIN_MESSAGE_MAP(CCalculate, CDialog)
	ON_BN_CLICKED(IDOK, &CCalculate::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCalculate::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CCalculate::OnTimer(UINT pParam)
{
	CProgressCtrl *progressBar = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	//progressBar->SetRange(0, m_digits/TRUSTED);
	progressBar->SetPos(position);
	if(canClose)
	{
		CString fin;
		fin.Format(_T("Finished calculation!\r\nCalculated %i digits of Pi in %.3lf sec.\r\nPress \"Stop / Close\" to close this window,\r\nor \"Start\" to begin once again."), pi_digits, diff);

		m_text = fin;
		UpdateData(false);

		GetDlgItem(IDOK)->EnableWindow(true);
	}
}

// CCalculate-Meldungshandler
void CCalculate::OnBnClickedOk()
{	
	canClose = false;					//wait until all threads have terminated and memory has been freed
	isRunning = true;					// operation is runing and can be stopped by the user
	isError = false;					

	GetDlgItem(IDOK)->EnableWindow(false);
	
	num_cpu = Ccpuinfo::get_num_cpu();
	timelist_position = m_position;
	pi_digits = m_digits;

	m_text.Format(_T("Calculating %i digits of Pi with %i threads.\r\nPress \"Stop / Close\" to cancel calculation."), pi_digits, num_cpu);
	UpdateData(false);


	CProgressCtrl *progressBar = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	//SetRange() has only support for short! SetRange32 supports 32bit integer!
	progressBar->SetRange32(0, pi_digits/TRUSTED);		
	progressBar->SetPos(0);

	if(pi_digits <= 8000)
		myTimer = SetTimer(1, 1000, 0);
	else
		myTimer = SetTimer(1, 2000, 0);

	CCalculate myThread;
	AfxBeginThread(CCalculate::Control_Thread, reinterpret_cast<LPVOID>(&myThread), THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

/* This function runs in a thread, starts the Calc_Threads and waits on their end
 * (all Calc_Threads have set isFinished["their thread number"] = true).
 * It also waits on a signal (isRunning = false) from the "Stop/Close" Button, and
 * freed than the memory and sets "canClose = true" to signalise the OnBnClickedCancel function
 * that memory has been freen and the dialog can be closed now. */
UINT CCalculate::Control_Thread(LPVOID pParam)
{
	//CCalculate *p_test = reinterpret_cast<CCalculate*>(pParam);

	
	bool allFinished = false;
	myThreadId = 0;						//set the myThreadId for the calc_threads to 0
	position = 0;						//set position in memsave back to 0

	double start_sec, start_mill, end_sec, end_mill;
	struct _timeb start_t, end_t;

	
	_ftime_s(&start_t);					//save start time

	//allocate memory
	memsave = (char(*)[NHX]) malloc(sizeof(memsave) * (pi_digits) * (NHX));
	if(memsave == NULL)
	{
		isError = true;				//dialog can be closed
		AfxMessageBox(_T("Error: Cannot allocale memory!"), MB_ICONERROR);
		return 1;
	}

	int t_id[MAX_CPU];
	// start as many calc_threads as logical cpus found
	for(int i = 0; i < num_cpu; i++)
	{
		t_id[i] = i;
		AfxBeginThread(CCalculate::Calc_Threads, reinterpret_cast<LPVOID>(&t_id[i]), THREAD_PRIORITY_NORMAL, 0, 0, NULL);
		isFinished[i] = false;
	}

	//leave loop only if ALL threads have finished, OR user stops operation
	while((!allFinished) && isRunning)
	{
		allFinished = true;
		for(int i = 0; i < num_cpu; i++)
		{
			if(!isFinished[i])
				allFinished = false;
		}
		/*progressBar->SetPos(position);*/
		Sleep(1000);
	}
		
	if(!isRunning)						//user stoped operation, exit function
	{
		free(memsave);					//freed memory
		canClose = true;				//allow to close dialog
		return 0;
	}


	_ftime_s(&end_t);					//save end time


	start_sec = (double) start_t.time;
	start_mill = (double) start_t.millitm;
	end_sec = (double) end_t.time;
	end_mill = (double) end_t.millitm;
	diff = (end_sec + (end_mill / 1000)) - (start_sec + (start_mill / 1000));

	//save result from memory to disk
	save_result();
	//freed allocated memory
	free(memsave);


	CString fin;
	fin.Format(_T("Calculated %i digits of Pi in %.3lf sec"), pi_digits, diff);
	AfxMessageBox(fin, MB_ICONINFORMATION);
	//AfxMessageBox(fin , MB_ICONINFORMATION);

	//save time needed for calculation
	CString temp_calc_time;
	temp_calc_time.Format(_T("%.3lf"), diff);
	MyLoader::setCalcTime(timelist_position, temp_calc_time);
	MyLoader::save_all();

	canClose = true;					//allow to close dialog
	return 0;
}

/* This are the calculation threads.
 * they pick the next available position on the memsave array (so they know which 8 digits of pi
 * they should calculate) and increment the position counter for the others.
 * WHen calculated a set of digits they save it to the picked position in memory and go on
 * with the first step.
 * But they also look every calculation loop if the user has pressed "Stop/Close" (isRunning = false)
 * if so they terminate themself. */
UINT CCalculate::Calc_Threads(LPVOID pParam)
{
	//CSingleLock id_lock(&cs_id_lock);
	CSingleLock pos_lock(&cs_pos_lock);
	//int my_id;
	//id_lock.Lock();
	//if(id_lock.IsLocked())				//pick an number (id) and increment for other threads
	//{
	//	my_id = myThreadId;
	//	myThreadId++;
	//	id_lock.Unlock();
	//}
	int *my_id = reinterpret_cast<int*>(pParam);

	int save_pos = 0, id = 0;
	double pi, s1, s2, s3, s4;			//actual pi digit and the 4 series

	do
	{
		pos_lock.Lock();
		if(pos_lock.IsLocked())
		{
			save_pos = position;
			position++;
			pos_lock.Unlock();
		}
		id = save_pos * TRUSTED;
		s1 = series (1, id);
		s2 = series (4, id);
		s3 = series (5, id);
		s4 = series (6, id);
		pi = 4. * s1 - 2. * s2 - s3 - s4;
		pi = pi - (int) pi + 1.;
		ihex (pi, save_pos);

		if(!isRunning)					//user pressed stop, so stop operation NOW
			return 0;
	}while(((save_pos + num_cpu) * TRUSTED) < (pi_digits));

	isFinished[(*my_id)] = true;			//signalise to control_thread that you have finished

	return 0;
}

/*  This returns, in chx, the first nhx hex digits of the fraction of x. */
void CCalculate::ihex (double x, int save_pos)
{
	CSingleLock mem_lock(&cs_mem_lock);

  int i;
  double y;
  char hx[] = "0123456789ABCDEF";
  char chx[NHX];							//hex digits of pi

  y = fabs (x);

  //for (i = 0; i < NHX; i++){
  for (i = 0; i < TRUSTED; i++){
    y = 16. * (y - floor (y));
    chx[i] = hx[(int) y];
  }
  chx[8] = '\0';	//finalise string
  
  mem_lock.Lock();
  if(mem_lock.IsLocked())
  {
	  strcpy_s(memsave[save_pos], chx);
	  mem_lock.Unlock();
  }
}

/*  This routine evaluates the series  sum_k 16^(id-k)/(8*k+m) 
    using the modular exponentiation technique. */
double CCalculate::series (int m, int id)
{
	int k;
	double ak, p, s, t;
	s = 0.;

	/*  Sum the series up to id. */

	for (k = 0; k < id; k++)
	{
		ak = 8 * k + m;
		p = id - k;
		t = expm (p, ak);
		s = s + t / ak;
		s = s - (int) s;
	}

	/*  Compute a few terms where k >= id. */

	for (k = id; k <= id + 100; k++)
	{
		ak = 8 * k + m;
		t = pow (16., (double) (id - k)) / ak;
		if (t < EPS) break;
		s = s + t;
		s = s - (int) s;
	}
	return s;
}

/*  expm = 16^p mod ak.  This routine uses the left-to-right binary 
    exponentiation scheme. */
double CCalculate::expm (double p, double ak)
{
	int i, j;
	double p1, pt, r;

	static double tp[NTP];
	static int tp1 = 0;

	/*  If this is the first call to expm, fill the power of two table tp. */

	if (tp1 == 0)
	{
		tp1 = 1;
		tp[0] = 1.;

		for (i = 1; i < NTP; i++) 
			tp[i] = 2. * tp[i-1];
	}

	if (ak == 1.) 
		return 0.;

	/*  Find the greatest power of two less than or equal to p. */

	for (i = 0; i < NTP; i++)
		if (tp[i] > p) 
			break;

	pt = tp[i-1];
	p1 = p;
	r = 1.;

	/*  Perform binary exponentiation algorithm modulo ak. */

	for (j = 1; j <= i; j++)
	{
		if (p1 >= pt)
		{
			r = 16. * r;
			r = r - (int) (r / ak) * ak;
			p1 = p1 - pt;
			}
		pt = 0.5 * pt;
		if (pt >= 1.)
		{
			r = r * r;
			r = r - (int) (r / ak) * ak;
		}
	}
	return r;
}

/* this function is called from the Control_Thread when the Cals_Threads have finished their work.
 * it saves the calculated digith from memory to disk */
int CCalculate::save_result()
{
	FILE * stream;
	if(!_wfopen_s(&stream, PI_RESULT_FILE, _T("w")))
	{
		fprintf(stream, "Ultra Pi\nFirst %i digits of the number PI in HEX:\n\n3.", pi_digits);
		for(int i = 0; i < position; i++)
		{
			if(i % 5 == 0)
				fprintf(stream, "\n%.8s", memsave[i]);
			else
				fprintf(stream, " %.8s", memsave[i]);
		}
			
		fclose(stream);

		return 0;
	}
	return -1;
}

void CCalculate::OnBnClickedCancel()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.

	isRunning = false;
	//GetDlgItem(IDOK)->EnableWindow(true);
	while((!canClose) && (!isError))
		Sleep(20);						//sleep for 100ms, so threads have chance to finish
	KillTimer(myTimer);

	OnCancel();
}