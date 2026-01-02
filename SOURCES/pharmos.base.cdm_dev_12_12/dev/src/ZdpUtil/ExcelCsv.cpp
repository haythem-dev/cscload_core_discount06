// ExcelCsv.cpp: Implementierung der Klasse CExcelCsv.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZdpUtil.h"

#include <phxlib/phxutil.h>
#include <hdatum/phodate.h>

#include "ExcelCsv.h"

#include <phxlib/LsArticleCodes.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------*/
CExcelCsv::CExcelCsv()
{
	m_TextDat = new CStdioFile( );
	m_nAnzGelesen = 0;
}

/*------------------------------------------------------------------------*/
CExcelCsv::~CExcelCsv()
{
	delete m_TextDat;
}


/*------------------------------------------------------------------------*/
const char* CExcelCsv::NextField( const char *str, char *field )
{
	int i;
	if ( *str == '\0' )
		return NULL;
	i = 0;
	if ( *str == '"' )
	{
		int fertig;
		str++;
		fertig = 0;
		while( *str && !fertig )
		{ 
			if ( *str == '"' )
			{
				str++;
				fertig = *str == ';' || *str == '\0' || *str == '|';
			}
			if ( !fertig )
				field[i++] = *str;
			if ( *str )
				str++;
		}

	}
	else
	{
		while( *str && *str != ';' && *str != '|' )
		{ 
			field[i++] = *str;
			str++;
		}
		if ( *str )
			str++;
	}
	field[i] = '\0';

	return str;
}

/*------------------------------------------------------------------------*/
void CExcelCsv::MakeUpper( char *str )
{
	while ( *str )
	{
		*str = toupper( *str );
		str++;
	}
}

/*------------------------------------------------------------------------*/
int CExcelCsv::ScanColumn( CString cZeile, char *cKey )
{
	int  pos;
	int  found;
	const char *str;
	char field[300];

	pos   = -1;
	found = 0;
	str = ( LPCTSTR ) cZeile;

	while ( str != NULL && !found )
	{
		str = NextField( str, field );
		if ( str != NULL )
		{
			MakeUpper( field );
			found = strcmp( field, cKey ) == 0;
			pos++;
		}

	}
	if ( found )
		return pos;
	else
		return -1;
}

/*------------------------------------------------------------------------*/
char* CExcelCsv::ScanItem( const char *zeile, int pos )
{
	int  i;
	const char *str;
	static char field[300];

	i     = -1;
	str   = zeile;

	if (pos == -9999)
	{
		strcpy(field, "-9999");
		return field;
	}

	while ( str != NULL && i < pos )
	{
		str = NextField( str, field );
		if ( str != NULL )
		{
			i++;
		}

	}
	if ( i == pos )
		return field;
	else
		return NULL;
}

/*------------------------------------------------------------------------*/
int CExcelCsv::ReadHeaderLine( const char *cDatei, char *cKey, char *errmld )
{
	BOOL ret;

	CString cZeile;

	ret = m_TextDat->Open( cDatei, CFile::modeRead );

	if ( !ret )
	{
		sprintf( errmld, "%s\nm_TextDat->Open ( not found )", cDatei );
		return -1;
	}

	ret = m_TextDat->ReadString( cZeile );
	if ( !ret )
	{
        m_TextDat->Close( );
		sprintf( errmld, "m_TextDat->ReadString ( Datei leer )" );
		return -1;
	}
	MakeUpper( cKey );
	m_nPos = ScanColumn( cZeile, cKey );
	if ( m_nPos == -1 )
	{
	   sprintf( errmld , "Key '%s' nicht gefunden", cKey );
       m_TextDat->Close( );
	   return -1;
	}

	m_nAnzGelesen = 0;
	return m_nPos;
}


/*------------------------------------------------------------------------*/
int CExcelCsv::ReadLine( CString &cZeile, CString &cItem )
{
	char *Item;

	cItem.Empty();
	if ( m_TextDat->ReadString( cZeile ) )
	{
		Item = ScanItem( (LPCTSTR) cZeile, m_nPos ); 
		if (!( Item == NULL || *Item == '\0' ))
		{
			cItem = Item;
			m_nAnzGelesen++;
		}
		return 0;
	}
	return 1;
}

/*------------------------------------------------------------------------*/
int CExcelCsv::GetCount()
{
	return m_nAnzGelesen;
}

