#if !defined(AFX_LINEPROTDLG_H__C8D4C178_49F9_4A8F_81A5_AC6718049E1E__INCLUDED_)
#define AFX_LINEPROTDLG_H__C8D4C178_49F9_4A8F_81A5_AC6718049E1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineprotDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CLineprotDlg 

class CLineprotDlg : public CDialog
{
// Konstruktion
public:
	CLineprotDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CLineprotDlg)
	enum { IDD = IDD_LINEPROT };
	CString	m_strFile;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CLineprotDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
public:
	void InitVars( int nProtocolMode, CString strProtocolFile, CString header );
	void GetVars ( int &nProtocolMode, CString& strProtocolFile );

private:
	int m_nProtocolMode;
	CString m_strProtocolFile;
	CString m_strHeader;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CLineprotDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnProtMode1();
	afx_msg void OnProtMode2();
	afx_msg void OnProtMode3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LINEPROTDLG_H__C8D4C178_49F9_4A8F_81A5_AC6718049E1E__INCLUDED_
