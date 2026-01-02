// hSelectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZdpDruck.h"

#include "hSelectDialog.h"
#include <eklibs/hamfcs/hMskChar.h>
#include <phxlib/phxutil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_VORBL ( WM_USER + 1 )
#define WM_RUEBL ( WM_USER + 2 )

/////////////////////////////////////////////////////////////////////////////
// ChSelectDialog dialog

ChSelectDialog::ChSelectDialog(CString Caption, ChSelectCtrl *SelBox,
							   DWORD dwStyle /* 0 */ ,
							   CWnd* pParent /*=NULL*/)
	: CDialog(ChSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ChSelectDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Caption = Caption;
	m_cSelectCtrl = SelBox;
	m_bButtonAltern = FALSE;
	m_bScrollInfo   = FALSE;
	m_nAuswahlIndex = 0;
	if ( dwStyle != 0 )
	{
		if ( dwStyle & HCD_BUTTONALTERN ) m_bButtonAltern  = TRUE;
		if ( dwStyle & HCD_SCROLLINFO   ) m_bScrollInfo    = TRUE;
	}
}


void ChSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChSelectDialog)
	DDX_Control(pDX, IDC_CB_SELECTDIALOG_AUSWAHL, m_cComboboxAuswahl);
	DDX_Control(pDX, IDC_ST_SELECTDIALOG_AUSWAHL, m_cStaticAuswahl);
	DDX_Control(pDX, IDCANCEL, m_Idcancel);
	DDX_Control(pDX, IDOK, m_cIdok);
	DDX_Control(pDX, IDC_STATIC_SUCHB1_1, m_cStaticSuchb1);
	DDX_Control(pDX, IDC_STATIC_FRAGE1_1, m_cStaticFrage1);
	DDX_Control(pDX, IDC_EDIT_SUCHB1_1, m_cEditSuchb1);
	DDX_Control(pDX, IDC_STATIC_SUCHB1_2, m_cStaticSuchb2);
	DDX_Control(pDX, IDC_STATIC_FRAGE1_2, m_cStaticFrage2);
	DDX_Control(pDX, IDC_EDIT_SUCHB1_2, m_cEditSuchb2);
	DDX_Control(pDX, IDC_SUCHE, m_cSuche);
	DDX_Control(pDX, IDC_RUEBL, m_cRuebl);
	DDX_Control(pDX, IDC_VORBL, m_cVorbl);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LISTCTRL_BOX, *m_cSelectCtrl);
}


BEGIN_MESSAGE_MAP(ChSelectDialog, CDialog)
	//{{AFX_MSG_MAP(ChSelectDialog)
	ON_BN_CLICKED(IDC_SUCHE, OnSuche)
	ON_BN_CLICKED(IDC_VORBL, OnVorbl)
	ON_BN_CLICKED(IDC_RUEBL, OnRuebl)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_BOX, OnDblclkListctrlBox)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LISTCTRL_BOX, OnKeydownListctrlBox)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_VORBL, OnMsgVorbl )
	ON_MESSAGE( WM_RUEBL, OnMsgRuebl )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////
//

void ChSelectDialog::RestoreAuswahlIndex( int index )
{
	m_nAuswahlIndex = index;
}

int ChSelectDialog::GetAuswahlIndex( )
{
	int index;
	index = 0;
	if ( m_bAuswahl )
	{
		index = m_nAuswahlIndex;
		if ( index == CB_ERR ) index = 0;
	}
	return index;
}

////////////////////////////////////////////////////////////////////////////

CString ChSelectDialog::GetKeyString()
{
	return m_cSelectCtrl->GetSelectedInfo();
}

int ChSelectDialog::GetCursorFd()
{
	return m_cSelectCtrl->GetCursorFd();
}

////////////////////////////////
// Suche Suchbegriff1

void ChSelectDialog::ShowSuchBegriff1( BOOL bMeldung )
{
}

void ChSelectDialog::SucheSuchBegriff1( )
{
	if ( m_cSelectCtrl->m_pSelBox1 != NULL )
	{
		ChSelectDialog dlg( m_cSelectCtrl->m_cHeaderSelBox1, 
						    m_cSelectCtrl->m_pSelBox1,
							HCD_SCROLLINFO );
//							HCD_SCROLLINFO | HCD_BUTTONALTERN );
		if ( dlg.DoModal() == IDOK )
		{
			CString Info;
			Info = m_cSelectCtrl->m_pSelBox1->GetSelectedInfo();
			if ( !Info.IsEmpty( ) )
			{
				m_cEditSuchb1.SetWindowText( Info );
				m_cEditSuchb1.p_GetInput();  // !!!!!!!!!
			}
		}
		m_cSelectCtrl->m_pSelBox1->CloseCursor();
	}
}