/*------------------------------------------------------------------------*/
int CExcelCsv::OpenDatei(const char *cDatei, char *errmld)
{
	BOOL ret;

	ret = m_TextDat->Open( cDatei, CFile::modeRead );

	if ( !ret )
	{
		sprintf( errmld, "%s\nm_TextDat->Open ( not found )", cDatei );
		return -1;
	}
	return 0;
}

/*------------------------------------------------------------------------*/
int CExcelCsv::ReadColPos ( const char *cDatei, char *cPznKey, struct CUpdateFromExcelView::sLine* ST_LineVal[], char *errmld )
{
	for ( int i = 0; i < ANZ_FELDER_UPD; i++ )
	{
		m_iColPos[i] = 0;
	}

	BOOL ret;

	CString cZeile;

	if ( OpenDatei(cDatei, errmld) != 0 )
		return -1;

	ret = m_TextDat->ReadString( cZeile );
	if ( !ret )
	{
        m_TextDat->Close( );
		sprintf( errmld, "m_TextDat->ReadString ( Datei leer )" );
		return -1;
	}

	MakeUpper( cPznKey );
	m_nPos = ScanColumn( cZeile, cPznKey );
	
	//skip Col PZN for mass upload irrelevant to PZN
	if (strcmp(ST_LineVal[0]->csUpdateCol, "Medical Actor ID ") == 0)
	{
		m_nPos = 0;
	}

	if ( m_nPos == -1 )
	{
		if (strcmp("-9999",cPznKey) == 0)
			m_nPos = -9999;
		else
		{
			sprintf( errmld , "PZN-Spalte '%s' nicht gefunden", cPznKey );
			m_TextDat->Close( );
			return -1;
		}
	}

	char ColName[50];
			
	for ( int iLine = 0; iLine < ANZ_FELDER_UPD; iLine ++ )
	{
		if ( ST_LineVal[iLine]->csUpdateCol.IsEmpty() )
			break;

		if ( ST_LineVal[iLine]->bTakeCsvCol == true )
		{
			strcpy ( ColName, ST_LineVal[iLine]->csCsvCol_StatVal );

			m_iColPos[iLine] = ScanColumn( cZeile, ColName );
			
			if ( m_iColPos[iLine] == -1 )
			{
				sprintf( errmld , "Spalte '%s' nicht gefunden!", ColName );
				m_TextDat->Close( );
				return -1;
			}
		}
		else
		{
			m_iColPos[iLine] = -1; // nicht aus Csv-File, sondern Festwert
		}
	}

	m_nAnzGelesen = 0;
	return m_nPos;
}

/*------------------------------------------------------------------------*/
int CExcelCsv::ReadColValuesForCDiscount( CString &cItem, char *errmld )
{
	CString Item;
	CString cZeile;
	int nPosCol;

	cItem.Empty();
	
	if ( m_TextDat->ReadString( cZeile ) )
	{
		int anzCol;

		if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "zpps2bg" || 
			 ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "ibg21")
			anzCol = ANZ_FELDER_UPD_CDISCOUNT_FIX_BG;
		else
			anzCol = ANZ_FELDER_UPD_CDISCOUNT_FIX_FR;
		

		for ( nPosCol = 0; nPosCol < anzCol; nPosCol ++ )
		{
			Item = ScanItem( (LPCTSTR) cZeile, nPosCol ); 
		
			// Test jeder Zeile ob gültige Spaltenwerte
			if ( ( Item.IsEmpty() ) ||
				 ValidateTxtColInput ( nPosCol, Item ) == false )
			{
				sprintf ( errmld, "Wert<%s> in Zeile <%ld>, Spalte <%ld> ist ungültig!", 
									(char*)Item.GetString(),
									m_nAnzGelesen+1, 
									nPosCol+1);
				return 3;
			}
			
			cItem.Append(Item);
			cItem.Append(DELIMITER);
		}

		if ( nPosCol != anzCol )
		{
			sprintf ( errmld, "Zeile <%ld> hat nur <%ld> Spalten!", 
									m_nAnzGelesen+1, 
									nPosCol);
			return 4;
		}

		m_nAnzGelesen++;

		return 0;
	}
	return 1;
}

