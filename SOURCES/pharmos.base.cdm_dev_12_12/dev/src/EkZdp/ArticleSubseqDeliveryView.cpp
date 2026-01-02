/******************************************************************************/
/**                                                                           */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"
#include "ekzdp.h"
#include "ArticleSubseqDeliveryView.h"
#include "ServerDatum.h"
#include "FeldBreite.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskUmlaut.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include <phxlib/PhxUtil.h>

#include <libscsvoodoo/libscsvoodoo.h>

#include <voodoo_table_header/passwd.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int iIndex4Invalid = 9999;

IMPLEMENT_DYNCREATE(CArticleSubseqDeliveryView, CFormViewMultiLang)

/*----------------------------------------------------------------------------*/
CArticleSubseqDeliveryView::CArticleSubseqDeliveryView()
	: ChPflegeView(CArticleSubseqDeliveryView::IDD), 
	  m_CodeConverter( m_ARTIKEL_CODE, m_ED_ARTNR, m_ArtSelBox )
{
	m_iBranchno = -1;
}

/*----------------------------------------------------------------------------*/
CArticleSubseqDeliveryView::~CArticleSubseqDeliveryView()
{
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArticleSubseqDeliveryView)
	DDX_Control(pDX, IDC_ST_ART_SUBSEQDELIVERY_ART_INFO,    m_ST_ART_INFO);
	DDX_Control(pDX, IDC_ED_ART_SUBSEQDELIVERY_ARTICLE_NO,	m_ED_ARTNR);
 	DDX_Control(pDX, IDC_ED_ART_SUBSEQDELIVERY_BRANCH,		m_ED_BRANCH);
	DDX_Control(pDX, IDC_SUBSEQUENTDELIVERY_MODIFY_ALL_BRANCHES, m_CK_MODIFY_ALL_BRANCHES);
 	DDX_Control(pDX, IDC_ED_ART_SUBSEQDELIVERY_ARTCICLENBR, m_ARTICLENBR);
 	DDX_Control(pDX, IDC_COMBO_SUBSEQDELIVERY_SUBSEQDELIVERYFLAG, m_CB_VERGABE_SUBSEQDEL_FLAG);
 	DDX_Control(pDX, IDC_ED_ART_SUBSEQDELIVERY_CHANGED_BY,  m_CHANGED_BY);
 	DDX_Control(pDX, IDC_ED_ART_SUBSEQDELIVERY_CHANGEDATE,  m_CHANGEDATE);

	DDX_Control(pDX, IDC_LC_BRANCHES_BOX, m_BOX);

	DDX_Control(pDX, IDC_ED_ART_SUBSEQDELIVERY_ARTICLE_CODE, m_ARTIKEL_CODE);
	//}}AFX_DATA_MAP
}

