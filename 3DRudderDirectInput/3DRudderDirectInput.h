
// 3DRudderDirectInput.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CMy3DRudderDirectInputApp�:
// Consultez 3DRudderDirectInput.cpp pour l'impl�mentation de cette classe
//

class CMy3DRudderDirectInputApp : public CWinApp
{
public:
	CMy3DRudderDirectInputApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CMy3DRudderDirectInputApp theApp;