/*------------------------------------------------------------------------*/
int CExcelCsv::ReadColValues( CString &cZeile, CString &cItem, struct CUpdateFromExcelView::sLine* ST_LineVal[], struct PFL_FELD* ActPflFeld[], bool printEmptyCol, char *errmld )
{
	char *Item;

	cItem.Empty();

	if ( m_TextDat->ReadString( cZeile ) )
	{
		// PZN
		Item = ScanItem( (LPCTSTR) cZeile, m_nPos );

		/* Bugfix: ScanItem() returns NULL, if cZeile='\0' (empty line in a csv file or at its end)
		--> treat it as an error , because otherwise it may cause a nullpointer exception below */
		if (Item == NULL)
		{
			sprintf( errmld, "Die CSV-Datei enthält Leerzeilen - Eine Verarbeitung ist nicht möglich!" );
			return 2;
		}

		m_nAnzGelesen++;
			
		// -----------
		CString code = Item;
		CString errMsg;
		code.Trim();
			
		if (code != "-9999")
		{
			// remove leading zeros
			while( code[0] == '0' ) 
			{
				code.Delete(0);
			}

			long pzn;

			if (code.IsEmpty())
			{
				pzn = 0;
			}
			else
			{
				CLsArticleCodes lsCode;
				pzn = lsCode.getArticleNoByCode( code, errMsg );
			}

			if (pzn < 0)
			{
				if ((strcmp(ST_LineVal[0]->csUpdateCol, "Baselist ID (A to Z)") != 0) && 
					(strcmp(ST_LineVal[0]->csUpdateCol, "Medical Actor ID ") != 0))
				{
					sprintf ( errmld, "Article-Code<%s> in Zeile <%ld> ist unbekannt!", Item, m_nAnzGelesen+1 );
					return 2;
				}
				else
				{
					cItem.Format("-%s", code);
				}
			}
			else
			{
				cItem.Format("%ld", pzn);
			}
		}
		else
		{
			cItem = code;
		}
		// -----------
		/*
		if ( !IsDigit( Item ) )
		{
			sprintf ( errmld, "PZN<%s> in Zeile <%ld> ist nicht numerisch!", Item, m_nAnzGelesen+1 );
			return 2;
		}
		else if ( TestPruefZiffer7( atol( Item ) ) == 0 )
		{
			sprintf ( errmld, "PZN<%s> in Zeile <%ld> hat ungültige Prüfziffer!", Item, m_nAnzGelesen+1 );
			return 2;
		}
		cItem = Item;
		*/
		// -----------
		// for mass upload irrelevant to PZN make the first cItem empty
		if (strcmp(ST_LineVal[0]->csUpdateCol, "Medical Actor ID ") == 0)
			cItem.Empty();
		else
			cItem.Append(DELIMITER);
				
		// Update-Columns
		for ( int iLine = 0; iLine < ANZ_FELDER_UPD; iLine ++ )
		{
			if ( ST_LineVal[iLine]->csUpdateCol.IsEmpty() )
				break;

			if ( ST_LineVal[iLine]->bTakeCsvCol == true )
			{
				Item = ScanItem( (LPCTSTR) cZeile, m_iColPos[iLine] );
				
				// Test jeder Zeile ob gültige Spaltenwerte
				if ( ValidateCsvColInput ( ActPflFeld[iLine], Item ) == false )
				{
					sprintf ( errmld, "Wert<%s> in Zeile <%ld>, Spalte <%ld> ist für die gewählte Update-Spalte<%s> ungültig!", 
										Item,
										m_nAnzGelesen+1, 
										m_iColPos[iLine]+1,
										ActPflFeld[iLine]->cName);
					return 3;
				}
			}
			else // Festwert
			{
				//TH Item = _strdup("                    ");
				strcpy ( Item, ST_LineVal[iLine]->csCsvCol_StatVal );
			}

			
			if  (( EDIT_MASK* )ActPflFeld[iLine]->iArt == A_EDIT )
			{
				EDIT_MASK* EM;
				EM = ( EDIT_MASK* )ActPflFeld[iLine]->pRef1;
								
				// für zartpreis: convert date-string to long !
				if ( EM->nType == ED_LDATE )
				{
					PHODATE datum;
					CString temp;
					ConvToPhoDate    ( Item, &datum, "tt.mm.jjjj" );
					temp.Format("%ld", datum);
					strcpy ( Item, temp );
				}

				// für zartpreis: "," durch "." ersetzen! - für double values "." mit "," ersetzen!
				CString str = Item;
										
				switch ( EM->nNrVal )
				{
				case VAL_PREIS_GROSSO:	//fall through
				case VAL_PREIS_AEP:		//fall through
				case VAL_PREIS_AVP:
				case VAL_PREIS_EAVP:
				case VAL_PREIS_MAXAEP:		//fall through
				case VAL_PREIS_MAXAVP:
				case VAL_PREIS_LBP:
				case VAL_PREIS_PHARMACY_BASEPRICE:
					str.Replace(',', '.');
					strcpy ( Item, str );
					break;
				case VAL_ART_ALCOHOLIC_STRENGTH:
					str.Replace(',', '.');
					strcpy ( Item, str );
					break;
				case VAL_HERSTEL_PROZ:
					str.Replace(',', '.');
					strcpy ( Item, str );
					break;
				case VAL_DISC_REFUND_PCT:		//fall through
				case VAL_DISC_SURCHARGE_PCT:	//fall through
				case VAL_DISC_FIXED_PRICE:		//fall through
				case VAL_DISC_VALUE_PCT:
				case VAL_ART_REIMBURSEMENT_PERC:
				case VAL_ART_TFR_BASE_PRICE:
				case VAL_ART_WARNPROZVORPLM:
					str.Replace(',', '.');
					strcpy ( Item, str );
					break;

				case VAL_CHARGE: // as this field is part of key in zchargenrueckruf, it has to be upper case always !
					str.MakeUpper();
					strcpy ( Item, str );
					break;
				case VAL_CMEDICALACTOR_ID:
				case VAL_CMEDICALACTOR_MATCHCODE:
				case VAL_CMEDICALACTOR_NAME:
				case VAL_CMEDICALACTOR_STREET_NR:
				case VAL_CMEDICALACTOR_STREET_NAME:
				case VAL_CMEDICALACTOR_CITY_NAME:
				case VAL_CMEDICALACTOR_COUNTRY_CODE:
					str.MakeUpper();
					strcpy(Item, str);
					break;
				case VAL_CARTMEDACTOR_ID:
					str.MakeUpper();
					strcpy(Item, str);
					break;
				case VAL_EAN:
					if (ST_LineVal[iLine]->bTakeCsvCol == false)  // fixed value makes no sense for ean
					{
						sprintf(errmld, "For ean_nr a fixed value is not allowed!");
						return 3;
					}
					break;

				default:
					break; // nothing to do
				}
			}
			else if ( ActPflFeld[iLine]->iArt == A_COMBO )
			{
				if (( strcmp(ActPflFeld[iLine]->cUpdColumn, "DISCOUNTCALCFROM") == 0 )
				 || ( strcmp(ActPflFeld[iLine]->cUpdColumn, "DISCOUNTAPPLYTO")  == 0 ))
				{
					if ( strcmp( Item, "GEP" ) == 0 )
					{
						strcpy( Item, "0" );
					}
					else if ( strcmp(Item, "AGP") == 0 )
					{
						strcpy( Item, "1" );
					}
				}
			}

			/* Idea for optimazion (KT): If for every field a EDIT_MASK definition is used (not yet defined for ARTICLE_NO_PACK),
			   we could use VAL_... definitions there to avoid the strcmp functions. Also a maximum length for the PZN could be defined there.	*/

			if ((strcmp(ActPflFeld[iLine]->cUpdColumn, "ARTICLE_NO_PACK") == 0)
			 || (strcmp(ActPflFeld[iLine]->cUpdColumn, "ERSATZ_NR") == 0)
			 || (strcmp(ActPflFeld[iLine]->cUpdColumn, "DISCOUNTARTICLE") == 0))	/* CPR-240764 (HR) */
			{
				long pzn;
				CLsArticleCodes lsCode;
				pzn = lsCode.getArticleNoByCode((CString)Item, errMsg);

				if (pzn < 0)
				{
					if (strcmp(ActPflFeld[iLine]->cUpdColumn, "ERSATZ_NR") == 0)
						sprintf(errmld, "Ersatz-Nr<%s> in Zeile <%ld> ist unbekannt!", Item, m_nAnzGelesen + 1);
					else if (strcmp(ActPflFeld[iLine]->cUpdColumn, "ARTICLE_NO_PACK") == 0)
						sprintf(errmld, "ARTICLE_NO_PACK <%s> in Zeile <%ld> ist unbekannt!", Item, m_nAnzGelesen + 1);
					else
						sprintf(errmld, "DISCOUNTARTICLE <%s> in Zeile <%ld> ist unbekannt!", Item, m_nAnzGelesen + 1);

					return 2;
				}

				sprintf(Item, "%ld", pzn);
			}

			if (!( Item == NULL || *Item == '\0' ))
			{
				cItem.Append(Item);
				cItem.Append(DELIMITER);
			}
			else if (printEmptyCol == true)
			{   /* print empty colvalue (for zartwg_5ag needed!) */
				cItem.Append(DELIMITER);
			}
		}

		return 0;
	}
	return 1;
}

