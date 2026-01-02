// ArtikelSekbez.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelSekbez.h"
#include <eklibs/hamfcs/hMskChar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelSekbez dialog


CArtikelSekbez::CArtikelSekbez(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelSekbez::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArtikelSekbez)
	//}}AFX_DATA_INIT
}

CArtikelSekbez::CArtikelSekbez(struct ZARTSEKBEZ *pBuf, int nNrOfSekbez,
							   CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelSekbez::IDD, pParent)
{
	m_pBuf = pBuf;
	m_nNrOfSekbez = nNrOfSekbez;

	*m_ARTIKEL_NAME = '\0';
	AppendBlanks( m_ARTIKEL_NAME, L_ZARTSEKBEZ_ARTIKEL_NAME );
	m_cNAME.SetMask	(ED_CHAR,
                     ED_UPPER,
                     m_ARTIKEL_NAME,
                     L_ZARTSEKBEZ_ARTIKEL_NAME,
					 new ChMaskChar );
	m_cNAME.SetMSStandard( TRUE );
	m_cNAME.SetDialog();

	*m_BEMERKUNG = '\0';
	AppendBlanks( m_BEMERKUNG, L_ZARTSEKBEZ_BEMERKUNGEN );
	m_cBEMERKUNG.SetMask(ED_CHAR,
						 ED_UPPER,
						 m_BEMERKUNG,
						 L_ZARTSEKBEZ_BEMERKUNGEN,
						 new ChMaskChar );
	m_cBEMERKUNG.SetMSStandard( TRUE );
	m_cBEMERKUNG.SetDialog();
}

void CArtikelSekbez::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelSekbez)
	DDX_Control(pDX, IDC_LC_ARTIKEL_SEKBEZ_BOX, m_cSEKBEZBOX);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SEKBEZ_BEMERKUNG, m_cBEMERKUNG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SEKBEZ_NAME, m_cNAME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelSekbez, CDialogMultiLang)
	//{{AFX_MSG_MAP(CArtikelSekbez)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LC_ARTIKEL_SEKBEZ_BOX, OnItemchangedLcArtikelSekbezBox)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SEKBEZ_LOESCH, OnPbArtikelSekbezLoesch)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SEKBEZ_UEBERN, OnPbArtikelSekbezUebern)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SEKBEZ_ENDE, OnPbArtikelSekbezEnde)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SEKBEZ_PHARMOS, OnPbArtikelSekbezPharmos)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CArtikelSekbez::MarkListPos( int pos )
{
	int nItem = m_cSEKBEZBOX.GetNextItem(-1, LVNI_FOCUSED);

	if( nItem != -1)
	{

		m_cSEKBEZBOX.SetItem(  nItem
                , 0
                , LVIF_STATE
                , NULL
                , 0
                , 0
				, LVIS_SELECTED|LVIS_FOCUSED
                , 0L);
	}

	m_cSEKBEZBOX.SetItem(  pos
            , 0
            , LVIF_STATE
            , NULL
            , 0
            , LVIS_SELECTED|LVIS_FOCUSED
            , LVIS_SELECTED|LVIS_FOCUSED
            , 0L);

	m_cSEKBEZBOX.EnsureVisible( pos, FALSE );

}

BOOL CArtikelSekbez::InitSuchBox()
{
	struct COLUMNS_TYPES
	{
		int Index;
		char *Columns;
		int Width;
		int Align;
	};

	COLUMNS_TYPES Columns[] =
	{
		0, _strdup(CResString::ex().getStrTblText(IDS_STRING325)), 26, LVCFMT_LEFT,
		1, _strdup(CResString::ex().getStrTblText(IDS_STRING326)), 400, LVCFMT_LEFT,
		-1, NULL, 0, 0
	};

	LV_COLUMN lvC;


	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for ( COLUMNS_TYPES* pType = Columns; pType->Index != -1; pType++ )
	{
		lvC.iSubItem	= pType->Index;
		lvC.pszText 	= LPTSTR(pType->Columns);
		lvC.fmt			= pType->Align;
		lvC.cx			= pType->Width;

		if ( m_cSEKBEZBOX.InsertColumn( pType->Index, &lvC ) == -1 )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING327) );
			return FALSE;
		}
	}
	m_cSEKBEZBOX.SetFullRowSel( TRUE );		// !!!!!!!!!!!!!!!!!!

	for (short ColNr = 0; ColNr < 2; ColNr++)
		free(Columns[ColNr].Columns);


	return TRUE;
}

