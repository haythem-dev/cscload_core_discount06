#if !defined(AFX_ARTIKELSEKBEZ_H__9328D341_7853_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELSEKBEZ_H__9328D341_7853_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelSekbez.h : header file
//

#include <eklibs/hamfcs/listctex.h>
#include <voodoo_table_header/zartsekb.h>
#include <eklibs/hamfcs/hDlgEdit.h>

/////////////////////////////////////////////////////////////////////////////
// CArtikelSekbez dialog

class CArtikelSekbez : public CDialogMultiLang
{
// Construction
public:
	CArtikelSekbez(CWnd* pParent = NULL);   // standard constructor
	CArtikelSekbez(struct ZARTSEKBEZ *pBuf, int nNrOfSekbez, 
				   CWnd* pParent = NULL);
	int GetNewNrOfSekbez( );
	CString GetPharmosSekbez( );

// Dialog Data
	//{{AFX_DATA(CArtikelSekbez)
	enum { IDD = IDD_ARTIKEL_SEKBEZ };
	CButton	m_cOk;
	CListCtrlEx	m_cSEKBEZBOX;
	ChDlgEdit	m_cBEMERKUNG;
	ChDlgEdit	m_cNAME;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtikelSekbez)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	BOOL InitSuchBox();
	bool IstAllesOk();
	void FillSuchBox(  CStringArray &s );
	void UpdateSuchBox( int index, CStringArray &s );
	void FillBuffer( int i, CStringArray &s );
	int  GetSekbez( );
	void MarkListPos( int pos );
	void AppendBlanks( char *str, int lng );

	int    m_nBoxPos;
	int	   m_nNrOfSekbez;
	char   m_ARTIKEL_NAME[L_ZARTSEKBEZ_ARTIKEL_NAME + 1];
	char   m_BEMERKUNG[L_ZARTSEKBEZ_BEMERKUNGEN + 1];
	struct ZARTSEKBEZ *m_pBuf;

protected:

	// Generated message map functions
	//{{AFX_MSG(CArtikelSekbez)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnItemchangedLcArtikelSekbezBox(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPbArtikelSekbezLoesch();
	afx_msg void OnPbArtikelSekbezUebern();
	afx_msg void OnPbArtikelSekbezEnde();
	afx_msg void OnPaint();
	afx_msg void OnPbArtikelSekbezPharmos();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELSEKBEZ_H__9328D341_7853_11D1_92F8_0060973B18D8__INCLUDED_)
