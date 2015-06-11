#ifndef _MYLOADER_H
#define _MYLOADER_H


// MyLoader class

class MyLoader
{

public:
	MyLoader(void);   // Standardkonstruktor
	virtual ~MyLoader(void);

	static bool load_all(void);
	static bool save_all(void);
	
	static CString getNextCalcTime(void);
	static void setCalcTime(int, CString);

	static void init(void);

};

#endif //_MYLOADER_H