/*------------------------------------------------------------------------*/
bool CExcelCsv::IsDigit( CString cS )
{
	int pos;
	cS.TrimLeft();
	cS.TrimRight();

	if ( cS.IsEmpty() )
		return false;

	pos = 0;
	for ( pos = 0; pos < cS.GetLength(); pos++ )
	{
		if (!isdigit( cS.GetAt( pos ) ) && cS.GetAt( pos )  != '.' )
			return false;
	}
	return true;
}

/*------------------------------------------------------------------------*/
bool CExcelCsv::ValidateTxtColInput ( const int colNo, CString & csItem )
{
	csItem.TrimLeft();
	csItem.TrimRight();

	if ( csItem.IsEmpty() )
		return false;

	CString errMsg;
	CUpdateFromExcelView objView;

	if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "zpps2bg" || 
		 ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "ibg21")
	{ // special file structure Bulgaria
		switch ( colNo )
		{
		case 0: //articleno
		
			if ( IsDigit( csItem ) && atol(csItem) == 0 )
				m_PznIsNull = true;
			else
			{
				// remove leading zeros
				while( csItem[0] == '0' ) 
					csItem.Delete(0);

				CLsArticleCodes lsCode;
				long pzn = lsCode.getArticleNoByCode( csItem, errMsg );

				if (pzn < 0)
					return false;

				csItem.Format("%ld", pzn);
				m_PznIsNull = false;
			}
			break;

		case 1: //discountgrpno
			if ( !IsDigit( csItem ) )
				return false;
			if ( objView.TestDiscountGroup( csItem, false ) == false )
				return false;

			/* entweder pzn oder grp muss / darf gefüllt sein !!!
			if ( m_PznIsNull == false && atoi(csItem) != 0 ) 
				return false;

			if ( m_PznIsNull == true && atoi(csItem) == 0 ) 
				return false;
			*/

			break;

		case 2: // manufacturerno
			if ( !IsDigit( csItem ) )
				return false;
			if ( objView.TestDiscountManufacturer( csItem, false ) == false )
				return false;
			
			break;

		case 3: // artcategoryno
			if ( !IsDigit( csItem ) )
				return false;
			if ( objView.TestArtCategory( csItem, false ) == false )
				return false;
			break;

		case 4: // baseqty
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) < 0 )
				return false;
			m_CurrentBaseQty = csItem;
			break;

		case 5: // base_value
			if ( !IsDigit( csItem ) )
				return false;
			if ( atof(csItem) > 9999999.99 || atof(csItem) < 0.00 )
				return false;
			if ( atof(csItem) == 0.00 && atoi(m_CurrentBaseQty) == 0 )
				return false;

			csItem.Replace(',','.');
			break;

		case 6: //datefrom
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) <= 0 )
				return false;
			m_CurrentDateFrom = csItem;
			break;

		case 7: //dateto
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) <= 0 )
				return false;
			if ( atoi(csItem) < atoi(m_CurrentDateFrom) )
				return false;
			break;

		case 8: //discountvaluepct
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 9: // grossprofitpct
			if ( !IsDigit( csItem ) )
				return false;
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 10: //discountqty
			if ( !IsDigit( csItem ) )
				return false;
			m_CurrentDiscQty = csItem;
			break;

		case 11: //pharmacygroupid 
			if ( csItem.GetLength() > 3 )
				return false;
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			m_CurrentPharmGrpId = csItem;
			break;

		case 12: //customerno
			if ( !IsDigit( csItem ) )
				return false;
			if ( csItem.GetLength() > 7 )
				return false;
			break;

		case 13: //discounttype
			if ( !IsDigit( csItem ) )
				return false;
			if ( csItem < "0" || csItem > "7" ) 
				return false;
			break;

		case 14: //discountspec
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) < 0 || atoi(csItem) > 11 ) 
				return false;
			break;

		case 15: // addondiscountok
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 16: // refundvalue
			if ( !IsDigit( csItem ) )
				return false;
			if ( atof(csItem) > 9999999.99 )
				return false;

			csItem.Replace(',','.');
			break;

		//BG: refundtype --> immer 1, nicht im File !!!
		
		case 17: // no_multiple_qty
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 18: // promotion_no
			if ( !IsDigit( csItem ) )
				return false;
			if ( objView.TestPromo( csItem, false ) == false )
				return false;			
			break;

		case 19: // turnovercalcimpact
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 20: //discountarticle
			if ( !IsDigit( csItem ) || atol(csItem) != 0 )
			{
				// remove leading zeros
				while( csItem[0] == '0' ) 
					csItem.Delete(0);

				CLsArticleCodes lsCode;
				long pzn = lsCode.getArticleNoByCode( csItem, errMsg );

				if (pzn < 0)
					return false;

				csItem.Format("%ld", pzn);
			}
		
			if ( atoi(csItem) != 0 && atoi(m_CurrentDiscQty) == 0 )
				return false;
			
			break;

		case 21: //pharmgrpexcluded
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId != "000" )
				return false;
			m_CurrentPharmGrpId_Excl_1 = csItem;
			break;

		case 22: // addondiscount
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 23: //internaldiscount
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 24: //surchargepct
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 25: // pharmgrpexcl_2
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId != "000" )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId_Excl_1 == "000" )
				return false;
			m_CurrentPharmGrpId_Excl_2 = csItem;
			break;

		case 26: //pharmgrpexcl_3
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId != "000" )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId_Excl_2 == "000" )
				return false;
			break;

		default:
			return false;
		}
	}
	else // std file structure (France)
	{
		switch ( colNo )
		{
		case 0: //articleno
		
			if ( IsDigit( csItem ) && atol(csItem) == 0 )
				m_PznIsNull = true;
			else
			{
				// remove leading zeros
				while( csItem[0] == '0' ) 
					csItem.Delete(0);

				CLsArticleCodes lsCode;
				long pzn = lsCode.getArticleNoByCode( csItem, errMsg );

				if (pzn < 0)
					return false;

				csItem.Format("%ld", pzn);
				m_PznIsNull = false;
			}
			break;

		case 1: //discountgrpno
			if ( !IsDigit( csItem ) )
				return false;
			if ( objView.TestDiscountGroup( csItem, false ) == false )
				return false;

			// entweder pzn oder grp muss / darf gefüllt sein !!!
			if ( m_PznIsNull == false && atoi(csItem) != 0 ) 
				return false;

			if ( m_PznIsNull == true && atoi(csItem) == 0 ) 
				return false;

			break;

		case 2: //pharmacygroupid
			if ( csItem.GetLength() > 3 )
				return false;
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			m_CurrentPharmGrpId = csItem;
			break;

		case 3: //customerno
			if ( !IsDigit( csItem ) )
				return false;
			if ( csItem.GetLength() > 7 )
				return false;
			break;

		case 4: //baseqty
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) <= 0 )
				return false;
			break;

		case 5: //datefrom
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) <= 0 )
				return false;
			m_CurrentDateFrom = csItem;
			break;

		case 6: //dateto
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) <= 0 )
				return false;
			if ( atoi(csItem) <= atoi(m_CurrentDateFrom) )
				return false;
			break;

		case 7: //grpdiscounttyp
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) != 0 )
				return false;
			break;

		case 8: //discounttype
			if ( !IsDigit( csItem ) )
				return false;
			//if ( csItem != "0" && csItem != "1" && csItem != "4" && csItem != "5" )
			if ( csItem < "0" || csItem > "7" ) 
				return false;
			break;

		case 9: //discountspec
			if ( !IsDigit( csItem ) )
				return false;
			if ( atoi(csItem) < 0 || atoi(csItem) > 11 ) 
				return false;
			break;

		case 10: //discountqty
			if ( !IsDigit( csItem ) )
				return false;
			m_CurrentDiscQty = csItem;
			break;

		case 11: //discountvaluepct
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 12: //discountqtypct
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 13: //surchargepct
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 14: //pharmgrpexcluded
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId != "000" )
				return false;
			m_CurrentPharmGrpId_Excl_1 = csItem;
			break;

		case 15: //fixedprice
			double price;
			price = atof(csItem);

			if ( price > 9999999.99 )
				return false;

			csItem.Replace(',','.');
			break;

		case 16: //refundpct
			if ( objView.TestPct( csItem, false ) == false )
				return false;
			break;

		case 17: //internaldiscount
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 18: //discountarticle
			if ( !IsDigit( csItem ) || atol(csItem) != 0 )
			{
				// remove leading zeros
				while( csItem[0] == '0' ) 
					csItem.Delete(0);

				CLsArticleCodes lsCode;
				long pzn = lsCode.getArticleNoByCode( csItem, errMsg );

				if (pzn < 0)
					return false;

				csItem.Format("%ld", pzn);
			}
		// ----
			/*
			if ( !IsDigit( csItem ) )
				return false;
			if ( TestPruefZiffer7( atol( csItem ) ) == 0 )
				return false;
			if ( objView.TestPZN( csItem, false ) == false )
				return false;
			*/
		// ----
			if ( atoi(csItem) != 0 && atoi(m_CurrentDiscQty) == 0 )
				return false;
			
			break;

		case 19: //monthlydiscount
			if ( csItem != "0" && csItem != "1" )
				return false;
			break;

		case 20: // pharmgrpexcl_2
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId != "000" )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId_Excl_1 == "000" )
				return false;
			m_CurrentPharmGrpId_Excl_2 = csItem;
			break;

		case 21: //pharmgrpexcl_3
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId != "000" )
				return false;
			if ( csItem != "000" && m_CurrentPharmGrpId_Excl_2 == "000" )
				return false;
			break;

		default:
			return false;
		}
	}
	return true;
}

