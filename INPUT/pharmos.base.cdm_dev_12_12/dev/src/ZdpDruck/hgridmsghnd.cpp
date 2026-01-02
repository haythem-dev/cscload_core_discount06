// hGridMsgHnd.cpp : implementation file
//

#include "stdafx.h"
	
#include "hGridMsgHnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ChGridMsgHnd

ChGridMsgHnd::ChGridMsgHnd()
{
	m_nGridBreite = 0;
	m_nGridHoehe  = 0;
}

ChGridMsgHnd::~ChGridMsgHnd()
{
}


BEGIN_MESSAGE_MAP(ChGridMsgHnd, CGXGridWnd)
	//{{AFX_MSG_MAP(ChGridMsgHnd)
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
// Implementation

void ChGridMsgHnd::hDisableMove()
{
	GetParam()->EnableUndo( FALSE );
	GetParam()->EnableMoveCols( FALSE ); 
	GetParam()->EnableMoveRows( FALSE ); 
//	GetParam()->EnableTrackColWidth(FALSE);
	GetParam()->EnableTrackRowHeight(FALSE);
	SetReadOnly( );
    GetParam()->EnableUndo( TRUE );
}

void ChGridMsgHnd::hInitRestGrid( int Row_Index )
{
	ROWCOL Row;
	ROWCOL Col;

	ROWCOL RowCount = GetRowCount( );
	ROWCOL ColCount = GetColCount( );

	for ( Row = Row_Index; Row <= RowCount; Row++ )
	{
		for ( Col = 1; Col <= ColCount; Col++ )
		{
			SetValueRange(CGXRange ( Row, Col), " " );
		}
	}
}

void ChGridMsgHnd::SetBackground( BOOL bEnabled )
{
	COLORREF color;
	if ( bEnabled )
		color = RGB(255,255,255);
	else
		color = RGB(192,192,192);
    GetParam()->EnableUndo( FALSE );
	SetStyleRange(CGXRange ( 1, 1, GetRowCount( ), GetColCount( ) ), 
							 CGXStyle().SetInterior( color) );
	GetParam()->EnableUndo( TRUE );
}



void ChGridMsgHnd::hInitGrid()
{

	BOOL bLockOld = LockUpdate(TRUE);

	SetReadOnly( FALSE );
	hInitRestGrid( 1 );
	SetReadOnly( );

	LockUpdate(bLockOld);

	RedrawRowCol( 1, 1,	GetRowCount( ), GetColCount( ) );
	// Deselect whole table
	SelectRange(CGXRange( ).SetTable( ), FALSE);
}

void ChGridMsgHnd::hInitGrid( long Row, long Col )
{
	BOOL bLockOld = LockUpdate(TRUE);

	SetReadOnly( FALSE );

	if ( Row >= 0 )
		SetRowCount( Row );
	if ( Col >= 0 )
		SetColCount( Col );

	hInitRestGrid( 1 );
	SetReadOnly( );

	LockUpdate(bLockOld);

	RedrawRowCol( 1, 1,	GetRowCount( ), GetColCount( ) );
	// Deselect whole table
	SelectRange(CGXRange( ).SetTable( ), FALSE);
	
	SetCurrentCell( 1, 1 );
}

void ChGridMsgHnd::hZeroGrid()
{
	BOOL bLockOld = LockUpdate(TRUE);
	SetReadOnly( FALSE );

    GetParam()->EnableUndo( FALSE );
	SetRowCount( 0 );
	SetColCount( 0 );
	SetColWidth(0, 0, 0 );
	SetScrollBarMode( SB_BOTH, gxnDisabled );  
    GetParam()->EnableUndo( TRUE );

	hDisableMove();

	SetReadOnly( );
	LockUpdate(bLockOld);
}


/////////////////////////////////////////////////////////////////////////////
// ChGridMsgHnd message handlers

