#if !defined(AFX_CARTIKELAGP_H__A46AA19E_8898_4D49_B4CA_EB600FA0CFDE_INCLUDED_)
#define AFX_CARTIKELAGP_H__A46AA19E_8898_4D49_B4CA_EB600FA0CFDE_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CArtikelAgp.h : header file
//
#include "AgpDoc.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
#include <eklibs/hamfcs/hColStatic.h>
#include <eklibs/hamfcs/hSqlListCtrl.h>
#include <voodoo_table_header/cagpoart.h>
#include "afxwin.h"
#include "afxcmn.h"


// List control box
class CAGPMBox1 : public ChSqlListCtrl
{
	// Construction
public:
	CAGPMBox1();

	// Attributes
public:

	// Operations
public:

	// Implementation
public:
	virtual ~CAGPMBox1();

	virtual void InitSuchBox();
	int	PrimeKeyOfNextRecord(long *PrimeKey1, long *PrimeKey2, long *Key3);
	int	PrimeKeyOfPrevRecord(long *PrimeKey1, long *PrimeKey2, long *Key3);
	int	PrimeKeyOfSelectedRecord(long *PrimeKey1, long *PrimeKey2, long *Key3);
	bool IsNumber(CString cStr);
	CString GetZeileStatus(short status);
protected:
	// Sets maximum records to fetch.
	enum { PUFFER_ANZAHL = 30 };

	// Data for each row in list control box
	struct SelBuf
	{
		long AGP_NR;
		long PZN;
		double AGP;
		long GUELTIG_AB;
		short ZEILE_STATUS;
		char STATUS_DETAIL[51];
	};
	struct SelBuf m_SelBuf;
	enum COLUMNS { PZN, AGP, GUELTIGAB, ZEILESTATUS, STATUS_DETAIL };
	struct VecBuf
	{
		long AGP_NR;
		long PZN;
		long GUELTIG_AB;
	};
	struct VecBuf m_VecBuf;
	virtual CString InitSelect(CString SuchBegriff);
	virtual void FillBuffer(CStringArray& s, void **vekp);		
};


#define ID_ARTAGP_END	 ( WM_USER + 20 )
#define ID_ARTAGP_VORBL ( 0 )
#define ID_ARTAGP_RUEBL ( 0 )

// ArtikelAgp dialog
class CArtikelAgp : public CDialogMultiLang
{

private:
	CView* m_pView1;
	CView* m_pView2;
	BOOL m_bWithoutViews;
	BOOL m_bFirstInit;
	int	 m_nWoher;
	ChDlg m_dlg;
	struct PFL_AGP* m_pBuf;
	CAgpDoc m_Doc;
	enum { MAX_AGP_ANZ = 20 };
	int  m_nAgpAnz;
	char m_AgpMask[MAX_AGP_ANZ + 1];

	// Holds data for AGP number combobox and import information
	struct CAGPOARTDATA
	{
		long AGP_NR;
		char AGP_INDEX[30];
		long DATUM_ANLAGE;
		long ZEIT_ANLAGE;
		char ANWENDER[9];
		char IMPORTDATEI[31];
		short TXN_STATUS;
		long REC_ERFOLG;
		long REC_WARNUNG;
		long REC_FEHLER;
	};

	struct CAGPOARTDATA m_AGPKopf[MAX_AGP_ANZ];

	struct CAGPART m_ValReportBuf;

	enum { L_ARTSUCHPZN = 7 };
	char m_cArtSuchPZN[L_ARTSUCHPZN + 1];

	enum { L_ARTSUCHGUTAB = 10 };
	char m_cArtSuchGutAb[L_ARTSUCHGUTAB + 1];
	char m_cAgpnr;
	char m_cArtStatus;
	void FillComboBox();
	BOOL InitAgp();
private:
	void MakeDialog();
	void InitPflege();
	int  SelectAgpNr(CString &errmld);
	int  FillBoxAgpNr(CString &errmld);
	void FillImportData();
	int SelectAgpIndexFromCB();
	void RefreshSearchBox();
	void SelectAgpIndexInCB(long agpnr);
public:
	CArtikelAgp(CWnd* pParent = NULL);   // standard constructor
	CArtikelAgp(CView* pView1, CView* pView2);		 // modeless constructor
	virtual ~CArtikelAgp();
	BOOL Create(int woher);
	void GoOn(int woher);
	int PrimeKeyOfSelectedRecord(long *PrimeKey1, long *PrimeKey2,long *Key3);
	int PrimeKeyOfNextRecord(long *PrimeKey1, long *PrimeKey2, long *Key3);
	int PrimeKeyOfPrevRecord(long *PrimeKey1, long *PrimeKey2, long *Key3);
	void F2Suche();
	CString GetTransactionStatus(short status);
	int GenerateValidationReport(CFile &file);

// Dialog Data
// #ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTIKEL_AGP };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	ChDlgEdit m_ARTSUCHPZN;
	ChDlgEdit m_ARTSUCHGUTAB;
	ChDlgComboBox m_ARTSUCHSTATUS;
	// AGP number of import dialog
	ChDlgComboBox m_AGPNR;
	CAGPMBox1 m_ARTBOX;
	// Stats for AGP number
	ChColStatic m_AGP_STATS;
	// Imported by user
	ChColStatic m_IMPORTBY;
	// Import date & times
	ChColStatic m_IMPORTDATUMZEIT;
	// Status of the import
	ChColStatic m_IMPORTSTATUS;
	ChDlgButton m_RUEBL;
	ChDlgButton m_SUCHE;
	ChDlgButton m_VORBL;
	// New import button
	CButton m_cAGPNEU;
	// Generate new validation report
	CButton m_cVALIDREPORT;
	// Deletes existing AGP import
	CButton m_cAGPLOESCHEN;
	CButton m_cAGPDUPLIZIEREN;
	CButton cIDCANCEL;
	CButton	m_cIDOK;
	CButton	m_cIDCANCEL;

protected:
	// Suchebox events
	void OnPbArtAgpArtpfl();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPbArtAgpRuebl();
	afx_msg void OnPbArtAgpSuche();
	afx_msg void OnPbArtAgpVorbl();
	afx_msg void OnPbArtAgpNeu();
	afx_msg void OnPbArtAgpValReport();
	afx_msg void OnPbArtAgpLoeschen();
	afx_msg void OnPbArtAgpDuplizieren();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAgpnrSelChange();
	afx_msg void OnDblclkLcArtagpBox(NMHDR *pNMHDR, LRESULT *pResult);
};


#endif // !defined(AFX_CARTIKELAGP_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)