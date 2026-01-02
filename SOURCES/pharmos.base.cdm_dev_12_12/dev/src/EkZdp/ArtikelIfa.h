#if !defined(AFX_ARTIKELIFA_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELIFA_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelIfa.h : header file
//

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
#include <voodoo_table_header/carticlecodes.h>

#include <eklibs/hamfcs/hSqlListCtrl.h>


/////////////////////////////////////////////////////////////////////////////
// MBOX2

#include <voodoo_table_header/zifaart.h>
#include <voodoo_table_header/herstel.h>

// class CMbox2 : public ChSelectCtrl
class CMbox2 : public ChSqlListCtrl
{
// Construction
public:
//	CMbox2();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbox2)
	//}}AFX_VIRTUAL

// Implementation
public:
	CMbox2(){ m_tagesdatum = -1; };

	virtual ~CMbox2();

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
		long IFANR;
		long SATZNR;
		long DATUMGUELTIGAB;
		char IFASTATUS[L_ZIFAART_IFASTATUS + 1];
		char NBSTATUS[L_ZIFAART_NBSTATUS + 1];
		char ARTIKEL_CODE [L_CARTICLECODES_ARTICLE_CODE + 1];
		char A00PBEZ[L_ZIFAART_A00PBEZ + 1]; 
		char A00PGMENG[L_ZIFAART_A00PGMENG + 1];
		char A00PGEINH[L_ZIFAART_A00PGEINH + 1];
		long A00ANBNR;
		char AENDERUNG[L_ZIFAART_AENDERUNG + 1];
		long HERSTELLER_NR;
		char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1];
		long A00PZN;
	};	

	struct SelBuf m_SelBuf;

	struct VecBuf 
	{
		long IFANR;
		long SATZNR;
		long A00PZN;
	};

	struct VecBuf m_VecBuf;

	enum COLUMNS { PHZNR, EAENDER, IFASTAT,  ENZWING, EZWING, EPLAU,
				   ARTBEZ, EINHEIT, HERNR, HERMC };

	// Generated message map functions
protected:
	//{{AFX_MSG(CMbox2)
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// MBOX1

class CMbox1 : public ChSqlListCtrl
{
// Construction
public:
	CMbox1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbox1)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMbox1();

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
		long IFANR;
		long A00ANBNR;
		char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1];
		char ORT        [L_HERSTEL_ORT + 1]; 
		char PLZ		[L_HERSTEL_PLZ + 1];
	};	
	
	struct SelBuf m_SelBuf;

	enum COLUMNS { HerNr, Matchcode, Plz, Ort };

	// Generated message map functions
protected:
	//{{AFX_MSG(CMbox1)
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CArtikelIfa dialog

#define ID_ARTIFA_END	 ( WM_USER + 5 )

#define ID_ARTIFA_VORBL1 ( 0 )
#define ID_ARTIFA_RUEBL1 ( 0 )
#define ID_ARTIFA_VORBL2 ( 0 )
#define ID_ARTIFA_RUEBL2 ( 0 )

class CArtikelIfa : public CDialogMultiLang
{
private:
    CView* m_pView1;
    CView* m_pView2;
	BOOL m_bWithoutViews;

// Construction
public:
	CArtikelIfa(CWnd* pParent = NULL);   // standard constructor
	CArtikelIfa(CView* pView1, CView* pView2);		 // modeless constructor
	BOOL Create( int woher );
	void GoOn( int woher );

// Dialog Data
	//{{AFX_DATA(CArtikelIfa)
	enum { IDD = IDD_ARTIKEL_IFA };
	CButton	m_cCOPY;
	CButton	m_cNEUGEN;
	CButton	m_cARTPFL;
	CButton	m_cARTGEN;
	CButton	m_cIFANEU;
	ChDlgEdit	m_ARTSUCHB1;
	ChDlgEdit	m_ARTSUCHB2;
	ChDlgEdit	m_HERSTSUCHB;
	CMbox1 m_BOX1;
	ChDlgButton	m_SUCHE1;
	ChDlgButton	m_VORBL1;
	ChDlgButton	m_RUEBL1;
	CMbox2 m_BOX2;
	ChDlgButton	m_SUCHE2;
	ChDlgButton	m_VORBL2;
	ChDlgButton	m_RUEBL2;
	ChDlgComboBox	m_IFANR;
	ChDlgComboBox	m_NBSATZ;
	ChDlgComboBox	m_AENART;
	ChDlgComboBox	m_BEARBSTAT;
	CButton	m_cIDOK;
	CButton	m_cIDCANCEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtikelIfa)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL InitIfa();
	int PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 );
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
	char m_cIfanr;

	enum { L_ARTSUCHB1 = 10 };
	char m_cArtSuchb1[ L_ARTSUCHB1 + 1];

	enum { L_ARTSUCHB2 = 16 };
	char m_cArtSuchb2[ L_ARTSUCHB2 + 1];

	enum { L_HERSTSUCHB = 16 };
	char m_cHerstSuchb[ L_HERSTSUCHB + 1];

	BOOL m_bFirstInit;

	enum { IFA_ANZ = 20 };
	int  m_nIfaAnz;
	char m_IfaMask  [ IFA_ANZ + 1];
	long m_IfaNummer[ IFA_ANZ ];
//	char m_IfaDatum [ IFA_ANZ ][12];
	char m_IfaDatum [ IFA_ANZ ][20];

/*
	enum { MAX_AENART = 4,
		   MAX_AENKEY = 9  };

	int  m_Arten[MAX_AENART][MAX_AENKEY];
*/

	void MakeDialog();
	void InitPflege();
	int  SelectIfaNr( CString &errmld );
	int  FillBoxIfaNr(  CString &errmld );
	BOOL InitSuchBox1();

	long GenIfaNeu(  CString &errmld );
	long Fill_Arten( char *buf, char *errmld );
	void GeneriereArtikel( char *mode, long datum );

	int IsIfaDateiname( CString Datei );

	void GeneriereDefpa( long datum );
	void FillComboBox();

protected:
	// Generated message map functions
	//{{AFX_MSG(CArtikelIfa)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnPbArtifaSuche1();
	afx_msg void OnPbArtifaVorbl1();
	afx_msg void OnPbArtifaRuebl1();
	afx_msg void OnPbArtifaSuche2();
	afx_msg void OnPbArtifaVorbl2();
	afx_msg void OnPbArtifaRuebl2();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDblclkLcArtifaBox1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkLcArtifaBox2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownLcArtifaBox1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownLcArtifaBox2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPbArtifaIfaneu();
	afx_msg void OnPbArtifaArtgen();
	afx_msg void OnPbArtifaArtpfl();
	afx_msg void OnPbArtifaNeugen();
	afx_msg void OnPbArtifaCopy();
	afx_msg void OnPbArtifaDefpa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELIFA_H__A092BC81_ADD7_11D1_92F8_0060973B18D8__INCLUDED_)