BOOL ChGridMsgHnd::OnLeftCell(ROWCOL nRow, ROWCOL nCol,
							  ROWCOL nNewRow, ROWCOL nNewCol)
{
	// bei Zeilenwechsel neue Zeile schwarz unterlegen

	if ( nRow != nNewRow )
	{
		// Deselect whole table
		SelectRange(CGXRange( ).SetTable( ), FALSE);
		// Select Row 1
		SelectRange(CGXRange( ).SetRows(nNewRow, nNewRow) , TRUE);

		// Sendet eine Message an Parent

		GetParent()->SendMessage( LEFTGRIDROW, nRow, nNewRow );

	}

	return CGXGridWnd::OnLeftCell(nRow, nCol, nNewRow, nNewCol);
}

// validation routine

BOOL ChGridMsgHnd::OnValidateCell(ROWCOL nRow, ROWCOL nCol)
{
	CString s;

	// retrieve text from current cell
	CGXControl* pControl = GetControl(nRow, nCol);
	pControl->GetCurrentText(s);

	if (_ttol(s) < 0 || _ttol(s) > 100)
	{
//		SetWarningText(_T("Please enter a value between 0 and 100!"));
		return TRUE;
//		return FALSE;
	}

	return CGXGridWnd::OnValidateCell(nRow, nCol);
}


BOOL ChGridMsgHnd::OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol,
										  UINT nFlags, CPoint pt)
{
	// Sendet eine Message an Parent

	GetParent()->SendMessage( LBUTTONCLICKEDROWCOL, nRow, nCol );

	return CGXGridWnd::OnLButtonClickedRowCol( nRow, nCol, nFlags, pt);
}


BOOL ChGridMsgHnd::OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, 
										 UINT nFlags, CPoint pt)
{
	// Sendet eine Message an Parent

	GetParent()->SendMessage( LBUTTONDBLCLKROWCOL, nRow, nCol );

	return CGXGridWnd::OnLButtonDblClkRowCol( nRow, nCol, nFlags, pt);
}

/*
void ChGridMsgHnd::OnInitialUpdate()
{
	CGXGridWnd::OnInitialUpdate();  // Creates all objects and links them to the grid

	GetParam()->EnableUndo(FALSE);

	SetAccelArrowKey(TRUE);

	SetRowCount(256);
	SetColCount(52);

	SetStyleRange(CGXRange(2, 2), CGXStyle()
			.SetControl(GX_IDS_CTRL_TEXTFIT)
			.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight"))
		);

	GetParam()->EnableUndo(TRUE);
}
*/



UINT ChGridMsgHnd::OnGetDlgCode() 
{
	// TODO: Add your message handler code here and/or call default

	return CGXGridWnd::OnGetDlgCode()|DLGC_WANTALLKEYS;
}


int ChGridMsgHnd::GetPixelUnit()
{
	TEXTMETRIC tm;
	CDC *dc = GetDC();
	dc->GetTextMetrics( &tm );
	return tm.tmAveCharWidth;
}

int ChGridMsgHnd::GetPixelUnit( char *str )
{
	int nUnit =	GetPixelWidth( str );
	if ( nUnit == 0 ) return 0;
	return MulDiv(1, nUnit, static_cast<int>(strlen( str )) );
}

int ChGridMsgHnd::GetPixelWidth( char *str )
{
	CDC *dc = GetDC();
	int lng;
	lng = static_cast<int>(strlen( str) );
	if ( lng == 0 ) return 0;
	CSize stSize = dc->GetTextExtent( str, lng );
	return stSize.cx;
}

void ChGridMsgHnd::ResizeGridWidth( CWnd *pParentWnd, int Width )
{
	// relativ zum ParentFenster
	CRect ParentRect;
	pParentWnd->GetWindowRect( ParentRect );

	// Grid
	CRect CtrlRect;
	this->GetWindowRect( CtrlRect );
	int Right;
	Right = CtrlRect.left + Width;
	CtrlRect.right = Right;

	CtrlRect.left   -= ParentRect.left;
	CtrlRect.right  -= ParentRect.left;
	CtrlRect.top    -= ParentRect.top;
	CtrlRect.bottom -= ParentRect.top;

	this->MoveWindow( CtrlRect, FALSE );
}


