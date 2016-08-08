
// 3DRudderDirectInput.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"	
#endif

#include "resource.h"		// main symbols


// CMy3DRudderDirectInputApp:
// See 3DRudderDirectInput.cpp for the implementation of this class
//

class CMy3DRudderDirectInputApp : public CWinApp
{
public:
	CMy3DRudderDirectInputApp();

	// Overrides
public:
	virtual BOOL InitInstance();

	// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy3DRudderDirectInputApp theApp;