/*----------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CArticleSubseqDeliveryView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArticleSubseqDeliveryView)
/////////////////////////////////////////////////////////////////////////////
//printing cformview
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LC_BRANCHES_BOX, OnItemchangedLcBox)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBSEQDELIVERY_SUBSEQDELIVERYFLAG, &CArticleSubseqDeliveryView::OnCbnSelchangeComboSubseqdeliverySubseqdeliveryflag)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SUBSEQUENTDELIVERY_MODIFY_ALL_BRANCHES, &CArticleSubseqDeliveryView::OnBnClickedSubsequentdeliveryModifyAllBranches)
END_MESSAGE_MAP()

//-----------------------------------------------------------
BOOL CArticleSubseqDeliveryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

//-----------------------------------------------------------
void CArticleSubseqDeliveryView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if( pInfo == NULL )
		return;

	if( m_dib.GetHandle( ) == NULL )
		return;
	{
		GLock lock( m_dib );
		BITMAPINFOHEADER *pBMI = (BITMAPINFOHEADER*)(LPVOID)lock;

		int nColors = 0;
		if( pBMI->biBitCount <= 8 )
			nColors = ( 1<< pBMI->biBitCount );

		::StretchDIBits( pDC->GetSafeHdc( ),
				pInfo->m_rectDraw.left, 
				pInfo->m_rectDraw.top,
				pBMI->biWidth,
				pBMI->biHeight,
				0, 
				0, 
				pBMI->biWidth,
				pBMI->biHeight,
				(LPBYTE)pBMI + (pBMI->biSize + nColors * sizeof(RGBQUAD)),
				(BITMAPINFO*)pBMI,
				DIB_RGB_COLORS, 
				SRCCOPY);
	}
}

//-----------------------------------------------------------
void CArticleSubseqDeliveryView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	if( pInfo )
	{
		CClientDC dc( this );
		pDC->SetMapMode(MM_ANISOTROPIC);

		CSize sz( dc.GetDeviceCaps(LOGPIXELSX), dc.GetDeviceCaps(LOGPIXELSY) );
		pDC->SetWindowExt( sz );
		sz = CSize( pDC->GetDeviceCaps(LOGPIXELSX),pDC->GetDeviceCaps(LOGPIXELSY) );
		pDC->SetViewportExt( sz );
	}
}

//-----------------------------------------------------------
void CArticleSubseqDeliveryView::grabImage( )
{
	//Grap Image
	CPoint oldPoint = GetScrollPosition( );
	CPoint pt( 0, 0 );//scroll to up
	this->ScrollToPosition( pt );

	CClientDC dc(this);
	CRect rect;
	this->GetClientRect( rect );
	m_dib.Attach( GDIUtil::GrabDIB( &dc, rect ) );

	ScrollToPosition( oldPoint );
}

//-----------------------------------------------------------
void CArticleSubseqDeliveryView::OnFilePrint() 
{
	grabImage( );
	CFormViewMultiLang::OnFilePrint() ;
}

/*----------------------------------------------------------------------------*/

BOOL CArticleSubseqDeliveryView::ShowSubseqDeliveryEntry(CSUBSEQDELIVERIES* pSubseqDeliveryEntry)
{
	int iStat;
	CString Name;
	CString Errmld;
	CString strArticleNo;
	long lArticleNo = pSubseqDeliveryEntry->lArtikelnr;

	m_iBranchno = pSubseqDeliveryEntry->iFilialnr;

	if (lArticleNo == 0)    // article no can not be 0 here, wtf is this if for???
	{
		m_ST_ART_INFO.SetWindowText( "" );
		return true;
	}

	// set article name in view
	/* it doesn't make sense to set the article name every time the selection 
	   in the subsequent delivery list changes, the article does never change 
	   by a selection in this list */
	m_RD_ZARTIKEL.Reset();
	iStat = m_RD_ZARTIKEL.IPlausi( lArticleNo, Name, &Errmld);
	m_ST_ART_INFO.SetWindowText( Name );

	CString csArticleNbr;
	csArticleNbr.Format("%ld", pSubseqDeliveryEntry->lArtikelnr);
	m_ARTICLENBR.SetWindowText(csArticleNbr);

	CString csUser(pSubseqDeliveryEntry->szUserLetzteAenderung);
	csUser.Trim();
	m_CHANGED_BY.SetWindowText(csUser);

	CString csLastchangeDate(pSubseqDeliveryEntry->szDatumLetzteAenderung);
	csLastchangeDate.Trim();
	m_CHANGEDATE.SetWindowText(csLastchangeDate);

	CString csBranchname(pSubseqDeliveryEntry->szFiliale);
	csBranchname.Trim();
	// replace & with double-&, so that it is correctly displayed in the list box
	csBranchname.Replace("&", "&&");

	CString csBranchlocation(pSubseqDeliveryEntry->szStandort);
	csBranchlocation.Trim();
	m_ED_BRANCH.SetWindowText(csBranchname + "    " + csBranchlocation);
	m_CK_MODIFY_ALL_BRANCHES.SetCheck(0);

	CString csSubseq(pSubseqDeliveryEntry->szSubseqDelFlag);
	csSubseq.Trim();

	// if the current entry was changed, we have to display the changed value from the
	// change buffer
	for (unsigned iChangeBuf = 0; iChangeBuf < m_changebufferlist.size(); iChangeBuf++)
	{
		if (m_changebufferlist[iChangeBuf].m_iBranchno == pSubseqDeliveryEntry->iFilialnr)
		{
			csSubseq.Format("%d", m_changebufferlist[iChangeBuf].m_iSubseqDelFlag);
			break;
		}
	}

	// now select the correct line in the subseq delivery state combo box
	int iSubseq = 9999;   // 9999 is the "not specified" entry in the combo box
	if (csSubseq.GetLength() > 0)
	{
		iSubseq = atoi(csSubseq);
	}

	int iNbrItems = m_CB_VERGABE_SUBSEQDEL_FLAG.GetCount();
	for (int iIdx = 0; iIdx < iNbrItems; iIdx++)
	{
		DWORD_PTR iData = m_CB_VERGABE_SUBSEQDEL_FLAG.GetItemData(iIdx);
		if (iSubseq == iData)
		{
			m_CB_VERGABE_SUBSEQDEL_FLAG.SetCurSel(iIdx);
			break;
		}
	}

	return TRUE;
}

