// ExcelCsv.h: Schnittstelle für die Klasse CExcelCsv.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELCSV_H__B21D30BE_EF72_4294_ACEA_84329B1EE347__INCLUDED_)
#define AFX_EXCELCSV_H__B21D30BE_EF72_4294_ACEA_84329B1EE347__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UpdateFromExcelView.h"

class CExcelCsv  
{

public:
	CExcelCsv();
	virtual ~CExcelCsv();

	int ReadHeaderLine( const char *cDatei, char *cKey, char *errmld );
	int ReadLine( CString &cZeile, CString &cItem );
	int GetCount();

	int OpenDatei		(const char *cDatei, char *errmld);


	int ReadColPos		( const char *cDatei, char *cPznKey, struct CUpdateFromExcelView::sLine* ST_LineVal[], char *errmld );
	int ReadColValues	( CString &cZeile, CString &cItem, struct CUpdateFromExcelView::sLine* ST_LineVal[], struct PFL_FELD* ActPflFeld[], bool printEmptyCol, char *errmld );
	int ReadColValuesForCDiscount( CString &cItem, char *errmld );

private:
	const char* NextField( const char *str, char *field );
	void  MakeUpper( char *str );
	int   ScanColumn( CString cZeile, char *cKey );
	char* ScanItem( const char *zeile, int pos );
	bool  IsDigit( CString cS );
	bool  ValidateCsvColInput ( struct PFL_FELD* ActPflFeld, CString csItem );
	bool  ValidateTxtColInput ( const int colNo, CString & csItem );


	// Data
	int m_nAnzGelesen;
	int m_nPos;
	class CStdioFile *m_TextDat;

	int m_iColPos [ ANZ_FELDER_UPD ];

	CString m_CurrentDiscQty;
	CString m_CurrentBaseQty;
	CString m_CurrentDateFrom;
	CString m_CurrentPharmGrpId;
	CString m_CurrentPharmGrpId_Excl_1;
	CString m_CurrentPharmGrpId_Excl_2;

	bool m_PznIsNull;
};

#endif // !defined(AFX_EXCELCSV_H__B21D30BE_EF72_4294_ACEA_84329B1EE347__INCLUDED_)
