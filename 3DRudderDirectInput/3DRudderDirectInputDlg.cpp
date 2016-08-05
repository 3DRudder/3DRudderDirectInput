
// 3DRudderDirectInputDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "3DRudderDirectInput.h"
#include "3DRudderDirectInputDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// boîte de dialogue CMy3DRudderDirectInputDlg



CMy3DRudderDirectInputDlg::CMy3DRudderDirectInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY3DRUDDERDIRECTINPUT_DIALOG, pParent)
	, m_sXAxis(_T("0"))
	, m_sYAxis(_T("0"))
	, m_sZAxis(_T("0"))
	, m_sZRotation(_T("0"))
	, m_sStatus(_T("Status :"))
	, m_sSensor1(_T("0"))
	, m_sSensor3(_T("0"))
	, m_sSensor5(_T("0"))
	, m_sSensor2(_T("0"))
	, m_sSensor4(_T("0"))
	, m_sSensor6(_T("0"))
	,m_pDI(nullptr)
	,m_pJoystick(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3DRudderDirectInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_XAXIS, m_sXAxis);
	DDX_Text(pDX, IDC_ED_YAXIS, m_sYAxis);
	DDX_Text(pDX, IDC_ED_ZAXIS, m_sZAxis);
	DDX_Text(pDX, IDC_ED_ZROTATION, m_sZRotation);
	DDX_Text(pDX, IDC_ST_STATUS, m_sStatus);
	DDX_Text(pDX, IDC_ED_SENSOR1, m_sSensor1);
	DDX_Text(pDX, IDC_ED_SENSOR3, m_sSensor3);
	DDX_Text(pDX, IDC_ED_SENSOR5, m_sSensor5);
	DDX_Text(pDX, IDC_ED_SENSOR2, m_sSensor2);
	DDX_Text(pDX, IDC_ED_SENSOR4, m_sSensor4);
	DDX_Text(pDX, IDC_ED_SENSOR6, m_sSensor6);
}

BEGIN_MESSAGE_MAP(CMy3DRudderDirectInputDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy3DRudderDirectInputDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// gestionnaires de messages pour CMy3DRudderDirectInputDlg

BOOL CMy3DRudderDirectInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
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

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône
	if (FAILED(InitDirectInput()))
		EndDialog(0);
	SetTimer (0, 1000 / 30, nullptr );

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CMy3DRudderDirectInputDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CMy3DRudderDirectInputDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CMy3DRudderDirectInputDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy3DRudderDirectInputDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

//-----------------------------------------------------------------------------
// Name: EnumJoysticksCallback()
// Desc: Called once for each enumerated joystick. If we find one, create a
//       device interface on it so we can play with it.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,
	VOID* pContext)
{
	auto pEnumContext = reinterpret_cast<DI_ENUM_CONTEXT*>(pContext);
	HRESULT hr;


	// Skip anything other than the perferred joystick device as defined by the control panel.  
	// Instead you could store all the enumerated joysticks and let the user pick.
	if (pEnumContext->bPreferredJoyCfgValid &&
		!IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
		return DIENUM_CONTINUE;

	// Obtain an interface to the enumerated joystick.
	hr = pEnumContext->m_pDlg->m_pDI->CreateDevice(pdidInstance->guidInstance, &pEnumContext->m_pDlg->m_pJoystick, nullptr);

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr))
		return DIENUM_CONTINUE;

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	return DIENUM_STOP;
}

//-----------------------------------------------------------------------------
// Name: EnumObjectsCallback()
// Desc: Callback function for enumerating objects (axes, buttons, POVs) on a 
//       joystick. This function enables user interface elements for objects
//       that are found to exist, and scales axes min/max values.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi,
	VOID* pContext)
{
	CMy3DRudderDirectInputDlg*pDlg = (CMy3DRudderDirectInputDlg*)pContext;

								  // For axes that are returned, set the DIPROP_RANGE property for the
								  // enumerated axis in order to scale min/max values.
								  // we use a value from -1000 to 1000 for the 4 main axis only 

	if (pdidoi->dwType & DIDFT_AXIS 
		&& (pdidoi->guidType == GUID_XAxis || pdidoi->guidType == GUID_YAxis || pdidoi->guidType == GUID_ZAxis || pdidoi->guidType == GUID_RzAxis)
		)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		// Set the range for the axis
		if (FAILED(pDlg->m_pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph)))
			return DIENUM_STOP;

	}

	return DIENUM_CONTINUE;
}