class CV_hSelectDialog_SuchBegriff1 : public ChValBase
{
public:
	CV_hSelectDialog_SuchBegriff1( ChSelectDialog* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((ChSelectDialog*)m_pWnd)->ShowSuchBegriff1( FALSE );
	}
	void NotifyProc( )
	{
		((ChSelectDialog*)m_pWnd)->SucheSuchBegriff1( );
	}
};

////////////////////////////////
// Suche Suchbegriff2

void ChSelectDialog::ShowSuchBegriff2( BOOL bMeldung )
{
}

void ChSelectDialog::SucheSuchBegriff2( )
{
	if ( m_cSelectCtrl->m_pSelBox2 != NULL )
	{
		ChSelectDialog dlg( m_cSelectCtrl->m_cHeaderSelBox2, 
						    m_cSelectCtrl->m_pSelBox2,
							HCD_SCROLLINFO );
//							HCD_SCROLLINFO | HCD_BUTTONALTERN );
		if ( dlg.DoModal() == IDOK )
		{
			CString Info;
			Info = m_cSelectCtrl->m_pSelBox2->GetSelectedInfo();
			if ( !Info.IsEmpty( ) )
			{
				m_cEditSuchb2.SetWindowText( Info );
				m_cEditSuchb2.p_GetInput();  // !!!!!!!!!
			}
		}
		m_cSelectCtrl->m_pSelBox2->CloseCursor();
	}
}

class CV_hSelectDialog_SuchBegriff2 : public ChValBase
{
public:
	CV_hSelectDialog_SuchBegriff2( ChSelectDialog* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((ChSelectDialog*)m_pWnd)->ShowSuchBegriff2( FALSE );
	}
	void NotifyProc( )
	{
		((ChSelectDialog*)m_pWnd)->SucheSuchBegriff2( );
	}
};

/////////////////////////////////////////////////////////////////////////////
// ChSelectDialog message handlers


void ChSelectDialog::F2Suche()
{
	OnSuche();
}


class CO_SELECTDIALOG_Com : public ChComBase
{
public:
	CO_SELECTDIALOG_Com( ChSelectDialog* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((ChSelectDialog*)m_pWnd)->F2Suche();
	}
};

