
// ultra_pi.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cultra_piApp:
// See ultra_pi.cpp for the implementation of this class
//

class Cultra_piApp : public CWinAppEx
{
public:
	Cultra_piApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cultra_piApp theApp;