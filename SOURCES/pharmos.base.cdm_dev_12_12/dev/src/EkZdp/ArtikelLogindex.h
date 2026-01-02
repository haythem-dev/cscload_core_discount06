#if !defined(AFX_ArtikelLogIndex_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ArtikelLogIndex_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelLogindex.h : header file
//

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>

#include <eklibs/hamfcs/hSqlListCtrl.h>
#include <voodoo_table_header/carticlecodes.h>


/////////////////////////////////////////////////////////////////////////////
// Datacare - MBOX2

// muss später zur Sicherheit rausgenommen werden
// #include <zifaart.h>

#include <voodoo_table_header/herstel.h>
#include <voodoo_table_header/cliart.h>

class CLIMBox2 : public ChSqlListCtrl
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCMBox2)
	//}}AFX_VIRTUAL

// Implementation
public:
	CLIMBox2(){ m_tagesdatum = -1; };

	virtual ~CLIMBox2();

	virtual void	InitSuchBox();

	int	PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 );
	int	PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 );
	int	PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 );

private:
	long m_tagesdatum;

	long GetTagesdatum();

protected:
	virtual CString InitSelect( CString SuchBegriff );
	virtual void FillBuffer( CStringArray& s, void **vekp );

	bool    IsNumber( CString cStr );

	enum { PUFFER_ANZAHL = 30 }; 

	struct SelBuf 
	{
		long LINR;
		long SATZNR;
		char LISTATUS[L_CLIART_LISTATUS + 1];
		char NBSTATUS[L_CLIART_NBSTATUS + 1];
		char ARTIKEL_CODE [L_CARTICLECODES_ARTICLE_CODE + 1];
		char DSCRD[L_CLIART_DSCRD + 1]; 
		double QTY;
		char QTYUD[L_CLIART_QTYUD + 1];
		char ZAENDERUNG[L_CLIART_ZAENDERUNG + 1];
		long HERSTELLER_NR;
		char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1];
		long PHAR;
	};	

	struct SelBuf m_SelBuf;

	struct VecBuf 
	{
		long LINR;
		long SATZNR;
		long PHAR;
	};

	struct VecBuf m_VecBuf;

	enum COLUMNS { PHZNR, EAENDER, LISTAT,  ENZWING, EZWING, EPLAU,
				   ARTBEZ, EINHEIT, HERNR, HERMC };

	// Generated message map functions
protected:
	//{{AFX_MSG(CLIMBox2)
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// Datacare - MBOX1

class CLIMBox1 : public ChSqlListCtrl
{
// Construction
public:
	CLIMBox1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLIMBox1)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLIMBox1();

	virtual void	InitSuchBox();

protected:
	virtual CString InitSelect( CString SuchBegriff );
	virtual void FillBuffer( CStringArray& s, void **vekp );

	bool    IsNumber( CString cStr );

	enum { PUFFER_ANZAHL = 20 }; 

	struct SelBuf 
	{
		long LINR;
		long HERSTELLER_NR;
		char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1];
		char ORT        [L_HERSTEL_ORT + 1]; 
		char PLZ		[L_HERSTEL_PLZ + 1];
	};	
	
	struct SelBuf m_SelBuf;

	enum COLUMNS { HerNr, Matchcode, Plz, Ort };

	// Generated message map functions
protected:
	//{{AFX_MSG(CLIMBox1)
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CArtikelLogIndex dialog

#define ID_ARTLOGINDEX_END	 ( WM_USER + 20 )

#define ID_ARTARTLOGINDEX_VORBL1 ( 0 )
#define ID_ARTARTLOGINDEX_RUEBL1 ( 0 )
#define ID_ARTARTLOGINDEX_VORBL2 ( 0 )
#define ID_ARTARTLOGINDEX_RUEBL2 ( 0 )

