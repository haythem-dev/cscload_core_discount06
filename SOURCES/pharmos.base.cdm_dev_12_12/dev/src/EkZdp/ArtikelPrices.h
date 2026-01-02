#if !defined(AFX_ARTIKELPRICES_H__9328D341_7853_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELPRICES_H__9328D341_7853_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelPrices.h : header file
//

#include <eklibs/hamfcs/listctex.h>
#include <voodoo_table_header/zartprei.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include "ArtikelPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CArtikelPrices dialog

class CArtikelPrices : public CDialogMultiLang
{
// Construction
public:
	CArtikelPrices(CWnd* pParent = NULL);   // standard constructor
	CArtikelPrices(struct ZARTPREIS *pBuf,  CWnd* pParent = NULL);
	
	
// Dialog Data
	//{{AFX_DATA(CArtikelPrices)
	enum { IDD = IDD_ARTIKEL_PRICES };
	CButton			m_bSAVE;
	CButton			m_bNEW;
	CButton			m_bCALC;
	CListCtrlEx		m_cPRICESBOX;
	ChDlgComboBox	m_cPREISTYP;
	ChDlgComboBox	m_cMWST;
	ChDlgComboBox	m_cDISC_DED_YET;
	ChDlgEdit		m_eGUELAB;
	ChDlgEdit		m_eGROSSO;
	ChDlgEdit		m_eAEP;
	ChDlgEdit		m_eAGP;
	ChDlgEdit		m_eAVP;
	ChDlgEdit		m_eEAVP;
	ChDlgEdit		m_eMAXAEP;
	ChDlgEdit		m_eMAXAVP;
	ChDlgEdit		m_eHPROZ;
	ChDlgEdit		m_eHPROZ_ART;
	ChDlgEdit		m_eLBP;
	ChDlgEdit		m_ePBP;
	ChDlgEdit		m_eERSTATTBETRAG;
	ChDlgEdit		m_ePUBL_NR;

	CStatic		m_stMWST;
	CStatic		m_stDISC_DED_YET;
	CStatic		m_stGUELAB;
	CStatic		m_stGROSSO;
	CStatic		m_stAEP;
	CStatic		m_stAGP;
	CStatic		m_stAVP;
	CStatic		m_stEAVP;
	CStatic		m_stMAXAEP;
	CStatic		m_stMAXAVP;
	CStatic		m_stHPROZ;
	CStatic		m_stLBP;
	CStatic		m_stPBP;
	CStatic		m_stERSTATTBETRAG;
	CStatic		m_stPUBL_NR;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtikelPrices)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

public:
	void Set_Grosso_From_LBP();
	void CalculatePercent( );
	void FillComboBoxVAT(long lDatum = 0);
	void Set_Taxe_AEP( );
	void Set_Taxe_AVP( );
	void Set_Herst_Prozent( );
	void Enable_AVP_Croatia( );
	void EnableCalcButton( );

// Implementation
private:
	BOOL InitSuchBox();
	void InitPflege();
	bool IstAllesOk();
	void FillSuchBox(  CStringArray &s );
	void FillBuffer( int i, CStringArray &s );
	void FillComboBoxes();
	int  GetSekbez( );
	void MarkListPos( int pos );
	void AppendBlanks( char *str, int lng );
	void EnableFields();
	void DisableFields();
	void SetDateTomorrow();
	void EnableNewButton();
	void CopyGuiToPriceBuffer(int pos);
	void CopyPriceBufferToGuiList();
	void CopySinglePriceToGui(int pos, bool withoutMwst = false);
	void CopyPrice(int pos);
	int  GetSelectedRow();

	bool Test_Preis( );
	bool Test_MaxAep_MaxAvp( );
	bool Test_PreisAufNull( );
	bool Test_NichtTaxartikel( );
	bool Test_NichtTaxartikelGesperrt(  );
	bool Test_Taxartikel( );
	
	double PreisAusProzent(const double preis, const double proz);

	struct ZARTPREIS	*m_pBuf;
	CWnd				*m_pView;
	CArtikelPage1		*m_ArtPage1;
	struct ZARTIKEL		*m_pBufArtikel;


	char   m_PUBLICATIONNUMBER[L_ZARTPREIS_PUBLICATIONNUMBER + 1];
	long   m_DATUMGUELTIGAB		;
	double m_GROSSO             ;
    double m_AEP                ;
	double m_AGP				;
    double m_AVP                ;
    char   m_KE_MWST          [L_ZARTPREIS_KE_MWST + 1];
    double m_HERST_PROZENT      ;
    double m_EAVP               ;
    double m_MAXAVP             ;
    short  m_PREIS_TYP          ;
    double m_LIEFERBASISPREIS   ;
    double m_MAXAEP             ;
    double m_ERSTATTBETRAG      ;
    short  m_DISC_DEDUCED_YET   ;
    double m_PHARMACY_BASEPRICE ;

	struct COLUMNS_TYPES
	{
		int Index;
		char Columns[100];
		int Width;
		int Align;
		bool isVisible;
	};

	#define NUM_OF_PRICE_COLUMNS	14
	struct COLUMNS_TYPES m_Columns[NUM_OF_PRICE_COLUMNS + 1];
	
protected:

	// Generated message map functions
	//{{AFX_MSG(CArtikelPrices)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnItemchangedLcArtikelPricesBox(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPbArtikelPricesNew();
	afx_msg void OnPbArtikelPricesSave();
	afx_msg void OnPbArtikelPricesEnd();
	afx_msg void OnPbArtikelPricesCalculate();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnSelchangeCbArtikelPreistyp();
	afx_msg void OnSelchangeCbArtikelMwst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	HACCEL    m_hAccelerator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELPRICES_H__9328D341_7853_11D1_92F8_0060973B18D8__INCLUDED_)