BOOL ChSelectDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// Text des 1. Suchbegriffes
	m_cStaticSuchb1.SetWindowText( m_cSelectCtrl->InitSuchBegr_1() ); 

	m_cEditSuchb1.SetMask	(ED_CHAR,
                             ED_UPPER,
                             100,
                             new ChMaskChar,
							 new CV_hSelectDialog_SuchBegriff1( this ) );

	m_cEditSuchb1.SetCommandHandler( new CO_SELECTDIALOG_Com( this ) );

	m_cEditSuchb1.SetDialog( TRUE );

	// Fragezeichen loeschen
	if ( m_cSelectCtrl->m_pSelBox1 == NULL )
		m_cStaticFrage1.DestroyWindow();


	// Text des 2. Suchbegriffes
	m_bSuchBegr2 = !(m_cSelectCtrl->InitSuchBegr_2()).IsEmpty();
	if ( m_bSuchBegr2 )
	{
		m_cStaticSuchb2.SetWindowText( m_cSelectCtrl->InitSuchBegr_2() ); 

		m_cEditSuchb2.SetMask	(ED_CHAR,
		                         ED_UPPER,
			                     100,
				                 new ChMaskChar,
								 new CV_hSelectDialog_SuchBegriff2( this ) );

		m_cEditSuchb2.SetCommandHandler( new CO_SELECTDIALOG_Com( this ) );

		m_cEditSuchb2.SetDialog( TRUE );

		// Fragezeichen loeschen
		if ( m_cSelectCtrl->m_pSelBox2 == NULL )
			m_cStaticFrage2.DestroyWindow();
	}
	else
	{
		// 2. Suchbegriff loeschen
		m_cStaticSuchb2.DestroyWindow();
		m_cEditSuchb2.DestroyWindow();
		m_cStaticFrage2.DestroyWindow();
	}

	// Text des Auswahlkriteriums
	m_bAuswahl = !(m_cSelectCtrl->InitAuswahlKrit()).IsEmpty();
	if ( m_bAuswahl )
	{	
		CString cText;
		CString cStr;
		int		nAnz;
		int		i;
		int		iPos;

		m_cComboboxAuswahl.ResetContent();

		cText = m_cSelectCtrl->InitAuswahlKrit();
		cStr  = cText;
		cStr.SpanIncluding( "\n" );
		nAnz = cStr.GetLength();
		
		iPos = -1;	// vorher 0
		cStr = ::ParseString( cText, '\n', &iPos );
		if ( !cStr.IsEmpty() )
		{
			m_cStaticAuswahl.SetWindowText( cStr );

			i = 0;
			while ( i < nAnz && iPos != -2 )	// vorher iPos != -1
			{
				cStr = ::ParseString( cText, '\n', &iPos );
				if ( !cStr.IsEmpty() )
					 m_cComboboxAuswahl.AddString( ( LPCTSTR ) cStr );
			}
			if ( m_nAuswahlIndex >= 0 && m_nAuswahlIndex < nAnz )
				m_cComboboxAuswahl.SetCurSel( m_nAuswahlIndex );
			else
				m_cComboboxAuswahl.SetCurSel( 0 );
		}
	}
	else
	{
		// Auswahlkriterium loeschen
		m_cStaticAuswahl.DestroyWindow();
		m_cComboboxAuswahl.DestroyWindow();
	}

	// Listbox parametrisieren
	m_cSelectCtrl->InitSuchBox();			

	// Scroll-Information
	m_cSelectCtrl->SetScrollInfo( WM_VORBL, WM_RUEBL, m_bScrollInfo );

	// mit oder ohne scrolling 
	if ( m_cSelectCtrl->SetScrollMode() )
		m_OpenMode = WITH_SCROLL;
	else
		m_OpenMode = WITHOUT_SCROLL;

	// alternative Buttonimages
	if ( m_bButtonAltern )	// Alternative Bitmaps zuordnen 
	{
		m_cSuche.InitBitmap(IDB_BM_SUCHE);
		m_cVorbl.InitBitmap(IDB_BM_VORBL);
		if ( m_OpenMode == WITH_SCROLL )
			m_cRuebl.InitBitmap(IDB_BM_RUEBL);	
	}
	else					// Bitmaps zuordnen 
	{
		m_cSuche.InitBitmap(IDB_BM_SUCHE1);
		m_cVorbl.InitBitmap(IDB_BM_VORBL1);
		if ( m_OpenMode == WITH_SCROLL )
			m_cRuebl.InitBitmap(IDB_BM_RUEBL1);	
	}

	// vor/rueckblaetter-Buttons initialisiern
	m_cVorbl.EnableWindow( FALSE );
	if ( m_OpenMode == WITH_SCROLL )
		m_cRuebl.EnableWindow( FALSE );
	else
		m_cRuebl.DestroyWindow();

	m_OpenMode |= WITH_HOLD;	// 22.07.98

	m_cEditSuchb1.SetFocus();


	/////////////////////////////////////////////////
	// Resize  09.02.2000

	// IDIOK
	CRect IdokRect;
	m_cIdok.GetWindowRect( IdokRect );

	// Box
	CRect CtrlRect;
	m_cSelectCtrl->GetWindowRect( CtrlRect );

	// Dialog
	CRect DlgRect;
	CWnd *pDlgWnd;
	pDlgWnd = this;
	pDlgWnd->GetWindowRect( DlgRect );

	TEXTMETRIC tm;
	CDC *dc = GetDC();
	dc->GetTextMetrics( &tm );

	if ( CtrlRect.right > IdokRect.right )
		DlgRect.right = CtrlRect.right + 3*tm.tmAveCharWidth;
	else
		DlgRect.right = IdokRect.right + 3*tm.tmAveCharWidth;

	pDlgWnd->MoveWindow( DlgRect, FALSE );		

	// Resize  09.02.2000
	/////////////////////////////////////////////////

	return FALSE; // FALSE wegen SetFocus();

//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// #include "MainFrm.h"

