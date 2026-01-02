#if !defined(AFX_HSELECTDIALOG_H__F10A4122_3A54_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_HSELECTDIALOG_H__F10A4122_3A54_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// hSelectDialog.h : header file
//

#include <phxlib/hSelectCtrl.h>
#include <eklibs/hamfcs/hBmpButton.h>
#include <eklibs/hamfcs/hDlgEdit.h>

#define HCD_BUTTONALTERN	1
#define HCD_SCROLLINFO		2


/////////////////////////////////////////////////////////////////////////////
// ChSelectDialog dialog

class ChSelectDialog : public CDialog
{
// Construction
public:
	ChSelectDialog(CString Caption, ChSelectCtrl *SelBox, DWORD dwStyle = 0,
				   CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ChSelectDialog)
	enum { IDD = IDD_SELECTDLG1 };
	CComboBox	m_cComboboxAuswahl;
	CStatic	m_cStaticAuswahl;
	CButton	m_Idcancel;
	CButton	m_cIdok;
	ChSelectCtrl *m_cSelectCtrl;
	CStatic		m_cStaticSuchb1;
	CStatic		m_cStaticFrage1;
	ChDlgEdit	m_cEditSuchb1;
	CStatic		m_cStaticSuchb2;
	CStatic		m_cStaticFrage2;
	ChDlgEdit   m_cEditSuchb2;
	ChBmpButton	m_cSuche;
	ChBmpButton	m_cRuebl;
	ChBmpButton	m_cVorbl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void BeendeDialog( int nResult );

public:
	CString GetKeyString( );
	int GetCursorFd();
	void F2Suche();
	void RestoreAuswahlIndex( int index );
	int  GetAuswahlIndex( );

	virtual void ShowSuchBegriff1( BOOL bMeldung );
	virtual void SucheSuchBegriff1( );
	virtual void ShowSuchBegriff2( BOOL bMeldung );
	virtual void SucheSuchBegriff2( );

private:
	CString m_Caption;
	BOOL m_bButtonAltern;
	BOOL m_bScrollInfo;
	BOOL m_bSuchBegr2;
	BOOL m_bAuswahl;
	int  m_OpenMode;
	int	 m_nAuswahlIndex;

protected:

	// Generated message map functions
	//{{AFX_MSG(ChSelectDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSuche();
	afx_msg void OnVorbl();
	afx_msg void OnRuebl();
	afx_msg void OnDblclkListctrlBox(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnKeydownListctrlBox(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnMsgVorbl( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMsgRuebl( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HSELECTDIALOG_H__F10A4122_3A54_11D1_92F8_0060973B18D8__INCLUDED_)
