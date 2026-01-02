
#include "stdafx.h"
#include "ZdpUtil.h"
#include "UpdateFromExcelView.h"
#include "ExcelCsv.h"
#include <libscsvoodoo/libscsvoodoo.h>
#include "FeldBreite.h"

#include <phxlib/LsArticleCodes.h>

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskBin.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskBuBl.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <eklibs/hamfcs/hMskInt.h>

#include <phxlib/phxutil.h>
#include <phxlib/EanTest.h>
#include <hdatum/phodate.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CUpdateFromExcelView, CFormViewMultiLang)

/*------------------------------------------------------------------------*/
CUpdateFromExcelView::CUpdateFromExcelView()
	: ChPflegeView(CUpdateFromExcelView::IDD)
{
	theApp = ((CZdpUtilApp*)AfxGetApp());
	m_bDoResize  = false;

	for ( int i = 0; i < ANZ_FELDER_UPD; i++ )
	{
		m_ed_UpdCol[i] = NULL;
		m_ck_StaticVal[i] = NULL;
		m_ck_NegRest[i] = NULL;
		m_i_CkStatVal[i] = 0;
		m_i_CkNegRest[i] = 0;
		m_ed_StatVal[i] = NULL;
		m_bt_StatVal[i] = NULL;
		m_cb_StatVal[i] = NULL;
		m_ed_NegVal[i] = NULL;
		m_bt_NegVal[i] = NULL;
		m_cb_NegVal[i] = NULL;
	}

	for ( int i = 0; i < ANZ_FELDER_UPD; i++ )
	{
		ST_LineVal[i] = new sLine;
	}
}

/*------------------------------------------------------------------------*/
CUpdateFromExcelView::~CUpdateFromExcelView()
{
	m_dlg.Reset( );

	int i;

	for ( i = 0; i < ANZ_FELDER_UPD; i++ )
	{
		delete ST_LineVal[i];
	}

	for ( i = 0; i < ANZ_FELDER_UPD; i++ )
	{
		if ( m_ed_UpdCol[i] != NULL )
		{
			delete m_ed_UpdCol[i];
			m_ed_UpdCol[i] = NULL;
		}

		if ( m_ck_StaticVal[i] != NULL )
		{
			delete m_ck_StaticVal[i];
			m_ck_StaticVal[i] = NULL;
		}

		if ( m_ck_NegRest[i] != NULL )
		{
			delete m_ck_NegRest[i];
			m_ck_NegRest[i] = NULL;
		}

		if ( m_cb_StatVal[i] != NULL )
		{
			delete m_cb_StatVal[i];
			m_cb_StatVal[i] = NULL;
		}

		if ( m_ed_StatVal[i] != NULL )
		{
			delete m_ed_StatVal[i];
			m_ed_StatVal[i] = NULL;
		}

		if ( m_bt_StatVal[i] != NULL )
		{
			delete m_bt_StatVal[i];
			m_bt_StatVal[i] = NULL;
		}

		if ( m_ed_NegVal[i] != NULL )
		{
			delete m_ed_NegVal[i];
			m_ed_NegVal[i] = NULL;
		}

		if ( m_bt_NegVal[i] != NULL )
		{
			delete m_bt_NegVal[i];
			m_bt_NegVal[i] = NULL;
		}

		if ( m_cb_NegVal[i] != NULL )
		{
			delete m_cb_NegVal[i];
			m_cb_NegVal[i] = NULL;
		}

		m_i_CkStatVal[i] = 0;
		m_i_CkNegRest[i] = 0;
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateFromExcelView)
	DDX_Control(pDX, IDC_ED_PZN_COL, m_ed_PznCol);
	DDX_Control(pDX, IDC_BT_ZARTIKEL, m_bt_ZArtikel);
	DDX_Control(pDX, IDC_BT_ZARTPREIS, m_bt_ZArtPreis);
	DDX_Control(pDX, IDC_BT_ZARTWG, m_bt_ZArtWg);
	DDX_Control(pDX, IDC_BT_CDISCOUNT, m_bt_CDiscount);
	DDX_Control(pDX, IDC_ST_RESTVAL, m_st_RestVal);
	DDX_Control(pDX, IDC_ST_CK_NEGREST, m_st_CkRestNeg);
	DDX_Control(pDX, IDC_ST_STATVAL_CSV, m_st_StatCsvVal);
	DDX_Control(pDX, IDC_ST_CK_STATICVAL, m_st_CkStatVal);
	DDX_Control(pDX, IDC_ST_COL, m_st_Column);
	DDX_Control(pDX, IDC_ED_MUSTER, m_ed_Muster);
	DDX_Control(pDX, IDC_CK_MUSTER, m_ck_Muster);
	DDX_Control(pDX, IDC_CB_MUSTER, m_cb_Muster);
	//}}AFX_DATA_MAP
}

