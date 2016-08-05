
// 3DRudderDirectInputDlg.h : fichier d'en-t�te
//

#pragma once

#pragma warning(push)
#pragma warning(disable:6000 28251)
#include <dinput.h>
#pragma warning(pop)

#include <dinputd.h>



// bo�te de dialogue CMy3DRudderDirectInputDlg
class CMy3DRudderDirectInputDlg : public CDialogEx
{
// Construction
public:
	CMy3DRudderDirectInputDlg(CWnd* pParent = NULL);	// constructeur standard

// Donn�es de bo�te de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY3DRUDDERDIRECTINPUT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Impl�mentation
protected:
	HICON m_hIcon;

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_sXAxis;
	CString m_sYAxis;
	CString m_sZAxis;
	CString m_sZRotation;
	CString m_sStatus;
	CString m_sSensor1;
	CString m_sSensor3;
	CString m_sSensor5;
	CString m_sSensor2;
	CString m_sSensor4;
	CString m_sSensor6;

	LPDIRECTINPUT8          m_pDI = nullptr;
	LPDIRECTINPUTDEVICE8    m_pJoystick = nullptr;

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	HRESULT CMy3DRudderDirectInputDlg::InitDirectInput();
};

struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG* pPreferredJoyCfg;
	bool bPreferredJoyCfgValid;
	CMy3DRudderDirectInputDlg *m_pDlg;
};