void ChGridMsgHnd::FirstInitGrid( int nRowCount, GridColDesc* pCoD,
								  CWnd *pParentWnd /* = NULL */ )
{
	int i;
	int size;
	int nWidth1;
	int nWidth2;
	int Breite;
	int Hoehe;
	int nColCount;
	char *column;
	int nPixelUnit = GetPixelUnit();

	BOOL bLockOld = LockUpdate(TRUE);
	SetReadOnly( FALSE );

    GetParam()->EnableUndo( FALSE );
	SetRowCount( nRowCount );

	SetColWidth(0, 0, 3*nPixelUnit );
	Breite = 3*nPixelUnit;

	nColCount = 0;
	while ( pCoD[nColCount].column != NULL ) nColCount++;
	
	SetColCount( nColCount );

	i = 0;
	column = pCoD[i].column;
	size   = pCoD[i].colsize;
	i++;

	while ( column != NULL )
	{
		SetValueRange(CGXRange (0, i), column );
		nWidth1 = GetPixelWidth( column );
		nWidth2 = size*nPixelUnit;
		if ( nWidth1 < nWidth2 )
			nWidth1 = nWidth2;
		SetColWidth(i, i, nWidth1 );
		Breite += nWidth1;
/*
		if ( size < ( int) strlen( column ) )
			size = strlen( column );
		SetColWidth(i, i, nPixelUnit*size );
*/
		column = pCoD[i].column;
		size   = pCoD[i].colsize;
		if ( column != NULL )
			i++;
	}

	Breite += 3*nPixelUnit;       // Platz fuer ScrollBalken;

//	SetScrollBarMode( SB_BOTH, gxnDisabled ); 
	SetScrollBarMode( SB_BOTH, gxnEnabled );  
	ShowScrollBar(SB_BOTH, TRUE );
//	SetScrollBarMode( SB_VERT, gxnEnabled );
	SetStyleRange( CGXRange( 0, 0, nRowCount, i ),
		CGXStyle().SetHorizontalAlignment( DT_LEFT) );

//	SetStyleRange( CGXRange( 0, 0, nRowCount, 6 ),
//		CGXStyle().SetControl( GX_IDS_CTRL_STATIC ) );

//	Groesse anpassen nein !!!!!!!!!!!!!!!!!!!
//	if ( pParentWnd != NULL )
//		ResizeGridWidth( pParentWnd, Breite );

    GetParam()->EnableUndo( TRUE );

	hDisableMove();

	SetReadOnly( );
	LockUpdate(bLockOld);

//	RedrawRowCol( 1, 1,
	RedrawRowCol( 0, 0, GetRowCount( ), GetColCount( ) );
	SetLeftCol( 0 );
	Redraw();

	m_nGridBreite = Breite;

	Hoehe = 2 * GetRowHeight( 0 );  // Ueberschrift + Scrollbalken
	for ( i = 0; i < nRowCount; i++ )
		Hoehe += GetRowHeight( i );

	m_nGridHoehe  = Hoehe;
}


int ChGridMsgHnd::GetGridBreite()
{
	return m_nGridBreite;
}

int ChGridMsgHnd::GetGridHoehe()
{
	return m_nGridHoehe;
}


void ChGridMsgHnd::RightAlignCol( int col1, int col2 )
{

	BOOL bLockOld = LockUpdate(TRUE);
	SetReadOnly( FALSE );

	SetStyleRange( CGXRange( 0, col1, GetRowCount(), col2 ),
		CGXStyle().SetHorizontalAlignment( DT_RIGHT) );

	SetReadOnly( );
	LockUpdate(bLockOld);
	Redraw();
}

void ChGridMsgHnd::AlterColHeader( int col, char *column )
{
	if ( col <= (int) GetColCount() )
	{
		SetReadOnly( FALSE );
		SetValueRange(CGXRange (0, col ), column );
		SetReadOnly( );
	}
}