/*------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CUpdateFromExcelView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CUpdateFromExcelView)
	ON_BN_CLICKED(IDC_BT_ZARTIKEL, OnBtZArtikel)
	ON_BN_CLICKED(IDC_BT_ZARTPREIS, OnBtZArtPreis)
	ON_BN_CLICKED(IDC_BT_CIMEXBLOCK, OnBtCimexblock)
	ON_BN_CLICKED(IDC_BT_ARTVE, OnBtArtVe)
	ON_BN_CLICKED(IDC_BT_COUNTRY_SPECIFIC, OnBtCountry)
	ON_BN_CLICKED(IDC_BT_CODES, OnBtCodes)
	ON_BN_CLICKED(IDC_BT_ZARTWG, OnBtZArtWg)
	ON_BN_CLICKED(IDC_BT_CDISCOUNT, OnBtCDiscount)
	ON_BN_CLICKED(IDC_BT_CDISCOUNT_FLEXIBLE, OnBtCDiscountFlexible)
	ON_BN_CLICKED(IDC_BT_CDISCOUNT_END, OnBtCDiscountEnd)
	ON_BN_CLICKED(IDC_BT_RPG, OnBtCDiscGrpMem)
	ON_BN_CLICKED(IDC_BT_ARTCOMPACK, OnBtCArtComPack)
	ON_BN_CLICKED(IDC_BT_GIBATCHENTRY, OnBtCGiBatchEntry)	
	ON_BN_CLICKED(IDC_BT_CARTICLEEXT, OnBnClickedBtCarticleext)
	ON_BN_CLICKED(IDC_BT_ZCHARGENRR, OnBnClickedBtZChargenRR)
	ON_BN_CLICKED(IDC_BT_IBT, OnBtCibt)
	ON_BN_CLICKED(IDC_BT_EAN, OnBtEAN)
	ON_BN_CLICKED(IDC_BT_SUBSEQUENTDELIVERY, OnBtSubsequentDelivery)
	ON_BN_CLICKED(IDC_BT_ZARTWG_5AG, OnBtZArtWg5AG)
	ON_BN_CLICKED(IDC_BT_BLIESORT, OnBtBliesort)
	ON_BN_CLICKED(IDC_BT_BASELIST, OnBtBaselist)
	ON_BN_CLICKED(IDC_BT_CARTMEDACTOR, OnBtCartmedactor)
	ON_BN_CLICKED(IDC_BT_CMEDICALACTOR, OnBtCmedicalactor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::CkStatValClicked()
{
	for ( int i = 0; i < m_nAnzRows; i++ )
	{
		int iCheck = m_ck_StaticVal[i]->GetCheck();

		if ( m_i_CkStatVal[i] != iCheck )
		{
			m_i_CkStatVal[i] = iCheck;
			
			CWnd * pWndAbove;
			if ( i == 0 )
			{
				pWndAbove = &m_st_StatCsvVal;
			}
			else
			{
				if ( m_ed_StatVal[ i-1 ] != NULL )
					pWndAbove = m_ed_StatVal[ i-1 ]; 
				else if ( m_bt_StatVal[ i-1 ] != NULL )
					pWndAbove = m_bt_StatVal[ i-1 ];
				else
					pWndAbove = m_cb_StatVal[ i-1 ];
			}

			if ( iCheck != CK_CLICKED )
			{	// Festwert
				m_ed_StatVal[i]->ShowWindow (SW_HIDE);
				delete m_ed_StatVal[i];
				m_ed_StatVal[i] = NULL;
				
				switch ( m_PflFelder[i]->iArt )
				{
				case A_EDIT:
					GenEditFeld( i, pWndAbove );
					break;
				case A_BUTTON:
					GenButtonFeld( i, pWndAbove );
					break;
				default:
					GenComboBoxFeld( i, pWndAbove );
					break;
				}
			}
			else
			{
				if ( m_ed_StatVal[i] != NULL )
				{
					m_ed_StatVal[i]->ShowWindow (SW_HIDE);
					delete m_ed_StatVal[i];
					m_ed_StatVal[i] = NULL;
				}
				else if ( m_bt_StatVal[i] != NULL )
				{
					m_bt_StatVal[i]->ShowWindow (SW_HIDE);
					delete m_bt_StatVal[i];
					m_bt_StatVal[i] = NULL;
				}
				else
				{
					m_cb_StatVal[i]->ShowWindow (SW_HIDE);
					delete m_cb_StatVal[i];
					m_cb_StatVal[i] = NULL;
				}

				GenEditFeld( i, pWndAbove, false, true );

			}
			break;
		}
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::CkRestNegClicked()
{
	for ( int i = 0; i < m_nAnzRows; i++ )
	{
		int iCheck = m_ck_NegRest[i]->GetCheck();

		if ( m_i_CkNegRest[i] != iCheck )
		{
			m_i_CkNegRest[i] = iCheck;
			
			CWnd * pWndAbove;
			pWndAbove = &m_st_RestVal;

			if ( iCheck != CK_CLICKED )
			{	
				if ( m_ed_NegVal[i] != NULL )
				{
					m_ed_NegVal[i]->ShowWindow (SW_HIDE);
					delete m_ed_NegVal[i];
					m_ed_NegVal[i] = NULL;
				}
				else if ( m_bt_NegVal[i] != NULL )
				{
					m_bt_NegVal[i]->ShowWindow (SW_HIDE);
					delete m_bt_NegVal[i];
					m_bt_NegVal[i] = NULL;
				}
				else
				{
					m_cb_NegVal[i]->ShowWindow (SW_HIDE);
					delete m_cb_NegVal[i];
					m_cb_NegVal[i] = NULL;
				}
			}
			else
			{
				switch ( m_PflFelder[i]->iArt )
				{
				case A_EDIT:
					GenEditFeld( i, pWndAbove, true );
					break;
				case A_BUTTON:
					GenButtonFeld( i, pWndAbove, true );
					break;
				default:
					GenComboBoxFeld( i, pWndAbove, true );
					break;
				}
			}
			break;
		}
	}
}

#define MAX_SPALTE 50

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::InitPflege()
{
	m_nAnzRows  = 0;

	HideControls();

	m_clrHeaderFarbe = RGB( 0, 0, 255 );
	
	m_st_Column.SetColor( m_clrHeaderFarbe  );
	m_st_CkStatVal.SetColor( m_clrHeaderFarbe  );
	m_st_StatCsvVal.SetColor( m_clrHeaderFarbe  );
	m_st_CkRestNeg.SetColor( m_clrHeaderFarbe  );
	m_st_RestVal.SetColor( m_clrHeaderFarbe  );		
	ShowPZNField(true);

}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::InitVariables()
{

}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::IsDigit( CString cS )
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
int  CUpdateFromExcelView::BearbeiteSatz()
{
	((CDialog*) this)->NextDlgCtrl( );
	return -1;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::ShowPZNField(bool bShow)
{
	// Show or Hide PZN Column field 
	// false if massupload irrelevant to PZN (e.g. cmedicalactor)
	m_ed_PznCol.ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_PZN)->ShowWindow(bShow);
}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::ExtractFromCsv( CString &cErrmld, char *ColumnHeaderPzn, long *nAnz ) 
{
// CSV
	bool bOk;
	long anz;
	char mld[200];
	CString cZeile;
	CString cItem;
	CExcelCsv Ecsv;

	bool bFirst;
	bool printEmptyCol;

// UNIX
	CString cDirec;
//	#define MAX_BUF 2048
//	char buf[ MAX_BUF + 1 ];
	int  unx_fd;

	cErrmld.Empty();
	
// Input CSV
	char BASED_CODE szFilter[] = 
		 "Csv Files (*.csv)|*.csv|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, "csv",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return false;

	CString sFileName;
	sFileName = dlg.GetPathName();	

	if ( sFileName.IsEmpty( ) || dlg.GetFileName( ).Find(' ') != -1 )
	{
		MsgBoxOK( "Dateiname nicht korrekt!");	
		return false;
	}
	
	long s = GetWWSDateiUnterVerz(cDirec, util, cErrmld);
	
	/* Output UNIX
	if ( UnxGetenv ( "WWS", buf ) != 0 )
	{
		cErrmld  = "Umgebungsvariable $WWS auf Server unbekannt\n";
		cErrmld += DynErrmld();
		return false;
	}

	cDirec  = buf;
	cDirec += _T( "/daten/zdputil/" );*/

	if ( s != 0 )
		return false;

	cDirec += dlg.GetFileName( );

	m_UnxDirectory = cDirec;

	bOk = true;
	bFirst = true;

	/* empty columns will be extracted for saison warengruppen to insert later */
	/* the correct lines into the unix file                                    */
	if (m_eUpdTable == UPD_ZARTWG_5AG || m_eUpdTable == UPD_MEDICALACTOR)
	{
		printEmptyCol = true;
	}
	else /* no change for all other imports */
	{
		printEmptyCol = false;
	}

	anz = 0;

	theApp->BeginWaitAction();
	int pos = Ecsv.ReadColPos ( (LPCTSTR )sFileName, ColumnHeaderPzn, ST_LineVal, mld );

	if ( pos >= 0  || pos == -9999 )
	{
		int  ret;
		ret	= 0;
		while ( ret == 0 && bOk )
		{
			ret = Ecsv.ReadColValues( cZeile, cItem, ST_LineVal, m_PflFelder, printEmptyCol, mld );
			if ( ret == 0 )
			{
				if (! cItem.IsEmpty() )
				{
					if ( bFirst )
					{
						if ( UnxFopen( &unx_fd, cDirec, "w" ) != 0 )
						{
							cErrmld.Format( "%s\n %s )", cDirec, DynErrmld() );
							bOk =  false;
						}
						else
						{
							bFirst = false;
							
							// Schreiben von 2 Headerzeilen!
							CString csHeaderLines;
							bOk = CreateHeaderLines( csHeaderLines ); 

							if ( bOk == true && UnxFwrite( unx_fd, (LPCTSTR) csHeaderLines, csHeaderLines.GetLength() ) != 0 )
							{
								cErrmld.Format( "%s\n %s )", cDirec, DynErrmld() );
								bOk = false;
							}

							detectColsForLineValidityCheck();
						}

					}

					if ( bOk )
					{
						bOk = checkLineValidity(cItem, cErrmld);

						if (bOk == false)
						{
							CString msg;
							msg.Format("\nZeile: %ld.", anz + 1);
							cErrmld += msg;
						}
						
					}

					if ( bOk )
					{
						if (m_eUpdTable == UPD_ZARTWG_5AG)
						{   /* for zartwg_5ag make max. three lines out of cItem */
							bOk = Create_ZArtWG_5AG_Lines( cItem );
							if (!bOk)
							{   /* empty line -> nothing to insert in the unix-file */
								bOk = true;   /* read further entries, bOK false will terminate the processing */
								continue;
							}
						}
						else
						{
							cItem += "\n";
						}
						
						if ( UnxFwrite( unx_fd, (LPCTSTR) cItem, cItem.GetLength() ) != 0 )
						{
							cErrmld.Format( "%s\n %s )", cDirec, DynErrmld() );
							bOk = false;
						}
						anz++;
					}
				}
			}
			else if ( ret > 1 )
			{//ReadColValues() != 0
				cErrmld = mld;
				cErrmld.Append("\nEs wurde kein Datensatz gespeichert!");
				bOk = false;
			}
		}

		if ( !bFirst )
			UnxFclose( unx_fd );
	
	}
	else
	{
		cErrmld = mld;
		bOk = false;
	}

	theApp->EndWaitAction();

	*nAnz = anz;

	return bOk;
}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::checkLineValidity( CString &csLine, CString &cErrmld )
{
	int old = 0;
	int pos = 0;

	CString discSpec	= "00";
	CString monthlyDisc = "0";
	PHODATE dateFrom	= 0;
	PHODATE dateTo		= 0;

	for ( int cnt = 0; cnt <= ANZ_FELDER_UPD; cnt++ )
	{
		pos = csLine.Find(DELIMITER, pos);

		if (m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE)
		{
			if (cnt == m_PosOfDiscountSpec)
				discSpec = csLine.Mid(old, pos-old);
			else if (cnt == m_PosOfMonthlyDiscountFlag)
				monthlyDisc = csLine.Mid(old, pos-old);
		}

		if (m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE || m_eUpdTable == UPD_CDISCOUNT_STOP)
		{
			if (cnt == m_PosOfMonthlyDiscountFlag)
				monthlyDisc = csLine.Mid(old, pos-old);
			else if (cnt == m_PosOfDiscDateFrom)
				dateFrom = atoi(csLine.Mid(old, pos-old));
			else if (cnt == m_PosOfDiscDateTo)
				dateTo = atoi(csLine.Mid(old, pos-old));
		}
		
		old = ++pos;		
	}

	if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "iat21" && 
		 m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE && 
		 ((monthlyDisc== "1" && discSpec != "04" ) ||
		 (monthlyDisc != "1" && discSpec == "04" ) ||
		 (monthlyDisc == "2" && discSpec != "00" && discSpec != "05" && discSpec != "06") ||
		 (monthlyDisc != "2" &&(discSpec == "05" || discSpec == "06"))
		 ))
	{
		cErrmld = "Kombination Rabattspezifikation / Monatsrabatt nicht plausibel!";
		return false;
	}

	if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE &&
		 dateFrom > dateTo )
	{
		cErrmld = "Startdatum darf nicht größer Endedatum sein!";
		return false;
	}

	if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE && 
		 ((dateFrom <= GetPhoDate() && monthlyDisc == "0") || 
		 (monthlyDisc != "0" && (dateFrom/100 < GetPhoDate()/100))) )
	{
		if (IsCountry("HR") && dateFrom == GetPhoDate())
		{
			// dateFrom == today is now allowed for HR (SCTASK0054765 27.06.2025)
		}
		else
		{
			cErrmld = "Startdatum muss in der Zukunft liegen!";
			return false;
		}
	}

	if (m_eUpdTable == UPD_CDISCOUNT_STOP && dateTo == 0)
		dateTo = GetPhoDate();

	if ( (m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE && dateTo < GetPhoDate()) || 
		 (m_eUpdTable == UPD_CDISCOUNT_STOP && dateTo < GetPhoDate() && monthlyDisc == "0") ||
		 (m_eUpdTable == UPD_CDISCOUNT_STOP && (AddDayToPhoDate(dateTo, 1)/100) < (GetPhoDate()/100) && monthlyDisc != "0")
		 )
	{
		cErrmld = "Endedatum muss in der Zukunft liegen!";
		return false;
	}

	return true;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::detectColsForLineValidityCheck()
{
	m_PosOfDiscountSpec = -1;
	m_PosOfMonthlyDiscountFlag = -1;
	m_PosOfDiscDateFrom = -1;
	m_PosOfDiscDateTo = -1;
		
	for ( int iPos = 0; iPos < ANZ_FELDER_UPD; iPos ++ )
	{
		if ( ST_LineVal[iPos]->csUpdateCol.IsEmpty() )
			break;

		// Prüfung Kombination monthlydiscount / discountspec
		if (m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE)
		{
			if ( ST_LineVal[iPos]->csUpdateCol == "Rabatt-Spezifikation" )
				m_PosOfDiscountSpec = iPos + 1;
			else if ( ST_LineVal[iPos]->csUpdateCol == "Monatsrabatt" )
				m_PosOfMonthlyDiscountFlag = iPos + 1;
		}

		// Prüfung Kombination monthlydiscount / datefrom bzw dateto
		if (m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE || m_eUpdTable == UPD_CDISCOUNT_STOP)
		{
			if ( ST_LineVal[iPos]->csUpdateCol == "Monatsrabatt" )
				m_PosOfMonthlyDiscountFlag = iPos + 1;
			else if ( ST_LineVal[iPos]->csUpdateCol == "gültig von" )
				m_PosOfDiscDateFrom = iPos + 1;
			else if ( ST_LineVal[iPos]->csUpdateCol == "gültig bis" )
				m_PosOfDiscDateTo = iPos + 1;
		}
	}
}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::CreateHeaderLines( CString &csHeaderLines )
{
	csHeaderLines.Empty();

	/* Header for zartwg_5ag */
	if (m_eUpdTable == UPD_ZARTWG_5AG)
	{
		/* First header line */
		csHeaderLines.Append( "ARTIKEL_NR" );
		csHeaderLines.Append( DELIMITER );
		csHeaderLines.Append( "ART" );
		csHeaderLines.Append( DELIMITER );
		csHeaderLines.Append( "WARENGRUPPE");
		csHeaderLines.Append( DELIMITER );
		csHeaderLines.Append( "\n" );

		/* Second header line */
		csHeaderLines.Append( "NEG_VALUES" );
		csHeaderLines.Append( DELIMITER );
		csHeaderLines.Append( DELIMITER );
		csHeaderLines.Append( DELIMITER );
		csHeaderLines.Append( "\n" );

		return true;
	} /* end header for zartwg_5ag */

	if ( m_eUpdTable == UPD_CDISCOUNT )
	{
		csHeaderLines.Append("CDISCOUNT - DEFINED FIXED FILE STRUCTURE");
		csHeaderLines.Append ("\n");
		
		if ( m_Reset_CDiscount_DateTo )
			csHeaderLines.Append("RESET_DATE_TO");
		
		csHeaderLines.Append ("|\n");
		return true;
	}

// 1. Headerzeile
	if (m_eUpdTable == UPD_KONTMENGENST)
	{
		csHeaderLines.Append("ARTICLENO");
	}
	else
	{
		csHeaderLines.Append("ARTIKEL_NR");
	}
	csHeaderLines.Append(DELIMITER);
	int iLine = 0;

	for ( iLine = 0; iLine < ANZ_FELDER_UPD; iLine ++ )
	{
		if ( ST_LineVal[iLine]->csUpdateCol.IsEmpty() )
			break;

		
		for ( int i = 0; i < ANZ_MAX_FELDER; i++ )
		{
			if ( ST_LineVal[iLine]->csUpdateCol == m_PflFelder[iLine]->cName )
			{
				if ( m_eUpdTable == UPD_ZARTWG )
				{
					CString csArt;
					
					if ( (( EDIT_MASK* )m_PflFelder[iLine]->pRef1)->nNrVal == VAL_WG_ART_A )
						csArt = "A";
					else if ( (( EDIT_MASK* )m_PflFelder[iLine]->pRef1)->nNrVal == VAL_WG_ART_G )
						csArt = "G";
					else
						csArt.Format("%d",(( EDIT_MASK* )m_PflFelder[iLine]->pRef1)->nNrVal - DIFF_ART_VAL_ZARTWG);
					
					csHeaderLines.Append( csArt );
				}
				else
					csHeaderLines.Append( m_PflFelder[iLine]->cUpdColumn );
				
				break;
			}
		}
		
		csHeaderLines.Append( DELIMITER );

	}

	csHeaderLines.Append ("\n");

// 2. Headerzeile
	csHeaderLines.Append("NEG_VALUES");
	csHeaderLines.Append(DELIMITER);

	for ( iLine = 0; iLine < ANZ_FELDER_UPD; iLine ++ )
	{
		if ( ST_LineVal[iLine]->csUpdateCol.IsEmpty() )
			break;

		if ( ST_LineVal[iLine]->bNegRest == true )
		{
			CString cQuestion;
			
			if ( m_eUpdTable == UPD_ZARTWG )
			{
				if ( (( EDIT_MASK* )m_PflFelder[iLine]->pRef1)->nNrVal == VAL_WG_ART_A )
				{ 
					cQuestion.Format( "Sollen wirklich ALLE Stammdaten-Sätze, die nicht in der CSV-Datei enthalten sind, "
									"für die Art <A> in der Spalte <warengruppe> auf den Wert '%s' gesetzt werden?",
									ST_LineVal[iLine]->csNegVal);	
				}
				else if ( (( EDIT_MASK* )m_PflFelder[iLine]->pRef1)->nNrVal == VAL_WG_ART_G )
				{ 
					cQuestion.Format( "Sollen wirklich ALLE Stammdaten-Sätze, die nicht in der CSV-Datei enthalten sind, "
									"für die Art <G> in der Spalte <warengruppe> auf den Wert '%s' gesetzt werden?",
									ST_LineVal[iLine]->csNegVal);	
				}
				else
				{
					cQuestion.Format( "Sollen wirklich ALLE Stammdaten-Sätze, die nicht in der CSV-Datei enthalten sind, "
									"für die Art <%d> in der Spalte <warengruppe> auf den Wert '%s' gesetzt werden?",
									(( EDIT_MASK* )m_PflFelder[iLine]->pRef1)->nNrVal - DIFF_ART_VAL_ZARTWG, ST_LineVal[iLine]->csNegVal);
				}
			}
			else
			{
				cQuestion.Format( "Sollen wirklich ALLE Stammdaten-Sätze, die nicht in der CSV-Datei enthalten sind, "
									"in der Spalte <'%s'> auf den Wert <'%s'> gesetzt werden?",
									m_PflFelder[iLine]->cUpdColumn, ST_LineVal[iLine]->csNegVal);
			}
		
			if ( MsgBoxYesNo( cQuestion, MB_ICONQUESTION | MB_DEFBUTTON2 ) == IDNO )
			{
				m_ck_NegRest[iLine]->SetFocus();
				return false;
			}

			if ( ST_LineVal[iLine]->csNegVal == ST_LineVal[iLine]->csCsvCol_StatVal && ST_LineVal[iLine]->bTakeCsvCol == false )
			{
				cQuestion.Format("Der Wert für Rest für die Spalte '%s' darf nicht gleich dem festen Wert für alle CSV-Zeilen sein!",
								ST_LineVal[iLine]->csUpdateCol);
				MsgBoxOK(cQuestion);
				m_ck_NegRest[iLine]->SetFocus();
				return false;
			}
			
			csHeaderLines.Append(ST_LineVal[iLine]->csNegVal);		
		}

		csHeaderLines.Append(DELIMITER);
	}

	csHeaderLines.Append ("\n");

	return true;
}