void CArtikelSekbez::UpdateSuchBox( int index, CStringArray &s )
{

	int iSubItem;

	for (iSubItem = 0; iSubItem < 2; iSubItem++)
	{
      m_cSEKBEZBOX.SetItemText(index, iSubItem, s[iSubItem].GetBuffer(100));
      s[iSubItem].ReleaseBuffer(-1);
	}

}
void CArtikelSekbez::FillSuchBox( CStringArray &s )
{

	int iSubItem;
	int index;

	index = m_cSEKBEZBOX.GetItemCount();
	if ( m_cSEKBEZBOX.InsertItem( index, s[0] ) == -1 ) return;

	for (iSubItem = 1; iSubItem < 2; iSubItem++)
	{
      m_cSEKBEZBOX.SetItemText(index, iSubItem, s[iSubItem].GetBuffer(100));
      s[iSubItem].ReleaseBuffer(-1);
	}

}

void CArtikelSekbez::FillBuffer( int i, CStringArray &s )
{
	s.SetSize( 2 );
	if ( m_pBuf[i].PHARMOS_SEKBEZ[0] == '1' )
		s[0] = CResString::ex().getStrTblText(IDS_STRING325);
	else
		s[0] = " ";
	s[1] = m_pBuf[i].ARTIKEL_NAME;
	s[1].TrimRight();
}

int CArtikelSekbez::GetSekbez( )
{
	int i;
	CStringArray s;

	for ( i = 0; i < m_nNrOfSekbez; i++ )
	{
		FillBuffer( i, s );
		FillSuchBox( s );
	}	
	return i;
}


/////////////////////////////////////////////////////////////////////////////
// CArtikelSekbez message handlers

BOOL CArtikelSekbez::OnInitDialog() 
{
	CDialogMultiLang::OnInitDialog();

	if ( !InitSuchBox() ) 
		return FALSE;

	m_nBoxPos = -1;

	if ( GetSekbez() > 0 )
		MarkListPos( 0 );	

//	SetFocus funktioniert hier nicht: siehe OnPaint()
/*
	if ( GetSekbez() > 0 )
	{
		GotoDlgCtrl( GetDlgItem( IDC_LC_ARTIKEL_SEKBEZ_BOX ));
		m_cSEKBEZBOX.SetFocus();
		MarkListPos( 0 );	
	}
	else
		m_cNAME.SetFocus();
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArtikelSekbez::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialogMultiLang::OnPaint() for painting messages

	// Funktioniert nicht in OnInitdialog
	if ( m_nNrOfSekbez == 0 )
		m_cNAME.SetFocus();
}


bool CArtikelSekbez::IstAllesOk() 
{
	int i;
	i = 0;
	while ( i < m_nNrOfSekbez && m_pBuf[i].PHARMOS_SEKBEZ[0] != '1' ) i++;
	if ( m_nNrOfSekbez > 0 && i == m_nNrOfSekbez )
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING328));
		return false;
	}
	return true;
}

CString CArtikelSekbez::GetPharmosSekbez()
{
	int i;
	i = 0;
	while ( i < m_nNrOfSekbez && m_pBuf[i].PHARMOS_SEKBEZ[0] != '1' ) i++;
	if ( i == m_nNrOfSekbez )
		return _T(" ");
	else
		return m_pBuf[i].ARTIKEL_NAME;
}

void CArtikelSekbez::OnPbArtikelSekbezEnde() 
{
	// TODO: Add your control notification handler code here
	if ( IstAllesOk() )
		CDialogMultiLang::OnOK();	
}


void CArtikelSekbez::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if ( IstAllesOk() )
		CDialogMultiLang::OnClose();
}

void CArtikelSekbez::OnOK()  
{
	NextDlgCtrl();
}


 
void CArtikelSekbez::OnItemchangedLcArtikelSekbezBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	int iItem = pNMListView->iItem;
/*
	CString cName;
	cName = m_cSEKBEZBOX.GetItemText(iItem, iSubItem);
	m_cNAME.SetWindowText( cName );
*/
	strcpy( m_ARTIKEL_NAME, m_pBuf[iItem].ARTIKEL_NAME );
	m_cNAME.p_SetInput();
/*
	CString cBem;
	cBem = m_pBuf[iItem].BEMERKUNGEN;
	cBem.TrimRight();
	m_cBEMERKUNG.SetWindowText( cBem );
*/
	strcpy( m_BEMERKUNG, m_pBuf[iItem].BEMERKUNGEN );
	m_cBEMERKUNG.p_SetInput();
	*pResult = 0;
}


