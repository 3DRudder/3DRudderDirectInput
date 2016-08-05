
// 3DRudderDirectInput.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CMy3DRudderDirectInputApp :
// Consultez 3DRudderDirectInput.cpp pour l'implémentation de cette classe
//

class CMy3DRudderDirectInputApp : public CWinApp
{
public:
	CMy3DRudderDirectInputApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CMy3DRudderDirectInputApp theApp;