/* Convert the input line into max. three output lines */
/* artikel_nr|swg_5|swg_A|swg_G| will be converted in  */
/* artikel_nr|5|swg_5|                                 */
/* artikel_nr|A|swg_A|                                 */
/* artikel_nr|G|swg_G|                                 */
/* empty swg_5, swg_A, swg_G values will be ignored    */
bool CUpdateFromExcelView::Create_ZArtWG_5AG_Lines(CString& cItem)
{
	char sIn[100];
	char artikel_nr[L_ARTIKEL_NR + 1];
	int col_no = 0;
	int start = 0;
	int end;
	int i;

	strcpy( sIn, cItem );
	end = (int) strlen( sIn );

	cItem.Empty();

	for (i = 0; i < end; i++)
	{
		if (sIn[i] == DELIMITER_CHAR)
		{
			sIn[i] = '\0';

			if (col_no == 0) /* artikel_nr */
			{
				strcpy (artikel_nr, sIn);
			}
			else	/* warengruppe_5 or warengruppe_A or warengruppe_G */
			{
				if (i > start) /* col not empty -> insert a line into unix file */
				{
					if (col_no < 4)
					{
						cItem.Append(artikel_nr);
						cItem.Append(DELIMITER);
					}

					if (col_no == 1) /* Art = 5 */
					{
						cItem.Append("5");
					}
					else if (col_no == 2) /* Art = A */
					{
						cItem.Append("A");
					}
					else if (col_no == 3) /* Art = G */
					{
						cItem.Append("G");
					}

					if (col_no < 4)
					{
						cItem.Append(DELIMITER);
						cItem.Append(&sIn[start]);
						cItem.Append(DELIMITER);
						cItem.Append("\n");
					}
				}
			}
			/* always go forward -> skip empty entries */
			start = i + 1;
			col_no++;
		}
	}

	if (cItem.IsEmpty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::CallUnxBatch( CString &cErrmld, short testMode ) 
{
	#define MAX_BUF 2048
	long lStatus;
	int rcv_lng;
	char buf[ MAX_BUF + 1 ];
	
	cErrmld.Empty();

	CString cDirec;
	long s = GetWWSDateiUnterVerz(cDirec, bin, cErrmld);

	if ( s != 0 )
		return false;

	sprintf( buf, "%szputil %ld %s %s %d", 
					(char*)cDirec.GetString(),
					m_eUpdTable,
					(char*)m_UnxDirectory.GetString(),
					(char*)((CZdpUtilApp*) AfxGetApp())->GetDbaseName().GetString(),
					testMode);  

	rcv_lng = MAX_BUF;

	theApp->BeginWaitAction();

	// Aufruf Batch
	lStatus = UnxPipwSystem ( buf, "", buf, &rcv_lng );
	
	theApp->EndWaitAction();

	buf[rcv_lng] ='\0';

	if ( lStatus < 0 || rcv_lng == 0 )
	{
		strcpy( buf, DynErrmld() );
		lStatus = 1;
	}

	if ( lStatus == 1 )
	{
		cErrmld  = "zputil\n";
		cErrmld += buf;
		return false;
	}

	cErrmld = buf;

	return true;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::EndValidate( )
{// Validierung der Edit-Felder!
	int iLine = 0;
	
	while ( iLine < m_nAnzRows )
	{
		if ( m_ck_StaticVal[iLine]->GetCheck() != CK_CLICKED )
		{
			if ( m_ed_StatVal[iLine] != NULL )
			{
				if ( m_ed_StatVal[iLine]->Validate(true) == false )
				{
					m_ed_StatVal[iLine]->SetFocus();
					return false;
				}
			}
		}

		if ( m_ck_NegRest[iLine]->GetCheck() == CK_CLICKED )
		{
			if ( m_ed_NegVal[iLine] != NULL )
			{
				if ( m_ed_NegVal[iLine]->Validate(true) == false )
				{
					m_ed_NegVal[iLine]->SetFocus();
					return false;
				}
			}
		}
		
		iLine++;
	}
	
	return true;
}

/*------------------------------------------------------------------------*/
int  CUpdateFromExcelView::SpeichereSatz( ) 
{
	char cHeader[MAX_SPALTE + 2];
	CString cSpaltenHeader;
    UpdateData( TRUE );

	if ( !EndValidate( ) )
		return -1;
	
	m_ed_PznCol.GetWindowText( cSpaltenHeader );
	cSpaltenHeader.TrimRight();
	if ( cSpaltenHeader.IsEmpty() )
	{
		if (m_eUpdTable == UPD_CDISCOUNT_STOP && 
			MsgBoxYesNo( "Sollen Rabatte wirklich ohne Angabe einer PZN beendet werden?", MB_ICONQUESTION | MB_DEFBUTTON1 ) == IDYES) // beenden von Rabatten auch ohne PZN erlaubt!
			cSpaltenHeader = "-9999";
		else if (!(m_eUpdTable == UPD_MEDICALACTOR))
		{
			MsgBoxOK( "Überschrift der PZN-Spalte darf nicht leer sein" ); 
			return 0;
		}
	}

	if ( ! theApp->YouWantToDo( "Aktion durchführen ?" ) ) 
		return -1;

	strcpy( cHeader, cSpaltenHeader );

	for ( int i = 0; i < ANZ_FELDER_UPD; i++ )
	{
		ST_LineVal[i]->csUpdateCol = "";
	}

	GetCtrlValues();

	CString cErrmld;
	long nAnz;
	if ( ExtractFromCsv( cErrmld, cHeader, &nAnz ) )
	{
		if (nAnz > 0)
		{
			cErrmld.Format("%ld Zeilen wurden ausgelesen und auf dem Server abgelegt!\nSollen die Werte jetzt in die Stammdaten übertragen werden?", nAnz);

			if (MsgBoxYesNo(cErrmld) == IDNO)
				return -1;
		}
		else /* no relevant entries in the csv-file */
		{
			cErrmld.Format("%ld Zeilen wurden ausgelesen!\nEs erfolgt kein Update.", nAnz);

			MsgBoxOK(cErrmld);

			return -1;
		}
	}
	else
	{
		if ( cErrmld.IsEmpty() )
		{
			cErrmld = "Die CSV-Datei wurde nicht vollständig gelesen bzw. geschrieben!";
		}

		MsgBoxOK( cErrmld );

		return -1;
	}	

	if ( m_eUpdTable == UPD_CDISCOUNT_STOP )
	{
		if ( CallUnxBatch( cErrmld, 1 ) )
		{
			cErrmld += "\nSollen die Daten übernommen werden?";
			
			if ( MsgBoxYesNo( cErrmld, MB_ICONQUESTION | MB_DEFBUTTON1 ) == IDNO )
				return 0;
		}
		else
		{
			cErrmld += "\nFehler beim zputil- Testlauf!";
			MsgBoxOK( cErrmld );
			return -1;
		}
	}

	// Aufruf Batch
	if ( CallUnxBatch( cErrmld, 0 ) )
	{
		if (strcmp(ST_LineVal[0]->csUpdateCol, "Baselist ID (A to Z)") != 0)
		{
		cErrmld += "\nSpeicherung erfolgreich!";
		}
		MsgBoxOK( cErrmld );
	}
	else
	{
		if ( cErrmld.IsEmpty() )
		{
			cErrmld = "Allgemeiner Fehler beim Update auf die Tabelle!";
		}

		MsgBoxOK( cErrmld );
		
		return -1;
	}

	return 0;
}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::GetCtrlValues()
{
	CString csHelp;

	for ( int i = 0; i < m_nAnzRows; i++ )
	{
		//------------
		m_ed_UpdCol[i]->GetWindowText(csHelp);
		ST_LineVal[i]->csUpdateCol = csHelp;

		//------------ 
		if ( m_ck_StaticVal[i]->GetCheck() == CK_CLICKED )
			ST_LineVal[i]->bTakeCsvCol = true;
		else
			ST_LineVal[i]->bTakeCsvCol = false;

		//------------
		if ( m_ed_StatVal[i] != NULL )
		{
			m_ed_StatVal[i]->GetWindowText(csHelp);
			if ( csHelp.IsEmpty() && ST_LineVal[i]->bTakeCsvCol == true )
			{
				m_ed_StatVal[i]->SetFocus();
				MsgBoxOK ( "Spalten-Überschriften dürfen nicht leer sein!" );
				return false;
			}
		}
		else if ( m_bt_StatVal[i] != NULL )
		{
			if ( m_bt_StatVal[i]->GetCheck() == CK_CLICKED )
				csHelp = "1";
			else
				csHelp = "0";
		}
		else
		{
			m_cb_StatVal[i]->GetLBText(m_cb_StatVal[i]->GetCurSel(), csHelp);
		}
		ST_LineVal[i]->csCsvCol_StatVal = csHelp;

		//------------
		if ( m_ck_NegRest[i]->GetCheck() == CK_CLICKED )
		{
			ST_LineVal[i]->bNegRest = true;
			if ( m_ed_NegVal[i] != NULL )
			{
				m_ed_NegVal[i]->GetWindowText(csHelp);
			}
			else if ( m_bt_NegVal[i] != NULL )
			{
				if ( m_bt_NegVal[i]->GetCheck() == CK_CLICKED )
					csHelp = "1";
				else
					csHelp = "0";
			}
			else
			{
				m_cb_NegVal[i]->GetLBText(m_cb_NegVal[i]->GetCurSel(), csHelp);
			}
			ST_LineVal[i]->csNegVal = csHelp;
		}
		else
		{
			ST_LineVal[i]->bNegRest = false;
			ST_LineVal[i]->csNegVal = "";
		}
	}

	return true;
}


/*------------------------------------------------------------------------*/
int  CUpdateFromExcelView::UndoSatz()
{
	return 0;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtZArtikel()
{
	char dat[12];
	PHODATE date;
	date = GetPhoDate();
	ConvFromPhoDate(dat, date, "tt.mm.jjjj");
	
	ShowPZNField(true);

	m_eUpdTable = UPD_ZARTIKEL;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}

	for (int i=0; i < m_nAnzF && m_PflFelder[i]->iAktiv != 0; i++) {
		if (0 == strcmp(m_PflFelder[i]->cName, "MWE-Datum"))
		{
			// preselect and inactivate fields for "datum_mwe"
			m_ck_StaticVal[i]->SetCheck(0);
			m_ck_StaticVal[i]->EnableWindow(false);
			CkStatValClicked();
			m_ed_StatVal[i]->SetWindowText((LPCTSTR) dat);  // auf aktuellen Tag setzen
			m_ed_StatVal[i]->EnableWindow(false);
			m_ck_NegRest[i]->EnableWindow(false);
		}
	}

}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBnClickedBtZChargenRR()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_ZCHARGENRR;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtZArtPreis()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_ZARTPREIS;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCimexblock()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_CIMEXBLOCK;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCDiscGrpMem()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_CDISCGRPMEM;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCArtComPack()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_CARTCOMPACK;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCountry()
{
	ShowPZNField(true);
	
	m_eUpdTable = NONE;

	if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "ifr21"	||
		 ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "ifr21pre" )
	{
		m_eUpdTable = UPD_ZARTFRANCE;
	}

	if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "ich21" ||
		 ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "ich21pre")
	{
		m_eUpdTable = UPD_ZARTSWITZERLAND;
	}

	if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "irs21" )
	{
		m_eUpdTable = UPD_ZARTSERBIA;
	}
	
	if ( ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "iat21" ||
		 ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() == "iat21pre")
	{
		m_eUpdTable = UPD_ZARTAUSTRIA;
	}
	
	if (m_eUpdTable == NONE) 
	{
		MsgBoxOK("Aktuell keine spezielle Unterstützung für dieses Land!");
		return;
	}

	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCodes()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_CARTICLECODES;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtArtVe()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_ARTVE;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCibt()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_CIBT;

	if (IsCountry("D"))
	{
		m_PflFeldDlg.InitPflege(m_eUpdTable);

		if (m_PflFeldDlg.DoModal() == IDOK)
		{
			m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
			GenMaske();
		}
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtEAN()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_EAN;

	m_PflFeldDlg.InitPflege(m_eUpdTable);

	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();

		if (0 == strcmp(m_PflFelder[0]->cName, "EAN-Nr. löschen"))
		{
			// preselect and inactivate fields for "EAN-Nr. löschen"
			m_ck_StaticVal[0]->SetCheck(0);
			m_ck_StaticVal[0]->EnableWindow(false);
			CkStatValClicked();
			m_bt_StatVal[0]->SetCheck(CK_CLICKED);
			m_bt_StatVal[0]->EnableWindow(false);
			m_ck_NegRest[0]->EnableWindow(false);
		}
	}
}