class CArtikelLogIndex : public CDialogMultiLang
{
private:
    CView* m_pView1;
    CView* m_pView2;
	BOOL m_bWithoutViews;

// Construction
public:
	CArtikelLogIndex(CWnd* pParent = NULL);   // standard constructor
	CArtikelLogIndex(CView* pView1, CView* pView2);		 // modeless constructor
	BOOL Create( int woher );
	void GoOn( int woher );

// Dialog Data
	//{{AFX_DATA(CArtikelLogIndex)
	enum { IDD = IDD_ARTIKEL_LOGINDEX };
	CButton	m_cCOPY;
	CButton	m_cNEUGEN;
	CButton m_cNEUGEN_IKS;
	CButton	m_cARTPFL;
	CButton	m_cARTGEN;
	CButton	m_cARTGEN_IKS;
	CButton	m_cLINEU;
	ChDlgEdit	m_ARTSUCHB1;
	ChDlgEdit	m_ARTSUCHB2;
	ChDlgEdit	m_HERSTSUCHB;
	CLIMBox1 m_BOX1;
	ChDlgButton	m_SUCHE1;
	ChDlgButton	m_VORBL1;
	ChDlgButton	m_RUEBL1;
	CLIMBox2 m_BOX2;
	ChDlgButton	m_SUCHE2;
	ChDlgButton	m_VORBL2;
	ChDlgButton	m_RUEBL2;
	ChDlgComboBox	m_LINR;
	ChDlgComboBox	m_NBSATZ;
	ChDlgComboBox	m_AENART;
	ChDlgComboBox	m_BEARBSTAT;
	ChDlgComboBox	m_IKSCODE;
	CButton	m_cIDOK;
	CButton	m_cIDCANCEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtikelLogIndex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL InitLogIndex();
	int PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2,
								  long *Key3 );
	int PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 );
	int PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 );

	void F2Suche1();
	void F2Suche2();

private:
	int	 m_nWoher; 
	ChDlg m_dlg;
	char m_cAenart;
	char m_cNbsatz;
	char m_cBearbstat;
	char m_cIksCode;
	char m_cLogindexnr;

	enum { L_ARTSUCHB1 = 10 };
	char m_cArtSuchb1[ L_ARTSUCHB1 + 1];

	enum { L_ARTSUCHB2 = 16 };
	char m_cArtSuchb2[ L_ARTSUCHB2 + 1];

	enum { L_HERSTSUCHB = 16 };
	char m_cHerstSuchb[ L_HERSTSUCHB + 1];

	BOOL m_bFirstInit;

	enum { LOGINDEX_ANZ = 20 };
	int  m_nLogindexAnz;
	char m_LogindexMask  [ LOGINDEX_ANZ + 1];
	long m_LogindexNummer[ LOGINDEX_ANZ ];
	char m_LogindexDatum [ LOGINDEX_ANZ ][20];

	void MakeDialog();
	void InitPflege();
	int  SelectLogIndexNr( CString &errmld );
	int  FillBoxLogIndexNr(  CString &errmld );
	BOOL InitSuchBox1();

	long GenLogIndexNeu(  CString &errmld );
	long Fill_Arten( char *buf, char *errmld );
	void GeneriereArtikel( char *mode, long datum );

	int IsLogIndexDateiname( CString Datei );
	void FillComboBox();

protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelLogIndex)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPbArtlogindexSuche1();
	afx_msg void OnPbArtlogindexVorbl1();
	afx_msg void OnPbArtlogindexRuebl1();
	afx_msg void OnPbArtlogindexSuche2();
	afx_msg void OnPbArtlogindexVorbl2();
	afx_msg void OnPbArtlogindexRuebl2();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDblclkLcArtlogindexBox1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkLcArtlogindexBox2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownLcArtlogindexBox1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownLcArtlogindexBox2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPbArtlogindexLogindexneu();
	afx_msg void OnPbArtlogindexArtgen();
	afx_msg void OnPbArtlogindexArtgenIks();
	afx_msg void OnPbArtlogindexArtpfl();
	afx_msg void OnPbArtlogindexNeugen();
	afx_msg void OnPbArtlogindexNeugenIks();
	afx_msg void OnPbArtlogindexCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ArtikelLogindex_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)