//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT CMy3DRudderDirectInputDlg::InitDirectInput()
{
	HRESULT hr;

	// Register with the DirectInput subsystem and get a pointer
	// to a IDirectInput interface we can use.
	// Create a DInput object
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&m_pDI, nullptr)))
		return hr;


	DIJOYCONFIG PreferredJoyCfg = { 0 };
	DI_ENUM_CONTEXT enumContext;
	enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
	enumContext.bPreferredJoyCfgValid = false;
	enumContext.m_pDlg = this;

	IDirectInputJoyConfig8* pJoyConfig = nullptr;
	if (FAILED(hr = m_pDI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
		return hr;

	PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
	if (SUCCEEDED(pJoyConfig->GetConfig(0, &PreferredJoyCfg, DIJC_GUIDINSTANCE))) // This function is expected to fail if no joystick is attached
		enumContext.bPreferredJoyCfgValid = true;
	SAFE_RELEASE(pJoyConfig);

	// Look for a simple joystick we can use for this sample program.
	if (FAILED(hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		&enumContext, DIEDFL_ATTACHEDONLY)))
		return hr;


	// Make sure we got a joystick
	if (!m_pJoystick)
	{
		AfxMessageBox(TEXT("Joystick not found. The sample will now exit."),
			MB_ICONERROR | MB_OK);
		return -1;
	}

	// Set the data format to "simple joystick" - a predefined data format 
	//
	// A data format specifies which controls on a device we are interested in,
	// and how they should be reported. This tells DInput that we will be
	// passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
	if (FAILED(hr = m_pJoystick->SetDataFormat(&c_dfDIJoystick2)))
		return hr;

	// Set the cooperative level to let DInput know how this device should
	// interact with the system and with other DInput applications.
	if (FAILED(hr = m_pJoystick->SetCooperativeLevel(m_hWnd, DISCL_EXCLUSIVE |
		DISCL_FOREGROUND)))
		return hr;
	// Enumerate the joystick objects. The callback function enabled user
	// interface elements for objects that are found, and sets the min/max
	// values property for discovered axes.
	if (FAILED(hr = m_pJoystick->EnumObjects(EnumObjectsCallback,
		(VOID*)this, DIDFT_ALL)))
		return hr;


	return S_OK;
}



void CMy3DRudderDirectInputDlg::OnTimer(UINT_PTR nIDEvent)
{
	HRESULT hr;
	DIJOYSTATE2 js;           // DInput joystick state 

	if (!m_pJoystick)
		return;

	// Poll the device to read the current state
	hr = m_pJoystick->Poll();
	if (FAILED(hr))
	{
		// DInput is telling us that the input stream has been
		// interrupted. We aren't tracking any state between polls, so
		// we don't have any special reset that needs to be done. We
		// just re-acquire and try again.
		hr = m_pJoystick->Acquire();
		while (hr == DIERR_INPUTLOST)
			hr = m_pJoystick->Acquire();

		// hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
		// may occur when the app is minimized or in the process of 
		// switching, so just try again later 
		return;
	}

	// Get the input's device state
	if (FAILED(hr = m_pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &js)))
		return ; // The device should have been acquired during the Poll()

	// Display joystick state to dialog

	m_sXAxis.Format(_T("%ld"), js.lX);
	m_sYAxis.Format(_T("%ld"), js.lY);
	m_sZAxis.Format(_T("%ld"), js.lZ);
	m_sZRotation.Format(_T("%ld"), js.lRz);

	switch (js.lRx>>12)
	{
		case 1:
			m_sStatus = _T("Status : Don't put your Feet !!! Stay still 5s");
			break;
		case 2:
			m_sStatus = _T("Status : Initialisation");
			break;
		case 3:
			m_sStatus = _T("Status : Please put your feet");
			break;
		case 4:
			m_sStatus = _T("Status :  Put your second foot");
			break;
		case 5:
			m_sStatus = _T("Status : Stay still");
			break;
		case 6:
			m_sStatus = _T("Status : 3DRudder in use");
			break;
		case 7:
			m_sStatus = _T("Status : Extended functions activated");
			break;

	}

	m_sSensor1.Format(_T("%ld"),js.lRy & 0xFF);
	m_sSensor2.Format(_T("%ld"), ( js.lRy >> 8) & 0xFF);
	m_sSensor3.Format(_T("%ld"), js.rglSlider[0] & 0xFF);
	m_sSensor4.Format(_T("%ld"), (js.rglSlider[0] >> 8) & 0xFF);
	m_sSensor5.Format(_T("%ld"), js.rglSlider[1] & 0xFF);
	m_sSensor6.Format(_T("%ld"), (js.rglSlider[1] >> 8) & 0xFF);


	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}