/*------------------------------------------------------------------------*/

void CUpdateFromExcelView::OnBtSubsequentDelivery()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_KONTMENGENST;

	m_PflFeldDlg.InitPflege(m_eUpdTable);

	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();

		const int iUserIdx = 2;
		const int iBrachnoIdx = 0;

		if (0 == strcmp(m_PflFelder[iUserIdx]->cName, "User"))
		{
			m_ck_StaticVal[iBrachnoIdx]->SetCheck(0);         
			m_ck_StaticVal[iBrachnoIdx]->EnableWindow(false);

			m_ck_StaticVal[iUserIdx]->SetCheck(0);
			m_ck_StaticVal[iUserIdx]->EnableWindow(false);

			CkStatValClicked();

			m_ed_StatVal[iUserIdx]->SetMask(ED_CHAR, ED_LOWER, 35, new ChMaskChar);
			m_ed_StatVal[iUserIdx]->SetWindowTextA(((CZdpUtilApp*)AfxGetApp())->GetUserName()); //("MyUser");
			m_ed_StatVal[iUserIdx]->EnableWindow(false);

			m_ck_NegRest[iUserIdx]->EnableWindow(false);
		}
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtZArtWg()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_ZARTWG;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

void CUpdateFromExcelView::OnBtZArtWg5AG()
{
	if (!(IsCountry("D")))
	{
		MsgBoxOK("\n Function only available for Germany");
		return;
	}

	ShowPZNField(true);

	m_eUpdTable = UPD_ZARTWG_5AG;

	m_PflFeldDlg.InitPflege(m_eUpdTable);

	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();
	}
}

void CUpdateFromExcelView::OnBtBliesort()
{
	if (!(IsCountry("D") || IsCountry("HR") || IsCountry("F")))
	{
		MsgBoxOK("\n Function is not available for this country!");
		return;
	}

	ShowPZNField(true);

	m_eUpdTable = UPD_BLIESORT;

	m_PflFeldDlg.InitPflege(m_eUpdTable);

	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();
	}
}

