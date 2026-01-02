/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH											  */
/**   Date   : 11.01.2006                                                     */
/**                                                                           */
/******************************************************************************/

#ifndef __ARTICLECODESVIEW_H__
#define __ARTICLECODESVIEW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/ccodetypes.h>

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>

#include <phxlib/ZartikelSelCtrl.h>

#include <phxlib/RdZartikel.h>

#include <eklibs/hamfcs/hSqlListCtrl.h>

#include "hSelectDialog.h"

#include "ArticleCodesDoc.h"
#include "ArticleCodesBox.h"
#include "ArticleCodesConverter.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "GDIUtil.h" // for printing cformview !

/*----------------------------------------------------------------------------*/
class CArticleCodesView : public ChPflegeView
{
	DECLARE_DYNCREATE(CArticleCodesView)

public:
	CArticleCodesView();           // protected constructor used by dynamic creation

private:
	UINT m_nStatus;

	enum {  IDC_LAST_KEY = IDC_ED_ARTCODE_CODE_KEY };


#define CB_YES	1
#define CB_NO	0


	BOOL m_bPrev;
	BOOL m_bNext;

	struct CARTICLECODES 	m_BufOld;

	ChDlg				m_dlg;
		
	CZartikelSelCtrl			m_ArtSelBox;

	int				 m_nAuswahlIndex;
	int				 m_nAuswahlIndex2;

	
	void EnableFields( BOOL bEnable );
	int  DoBearbeiten( );
	int  DoSuche	 ( ); 
	BOOL Validate	 ( );
	void SetValidation( BOOL bValid );
	BOOL EndValidate( int *ind );
	BOOL IsLastKeyFocus( );

	void FillComboBox();

	void MakeDialog( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;
	int m_nMaxFields;

	bool m_bShowSelect;

	int m_PrefCodeType;

	char   m_ARTCODE[L_CARTICLECODES_ARTICLE_CODE + 1];
	CArticleCodesConverter m_CodeConverter;

	BOOL SetArticleNoEditCtrl( CString& cErrmld );
	void SetArticleCodeEditCtrl();

	void KeyGetInput();
	void KeySetInput();


public:
	long					m_nARTIKEL_NR;
	struct CARTICLECODES *	m_pBuf;
	CRdZartikel				m_RD_ZARTIKEL;
	CArticleCodesDoc		m_Doc;	
	short					m_nVERGABE_ART_PZN_NEU;
	
	//{{AFX_DATA(CArticleCodesView)
	enum { IDD = IDD_ARTCODES };
	ChDlgEdit		m_ED_ARTNR;
	CStatic			m_ST_ART_INFO;
	ChDlgComboBox	m_CB_VERGABE_ART_PZN_NEU;
	ChDlgEdit		m_ED_PZN_NEU;
	ChDlgEdit		m_ED_ARTICLE_CODE;
	ChDlgComboBox	m_CB_CODE_TYPE;
	ChDlgButton		m_CK_PREFERRED;
	CArticleCodesBox m_BOX;
	ChDlgEdit	m_ARTIKEL_CODE;
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

	void SucheArtikel( CEdit *pWnd );
	BOOL ShowArtikel( BOOL bMeldung = FALSE );

	bool    IsNumber( CString cStr );

	//{{AFX_VIRTUAL(CArticleCodesView)
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
	virtual ~CArticleCodesView();

	//{{AFX_MSG(CArticleCodesView)
	afx_msg void OnSelchangeCbVergabeArtPznNeu();
	afx_msg void OnSelchangeCbCodeType();
	afx_msg void OnItemchangedLcBox(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
