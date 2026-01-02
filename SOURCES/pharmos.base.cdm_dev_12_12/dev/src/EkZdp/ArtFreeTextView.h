/******************************************************************************/
/**                                                                           */
/**   Author : R. Raab PRZ GmbH	    										  */
/**   Date   : 21.01.2015                                                     */
/**                                                                           */
/******************************************************************************/

#ifndef __ARTFREETEXTVIEW_H__
#define __ARTFREETEXTVIEW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <voodoo_table_header/cartfreetext.h>

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>

#include <phxlib/ZartikelSelCtrl.h>

#include <phxlib/RdZartikel.h>
#include <phxlib/RdCtexttypes.h>

#include <eklibs/hamfcs/hSqlListCtrl.h>

#include "hSelectDialog.h"

#include "ArtFreeTextDoc.h"
#include "ArtFreeTextBox.h"
#include "ArticleCodesConverter.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "GDIUtil.h" // for printing cformview !

/*----------------------------------------------------------------------------*/
class CArtFreeTextView : public ChPflegeView
{
	DECLARE_DYNCREATE(CArtFreeTextView)

public:
	CArtFreeTextView();           // protected constructor used by dynamic creation

private:
	UINT m_nStatus;

	enum { IDC_LAST_KEY = IDC_ED_ARTFREETEXT_ARTIKEL_CODE };

	BOOL m_bPrev;
	BOOL m_bNext;

	CArtFreeTextDoc			m_Doc;	
	struct CARTFREETEXT*	m_pBuf;
	struct CARTFREETEXT 	m_BufOld;

	ChDlg				m_dlg;
		
	CZartikelSelCtrl	m_ArtBasisSelBox;

	short			m_sMAX_LENGTH;
	short			m_sVALIDITYPERIOD;
	short			m_sMAXNUMBEROFLINES;

	int				m_nAuswahlIndex;
	int				m_nAuswahlIndex2;

	CRdZartikel		m_RD_ZARTIKEL;
	CRdCTextTypes   m_RD_CTEXTTYPES;

	void EnableFields( BOOL bEnable );
	void DisableSpecial( );
	int  DoBearbeiten( );
	int  DoSuche	 ( ); 
	BOOL Validate	 ( );
	void SetValidation( BOOL bValid );
	BOOL EndValidate( int *ind );
	BOOL IsLastKeyFocus( );

    void ShowSelectedInfo( );
	BOOL AreFieldsEnabled();
	void ResetKeys( );

	void MakeDialog( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void GotoFirstField();
	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;
	int m_nMaxFields;

	int	 m_Pos_TEXT;
	int	 m_Pos_DATVON;
	
	long m_nARTIKEL_NR;

	CString m_csArtikelName;

	bool m_bKeyArtikel;

	bool m_bShowSelect;
	bool m_bAskForDelete;

	BOOL m_bFieldsEnabled;

	char   m_ARTCODE_BASIS		[L_CARTICLECODES_ARTICLE_CODE + 1];

public:
	CArticleCodesConverter m_CodeConverterBasis;

	BOOL SetKeyArticleNoEditCtrl			( CString& cErrmld );
	void SetKeyArticleCodeEditCtrl			();
	BOOL SetArticleNoEditCtrl				( CArticleCodesConverter& codeConverter, CString& cErrmld );

public:
	//{{AFX_DATA(CArtFreeTextView)
	enum { IDD = IDD_ARTFREETEXT };
	ChDlgEdit		m_ED_ARTNR;		// this will be considered as basis-artikelno
	ChDlgEdit		m_ED_ARTCODE;
	CStatic			m_ST_SELECTION_INFO;
	ChDlgEdit		m_ED_TEXTTYPE;
	ChDlgEdit		m_ED_DATEFROM;
	ChDlgEdit		m_ED_DATETO;
	ChDlgEdit		m_ED_TEXT;
	CArtFreeTextBox	m_BOX;
	//}}AFX_DATA

public:
	virtual void InitPflege( );
	virtual void InitPflegeDocument( char* Anwender );
	virtual void ReleasePflegeDocument( );
	virtual int  SucheSatz( );
	virtual int  NextSatz( );
	virtual int  PrevSatz();
	virtual int  CloseSuche();
	virtual int  BearbeiteSatz();
	virtual int  SpeichereSatz();
	virtual int  LoescheSatz();
	virtual int  UndoSatz();

	bool IsNumber( CString cStr );

	BOOL CheckAufPzn( );

	void SucheArtikel( CEdit *pWnd );
	BOOL ShowArtikel( BOOL bMeldung = FALSE );

	BOOL ShowTexttype( BOOL bShow, BOOL bMeldung = FALSE );
	void SucheTexttype();

	void ResetVkn( );

	void CheckTexttypeChange( );

	// Dummy für Füllen der Selektionsbox
	BOOL ShowAuftragsart( );

	//{{AFX_VIRTUAL(CArtFreeTextView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
/////////////////////////////////////////////////////////////////////////////
//printing cformview
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

protected:
	GHandle m_dib;
	void grapImage( );
	afx_msg void OnFilePrint();

public: 
	virtual ~CArtFreeTextView();

	//{{AFX_MSG(CArtFreeTextView)
	afx_msg void OnItemchangedLcBox(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