void CUpdateFromExcelView::OnBtBaselist()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_BASELISTARTICLES;

	m_PflFeldDlg.InitPflege(m_eUpdTable);

	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCartmedactor()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_ARTMEDACTOR;

	m_PflFeldDlg.InitPflege(m_eUpdTable);

	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCmedicalactor()
{
	ShowPZNField(false);

	m_eUpdTable = UPD_MEDICALACTOR;

	m_PflFeldDlg.InitPflege(m_eUpdTable);


	if (m_PflFeldDlg.DoModal() == IDOK)
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo(m_PflFelder);
		if (0 == m_nAnzF)
			return;

		GenMaske();
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCDiscountFlexible()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_CDISCOUNT_FLEXIBLE;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCGiBatchEntry()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_CGIBATCHENTRY;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCDiscountEnd()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_CDISCOUNT_STOP;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnBtCDiscount()
{
	ShowPZNField(true);

	m_eUpdTable = UPD_CDISCOUNT;

	// insert all discounts in given csv-file (defined structure!!!) to cdiscount

	CString cQuestion;
	cQuestion = "Soll das Ende-Datum bestehender Rabatte zurückgesetzt werden?";

	if ( MsgBoxYesNo( cQuestion, MB_ICONQUESTION | MB_DEFBUTTON1 ) == IDYES )
		m_Reset_CDiscount_DateTo = true;
	else
		m_Reset_CDiscount_DateTo = false;

	if ( ! theApp->YouWantToDo( "Aktion durchführen ?" ) ) 
		return;


	CString cErrmld;
	long nAnz = 0;
	
// copy data from txt-file (without headers) to unix
	if ( ExtractFromTxt( cErrmld, &nAnz ) )
	{
		cErrmld.Format( "%ld Zeilen wurden ausgelesen und auf dem Server abgelegt!\nSollen die Werte jetzt in die Stammdaten übertragen werden?", nAnz );
		
		if ( MsgBoxYesNo( cErrmld ) == IDNO )
			return;
	}
	else
	{
		if ( cErrmld.IsEmpty() )
		{
			cErrmld = "Die CSV-Datei wurde nicht vollständig gelesen bzw. geschrieben!";
		}

		MsgBoxOK( cErrmld );

		return;
	}	
	
	
// Aufruf Batch
	if ( CallUnxBatch( cErrmld, 0 ) )
	{
		cErrmld += "\nSpeicherung erfolgreich!";
	}
	else
	{
		if ( cErrmld.IsEmpty() )
		{
			cErrmld = "Allgemeiner Fehler beim Update auf die Tabelle!";
		}
	}

	MsgBoxOK( cErrmld );
	
}

/*------------------------------------------------------------------------*/
bool CUpdateFromExcelView::ExtractFromTxt( CString &cErrmld, long *nAnz ) 
{
// TXT
	bool bOk;
	long anz;
	char mld[200];
	CString cZeile;
	CString cItem;
	CExcelCsv Etxt;

	bool bFirst;

// UNIX
	CString cDirec;
//	#define MAX_BUF 2048
//	char buf[ MAX_BUF + 1 ];
	int  unx_fd;

	cErrmld.Empty();
	
// Input TXT
	char BASED_CODE szFilter[] = 
		 "Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, "txt",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return false;

	CString sFileName;
	sFileName = dlg.GetPathName();	
	if ( sFileName.IsEmpty( ) || dlg.GetFileName( ).Find(' ') != -1 )
		return false;
	
	long s = GetWWSDateiUnterVerz(cDirec, util, cErrmld);
	
	/* Output UNIX
	if ( UnxGetenv ( "WWS", buf ) != 0 )
	{
		cErrmld  = "Umgebungsvariable $WWS auf Server unbekannt\n";
		cErrmld += DynErrmld();
		return false;
	}

	cDirec  = buf;
	cDirec += _T( "/daten/zdputil/" );*/

	if ( s != 0 )
		return false;

	cDirec += dlg.GetFileName( );

	m_UnxDirectory = cDirec;

	bOk = true;
	bFirst = true;

	anz = 0;

	theApp->BeginWaitAction();

	if ( Etxt.OpenDatei((LPCTSTR )sFileName, mld ) >= 0 )
	{
		int ret = 0;

		// Unix- File öffnen
		if ( UnxFopen( &unx_fd, m_UnxDirectory, "w" ) != 0 )
		{
			cErrmld.Format( "%s\n %s )", m_UnxDirectory, DynErrmld() );
			bOk =  false;
		}
		else
		{
			// Unix- Header schreiben (Rücksetzen date-to !?)
			CString csHeaderLines;
			bOk = CreateHeaderLines( csHeaderLines ); 

			if ( bOk == true && UnxFwrite( unx_fd, (LPCTSTR) csHeaderLines, csHeaderLines.GetLength() ) != 0 )
			{
				cErrmld.Format( "%s\n %s )", m_UnxDirectory, DynErrmld() );
				bOk = false;
			}

			while ( ret == 0 && bOk )
			{
			// Txt- Zeilen lesen
			// Txt- Spalten lesen + validieren
				ret = Etxt.ReadColValuesForCDiscount( cItem, mld );
				if ( ret == 0 && !cItem.IsEmpty() )
				{
					// Unix- Zeilen schreiben
					cItem += "\n";

					if ( UnxFwrite( unx_fd, (LPCTSTR) cItem, cItem.GetLength() ) != 0 )
					{
						cErrmld.Format( "%s\n %s )", m_UnxDirectory, DynErrmld() );
						bOk = false;
					}
					anz++;
				}
				else if ( ret > 1 )
				{
					cErrmld = mld;
					cErrmld.Append("\nEs wurde kein Datensatz gespeichert!");
					bOk = false;
				}
			}
		
			// Unix- File schließen
			UnxFclose( unx_fd );
		}
	}
	else
	{
		cErrmld = mld;
		bOk = false;
	}

	theApp->EndWaitAction();

	*nAnz = anz;

	return bOk;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::HideControls()
{
	m_ed_Muster.ShowWindow( SW_HIDE );
	m_ck_Muster.ShowWindow( SW_HIDE );
	m_cb_Muster.ShowWindow( SW_HIDE );
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::GenMaske(  )
{
	int i;

	m_dlg.Reset( );

	for ( i = 0; i < m_nAnzRows; i++ )
	{
		m_ed_UpdCol[i]->ShowWindow( SW_HIDE );
        delete m_ed_UpdCol[i];
		m_ed_UpdCol[i] = NULL;
	
		m_ck_StaticVal[i]->ShowWindow( SW_HIDE );
        delete m_ck_StaticVal[i];
		m_ck_StaticVal[i] = NULL;
	
		m_ck_NegRest[i]->ShowWindow( SW_HIDE );
		delete m_ck_NegRest[i];
		m_ck_NegRest[i] = NULL;

		m_i_CkStatVal[i] = 0;
		m_i_CkNegRest[i] = 0;

		if ( m_ed_StatVal[i] != NULL )
		{
			m_ed_StatVal[i]->ShowWindow( SW_HIDE );
			delete m_ed_StatVal[i];
			m_ed_StatVal[i] = NULL;
		}

		if ( m_bt_StatVal[i] != NULL )
		{
			m_bt_StatVal[i]->ShowWindow( SW_HIDE );
			delete m_bt_StatVal[i];
			m_bt_StatVal[i] = NULL;
		}
	
		if ( m_cb_StatVal[i] != NULL )
		{
			m_cb_StatVal[i]->ShowWindow( SW_HIDE );
			delete m_cb_StatVal[i];
			m_cb_StatVal[i] = NULL;
		}
	
		if ( m_ed_NegVal[i] != NULL )
		{
			m_ed_NegVal[i]->ShowWindow( SW_HIDE );
			delete m_ed_NegVal[i];
			m_ed_NegVal[i] = NULL;
		}
	
		if ( m_bt_NegVal[i] != NULL )
		{
			m_bt_NegVal[i]->ShowWindow( SW_HIDE );
			delete m_bt_NegVal[i];
			m_bt_NegVal[i] = NULL;
		}
	
		if ( m_cb_NegVal[i] != NULL )
		{
			m_cb_NegVal[i]->ShowWindow( SW_HIDE );
			delete m_cb_NegVal[i];
			m_cb_NegVal[i] = NULL;
		}		
	}

	m_nAnzRows	= 0;

	HideControls();

	if ( m_nAnzF == 0 ) 
		return;		

	m_Pos_Top = m_dlg.GetFieldNumber();
	
	GenTabelle( );	

	GotoTop();
}


/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::GenTabelle( )
{
	int i;
	for ( i = 0; i < m_nAnzF; i++ )
	{
		if ( i <= ANZ_FELDER_UPD )
			GenFelder( );
		else
			break;

		m_nAnzRows++;
	}
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::GenFelder( )
{
	BOOL bOK;

	//Update-Spalte
	if ( m_nAnzRows == 0 )
		bOK = GenColNameFeld( &m_st_Column);
	else
		bOK = GenColNameFeld( m_ed_UpdCol[ m_nAnzRows - 1 ] );
	
	
	if ( bOK )
	{// Festwert oder aus CSV?
		if ( m_nAnzRows == 0 )
			bOK = GenCkStatVal( &m_st_CkStatVal);
		else
			bOK = GenCkStatVal( m_ck_StaticVal[ m_nAnzRows - 1 ] );
	}
	
 
	// zu Beginn nur Edit-Feld für Spaltenname
	if ( bOK )
	{
		if ( m_nAnzRows == 0 )
			bOK = GenEditFeld( m_nAnzRows, &m_st_CkStatVal, false, true );
		else
			bOK = GenEditFeld( m_nAnzRows, m_ck_StaticVal[ m_nAnzRows - 1 ], false, true );
	}

	if ( bOK )
	{// Rest negieren?
		if ( m_nAnzRows == 0 )
			bOK = GenCkRestNeg ( &m_st_CkRestNeg );
		else
			bOK = GenCkRestNeg ( m_ck_NegRest[ m_nAnzRows - 1 ] );
	}

	// zu Beginn kein Feld für negierten Wert

	if ( !bOK )
		MsgBoxOK( "Fehler beim Erzeugen eines Dialogfeldes" );
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::GenColNameFeld( CWnd *pWndAbove )
{
	BOOL bOk;
	CRect Rect;
	CRect RectColName;

	ChDlgEdit* pWnd;
	pWnd = new ChDlgEdit;

	pWndAbove->GetWindowRect( Rect );
	m_st_Column.GetWindowRect( RectColName );

	int nHeigh  = Rect.bottom - Rect.top;

	Rect.top    += 140 * nHeigh / 100;   
	Rect.bottom += 140 * nHeigh / 100;  
	Rect.left   = RectColName.left;
	Rect.right  = RectColName.right; 
	ScreenToClient( Rect );

	bOk = pWnd->Create( m_ed_Muster.GetStyle( ),
					    Rect,					 
						this,					
						IDC_OFFSET_EDIT + m_nAnzRows);
	if ( bOk )
	{
		GenFont ( pWnd );
		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );

		pWnd->SetWindowText( m_PflFelder[m_nAnzRows]->cName );
		
		pWnd->SetDialog( );
		pWnd->SetValidation( FALSE );
		m_ed_UpdCol[m_nAnzRows] = pWnd;
		pWnd->EnableWindow(false);

		m_dlg.InitDialog( *pWnd );
	}
	return bOk;
}


/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::GenEditFeld( int iLine, CWnd *pWndAbove, bool bEdNegVal, bool bCsvCol )
{
	BOOL bOk;
	CRect Rect;
	CRect RectAbove;

	ChDlgEdit* pWnd;
	pWnd = new ChDlgEdit;
	CUpdateFromExcelView* pThisView = this;
	EDIT_MASK* CM;

	if ( bCsvCol ) 
		CM = NULL;
	else
		CM = ( EDIT_MASK* )m_PflFelder[iLine]->pRef1;

	pWndAbove->GetWindowRect( Rect );
	
	int nHeigh  = Rect.bottom - Rect.top;
	
	if ( bEdNegVal == false)
	{
		m_st_StatCsvVal.GetWindowRect( RectAbove );
		Rect.top    += 140 * nHeigh / 100;   
		Rect.bottom += 140 * nHeigh / 100; 
	}
	else
	{
		m_st_RestVal.GetWindowRect( RectAbove );
		Rect.top    += (140 * nHeigh / 100 ) * (iLine + 1);   
		Rect.bottom += (140 * nHeigh / 100 ) * (iLine + 1); 
	}
	
	Rect.left   = RectAbove.left;
	Rect.right  = RectAbove.right;
 
	ScreenToClient( Rect );


	DWORD dwStyle = m_ed_Muster.GetStyle();
	if ( CM != NULL && ( CM->nStyle & ED_RIGHT ) )
		dwStyle |= ES_RIGHT | ES_MULTILINE | ES_AUTOHSCROLL;
	
	bOk = pWnd->Create( dwStyle,
					    Rect,					 
						this,					
						IDC_OFFSET_EDIT + iLine );
	if ( bOk )
	{
		GenFont ( pWnd );
		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );
		
		if ( CM == NULL )
		{
			pWnd->SetMask( ED_CHAR,
						   ED_UPPER,
						   20,
						   new ChMaskChar );

			pWnd->SetDialog( );
			pWnd->SetValidation( FALSE );
		}
		else
		{
			static double	pDData1 = 0.0;
			static double	pDData2 = 0.0;
			static double	pDData3 = 0.0;
					
			switch ( CM->nType )
			{
			case ED_CHAR:
				pWnd->SetMask( CM->nType, 
							   CM->nStyle, 
							   CM->nTextLen,
							   NewMask( CM->nNrMask ),
							   NewValidate( CM->nNrVal, pThisView, pWnd ) );			   
				break;

			case ED_DBL:
				// only for prices:
				if ( iLine == 1 )
				{
					pWnd->SetMask( CM->nType, 
							   CM->nStyle, 
							   &pDData1,	
							   CM->nTextLen,
							   CM->nNachKomma,
							   NewMask( CM->nNrMask ),
							   NewValidate( CM->nNrVal, pThisView, pWnd ) );
				}
				else if ( iLine == 2 )
				{
					pWnd->SetMask( CM->nType, 
							   CM->nStyle, 
							   &pDData2,	
							   CM->nTextLen,
							   CM->nNachKomma,
							   NewMask( CM->nNrMask ),
							   NewValidate( CM->nNrVal, pThisView, pWnd ) );
				}
				else
				{
					pWnd->SetMask( CM->nType, 
							   CM->nStyle, 
							   &pDData3,	
							   CM->nTextLen,
							   CM->nNachKomma,
							   NewMask( CM->nNrMask ),
							   NewValidate( CM->nNrVal, pThisView, pWnd ) );
				}
				break;

			case ED_LONG:
			case ED_LDATE:
				pWnd->SetMask( CM->nType, 
							   CM->nStyle,
							   CM->nTextLen,
							   NewMask( CM->nNrMask ),
							   NewValidate( CM->nNrVal, pThisView, pWnd ) );	 
				break;

			case ED_SHORT:
				pWnd->SetMask( CM->nType, 
							   CM->nStyle,
							   CM->nTextLen,
							   NewMask( CM->nNrMask ),
							   NewValidate( CM->nNrVal, pThisView, pWnd ) );	
				break;
			}

			pWnd->SetDialog( );
			pWnd->SetValidation( TRUE );
		}
		
		if ( bEdNegVal == false )
			m_ed_StatVal[iLine] = pWnd;
		else
			m_ed_NegVal[iLine] = pWnd;

		m_dlg.InitDialog( *pWnd );
	}
	return bOk;
}


/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::GenButtonFeld( int iLine, CWnd *pWndAbove, bool bEdNegVal )
{
	BOOL bOk;
	CRect Rect;
	CRect RectAbove;

	ChDlgButton* pWnd;
	pWnd = new ChDlgButton;
	CUpdateFromExcelView* pThisView = this;
	
	pWndAbove->GetWindowRect( Rect );
	
	int nHeigh  = Rect.bottom - Rect.top;
	
	if ( bEdNegVal == false)
	{
		m_st_StatCsvVal.GetWindowRect( RectAbove );
		Rect.top    += 140 * nHeigh / 100;   
		Rect.bottom += 140 * nHeigh / 100; 
	}
	else
	{
		m_st_RestVal.GetWindowRect( RectAbove );
		Rect.top    += (140 * nHeigh / 100 ) * (iLine + 1);   
		Rect.bottom += (140 * nHeigh / 100 ) * (iLine + 1); 
	}
	
	Rect.left   = RectAbove.left;
	Rect.right  = RectAbove.right;
 
	ScreenToClient( Rect );
	
	
	bOk = pWnd->Create( m_PflFelder[iLine]->cName,     
					    m_ck_Muster.GetStyle( ),
						Rect, 
						this, 
						IDC_OFFSET_BUTTON + iLine );
	if ( bOk )
	{
		GenFont ( pWnd );
		pWnd->ShowWindow( SW_SHOW );

		pWnd->SetMask('1', '0', "" );
		pWnd->SetDialog( );
		
		
		if ( bEdNegVal == false )
			m_bt_StatVal[iLine] = pWnd;
		else
			m_bt_NegVal[iLine] = pWnd;
		
		m_dlg.InitDialog( *pWnd );
	}

	return bOk;
}

//--------------------------------------------------------------------//
class CV_CkStatVal : public ChValBase
{
public:
	CV_CkStatVal( CUpdateFromExcelView* pWnd ) : ChValBase( pWnd ){};
	void PostProc( )
	{
		((CUpdateFromExcelView*)m_pWnd)->CkStatValClicked( );
	}
};

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::GenCkStatVal( CWnd *pWndAbove )
{
	BOOL bOk;
	CRect Rect;
	CRect RectCkStatVal;

	ChDlgButton* pWnd;
	pWnd = new ChDlgButton;
	
	pWndAbove->GetWindowRect( Rect );
	m_st_CkStatVal.GetWindowRect( RectCkStatVal );

	int nHeigh  = Rect.bottom - Rect.top;

	Rect.top    += 140 * nHeigh / 100;   
	Rect.bottom += 140 * nHeigh / 100;  
	Rect.left   = RectCkStatVal.left;
	Rect.right  = RectCkStatVal.right; 
	ScreenToClient( Rect );

	bOk = pWnd->Create( "Wert aus CSV-Datei",
						m_ck_Muster.GetStyle( ),
					    Rect,					 
						this,					
						IDC_OFFSET_BUTTON + m_nAnzRows);

	if ( bOk )
	{
		GenFont ( pWnd );
		pWnd->ShowWindow( SW_SHOW );

		pWnd->SetMask('1', '0', "", 0, new CV_CkStatVal( this ) );
		pWnd->SetDialog( );
		m_ck_StaticVal[m_nAnzRows] = pWnd;
		m_ck_StaticVal[m_nAnzRows]->SetCheck(CK_CLICKED);
		m_i_CkStatVal [m_nAnzRows] = CK_CLICKED;
		m_dlg.InitDialog( *pWnd );

	}

	return bOk;
}

//--------------------------------------------------------------------//
class CV_CkRestNeg : public ChValBase
{
public:
	CV_CkRestNeg( CUpdateFromExcelView* pWnd ) : ChValBase( pWnd ){};
	void PostProc( )
	{
		((CUpdateFromExcelView*)m_pWnd)->CkRestNegClicked( );
	}
};

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::GenCkRestNeg( CWnd *pWndAbove )
{
	BOOL bOk;
	CRect Rect;
	CRect RectCkRestNeg;
	
	ChDlgButton* pWnd;
	pWnd = new ChDlgButton;
	
	pWndAbove->GetWindowRect( Rect );
	m_st_CkRestNeg.GetWindowRect( RectCkRestNeg );

	int nHeigh  = Rect.bottom - Rect.top;

	Rect.top    += 140 * nHeigh / 100;   
	Rect.bottom += 140 * nHeigh / 100;  
	Rect.left   = RectCkRestNeg.left;
	Rect.right  = RectCkRestNeg.right; 
	ScreenToClient( Rect );

	bOk = pWnd->Create( "Rest negieren",     
					    m_ck_Muster.GetStyle( ),
						Rect, 
						this, 
						IDC_OFFSET_BUTTON + m_nAnzRows );

	if ( bOk )
	{
		GenFont ( pWnd );
		pWnd->ShowWindow( SW_SHOW );

		pWnd->SetMask('1', '0', "", 0, new CV_CkRestNeg( this ) );
		pWnd->SetDialog( );
		m_ck_NegRest[m_nAnzRows] = pWnd;
		m_dlg.InitDialog( *pWnd );
	}

	// keine Negierung
	if ( m_eUpdTable == UPD_ZARTWG || m_eUpdTable == UPD_ZARTPREIS || m_eUpdTable == UPD_CARTICLECODES || m_eUpdTable == UPD_CIMEXBLOCK || 
		 m_eUpdTable == UPD_ARTVE || m_eUpdTable == UPD_CDISCGRPMEM || m_eUpdTable == UPD_CARTCOMPACK || m_eUpdTable == UPD_ZCHARGENRR ||
		 m_eUpdTable == UPD_EAN || m_eUpdTable == UPD_CIBT || m_eUpdTable == UPD_KONTMENGENST || m_eUpdTable == UPD_ZARTWG_5AG || m_eUpdTable == UPD_BLIESORT || 
		 m_eUpdTable == UPD_BASELISTARTICLES || m_eUpdTable == UPD_MEDICALACTOR || m_eUpdTable == UPD_ARTMEDACTOR)
		pWnd->EnableWindow(false);
	
	return bOk;
}


/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::GenComboBoxFeld( int iLine, CWnd *pWndAbove, bool bEdNegVal )
{
	BOOL bOk;
	CRect Rect;
	CRect RectAbove;

	ChDlgComboBox* pWnd;
	pWnd = new ChDlgComboBox;
	CUpdateFromExcelView* pThisView = this;

	COMBO_MASK* CM;
	CM = ( COMBO_MASK* )m_PflFelder[iLine]->pRef1;

	pWndAbove->GetWindowRect( Rect );
	
	int nHeigh  = Rect.bottom - Rect.top;
	
	if ( bEdNegVal == false)
	{
		m_st_StatCsvVal.GetWindowRect( RectAbove );
		Rect.top    += 140 * nHeigh / 100;   
		Rect.bottom += 140 * nHeigh / 100; 
	}
	else
	{
		m_st_RestVal.GetWindowRect( RectAbove );
		Rect.top    += (140 * nHeigh / 100 ) * (iLine + 1);   
		Rect.bottom += (140 * nHeigh / 100 ) * (iLine + 1); 
	}
	
	Rect.left   = RectAbove.left;
	Rect.right  = RectAbove.right;
 
	ScreenToClient( Rect );

	
	Rect.bottom +=
		AnzComboDaten( CM->cTexte ) * ( Rect.bottom - Rect.top );
	
	DWORD dwStyle = m_cb_Muster.GetStyle();
	if (m_eUpdTable == UPD_KONTMENGENST)
	{
		dwStyle &= ~CBS_DROPDOWN;
		dwStyle &= ~CBS_SORT;
		dwStyle |= CBS_DROPDOWNLIST; // it is only possible to select a value from the dropdown list, no manual editing possible 
	}

	bOk = pWnd->Create( dwStyle,
						Rect,
						this, 
						IDC_OFFSET_COMBO + iLine );
	if ( bOk )
	{
		GenFont  ( pWnd );
		FillCombo( pWnd, CM->cTexte );
		pWnd->ShowWindow( SW_SHOW );

		pWnd->SetMask( CM->cWerte, CM->nBufLen, "", CM->nDefaultPos );
		pWnd->SetDialog( );
		
		if ( bEdNegVal == false )
			m_cb_StatVal[iLine] = pWnd;
		else
			m_cb_NegVal[iLine] = pWnd;

		m_dlg.InitDialog( *pWnd );
	}
	return bOk;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::GenFont( CWnd *pWnd )
{
	CWnd* m_pWndParent = this;
	CFont* pDlgFont = (CFont*)m_pWndParent->GetFont();
	pWnd->SetFont(pDlgFont);
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::FillCombo( CComboBox *pWnd, char *str1 )
{
	int i;
	int anz;
	char *anf;
	char *str;	
	if ( pWnd == NULL ) return;

	str = (char *) malloc( strlen(str1) + 1 );

	if ( str == NULL )
		return;


	strcpy( str, str1 );

	pWnd->ResetContent( );

	anz = 0;
	i = 0;
	while ( str[i] )
	{
		anf = &str[i];
		while ( str[i] && str[i] != '\n' ) i++;
		if ( str[i] == '\n' )
		{
			str[i] = '\0';			
			pWnd->AddString( anf );
			str[i] = '\n';
			i++;
		}
		else
		{
			pWnd->AddString( anf );
		}
		anz++;
	}

	free( str );	

	pWnd->SetCurSel( 0 );

}

/*------------------------------------------------------------------------*/
int CUpdateFromExcelView::AnzComboDaten( char *str )
{
	int i;
	int anz;

	anz = 0;
	i = 0;
	
	while ( str[i] )
	{
		while ( str[i] && str[i] != '\n' ) 
			i++;

		if ( str[i] == '\n' )
			i++;
		
		anz++;
	}

	return anz;
}

/*------------------------------------------------------------------------*/
ChMaskBase* CUpdateFromExcelView::NewMask( int nMaskNumber )
{
	switch ( nMaskNumber )
	{
	case NR_MASKBINAER:
		return new ChMaskBinaer;
		break;
	case NR_MASKBUBL:
		return new ChMaskBuBl;
		break;
	case NR_MASKCHAR: 
		return new ChMaskChar;
		break;
	case NR_MASKLDATE:  
		return new ChMaskLDate;
		break;
	case NR_MASKSDATE:   
		return new ChMaskSDate;
		break;
	case NR_MASKDBL:	
		return new ChMaskDbl;
		break;
	case NR_MASKDBLPOS:	
		return new ChMaskDblPos;
		break;
	case NR_MASKINT:		
		return new ChMaskInt;
		break;
	case NR_MASKNUM:		
		return new ChMaskNum;
		break;
	}
	return NULL;
}

/*------------------------------------------------------------------------*/
class CV_AWL1 : public ChValBase
{
public:
	CV_AWL1( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestAwl1( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_ARTNRORIG : public ChValBase
{
public:
	CV_ARTNRORIG( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestArtNrOrig( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_1 : public ChValBase
{
public:
	CV_WG_ART_1( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt1( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_2 : public ChValBase
{
public:
	CV_WG_ART_2( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt2( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_3 : public ChValBase
{
public:
	CV_WG_ART_3( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt3( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_4 : public ChValBase
{
public:
	CV_WG_ART_4( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt4( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_5 : public ChValBase
{
public:
	CV_WG_ART_5( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt5( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_6 : public ChValBase
{
public:
	CV_WG_ART_6( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt6( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_7 : public ChValBase
{
public:
	CV_WG_ART_7( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt7( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_8 : public ChValBase
{
public:
	CV_WG_ART_8( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt8( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_9 : public ChValBase
{
public:
	CV_WG_ART_9( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArt9( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_A : public ChValBase
{
public:
	CV_WG_ART_A( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArtA( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_WG_ART_G : public ChValBase
{
public:
	CV_WG_ART_G( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestWgArtG( cs, bMeldung );
	}			
};

/*------------------------------------------------------------------------*/
class CV_BATCHENTRY_COMPANYCODE : public ChValBase
{
public:
	CV_BATCHENTRY_COMPANYCODE( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestCompanyCode( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_PREIS_GUELTIGAB : public ChValBase
{
public:
	CV_PREIS_GUELTIGAB( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestGueltab( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DATUM_AH : public ChValBase
{
public:
	CV_DATUM_AH( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDatumAh( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_PREIS_PREISE : public ChValBase
{
public:
	CV_PREIS_PREISE( CUpdateFromExcelView* pView, CEdit* pWnd, int nValNumber ) :
			ChValBase( pView, pWnd ), m_nValNr(nValNumber){};
	
	int m_nValNr;

	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestPrice( cs, bMeldung, m_nValNr );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_BASE_QTY : public ChValBase
{
public:
	CV_DISC_BASE_QTY( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDiscBaseQty( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_DATE_FROM : public ChValBase
{
public:
	CV_DISC_DATE_FROM( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDiscDateFrom( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_DATE_TO : public ChValBase
{
public:
	CV_DISC_DATE_TO( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDiscDateTo( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_PHARM_GRP : public ChValBase
{
public:
	CV_DISC_PHARM_GRP( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestPharmacyGroup( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_CUSTOMER : public ChValBase
{
public:
	CV_DISC_CUSTOMER( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDiscountCustomer( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_MANUFACTURER: public ChValBase
{
public:
	CV_MANUFACTURER( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestManufacturer( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_MANUFACTURER : public ChValBase
{
public:
	CV_DISC_MANUFACTURER( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDiscountManufacturer( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_ARTCODES_CODE : public ChValBase
{
public:
	CV_ARTCODES_CODE( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestArtCode( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_CODE_LPPR : public ChValBase
{
public:
	CV_CODE_LPPR( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestCodeLppr( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_REIMBURSEMENT_PERC : public ChValBase
{
public:
	CV_REIMBURSEMENT_PERC( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestReimbPct( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_CHARGE : public ChValBase
{
public:
	CV_CHARGE( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestCharge( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_COUNTRY : public ChValBase
{
public:
	CV_COUNTRY( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestCountry( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_RPG : public ChValBase
{
public:
	CV_DISC_RPG( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestDiscountGroup( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_DISC_ARTCAT : public ChValBase
{
public:
	CV_DISC_ARTCAT( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestArtCategory( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_ARTVE_VPE : public ChValBase
{
public:
	CV_ARTVE_VPE( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestArtVeVPE( cs, bMeldung );
	}
};

/*------------------------------------------------------------------------*/
class CV_PRISMAEWOCHE : public ChValBase
{
public:
	CV_PRISMAEWOCHE( CUpdateFromExcelView* pView, CEdit* pWnd ) :
			ChValBase( pView, pWnd ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		CString cs;
		m_pWnd1->GetWindowText(cs);
		return ((CUpdateFromExcelView*)m_pWnd)->TestPrismaEWoche( cs, bMeldung );
	}
};



/*------------------------------------------------------------------------*/
ChValBase* CUpdateFromExcelView::NewValidate( int nValNumber,
									 CUpdateFromExcelView *pThisView, ChDlgEdit* pWnd )
{
	switch ( nValNumber )
	{
	//-- zartikel --
	case VAL_AWL1:
		return new CV_AWL1( pThisView, pWnd  );
		break;

	case VAL_ART_NR_ORIG:
		return new CV_ARTNRORIG( pThisView, pWnd  );
		break;

	case VAL_HNR:
		return new CV_MANUFACTURER( pThisView, pWnd );
		break;

	case VAL_ART_DATUMAH:
	case VAL_DATETO_GI:
	case VAL_DATETO_CUSTRETURNS:
		return new CV_DATUM_AH( pThisView, pWnd );
		break;
	case VAL_PRISMAEWOCHE:
		return new CV_PRISMAEWOCHE(pThisView, pWnd);
		break;

	//-- zartwg --
	case VAL_WG_ART_1:
		return new CV_WG_ART_1( pThisView, pWnd );
		break;
	case VAL_WG_ART_2:
		return new CV_WG_ART_2( pThisView, pWnd );
		break;
	case VAL_WG_ART_3:
		return new CV_WG_ART_3( pThisView, pWnd );
		break;
	case VAL_WG_ART_4:
		return new CV_WG_ART_4( pThisView, pWnd );
		break;
	case VAL_WG_ART_5:
		return new CV_WG_ART_5( pThisView, pWnd );
		break;
	case VAL_WG_ART_6:
		return new CV_WG_ART_6( pThisView, pWnd );
		break;
	case VAL_WG_ART_7:
		return new CV_WG_ART_7( pThisView, pWnd );
		break;
	case VAL_WG_ART_8:
		return new CV_WG_ART_8( pThisView, pWnd );
		break;
	case VAL_WG_ART_9:
		return new CV_WG_ART_9( pThisView, pWnd );
		break;
	case VAL_WG_ART_A:
		return new CV_WG_ART_A( pThisView, pWnd );
		break;
	case VAL_WG_ART_G:
		return new CV_WG_ART_G( pThisView, pWnd );
		break;
	
	case VAL_BATCHENTRY_COMPANYCODE:
		return new CV_BATCHENTRY_COMPANYCODE( pThisView, pWnd );
		break;

	//-- zartpreis -- 
	case VAL_PREIS_GUELTIGAB:
	case VAL_BATCHENTRY_DATE:
		return new CV_PREIS_GUELTIGAB( pThisView, pWnd );
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
		return new CV_PREIS_PREISE( pThisView, pWnd, nValNumber );
		break;	

	case VAL_DISC_BASE_QTY:
		return new CV_DISC_BASE_QTY( pThisView, pWnd );
		break;

	case VAL_DISC_DATEFROM:
		return new CV_DISC_DATE_FROM( pThisView, pWnd );
		break;

	case VAL_DISC_DATETO:
		return new CV_DISC_DATE_TO( pThisView, pWnd );
		break;

	case VAL_DISC_PHARM_GRP:
	case VAL_DISC_PHARM_GRP_EXCL:
	case VAL_DISC_PHARM_GRP_EXCL2:
	case VAL_DISC_PHARM_GRP_EXCL3:
		return new CV_DISC_PHARM_GRP( pThisView, pWnd );
		break;

	case VAL_DISC_CUSTOMER:
		return new CV_DISC_CUSTOMER( pThisView, pWnd );
		break;

	case VAL_DISC_MANUFACTURER:
	case VAL_DISC_STOP_HNR:
		return new CV_DISC_MANUFACTURER( pThisView, pWnd );
		break;

	case VAL_DISC_RPG:
		return new CV_DISC_RPG( pThisView, pWnd );
		break;	

	case VAL_DISC_ARTCAT:
		return new CV_DISC_ARTCAT( pThisView, pWnd );
		break;	

	case VAL_ORIG_KART:
	case VAL_VPE1:
	case VAL_VPE2:
	case VAL_VPE3:
	case VAL_VPE4:
		return new CV_ARTVE_VPE( pThisView, pWnd );
		break;

	case VAL_ART_CODE:
		return new CV_ARTCODES_CODE( pThisView, pWnd );
		break;

	case VAL_ART_CODE_LPPR:
		return new CV_CODE_LPPR( pThisView, pWnd );
		break;

	case VAL_ART_REIMBURSEMENT_PERC:
		return new CV_REIMBURSEMENT_PERC( pThisView, pWnd );
		break;

	case VAL_CHARGE:
		return new CV_CHARGE( pThisView, pWnd );
		break;

	case VAL_IMEX_COUNTRY:
		return new CV_COUNTRY( pThisView, pWnd );
		break;

	default:
		break;
	}
	return NULL;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestArtVeVPE( CString csVPE, BOOL bMeldung )
{
	if ( /*!csVPE.IsEmpty() &&*/ (atoi(csVPE) < 0 || atoi(csVPE) > 99999 ))
	{
		if ( bMeldung ) 
			MsgBoxOK( "Eingabe für VPE nicht numerisch!" ); 

		return false;
	}
	return true;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestPZN( CString csPZN, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	int iStat;
	
	long Pzn;
	Pzn = atol(csPZN);
	
	if (Pzn == 0)
		return true;

	iStat = m_RD_ZARTIKEL.IPlausi( Pzn, Name, &Errmld);
	
	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDiscountGroup( CString csDiscGrp, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	long DiscGrp;
	DiscGrp = atol(csDiscGrp);

	if (m_eUpdTable == UPD_CDISCGRPMEM)
	{
		// wenn noch nicht existiert, dann automatisch anlegen!
		if (DiscGrp > 0 && DiscGrp <= 99999)
			return true;
		else
			iStat = 1;
	}
	else
	{
		if (DiscGrp == 0)
			return true;

		iStat = m_RD_CDISCGRP.IPlausi( DiscGrp, Name, &Errmld); 
	}
		
	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDiscountCustomer( CString csCustomer, BOOL bMeldung )
{
	int iStat = 0;

	if (atoi(csCustomer) == 0)
		return true;

	if (TestPruefZiffer7(atoi(csCustomer)) != 2)
		iStat = -1;

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( "Prüfziffer der IDF nicht korrekt!" );

	return iStat == 0; 
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestManufacturer(CString csManufacturer, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	CString PPE;
	CString cZentralppeList;

	long Hnr = atol(csManufacturer);

	iStat = m_RD_HERSTELLER.IPlausi( Hnr, Name, PPE, cZentralppeList, &Errmld);

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestPrismaEWoche(CString csPrimaEWoche, BOOL bMeldung)
{
	int iStat;
	CString Name;
	CString Errmld;

	short PrismaEWoche = atoi(csPrimaEWoche);

	iStat = m_RD_CPPEARTCATEGORY.IPlausi(PrismaEWoche, Name, &Errmld);

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDiscountManufacturer(CString csManufacturer, BOOL bMeldung )
{
	if (atol(csManufacturer) == 0)
		return true;

	return TestManufacturer(csManufacturer, bMeldung);
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestArtCategory(CString csArtCatNo, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	
	long CatNo = atol(csArtCatNo);

	if (CatNo == 0)
		return true;
	
	iStat = m_RD_CARTCAT.IPlausi( CatNo, Name, &Errmld );

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestPromo(CString csPromoNo, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	
	short PromoNo = atoi(csPromoNo);

	if (PromoNo == 0)
		return true;
	
	iStat = m_RD_CPROMOTIONS.IPlausi( PromoNo, Name, &Errmld );

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestPharmacyGroup( CString csPharmGrp, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	char Pgr [4];
	strcpy ( Pgr, csPharmGrp );
	

	if (strncmp(Pgr, "000", 3) == 0)
	{
		iStat = 0;
	}
	else
	{
		iStat = m_RD_CPHARMGRP.IPlausi( Pgr, Name, &Errmld);
	}

	if ( iStat >= 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestPct			( CString & csPct, BOOL bMeldung )
{
	double pct;
	pct = atof(csPct);

	if ( pct > 100.0 )
		return false;

	csPct.Replace(',','.');
	return true;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestArtCode( CString code, BOOL bMeldung )
{
	int iStat = 0;

	/* no possibility to distinguish between different code types here ...

	CString Name;
	CString Errmld;

	char artCode [L_CARTICLECODES_ARTICLE_CODE + 1];
	strcpy ( artCode, code );

	iStat = m_RD_EPHMRA.IPlausi( artCode, Name, &Errmld);

	if ( iStat > 1 )
	{
		iStat = m_RD_ATC.IPlausi( artCode, Name, &Errmld);
	}

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	*/

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestBeslaNo(CString beslano, BOOL bMeldung)
{
	int iStat = 0;

	CString Name;
	CString Errmld;

	long BeslaNr = atol(beslano);

	iStat = m_RD_BLIEFER.IPlausi(BeslaNr, Name, &Errmld);

	if (iStat > 1 && bMeldung)
		MsgBoxOK(Errmld);

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestCodeLppr( CString lppr, BOOL bMeldung )
{
	int iStat;
	CString Name;
	double val;
	CString Errmld;

	char code [L_ZARTFRANCE_CODE_LPPR + 1];
	strcpy ( code, lppr );

	iStat = m_RD_LPPRCODE.IPlausi( code, Name, val, &Errmld);

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	
	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestReimbPct( CString pct, BOOL bMeldung )
{
	int iStat;
	double Name;
	CString Errmld;
	
	long reimbPct = atoi(pct);

	iStat = m_RD_REIMBPCT.IPlausi( reimbPct, Name, &Errmld );

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestCountry( CString country, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	short plz_Flag;

	char cc [L_CIMEXBLOCK_COUNTRY_IFACODE + 1];
	strcpy ( cc, country );
	
	m_RD_COUNTRY.SetTyp(1);
	iStat = m_RD_COUNTRY.IPlausi( cc, Name, plz_Flag, &Errmld);
	
	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestCharge( CString batch, BOOL bMeldung )
{
	return batch.IsEmpty() == false;  
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestArtNrOrig( CString & csArtNr, BOOL bMeldung )
{
	CString errMsg;

	if ( !IsDigit( csArtNr ) || atol(csArtNr) != 0 )
	{
		// remove leading zeros
		while( csArtNr[0] == '0' ) 
			csArtNr.Delete(0);

		CLsArticleCodes lsCode;
		long pzn = lsCode.getArticleNoByCode( csArtNr, errMsg );

		if (pzn >= 0)
		{
			csArtNr.Format("%ld", pzn);
			return true;
		}
	}

	if ( bMeldung ) 
		MsgBoxOK( errMsg );

	return false;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestAwl1( CString csAwl1, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	CString PPE;
	
	int iStat;
	long Awl1;
	Awl1 = atol(csAwl1);
	
	if (IsCountry("F"))
		iStat = m_RD_AWL1_FR.IPlausi( Awl1, Name, &Errmld);
	else
		iStat = m_RD_AWL1.IPlausi( Awl1, Name, PPE, &Errmld );

	// AWL1 soll in Frankreich Mussfeld sein
	if ( ( iStat > 1 || (iStat == 1 && IsCountry("F") && !IsPrewhole())) && bMeldung ) 
		MsgBoxOK( Errmld );

	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	if (IsCountry("F") && !IsPrewhole())
		return iStat <= 0;
	else
		return iStat <= 1; 
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt1( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	CString Rabgrp;
		
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_IMSWGR.IPlausi( Wgr, Name, Rabgrp, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt2( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	CString Skontof;
	CString Taxgrp;
		
	int iStat;
	char Wgr [6];
	//strcpy ( Wgr, csWgr );
	sprintf(Wgr, "%-5s", (char*)csWgr.GetString());
	
	if (IsCountry("A"))
		iStat = m_RD_EIGENEWGR.IPlausiAustria( Wgr, Name, Skontof, Taxgrp, &Errmld);
	else if (IsCountry("CH"))
		iStat = m_RD_EIGENEWGR.IPlausiCH( Wgr, Name, Skontof, &Errmld);
	else
		iStat = m_RD_EIGENEWGR.IPlausi( Wgr, Name, Skontof, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt3( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_THERAPIEGRUPPE.IPlausi( Wgr, Name, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt4( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = 1; //kein Plausi-Test

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt5( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_SAISONWGR.IPlausi( Wgr, Name, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt6( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_BTMGRUPPE.IPlausi( Wgr, Name, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt7( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = 1; //kein Plausi-Test

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt8( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = 1; //kein Plausi-Test

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArt9( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_RABATTGRP.IPlausi( Wgr, Name, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArtA( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_SAISONWGR2.IPlausi( Wgr, Name, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	
	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestWgArtG( CString csWgr, BOOL bMeldung )
{
	CString Name;
	CString Errmld;
	
	int iStat;
	char Wgr [6];
	strcpy ( Wgr, csWgr );
	
	iStat = m_RD_SAISONWGR3.IPlausi( Wgr, Name, &Errmld);
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );
	
	return iStat <= 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDatumAh( CString csDat, BOOL bMeldung )
{
	CString Name;
	
	int iStat;
	char dat [12];
	strcpy ( dat, csDat );

	if (csDat.IsEmpty() || csDat == "0")
		return TRUE;

	PHODATE date;
	iStat = ConvToPhoDate(dat, &date, "tt.mm.jjjj");
	
	if ( iStat != 1 && bMeldung ) 
		MsgBoxOK( "Datum hat kein gültiges Format <tt.mm.jjjj>!" );

	return iStat == 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestCompanyCode( CString csDat, BOOL bMeldung )
{
	short comp_code;
	bool iStat;

	comp_code = atoi(csDat);

	iStat = (comp_code > 0 && comp_code <= 10);

	if ( iStat == false && bMeldung ) 
		MsgBoxOK( "Firmencode ist ungültig!" );

	return iStat;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestGueltab( CString csDat, BOOL bMeldung )
{
	CString Name;
	
	int iStat;
	char dat [12];
	strcpy ( dat, csDat );

	PHODATE date;
	iStat = ConvToPhoDate(dat, &date, "tt.mm.jjjj");
	
	if ( iStat != 1 && bMeldung ) 
		MsgBoxOK( "Datum hat kein gültiges Format <tt.mm.jjjj>!" );

	if ( GetPhoDate() >= date && bMeldung )
		MsgBoxOK( "Datum muss in der Zukunft liegen!" );

	return iStat == 1 && GetPhoDate() < date;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestPrice( CString csPrice, BOOL bMeldung, int nValNumber )
{
	int iStat = 1;
	
	csPrice.TrimLeft();
	csPrice.TrimRight();

	if ( csPrice.IsEmpty() ) 
		return false;

	int i = 0;
	
	while ( i < csPrice.GetLength( ) )
	{
		if ( !isdigit( csPrice.GetAt( i ) ) )
		{
			if ( (csPrice.GetAt( i ) != ',') && (csPrice.GetAt( i ) != '.') )
			{
				iStat = -1;
				break;
			}
		}
		++i;
	}

	if ( iStat != 1 && bMeldung ) 
		MsgBoxOK( "Preis ist nicht numerisch!" );
	else
	{
		csPrice.Replace(',', '.');
					
		if ( atof(csPrice) <= 0.00 && nValNumber != VAL_PREIS_AVP && nValNumber != VAL_PREIS_MAXAVP && nValNumber != VAL_ART_TFR_BASE_PRICE &&
									  nValNumber != VAL_PREIS_MAXAEP && nValNumber != VAL_PREIS_LBP && nValNumber != VAL_PREIS_PHARMACY_BASEPRICE)
		{
			iStat = -1;

			if ( bMeldung )
				MsgBoxOK( "Preis ist <= 0!" );
		}
	}

	return iStat == 1;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDiscDateFrom( CString csDat, BOOL bMeldung )
{
	CString Name;
	
	int iStat;
	char dat [12];
	strcpy ( dat, csDat );

	PHODATE date;
	iStat = ConvToPhoDate(dat, &date, "tt.mm.jjjj");
	
	if ( iStat != 1 && bMeldung ) 
		MsgBoxOK( "Datum hat kein gültiges Format <tt.mm.jjjj>!" );
	else if (date <= 0 && bMeldung ) 
		MsgBoxOK( "Es wurde kein Datum eingegeben!" );
	
	/*
	else if ( GetPhoDate() > date && bMeldung )
		MsgBoxOK( "Datum muss in der Zukunft liegen!" );
	*/

	return iStat == 1 && date > 0; //&& GetPhoDate() < date;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDiscDateTo( CString csDat, BOOL bMeldung )
{
	CString Name;
	
	int iStat;
	char dat [12];
	strcpy ( dat, csDat );

	PHODATE date;
	iStat = ConvToPhoDate(dat, &date, "tt.mm.jjjj");
	
	if ( iStat != 1 && bMeldung ) 
		MsgBoxOK( "Datum hat kein gültiges Format <tt.mm.jjjj>!" );
	else if (date <= 0 && bMeldung ) 
		MsgBoxOK( "Es wurde kein Datum eingegeben!" );
	
	/*
	else if ( GetPhoDate() > date && bMeldung && 
				(m_eUpdTable != UPD_CDISCOUNT_STOP || ( AddDayToPhoDate(date, 1) / 100) != (GetPhoDate() / 100) )) // bei Monatsrabatten auch rückwirkend bis Monatsletzten des Vormonats beim Beenden erlaubt!
		MsgBoxOK( "Datum muss in der Zukunft liegen!" ); 
	*/

	return iStat == 1 && date > 0; //&& (GetPhoDate() <= date || (m_eUpdTable == UPD_CDISCOUNT_STOP && ( AddDayToPhoDate(date, 1) / 100) == (GetPhoDate() / 100)  ));
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestDiscBaseQty( CString csBaseQty, BOOL bMeldung )
{
	if ( atoi(csBaseQty) <= 0 && bMeldung ) 
		MsgBoxOK( "Basismenge <= 0!" );
	
	return atoi(csBaseQty) > 0;
}

/*------------------------------------------------------------------------*/
BOOL CUpdateFromExcelView::TestEan( CString csEan, BOOL bMeldung )
{
	char Ean[14];
	char errmsg[100];
	int iTest;

	sprintf(Ean, "%13s", (char*)csEan.GetString());

	iTest = TestEan13PruefZiffer( Ean );
	if ( iTest != 2 )
	{
		sprintf( errmsg, "EAN ungültig (Prüfziffer falsch) - EAN: %13s", (char*)csEan.GetString() );
		MsgBoxOK( errmsg );
	}

	return iTest == 2;
}

BOOL CUpdateFromExcelView::TestNachl(CString csNachlieferung, BOOL bMeldung)
{
	csNachlieferung.Trim();
	if (csNachlieferung == "0"
		|| csNachlieferung == "1"
		|| csNachlieferung == "8"
		|| csNachlieferung == "9")
	{
		return TRUE;
	}
	else
	{
		char errmsg[100];

		sprintf(errmsg, "Ungültiges Nachliefer-Kennzeichen: %s", (char*)csNachlieferung.GetString());
		MsgBoxOK(errmsg);
		return FALSE;
	}
// 	int iVal = atoi(csNachlieferung.GetString());
// 
// 	switch (iVal)
// 	{
// 	case 0:
// 	case 1:
// 	case 8:
// 	case 9:
// 	{
// 		break;
// 	}
// 	default:
// 	{
// 	}
// 	}
// 	return TRUE;
}

BOOL CUpdateFromExcelView::TestKontMengenSteuerung(CString csFlag, BOOL bMeldung)
{
	csFlag.Trim();
	if (csFlag == "0"
		|| csFlag == "1")
	{
		return TRUE;
	}
	else
	{
		char errmsg[100];

		sprintf(errmsg, "Ungültiges Kontingent-Mengensteuerungs-Kennzeichen: %s (zulässig sind nur 0 und 1)", (char*)csFlag.GetString());
		MsgBoxOK(errmsg);
		return FALSE;
	}
// 	char errmsg[100];
// 	int iVal = atoi(csFlag.GetString());
// 
// 	switch (iVal)
// 	{
// 	case 0:
// 	case 1:
// 	{
// 		break;
// 	}
// 	default:
// 	{
// 		sprintf(errmsg, "Ungültiges Kontingent-Mengensteuerungs-Kennzeichen: %s (zulässig sind nur 0 und 1)", (char*)csFlag.GetString());
// 		MsgBoxOK(errmsg);
// 		return FALSE;
// 	}
// 	}
// 	return TRUE;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::GotoTop()
{
	m_dlg.SetFocus( m_Pos_Top );
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	InitPflege();

	m_bComeBack = false;
}

/*------------------------------------------------------------------------*/
void CUpdateFromExcelView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			m_bDoResize = true;
			if ( !m_bComeBack )
			{
				InitVariables();
				theApp->SetMenuOnOff( 1, 1, -1, -1, -1, -1 ); 
			}
			else
			{
				m_bComeBack = false;
				theApp->PopMenuState(  );
				theApp->SetMenuOnOff( 1, 1, -1, -1, -1, -1 ); 
			}
		}		
	}
}

////////////////////////////////////////////////
// Drucken
bool CUpdateFromExcelView::GetInfoFromCallingView( CString& cStr, int nAction )
{
	return true;
}




void CUpdateFromExcelView::OnBnClickedBtCarticleext()
{
	ShowPZNField(true);
	
	m_eUpdTable = UPD_CARTICLEEXT;
	
	m_PflFeldDlg.InitPflege( m_eUpdTable );

	if ( m_PflFeldDlg.DoModal() == IDOK ) 
	{
		m_nAnzF = m_PflFeldDlg.GetFeldInfo( m_PflFelder );
		GenMaske( );		
	}
}