void CArtikelSekbez::AppendBlanks( char *str, int lng )
{
	int slng = static_cast<int>(strlen( str ));
	if ( slng < lng )
		memset( &str[slng], ' ', lng - slng );
	str[lng] = '\0';
}

void CArtikelSekbez::OnPbArtikelSekbezUebern() 
{
	// TODO: Add your control notification handler code here

	CString cName;
	m_cNAME.GetWindowText( cName );

	cName.TrimLeft();
	if ( cName.IsEmpty() )
	{
		m_cNAME.SetFocus();		
		return;
	}

	char name[ L_ZARTSEKBEZ_ARTIKEL_NAME + 1 ];
	strcpy( name, (LPCTSTR) cName );
	AppendBlanks( name, L_ZARTSEKBEZ_ARTIKEL_NAME );
	strcpy( m_ARTIKEL_NAME, name );
	m_cNAME.ShowWindow( SW_SHOW );

	int i = 0;
	while ( i < m_nNrOfSekbez &&
		    strcmp( name, m_pBuf[i].ARTIKEL_NAME ) != 0 ) i++;

	if ( i == 20 ) 
	{
		MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING329) );
		m_cNAME.SetFocus();
		return; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

/*
	m_cBEMERKUNG.GetWindowText( m_pBuf[i].BEMERKUNGEN,
							    L_ARTIKELSEKBEZ_BEMERKUNGEN );
	AppendBlanks( m_pBuf[i].BEMERKUNGEN, L_ARTIKELSEKBEZ_BEMERKUNGEN );
*/
	m_cBEMERKUNG.p_GetInput();
	strcpy( m_pBuf[i].BEMERKUNGEN, m_BEMERKUNG );

	if ( i == m_nNrOfSekbez ) 
	{
		CStringArray s;
		strcpy( m_pBuf[i].ARTIKEL_NAME, name );
		if ( i == 0 )
			strcpy( m_pBuf[i].PHARMOS_SEKBEZ, "1" );
		else
			strcpy( m_pBuf[i].PHARMOS_SEKBEZ, " " );
		FillBuffer( i, s );
		FillSuchBox( s );
		m_nNrOfSekbez++;
	}
	MarkListPos( i );	
	m_cNAME.SetFocus();
}

void CArtikelSekbez::OnPbArtikelSekbezLoesch() 
{
	// TODO: Add your control notification handler code here
	int pos;
	if ((pos = m_cSEKBEZBOX.GetNextItem(-1, LVNI_SELECTED)) >= 0)
	{
		m_cSEKBEZBOX.DeleteItem( pos );
		int i;
		for ( i = pos; i < m_nNrOfSekbez - 1; i++ )
		{
			m_pBuf[i] = m_pBuf[i+1];
/*
			strcpy( m_pBuf[i].ARTIKEL_NAME, m_pBuf[i+1].ARTIKEL_NAME );
			strcpy( m_pBuf[i].BEMERKUNGEN, m_pBuf[i+1].BEMERKUNGEN );
			strcpy( m_pBuf[i].PHARMOS_SEKBEZ, m_pBuf[i+1].PHARMOS_SEKBEZ );
*/
		}
		m_nNrOfSekbez--;
		if ( m_nNrOfSekbez > 0 )
		{	pos--;
			if ( pos < 0 )
				pos = 0;
			MarkListPos( pos );	
			m_cSEKBEZBOX.SetFocus();
		}
		else
			m_cNAME.SetFocus();
	}
	else
		m_cNAME.SetFocus();

}

int CArtikelSekbez::GetNewNrOfSekbez( )
{
	return m_nNrOfSekbez;
}


void CArtikelSekbez::OnPbArtikelSekbezPharmos() 
{
	// TODO: Add your control notification handler code here
	int pos;
	if ((pos = m_cSEKBEZBOX.GetNextItem(-1, LVNI_SELECTED)) >= 0)
	{
		int i;
		for ( i = 0; i < m_nNrOfSekbez; i++ )
		{
			strcpy( m_pBuf[i].PHARMOS_SEKBEZ, " " );
		}
		strcpy( m_pBuf[pos].PHARMOS_SEKBEZ , "1" );

		CStringArray s;
		for ( i = 0; i < m_nNrOfSekbez; i++ )
		{
			FillBuffer( i, s );
			UpdateSuchBox( i, s );
		}

		MarkListPos( pos );	
		m_cSEKBEZBOX.SetFocus();
	}
	else
		m_cNAME.SetFocus();
	
}


