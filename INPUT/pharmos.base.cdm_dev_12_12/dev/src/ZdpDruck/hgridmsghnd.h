#if !defined(AFX_HGRIDMSGHND_H__BAF8DF21_7E63_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_HGRIDMSGHND_H__BAF8DF21_7E63_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Grid.h : header file
//


///////////////////////////////////////////////
// Beschreibung der Spalten bei FirstInitGrid

struct GridColDesc
{
	char *column;
	int  colsize;
};


/////////////////////////////////////////////////////////////////////////////
// ChGridMsgHnd window


enum
{ 
	LBUTTONCLICKEDROWCOL = WM_USER+10,
	LBUTTONDBLCLKROWCOL  = WM_USER+11, 
	LEFTGRIDROW          = WM_USER+12 
};


class ChGridMsgHnd : public CGXGridWnd
{
// Construction
public:
	ChGridMsgHnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChGridMsgHnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ChGridMsgHnd();
	
	void hInitRestGrid( int Row_Index );
	void hInitGrid( );
	void hInitGrid( long Row, long Col );
	void hDisableMove();
	void hZeroGrid();
	void SetBackground( BOOL bEnabled );

	int  GetPixelUnit ( );
	int  GetPixelUnit ( char *str );
	int  GetPixelWidth( char *str );
	void ResizeGridWidth( CWnd *pParentWnd, int Width );

	void FirstInitGrid( int nRowCount, GridColDesc* pCoD, 
						CWnd *pParentWnd = NULL );
	int  GetGridBreite();
	int  GetGridHoehe();
	void RightAlignCol( int col1, int col2  );
	void AlterColHeader( int col, char *column );

private:
	int  m_nGridBreite;
	int	 m_nGridHoehe;

	// Generated message map functions
public:

	virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol,
							ROWCOL nNewRow, ROWCOL nNewCol);
	virtual BOOL OnValidateCell(ROWCOL nRow, ROWCOL nCol );
								
	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol,
										UINT nFlags, CPoint pt);
	virtual BOOL OnLButtonDblClkRowCol (ROWCOL nRow, ROWCOL nCol, 
										UINT nFlags, CPoint pt);

	//{{AFX_MSG(ChGridMsgHnd)
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HGRIDMSGHND_H__BAF8DF21_7E63_11D2_92F8_0060973B18D8__INCLUDED_)
