#if !defined(AFX_ArtikelDatacare_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ArtikelDatacare_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelDatacare.h : header file
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
#include <voodoo_table_header/zdcart.h>

// class CDCMBox2 : public ChSelectCtrl
class CDCMBox2 : public ChSqlListCtrl
{
// Construction
public:
//	CDCMBox2();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCMBox2)
	//}}AFX_VIRTUAL

// Implementation
public:
	CDCMBox2(){ m_tagesdatum = -1; };

	virtual ~CDCMBox2();

	virtual void	InitSuchBox();
//	virtual CString InitSuchBegr_1( );
//	virtual BOOL	SetScrollMode();

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
		long DCNR;
		long SATZNR;
		long DC_DATUMGUELTIGAB;
		char DCSTATUS[L_ZDCART_DCSTATUS + 1];
		char NBSTATUS[L_ZDCART_NBSTATUS + 1];
		char ARTIKEL_CODE [L_CARTICLECODES_ARTICLE_CODE + 1];
		char DC_ARTIKELTEXT[L_ZDCART_DC_ARTIKELTEXT + 1]; 
		char DC_EINH_MENGE[L_ZDCART_DC_EINH_MENGE + 1];
		char DC_EINH_EINH[L_ZDCART_DC_EINH_EINHEIT + 1];
		char ZAENDERUNG[L_ZDCART_ZAENDERUNG + 1];
		long HERSTELLER_NR;
		char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1];
		long DC_ARTIKEL_NR;
	};	

	struct SelBuf m_SelBuf;

	struct VecBuf 
	{
		long DCNR;
		long SATZNR;
		long DC_ARTIKEL_NR;
	};

	struct VecBuf m_VecBuf;

	enum COLUMNS { PHZNR, EAENDER, DCSTAT,  ENZWING, EZWING, EPLAU,
				   ARTBEZ, EINHEIT, HERNR, HERMC };

	// Generated message map functions
protected:
	//{{AFX_MSG(CDCMBox2)
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// Datacare - MBOX1

class CDCMBox1 : public ChSqlListCtrl
{
// Construction
public:
	CDCMBox1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCMBox1)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDCMBox1();

	virtual void	InitSuchBox();
/*
	int	PrimeKeyOfNextRecord( char *PrimeKey );
	int	PrimeKeyOfPrevRecord( char *PrimeKey );
	int	PrimeKeyOfSelectedRecord( char *PrimeKey );
*/

protected:
	virtual CString InitSelect( CString SuchBegriff );
	virtual void FillBuffer( CStringArray& s, void **vekp );

	bool    IsNumber( CString cStr );

	enum { PUFFER_ANZAHL = 20 }; 

	struct SelBuf 
	{
		long DCNR;
		long HERSTELLER_NR;
		char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1];
		char ORT        [L_HERSTEL_ORT + 1]; 
		char PLZ		[L_HERSTEL_PLZ + 1];
	};	
	
	struct SelBuf m_SelBuf;

	enum COLUMNS { HerNr, Matchcode, Plz, Ort };

	// Generated message map functions
protected:
	//{{AFX_MSG(CDCMBox1)
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CArtikelDatacare dialog

#define ID_ARTDATACARE_END	 ( WM_USER + 20 )

#define ID_ARTARTDATACARE_VORBL1 ( 0 )
#define ID_ARTARTDATACARE_RUEBL1 ( 0 )
#define ID_ARTARTDATACARE_VORBL2 ( 0 )
#define ID_ARTARTDATACARE_RUEBL2 ( 0 )

class CArtikelDatacare : public CDialogMultiLang
{
private:
    CView* m_pView1;
    CView* m_pView2;
	BOOL m_bWithoutViews;

// Construction
public:
	CArtikelDatacare(CWnd* pParent = NULL);   // standard constructor
	CArtikelDatacare(CView* pView1, CView* pView2);		 // modeless constructor
	BOOL Create( int woher );
	void GoOn( int woher );

// Dialog Data
	//{{AFX_DATA(CArtikelDatacare)
	enum { IDD = IDD_ARTIKEL_DATACARE };
	CButton	m_cCOPY;
	CButton	m_cNEUGEN;
	CButton	m_cARTPFL;
	CButton	m_cARTGEN;
	CButton	m_cDCNEU;
	CButton m_cDCEAN;
	CButton m_cDCDEMEST;
	ChDlgEdit	m_ARTSUCHB1;
	ChDlgEdit	m_ARTSUCHB2;
	ChDlgEdit	m_HERSTSUCHB;
	CDCMBox1 m_BOX1;
	ChDlgButton	m_SUCHE1;
	ChDlgButton	m_VORBL1;
	ChDlgButton	m_RUEBL1;
	CDCMBox2 m_BOX2;
	ChDlgButton	m_SUCHE2;
	ChDlgButton	m_VORBL2;
	ChDlgButton	m_RUEBL2;
	ChDlgComboBox	m_DCNR;
	ChDlgComboBox	m_NBSATZ;
	ChDlgComboBox	m_AENART;
	ChDlgComboBox	m_BEARBSTAT;
	CButton	m_cIDOK;
	CButton	m_cIDCANCEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtikelDatacare)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL InitDatacare();
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
	char m_cDatacarenr;

	enum { L_ARTSUCHB1 = 10 };
	char m_cArtSuchb1[ L_ARTSUCHB1 + 1];

	enum { L_ARTSUCHB2 = 16 };
	char m_cArtSuchb2[ L_ARTSUCHB2 + 1];

	enum { L_HERSTSUCHB = 16 };
	char m_cHerstSuchb[ L_HERSTSUCHB + 1];

	BOOL m_bFirstInit;

	enum { DATACARE_ANZ = 20 };
	int  m_nDatacareAnz;
	char m_DatacareMask  [ DATACARE_ANZ + 1];
	long m_DatacareNummer[ DATACARE_ANZ ];
	char m_DatacareDatum [ DATACARE_ANZ ][20];

/*
	enum { MAX_AENART = 4,
		   MAX_AENKEY = 9  };

	int  m_Arten[MAX_AENART][MAX_AENKEY];
*/

	void MakeDialog();
	void InitPflege();
	int  SelectDatacareNr( CString &errmld );
	int  FillBoxDatacareNr(  CString &errmld );
	BOOL InitSuchBox1();

	long GenDatacareNeu(  CString &errmld );
	long Fill_Arten( char *buf, char *errmld );
	void GeneriereArtikel( char *mode, long datum );

	int IsDatacareDateiname( CString Datei );
	void FillComboBox();

	void processAklFile(CStdioFile * stdiofile);
	void processAsmFile(CStdioFile * stdiofile);
	void processKlgFile(CStdioFile * stdiofile);

protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelDatacare)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPbArtdatacareSuche1();
	afx_msg void OnPbArtdatacareVorbl1();
	afx_msg void OnPbArtdatacareRuebl1();
	afx_msg void OnPbArtdatacareSuche2();
	afx_msg void OnPbArtdatacareVorbl2();
	afx_msg void OnPbArtdatacareRuebl2();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDblclkLcArtdatacareBox1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkLcArtdatacareBox2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownLcArtdatacareBox1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownLcArtdatacareBox2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPbArtdatacareDatacareneu();
	afx_msg void OnPbArtdatacareEan();
	afx_msg void OnPbArtdatacareDemEst();
	afx_msg void OnPbArtdatacareArtgen();
	afx_msg void OnPbArtdatacareArtpfl();
	afx_msg void OnPbArtdatacareNeugen();
	afx_msg void OnPbArtdatacareCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ArtikelDatacare_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)
