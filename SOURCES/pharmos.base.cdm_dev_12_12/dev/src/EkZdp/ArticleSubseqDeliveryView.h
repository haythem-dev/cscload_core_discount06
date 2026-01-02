/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH											  */
/**   Date   : 11.01.2006                                                     */
/**                                                                           */
/******************************************************************************/

#ifndef __ARTICLESUBSEQDELIVERYVIEW_H__
#define __ARTICLESUBSEQDELIVERYVIEW_H__

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

#include "ArticleSubseqDeliveryDoc.h"
#include "SubseqDeliveryFlagBox.h"
#include "ArticleCodesConverter.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "GDIUtil.h" // for printing cformview !

#include "Ekzdp.h"

#include <vector>



/*----------------------------------------------------------------------------*/
class CArticleSubseqDeliveryView : public ChPflegeView
{
	DECLARE_DYNCREATE(CArticleSubseqDeliveryView)

public:
	CArticleSubseqDeliveryView();           // protected constructor used by dynamic creation

private:
	enum {
		IDC_LAST_KEY = IDC_ED_ART_SUBSEQDELIVERY_ARTICLE_CODE
	};

	ChDlg				m_dlg;
		
	CZartikelSelCtrl	m_ArtSelBox;

	int	m_nAuswahlIndex;
	int	m_nAuswahlIndex2;
	int m_Pos_FirstKey;
	int m_Pos_LastKey;

	UINT m_nStatus;

	char   m_ARTCODE[L_CARTICLECODES_ARTICLE_CODE + 1];
	CArticleCodesConverter m_CodeConverter;

	void EnableFields( BOOL bEnable );
	int  DoSuche	 ( ); 

	void FillComboBox();

	void MakeDialog( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );

//	BOOL SetArticleNoEditCtrl( CString& cErrmld );
	void SetArticleCodeEditCtrl();

	void KeyGetInput();
	void KeySetInput();

public:
	long					m_nARTIKEL_NR;
	int                     m_iBranchno;
	struct CSUBSEQDELIVERIES*	m_pBuf;
	CRdZartikel				m_RD_ZARTIKEL;
	CArticleSubseqDeliveryDoc	m_Doc;	
	short					m_nVERGABE_ART_PZN_NEU;
	
	//{{AFX_DATA(CArticleSubseqDeliveryView)
	enum { IDD = IDD_ART_SUBSEQDELIVERY };
	CStatic			m_ST_ART_INFO;
	ChDlgEdit		m_ED_ARTNR;
	ChDlgEdit		m_ED_ARTICLE_CODE;
	CStatic    		m_ED_BRANCH;
	CButton         m_CK_MODIFY_ALL_BRANCHES;
	ChDlgEdit		m_ARTIKEL_CODE;
	CStatic		    m_ARTICLENBR;
	ChDlgComboBox	m_CB_VERGABE_SUBSEQDEL_FLAG;
	CStatic		    m_CHANGED_BY;
	CStatic		    m_CHANGEDATE;
	CSubseqDeliveryFlagBox m_BOX;

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
	void redrawListCtrl();
	virtual int  UndoSatz();

	BOOL ShowSubseqDeliveryEntry( CSUBSEQDELIVERIES *pSubseqDeliveryEntry );

	//{{AFX_VIRTUAL(CArticleSubseqDeliveryView)
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
	void grabImage( );
	afx_msg void OnFilePrint();
	void SetArticleNoEditCtrl(long lNewArticleNo);
	void ShowSelectedArticle();

	void SetCurrentArticleNo(long lArticleNo) { m_nARTIKEL_NR = lArticleNo; };
	void SetCurrentArticleNo(const CString& strArticleNo) { m_nARTIKEL_NR = atol(strArticleNo); };
	long GetCurrentArticleNo() { return m_nARTIKEL_NR; };


public: 
	virtual ~CArticleSubseqDeliveryView();

	//{{AFX_MSG(CArticleSubseqDeliveryView)
	afx_msg void OnItemchangedLcBox(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeComboSubseqdeliverySubseqdeliveryflag();

	std::vector<ChangeBuffer> m_changebufferlist;

public:
	std::vector<ChangeBuffer>* getChangebufferlist()
	{
		return &m_changebufferlist;
	}
	afx_msg void OnBnClickedSubsequentdeliveryModifyAllBranches();
};

#endif 