void ChSelectDialog::OnSuche() 
{
	// TODO: Add your control notification handler code here
	CString suchbegr;
	CString suchbegr1;
	if ( m_bAuswahl )
		suchbegr.Format("%d\n", m_cComboboxAuswahl.GetCurSel() );
	else
		suchbegr = "";
		
	m_cEditSuchb1.GetWindowText( suchbegr1 );
	suchbegr += suchbegr1;

	if ( m_bSuchBegr2 )
	{
		CString suchbegr2;
		m_cEditSuchb2.GetWindowText( suchbegr2 );
		if ( !suchbegr2.IsEmpty() )
		{
			suchbegr += "\n";
			suchbegr += suchbegr2;
		}
	}


// ((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->PleaseWait();

	if ( m_cSelectCtrl->StartSelect( suchbegr, m_OpenMode ) )
		m_cVorbl.EnableWindow( TRUE );
	else
	{
		m_cVorbl.EnableWindow( FALSE );
		m_cEditSuchb1.SetFocus();
	}
	m_cRuebl.EnableWindow( FALSE );

// ((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->EndPleaseWait();
}


void ChSelectDialog::OnVorbl() 
{
	// TODO: Add your control notification handler code here

	if ( m_cSelectCtrl->NextSelect() )  
		m_cRuebl.EnableWindow( TRUE );
	else
		m_cVorbl.EnableWindow( FALSE );
}

void ChSelectDialog::OnRuebl() 
{
	// TODO: Add your control notification handler code here

	if ( m_cSelectCtrl->PrevSelect() ) 
		m_cVorbl.EnableWindow( TRUE );
	else
		m_cRuebl.EnableWindow( FALSE );
}

// Doppelklick auf Listboxelement
void ChSelectDialog::OnDblclkListctrlBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	if ( m_cSelectCtrl->ItemChoise() ) BeendeDialog(IDOK);
}

// Blaettertaste innerhalb der Listbox
void ChSelectDialog::OnKeydownListctrlBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

    m_cSelectCtrl->NewFetch( pLVKeyDow->wVKey );
	*pResult = 0;
}

// innerhalb der Listbox wurde vorgeblaettert
LRESULT ChSelectDialog::OnMsgVorbl( WPARAM wParam, LPARAM lParam )
{
	if ( wParam == 1 )
		m_cRuebl.EnableWindow( TRUE );
	else
		m_cVorbl.EnableWindow( FALSE );
	return 0;
}

// innerhalb der Listbox wurde zurueckgeblaettert
LRESULT ChSelectDialog::OnMsgRuebl( WPARAM wParam, LPARAM lParam )
{
	if ( wParam == 1 )
		m_cVorbl.EnableWindow( TRUE );
	else
		m_cRuebl.EnableWindow( FALSE );
	return 0;
}


void ChSelectDialog::BeendeDialog( int nResult )
{
	if ( m_bAuswahl )
		m_nAuswahlIndex = m_cComboboxAuswahl.GetCurSel( );
	EndDialog( nResult );
}

// ENTER-Taste
void ChSelectDialog::OnOK() 
{
	// TODO: Add extra validation here

	CWnd *wnd = GetFocus();
	if ( wnd == m_cSelectCtrl )
	{
		if ( m_cSelectCtrl->ItemChoise() ) 
			BeendeDialog(IDOK);
		else
		{
			m_cSelectCtrl->CloseCursor();
			BeendeDialog(IDCANCEL );
		}
	}
	else if ( wnd == &m_cIdok )
	{
		if ( m_cSelectCtrl->ItemChoise() ) 
			BeendeDialog(IDOK);
		else
		{
			m_cSelectCtrl->CloseCursor();
			BeendeDialog(IDCANCEL );
		}			
	}
	else if ( wnd == &m_cEditSuchb1 )
	{
		if ( m_bSuchBegr2 )				// wenn 2. Suchbegriff
			NextDlgCtrl();
		else
			OnSuche();
	}
	else if ( wnd == &m_cEditSuchb2 )   // wenn 2. Suchbegriff
		OnSuche();
	else
		NextDlgCtrl( );
	
}

// escape
void ChSelectDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	if ( m_bAuswahl )
		m_nAuswahlIndex = m_cComboboxAuswahl.GetCurSel( );

	m_cSelectCtrl->CloseCursor( );
	CDialog::OnCancel();
}

// die Dialogueberschrift wird gesetzt
void ChSelectDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages

	SetWindowText( m_Caption );
}