/**---------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ARTIKEL_CODE  );
	m_Pos_LastKey = m_dlg.GetFieldNumber();

	m_dlg.InitDialog(m_ED_ARTNR);

	m_dlg.InitDialog( m_CB_VERGABE_SUBSEQDEL_FLAG );
}

/**---------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

/**---------------------------------------------------------------------------*/
class CV_SUBSEQDEL_Artikel : public ChValBase
{
public:
	CV_SUBSEQDEL_Artikel( CArticleSubseqDeliveryView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL /*bMeldung*/)
	{
		//return ((CArticleSubseqDeliveryView*)m_pWnd)->ShowArtikel( TRUE );
		return TRUE;
	}
	void PostProc( )
	{
		//((CArticleSubseqDeliveryView*)m_pWnd)->ShowArtikel( FALSE );
	}
	void NotifyProc( )
	{
		//((CArticleSubseqDeliveryView*)m_pWnd)->SucheArtikel( (CEdit*)m_pWnd1 );
	}
};


/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::InitPflege()
{
	MakeDialog();

	CArticleSubseqDeliveryView* pThisView = this;
	m_pBuf = m_Doc.GetBuffer();

	m_ARTIKEL_CODE.SetMask(ED_CHAR,
						 ED_UPPER,
						 m_ARTCODE,
						 L_CARTICLECODES_ARTICLE_CODE,
						 new ChMaskChar,
						 new CV_SUBSEQDEL_Artikel( pThisView ));
//	m_ARTIKEL_CODE.SetDialog(TRUE);

	m_ED_ARTNR.SetMask	(ED_LONG,
							ED_NORMAL,
							&m_nARTIKEL_NR,
			                L_ARTIKEL_NR,
							new ChMaskNum,
							new CV_SUBSEQDEL_Artikel( pThisView ) );
//	m_ED_ARTNR.SetDialog( TRUE );

	EnableFields( FALSE );
	SetDialog( TRUE );

 	m_BOX.InitSuchBox();
	m_BOX.SetScrollInfo(ID_ARTIFA_VORBL1, ID_ARTIFA_RUEBL1, TRUE);

	m_nAuswahlIndex = 0;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::CloseSuche( )
{
 	m_BOX.CloseCursor();
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::DoSuche()
{
	CString strArticleNo;
	BOOLEAN bFound = FALSE;

	m_ED_ARTNR.GetWindowText(strArticleNo);

	if ( m_BOX.StartSelect( strArticleNo, WITH_SCROLL | WITH_HOLD ) )
	{
		bFound = TRUE;
	}
	else
	{
		// why ???
		m_pBuf->lArtikelnr = GetCurrentArticleNo();
	}

	m_BOX.SetFocus();

	return bFound;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::SucheSatz( )
{
	int suchen = 0;
	long lArticleNo;

	m_ArtSelBox.SetPflegeProgNeuheit(NH_NEUHEIT_PHARMOS);
	ChSelectDialog dlg(CResString::ex().getStrTblText(IDS_STRING338), &m_ArtSelBox, HCD_SCROLLINFO);

	dlg.RestoreAuswahlIndex(m_nAuswahlIndex);
	dlg.RestoreAuswahlIndex2(m_nAuswahlIndex2);

	if (dlg.DoModal() == IDOK)
	{
		if (m_changebufferlist.size() > 0)
		{
			CString csQuestion = CResString::ex().getStrTblText(IDS_STRING_ASKSAVE_SUBSEQFLAGS);
			if (MsgBoxYesNo(csQuestion, MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
			{
				m_changebufferlist.clear();
			}
			else
			{
				return 0;
			}
		}

		if (m_ArtSelBox.PrimeKeyOfSelectedRecord(&lArticleNo) == 0)
		{
			SetCurrentArticleNo(lArticleNo);
			ShowSelectedArticle();

			suchen = 1;
		}
	}
	// article has been selected by article search
	m_nStatus = 0;

	m_nAuswahlIndex = dlg.GetAuswahlIndex();
	m_nAuswahlIndex2 = dlg.GetAuswahlIndex2();

	return suchen;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::NextSatz( )
{
	long lArticleNo;

	// do we have unsaved changes?
	if (m_changebufferlist.size() > 0)
	{
		// ask: discard changes for current article?
		CString csQuestion = CResString::ex().getStrTblText(IDS_STRING_ASKSAVE_SUBSEQFLAGS);
		if (MsgBoxYesNo(csQuestion, MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
		{
			// answer yes: discard changes and change to next article
			m_changebufferlist.clear();
		}
		else
		{
			// answer no: stay on current article
			return 0;
		}
	}

	// get key of next article in article search box
	if ( m_ArtSelBox.PrimeKeyOfNextRecord(&lArticleNo) == 0 )
	{
		SetCurrentArticleNo(lArticleNo);
		ShowSelectedArticle();
		return 1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::PrevSatz( )
{
	long lArticleNo;

	// do we have unsaved changes?
	if (m_changebufferlist.size() > 0)
	{
		// ask: discard changes for current article?
		CString csQuestion = CResString::ex().getStrTblText(IDS_STRING_ASKSAVE_SUBSEQFLAGS);
		if (MsgBoxYesNo(csQuestion, MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
		{
			// answer yes: discard changes and change to previous article
			m_changebufferlist.clear();
		}
		else
		{
			// answer no: stay on current article
			return 0;
		}
	}

	// get key of previous article in article search box
	if (m_ArtSelBox.PrimeKeyOfPrevRecord(&lArticleNo) == 0)
	{
		SetCurrentArticleNo(lArticleNo);
		ShowSelectedArticle();
		return 1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::EnableFields( BOOL bEnab )
{
	// Key (i.e. PZN) is editable when all other fields are not editable and v.v.
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );

	// only the subsequent delivery flag (Combobox) and the branch list are 
	// editable in edit mode
	m_CB_VERGABE_SUBSEQDEL_FLAG.EnableWindow(bEnab);
	m_CK_MODIFY_ALL_BRANCHES.EnableWindow(bEnab);
	m_BOX.EnableWindow(true);

	// Artikelnr field is hidden (!) and always disabled
	/* it contains the article number, that is "magically" written there
       by m_CodeConverter, which converts the article code entered by the
	   user to the corresponding article number */
	m_ED_ARTNR.EnableWindow(true); // Eingabe nur noch in Artikel-Code-Feld
	m_ED_ARTNR.ShowWindow(SW_HIDE);
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::SetArticleCodeEditCtrl()
{
 	m_CodeConverter.setArticleCodeEditCtrl();
}

void CArticleSubseqDeliveryView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CArticleSubseqDeliveryView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

/*----------------------------------------------------------------------------*/
/* method is called when the user presses ENTER in the PZN key field   */
int CArticleSubseqDeliveryView::BearbeiteSatz( )
{
	CString cErrmld;
	CString cArtikelNr;

	// check, if a correct article code has been entered
	if (m_CodeConverter.setArticleNoEditCtrl(cErrmld) < 0) // code not found!
	{
		MsgBoxOK(cErrmld);
		m_ARTIKEL_CODE.SetFocus();
		return FALSE;
	}

	// article was selected via manually entering a article number
	m_nStatus = 1;

	m_ED_ARTNR.GetWindowText(cArtikelNr);
	SetCurrentArticleNo(cArtikelNr);
	m_bChanged = FALSE;

	if (DoSuche())
	{
		EnableFields(TRUE);
	}
	else
	{
		EnableFields(FALSE);
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::SpeichereSatz( )
{
	if (m_changebufferlist.size() > 0)
	{
		CWaitCursor cwc;

		const int iBufsize = 256;

		char  subseqflag[iBufsize];
		char  originaluser[iBufsize];

		long lSaveStatus = -1;

		for (unsigned iBufIdx = 0; iBufIdx < m_changebufferlist.size(); iBufIdx++)
		{
			memset(subseqflag, 0, iBufsize);
			memset(originaluser, 0, iBufsize);

			long lStatus = -1;

			CString csCheckSql;
			csCheckSql.Format("select LEFT(TO_CHAR(subsequentdelivery), 10), lastchangeuser from csubsequentdeliverybrancharticleconfig where articleno =  %ld and branchno = %ld", 
				m_changebufferlist[iBufIdx].m_iArticleNbr, m_changebufferlist[iBufIdx].m_iBranchno);

			((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
			lStatus = SqlRead(csCheckSql, subseqflag, originaluser, NULL);
			((CEkZdpApp*)AfxGetApp())->EndWaitAction();

			CString csUpdateSql;
			switch (lStatus)
			{
			case 0: // record found
			{
				if (m_changebufferlist[iBufIdx].m_iSubseqDelFlag != atoi(subseqflag))
				{// updating is only needed if the selected flag is different from the old one
					switch (m_changebufferlist[iBufIdx].m_iSubseqDelFlag)
					{
					case 0:
					case 1:
					case 8:
					case 9:
					{// new flag is valid
						csUpdateSql.Format("update csubsequentdeliverybrancharticleconfig set subsequentdelivery = %ld, lastchangeuser = '%s', lastchangedate = CURRENT where articleno = %ld and branchno = %ld", 
							m_changebufferlist[iBufIdx].m_iSubseqDelFlag, ((CEkZdpApp*)AfxGetApp())->GetUserName(),
							m_changebufferlist[iBufIdx].m_iArticleNbr, m_changebufferlist[iBufIdx].m_iBranchno);
						lSaveStatus = SqlExecuteImm(csUpdateSql);
						break;
					}
					case iIndex4Invalid:
					{// invalid flag or "unspecified" has been selected
						csUpdateSql.Format("delete from csubsequentdeliverybrancharticleconfig where articleno = %ld and branchno = %ld", 
							m_changebufferlist[iBufIdx].m_iArticleNbr, m_changebufferlist[iBufIdx].m_iBranchno);
						lSaveStatus = SqlExecuteImm(csUpdateSql);
						break;
					}
					}
				}
				break;
			}
			case 100: // no record found
			{
				csUpdateSql.Format("insert into csubsequentdeliverybrancharticleconfig (articleno, branchno, lastchangedate, lastchangeuser, subsequentdelivery) values (%ld, %d, CURRENT, '%s', %d)", 
					m_changebufferlist[iBufIdx].m_iArticleNbr, m_changebufferlist[iBufIdx].m_iBranchno, 
					((CEkZdpApp*)AfxGetApp())->GetUserName(), m_changebufferlist[iBufIdx].m_iSubseqDelFlag);
				lSaveStatus = SqlExecuteImm(csUpdateSql);
				break;
			}
			}

			if (lSaveStatus != 0)
			{ // something went wrong
				break;
			}
		}

		if (lSaveStatus == 0)
		{
			m_changebufferlist.clear();

			redrawListCtrl();

			// no more changes
			m_bChanged = FALSE;

			return 1;
		}
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryView::LoescheSatz( )
{
	return 0;
}

void CArticleSubseqDeliveryView::redrawListCtrl()
{
	m_BOX.SendMessage(WM_SETREDRAW, FALSE);
	int iCurSel = m_BOX.GetSelectedIndex();
	int iTopItem = m_BOX.GetTopIndex();

	m_BOX.ClearBox();
	DoSuche();

	if (iCurSel >= 0)
	{
		m_BOX.SetItemState(-1, 0, LVIS_SELECTED);
		m_BOX.SetItemState(iCurSel, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	}

	if (iTopItem >= 0)
	{
		m_BOX.EnsureVisible(m_BOX.GetItemCount() - 1, FALSE); // Scroll down to the bottom
		m_BOX.EnsureVisible(iTopItem, FALSE);// scroll back up just enough to show said item on top
	}
	m_BOX.SendMessage(WM_SETREDRAW, TRUE);
}

/*----------------------------------------------------------------------------*/
/* method is called when the "leave edit mode" button (thick up arrow) has 
   been clicked */
int CArticleSubseqDeliveryView::UndoSatz( )
{
	// do we have unsaved changes?
	if (m_changebufferlist.size() > 0)
	{
		// ask: discard changes?
		CString csQuestion = CResString::ex().getStrTblText(IDS_STRING_ASKSAVE_SUBSEQFLAGS);
		if (MsgBoxYesNo(csQuestion, MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
		{
			// answer: yes --> discard changes
			m_changebufferlist.clear();
		}
		else
		{
			// answer: no --> stay in the view
			return 2;
		}
	}

	// was the current article selected by manually entering a number in the PZN field?
	if (m_nStatus == 1)
	{
		// then we stay in the view and let the user enter a new article number
		// (or search for a new article)
		m_nStatus = 0;

		// redraw list after discarding changes
		redrawListCtrl();
		// select the first row in the list
		m_BOX.SetItemState(-1, 0, LVIS_SELECTED);
		m_BOX.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

		EnableFields(FALSE);
		m_bChanged = FALSE;

		// stay in view
		return 1;
	}

	// leave the view
	return 0;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::ReleasePflegeDocument( )
{
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::OnInitialUpdate() 
{
	CFormViewMultiLang::OnInitialUpdate();
	
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			CString strArticleCode;

			m_bChanged = FALSE;  // noch keine Aenderung

			m_ARTIKEL_CODE.GetWindowText(strArticleCode);
			// has no article been loaded yet?
			if (strArticleCode.IsEmpty())
			{
				FillComboBox();
				m_BOX.ClearBox();
				m_Doc.SetTagesdatum(::Today());
			}
			else
			{
				redrawListCtrl();
			}
			// select the first row in the list
			m_BOX.SetItemState(-1, 0, LVIS_SELECTED);
			m_BOX.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
			EnableFields(FALSE);
		}
	}
}

void CArticleSubseqDeliveryView::OnItemchangedLcBox(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	/* Werte der in der subseq delivery Listbox selektierten Zeile in Edit-Felder übertragen */
	*pResult = 0;

	int pos;
	if ((pos = m_BOX.GetNextItem(-1, LVNI_SELECTED)) >= 0)
	{
		m_BOX.SelectedCode(m_pBuf);

		// update content of fields with current subseq delivery settings for currently
		// selected article / branch
		ShowSubseqDeliveryEntry(m_pBuf);
	}
	else
	{
		//reset empty - why???
		memset(m_pBuf, 0, sizeof(CSUBSEQDELIVERIES));
	}
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryView::FillComboBox()
{
	m_CB_VERGABE_SUBSEQDEL_FLAG.ResetContent();
	
	int iZeroIdx = m_CB_VERGABE_SUBSEQDEL_FLAG.AddString(CResString::ex().getStrTblText(IDS_NL_NOT_DEFINED));
	m_CB_VERGABE_SUBSEQDEL_FLAG.SetItemData(iZeroIdx, iIndex4Invalid);

	int iIdx = m_CB_VERGABE_SUBSEQDEL_FLAG.AddString(CResString::ex().getStrTblText(IDS_NL_0));
	m_CB_VERGABE_SUBSEQDEL_FLAG.SetItemData(iIdx, 0);

	iIdx = m_CB_VERGABE_SUBSEQDEL_FLAG.AddString(CResString::ex().getStrTblText(IDS_NL_1));
	m_CB_VERGABE_SUBSEQDEL_FLAG.SetItemData(iIdx, 1);

	iIdx = m_CB_VERGABE_SUBSEQDEL_FLAG.AddString(CResString::ex().getStrTblText(IDS_NL_8));
	m_CB_VERGABE_SUBSEQDEL_FLAG.SetItemData(iIdx, 8);

	iIdx = m_CB_VERGABE_SUBSEQDEL_FLAG.AddString(CResString::ex().getStrTblText(IDS_NL_9));
	m_CB_VERGABE_SUBSEQDEL_FLAG.SetItemData(iIdx, 9);

	m_CB_VERGABE_SUBSEQDEL_FLAG.SetCurSel( iZeroIdx );
}

/*----------------------------------------------------------------------------*/
// void CArticleSubseqDeliveryView::SetValidation( BOOL bValid )
// {
// 	m_dlg.SetValidation( bValid );
// }


void CArticleSubseqDeliveryView::OnCbnSelchangeComboSubseqdeliverySubseqdeliveryflag()
{
	m_BOX.setChangebufferlist(&m_changebufferlist);

	ChangeBuffer chgBuf;

	if (m_CK_MODIFY_ALL_BRANCHES.GetCheck() == 1)
	{
		int bIndex = 0;
		CSubseqDeliveryFlagBox::SelBuf* listSubDeliveryItem = NULL;
		while ((listSubDeliveryItem = m_BOX.GetSelectBoxItem(bIndex)) != NULL)
		{
			boolean found = false;
			if (m_changebufferlist.size() > bIndex)
			{
				// the order of this list may be different to the selection box and may contain some
				// elements but not all elements
				for (int cIndex = 0; cIndex < m_changebufferlist.size(); cIndex++)
				{
					if (m_changebufferlist[cIndex].m_iBranchno == listSubDeliveryItem->iFilialNr)
					{
						found = true;
						break;
					}
				}
			}
			if (!found)
			{
				chgBuf.m_iArticleNbr = listSubDeliveryItem->lArtikelNr;
				chgBuf.m_iBranchno = listSubDeliveryItem->iFilialNr;
				chgBuf.m_iSubseqDelFlag = 0; // will be set later below
				m_changebufferlist.push_back(chgBuf);
			}
			bIndex++;
		}
	}


	if (m_iBranchno > 0)
	{
		chgBuf.m_iBranchno = m_iBranchno;
		chgBuf.m_iArticleNbr = GetCurrentArticleNo();

		int iSelIdx = m_CB_VERGABE_SUBSEQDEL_FLAG.GetCurSel();
		if (iSelIdx >= 0)
		{
			int iSelectedFlag = (int)m_CB_VERGABE_SUBSEQDEL_FLAG.GetItemData(iSelIdx);
			BOOL bFound = FALSE;
			for (unsigned iIdx = 0; iIdx < m_changebufferlist.size(); iIdx++)
			{
				if (m_CK_MODIFY_ALL_BRANCHES.GetCheck() == 1)
				{
					// modification on one branch is to be propagated on all branches
					m_changebufferlist[iIdx].m_iSubseqDelFlag = iSelectedFlag;
					bFound = TRUE;
					continue;
				}
				if (m_changebufferlist[iIdx].m_iBranchno == m_iBranchno)
				{
					m_changebufferlist[iIdx].m_iSubseqDelFlag = iSelectedFlag;
					bFound = TRUE;
					break;
				}
			}
			m_CK_MODIFY_ALL_BRANCHES.SetCheck(0);
			if (!bFound)
			{
				chgBuf.m_iSubseqDelFlag = iSelectedFlag;
				m_changebufferlist.push_back(chgBuf);
			}

			// now we have a change
			m_bChanged = TRUE;

			redrawListCtrl();
		}
	}
}

void CArticleSubseqDeliveryView::ShowSelectedArticle()
{
	// write article no to hidden article no edit field
	// why ???
	SetArticleNoEditCtrl(GetCurrentArticleNo());

	// do magical stuff for/with article code
	// why ???
	SetArticleCodeEditCtrl();

	// load subseq delivery data for current article
	// into list box
	DoSuche();
    EnableFields(FALSE);

	m_bChanged = FALSE;
}

void CArticleSubseqDeliveryView::SetArticleNoEditCtrl(long lNewArticleNo)
{
	CString s;
	s.Format("%ld", lNewArticleNo);
	m_ED_ARTNR.SetWindowText(s);
}

void CArticleSubseqDeliveryView::OnBnClickedSubsequentdeliveryModifyAllBranches()
{
	// nothing to do here
}