/*------------------------------------------------------------------------*/
bool CExcelCsv::ValidateCsvColInput ( struct PFL_FELD* ActPflFeld, CString csItem )
{
	if (ActPflFeld->iArt != A_EDIT || (( EDIT_MASK* )ActPflFeld->pRef1)->nNrVal != VAL_CHARGE)
	{ // für zchargenrueckruf.charge ist "blank" eine gültige Eingabe!
		csItem.TrimLeft();
		csItem.TrimRight();
	}
	
	CUpdateFromExcelView objView;

	switch ( ActPflFeld->iArt )
	{
	case A_EDIT:
		EDIT_MASK* EM;
		EM = ( EDIT_MASK* )ActPflFeld->pRef1;
		if ( csItem.GetLength() > EM->nTextLen )
			return false;

		switch ( EM->nNrVal )
		{
		case VAL_AWL1:
			if ( objView.TestAwl1( csItem, false ) == false )
				return false;
			break;

		case VAL_ART_NR_ORIG:
			if ( objView.TestArtNrOrig( csItem, false ) == false )
				return false;
			break;

		case VAL_HNR:
			if ( objView.TestManufacturer( csItem, false ) == false )
				return false;
			break;	
		
		case VAL_WG_ART_1:
			if ( objView.TestWgArt1( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_2:
			if ( objView.TestWgArt2( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_3:
			if ( objView.TestWgArt3( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_4:
			if ( objView.TestWgArt4( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_5:
			if ( objView.TestWgArt5( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_6:
			if ( objView.TestWgArt6( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_7:
			if ( objView.TestWgArt7( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_8:
			if ( objView.TestWgArt8( csItem, false ) == false )
				return false;
			break;
		
		case VAL_WG_ART_9:
			if ( objView.TestWgArt9( csItem, false ) == false )
				return false;
			break;

		case VAL_WG_ART_A:
			if ( objView.TestWgArtA( csItem, false ) == false )
				return false;
			break;

		case VAL_WG_ART_G:
			if ( objView.TestWgArtG( csItem, false ) == false )
				return false;
			break;

		case VAL_ART_DATUMAH:
		case VAL_DATETO_GI:
		case VAL_DATETO_CUSTRETURNS:
			if ( objView.TestDatumAh( csItem, false ) == false )
				return false;
			break;
			
		case VAL_PREIS_GUELTIGAB:
		case VAL_BATCHENTRY_DATE:
			if ( objView.TestGueltab( csItem, false ) == false )
				return false;
			break;

		case VAL_BATCHENTRY_COMPANYCODE:
			if ( objView.TestCompanyCode( csItem, false ) == false )
				return false;
			break;

		case VAL_PREIS_GROSSO:	//fall through
		case VAL_PREIS_AEP:		//fall through
		case VAL_PREIS_AVP:
		case VAL_PREIS_EAVP:
		case VAL_PREIS_MAXAEP:	//fall through
		case VAL_PREIS_MAXAVP:
		case VAL_PREIS_LBP:
		case VAL_ART_TFR_BASE_PRICE:
		case VAL_PREIS_PHARMACY_BASEPRICE:
			if ( objView.TestPrice( csItem, false, EM->nNrVal ) == false )
				return false;
			break;

		case VAL_DISC_BASE_QTY:
			if ( objView.TestDiscBaseQty( csItem, false ) == false )
				return false;
			break;

		case VAL_DISC_DATEFROM:
			if ( objView.TestDiscDateFrom( csItem, false ) == false )
				return false;
			break;

		case VAL_DISC_DATETO:
			if ( objView.TestDiscDateTo( csItem, false ) == false )
				return false;
			break;

		case VAL_DISC_PHARM_GRP:
		case VAL_DISC_PHARM_GRP_EXCL:
		case VAL_DISC_PHARM_GRP_EXCL2:
		case VAL_DISC_PHARM_GRP_EXCL3:
			if ( objView.TestPharmacyGroup( csItem, false ) == false )
				return false;		
			break;

		case VAL_DISC_CUSTOMER:
			if ( objView.TestDiscountCustomer( csItem, false ) == false )
				return false;				
			break;

		case VAL_DISC_MANUFACTURER:
		case VAL_DISC_STOP_HNR:
			if ( objView.TestDiscountManufacturer( csItem, false ) == false )
				return false;	
			break;

		case VAL_DISC_RPG:
			if ( objView.TestDiscountGroup( csItem, false ) == false )
				return false;	
			break;	

		case VAL_DISC_ARTCAT:
			if ( objView.TestArtCategory( csItem, false ) == false )
				return false;	
			break;	

		case VAL_ORIG_KART:
		case VAL_VPE1:
		case VAL_VPE2:
		case VAL_VPE3:
		case VAL_VPE4:
			if ( objView.TestArtVeVPE( csItem, false ) == false )
				return false;
			break;

		case VAL_ART_CODE:
			if ( objView.TestArtCode( csItem, false ) == false )
				return false;
			break;

		case VAL_ART_CODE_LPPR:
			if ( objView.TestCodeLppr( csItem, false ) == false )
				return false;
			break;

		case VAL_ART_REIMBURSEMENT_PERC:
			if ( objView.TestReimbPct( csItem, false ) == false )
				return false;
			break;

		case VAL_IMEX_COUNTRY:
			if ( objView.TestCountry( csItem, false ) == false )
				return false;
			break;	

		case VAL_CHARGE:
			if ( objView.TestCharge( csItem, false ) == false )
				return false;
			break;

		case VAL_EAN:
			if ( objView.TestEan( csItem, false ) == false )
				return false;
			break;

		case VAL_NACHL:
			if (objView.TestNachl(csItem, false) == false)
				return false;
			break;

		case VAL_KONTMENGENST:
				if (objView.TestKontMengenSteuerung(csItem, false) == false)
					return false;
			break;

		case VAL_BESLA_NO:
			if (objView.TestBeslaNo(csItem, false) == false)
				return false;
			break;

		default:
			break;
		}

		break;

	case A_BUTTON:
		if ( csItem != "0" && csItem != "1" )
			return false;
		break;

	case A_COMBO:
		COMBO_MASK* CM;
		CM = ( COMBO_MASK* )ActPflFeld->pRef1;
		
		char * GueltigeWerte;
		GueltigeWerte = strstr ( CM->cWerte, csItem );

		while ( GueltigeWerte != NULL )
		{
			if ( ( GueltigeWerte - CM->cWerte ) % CM->nBufLen == 0 )
				break;

			GueltigeWerte = strstr ( GueltigeWerte + 1, csItem );
		}

		if ( GueltigeWerte == NULL )
			return false;

		break;

	default: 
		break;
	}
	return true;
}
