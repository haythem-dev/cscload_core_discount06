#pragma once
#include "afxwin.h"


// CArtAgpImportGen dialog
class CArtAgpImportGen : public CDialogEx
{
	DECLARE_DYNAMIC(CArtAgpImportGen)

public:
	CArtAgpImportGen(long lngCurrentAGPNr, CString strCurrentImportName, CWnd* pParent = NULL);   // standard constructor
	virtual ~CArtAgpImportGen();

	long GetNewAGPNr() { return m_newAGPNr; };

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTAGP_IMPGEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//void fetchImportPath();
	long updateImportMaster(bool withWarnings);
	BOOL generateImport(bool withWarnings);

	DECLARE_MESSAGE_MAP()
	CString m_curImportName;
	CString m_newImportName;
	long	m_curAGPNr;
	long	m_newAGPNr;

public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnPbPass();
	afx_msg void OnPbPassWarn();
	afx_msg void OnPbCancel();
};
