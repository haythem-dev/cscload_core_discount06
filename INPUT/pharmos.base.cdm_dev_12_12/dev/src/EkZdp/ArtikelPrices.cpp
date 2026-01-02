// ArtikelPrices.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelPrices.h"
#include "ArtikelView.h"
#include "ArtikelDoc.h"
#include <eklibs/hamfcs/hMskChar.h>
#include <hdatum/phodate.h>
#include "ServerDatum.h"
#include <phxlib/PhxUtil.h>

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelPrices dialog

CArtikelPrices::CArtikelPrices(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelPrices::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArtikelPrices)
	//}}AFX_DATA_INIT
}

CArtikelPrices::CArtikelPrices(struct ZARTPREIS *pBuf, CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelPrices::IDD, pParent)
{
	m_pBuf  = pBuf;
	m_pView = pParent; //(CArtikelView* )m_pView
	m_ArtPage1 = &((CArtikelView* )m_pView)->m_Page0;
	m_pBufArtikel = &m_ArtPage1->m_pBuf->zartikel;

	double i = m_pBufArtikel->HERST_PROZENT; // by InitPflege, value of this field seems to get lost !?
	
	InitPflege();

	m_pBufArtikel->HERST_PROZENT = i;
}

void CArtikelPrices::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPrices)
	DDX_Control(pDX, IDC_LC_ARTIKEL_PRICES_BOX, m_cPRICESBOX);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICES_PREISTYP, m_cPREISTYP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_GUELAB, m_eGUELAB);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_GROSSO, m_eGROSSO);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_AEP, m_eAEP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_AGP, m_eAGP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_AVP, m_eAVP);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICES_MWST, m_cMWST);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_HPROZ, m_eHPROZ);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_HPROZ_ART, m_eHPROZ_ART);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_MAXAEP, m_eMAXAEP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_MAXAVP, m_eMAXAVP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_EAVP, m_eEAVP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_ERSTATTBETRAG, m_eERSTATTBETRAG);
	DDX_Control(pDX, IDC_CB_ARTIKEL_PRICES_DISC_DED_YET, m_cDISC_DED_YET);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_PUBLNR, m_ePUBL_NR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_LBP, m_eLBP);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PRICES_PBP, m_ePBP);
	DDX_Control(pDX, IDC_PB_ARTIKEL_PRICES_SAVE, m_bSAVE);	
	DDX_Control(pDX, IDC_PB_ARTIKEL_PRICES_NEW, m_bNEW);	
	DDX_Control(pDX, IDC_PB_ARTIKEL_PRICES_CALCULATE, m_bCALC);	

	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_GUELAB, m_stGUELAB);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_GROSSO, m_stGROSSO);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_AEP, m_stAEP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_AGP, m_stAGP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_AVP, m_stAVP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_MWST, m_stMWST);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_HPROZ, m_stHPROZ);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_MAXAEP, m_stMAXAEP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_MAXAVP, m_stMAXAVP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_EAVP, m_stEAVP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_ERSTATTBETRAG, m_stERSTATTBETRAG);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_DISC_DED_YET, m_stDISC_DED_YET);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_PUBLNR, m_stPUBL_NR);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_LBP, m_stLBP);
	DDX_Control(pDX, IDC_ST_ARTIKEL_PRICES_PBP, m_stPBP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelPrices, CDialogMultiLang)
	//{{AFX_MSG_MAP(CArtikelPrices)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LC_ARTIKEL_PRICES_BOX, OnItemchangedLcArtikelPricesBox)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_PRICES_NEW, OnPbArtikelPricesNew)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_PRICES_SAVE, OnPbArtikelPricesSave)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_PRICES_END, OnPbArtikelPricesEnd)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_PRICES_CALCULATE, OnPbArtikelPricesCalculate)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_PRICES_PREISTYP,	OnSelchangeCbArtikelPreistyp)
	ON_CBN_SELCHANGE(IDC_CB_ARTIKEL_PRICES_MWST,	OnSelchangeCbArtikelMwst)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// --------------------------------------------------------------------- //
void CArtikelPrices::MarkListPos( int pos )
{
	m_cPRICESBOX.SetItem(  pos
            , 0
            , LVIF_STATE
            , NULL
            , 0
            , LVIS_SELECTED|LVIS_FOCUSED
            , LVIS_SELECTED|LVIS_FOCUSED
            , 0L);

	m_cPRICESBOX.EnsureVisible( pos, FALSE );
}

// --------------------------------------------------------------------- //
BOOL CArtikelPrices::InitSuchBox()
{
	m_Columns[NUM_OF_PRICE_COLUMNS].Index = -1;
	strcpy(m_Columns[NUM_OF_PRICE_COLUMNS].Columns, "");
	m_Columns[NUM_OF_PRICE_COLUMNS].Width = 0;
	m_Columns[NUM_OF_PRICE_COLUMNS].Align = 0;
	m_Columns[NUM_OF_PRICE_COLUMNS].isVisible = false;


	m_Columns[0].Index = 0;
	strcpy(m_Columns[0].Columns, CResString::ex().getStrTblText(IDS_STRING1408)); //Datum
	m_Columns[0].Width = 70;
	m_Columns[0].Align = LVCFMT_LEFT;
	m_Columns[0].isVisible = true;
	

	m_Columns[1].Index = 1;
	strcpy(m_Columns[1].Columns, CResString::ex().getStrTblText(IDS_STRING1409)); //Grosso
	m_Columns[1].Width = 70;
	m_Columns[1].Align = LVCFMT_RIGHT;
	m_Columns[1].isVisible = true;
		
	//if ((IsCountry("CH") == TRUE) && (IsAGP() == TRUE) && !IsPrewhole()) // AGP check is normally only for prewhole check, which is already there
	if ((IsCountry("CH") == TRUE) && !IsPrewhole())
	{
		m_Columns[2].Index = 2; 
		strcpy(m_Columns[2].Columns, CResString::ex().getStrTblText(IDS_AGP)); //AGP
		m_Columns[2].Width = 70;
		m_Columns[2].Align = LVCFMT_RIGHT;
		m_Columns[2].isVisible = true;
	}
	else
	{
		m_Columns[2].Index = 2;
		strcpy(m_Columns[2].Columns, CResString::ex().getStrTblText(IDS_STRING1410)); //AEP
		m_Columns[2].Width = 70;
		m_Columns[2].Align = LVCFMT_RIGHT;
		m_Columns[2].isVisible = true;
	}
    	

	m_Columns[3].Index = 3;
	strcpy(m_Columns[3].Columns, CResString::ex().getStrTblText(IDS_STRING1411)); //AVP
	m_Columns[3].Width = 70;
	m_Columns[3].Align = LVCFMT_RIGHT;
	m_Columns[3].isVisible = true;
	

	m_Columns[4].Index = 4;
	strcpy(m_Columns[4].Columns, CResString::ex().getStrTblText(IDS_STRING1412)); //EAVP
	m_Columns[4].Width = 70;
	m_Columns[4].Align = LVCFMT_RIGHT;

	if (IsCountry("D") )
	{
		m_Columns[4].isVisible = true;
		m_Columns[8].isVisible = true;
		m_Columns[9].isVisible = true;
	}
	else
	{
		m_Columns[4].isVisible = false;
		m_Columns[8].isVisible = false;
		m_Columns[9].isVisible = false;
	}
    	
	m_Columns[5].Index = 5;
	strcpy(m_Columns[5].Columns, CResString::ex().getStrTblText(IDS_STRING1413)); //maxAEP
	m_Columns[5].Width = 70;
	m_Columns[5].Align = LVCFMT_RIGHT;

	if (IsCountry("F") )
	{
		m_Columns[5].isVisible = true;
		m_Columns[12].isVisible = true;
		m_Columns[13].isVisible = true;
	}
	else
	{
		m_Columns[5].isVisible = false;
		m_Columns[12].isVisible = false;
		m_Columns[13].isVisible = false;
	}
	
	m_Columns[6].Index = 6;
	strcpy(m_Columns[6].Columns, CResString::ex().getStrTblText(IDS_STRING1414)); //LBP
	m_Columns[6].Width = 70;
	m_Columns[6].Align = LVCFMT_RIGHT;

	if (IsCountry("F") || IsCountry("CH"))
		m_Columns[6].isVisible = true;
	else
		m_Columns[6].isVisible = false;
	
	m_Columns[7].Index = 7;
	strcpy(m_Columns[7].Columns, CResString::ex().getStrTblText(IDS_STRING1415)); //maxAVP
	m_Columns[7].Width = 70;
	m_Columns[7].Align = LVCFMT_RIGHT;

	if (IsCountry("F") || IsCountry("BG"))
		m_Columns[7].isVisible = true;
	else
		m_Columns[7].isVisible = false;
	
	m_Columns[8].Index = 8;
	strcpy(m_Columns[8].Columns, CResString::ex().getStrTblText(IDS_STRING1416)); //Erstattbetrag
	m_Columns[8].Width = 70;
	m_Columns[8].Align = LVCFMT_RIGHT;
	
	m_Columns[9].Index = 9;
	strcpy(m_Columns[9].Columns, CResString::ex().getStrTblText(IDS_STRING1417)); //Abzug APU
	m_Columns[9].Width = 70;
	m_Columns[9].Align = LVCFMT_RIGHT;
	
	m_Columns[10].Index = 10;
	strcpy(m_Columns[10].Columns, CResString::ex().getStrTblText(IDS_STRING1418)); //MWST
	m_Columns[10].Width = 70;
	m_Columns[10].Align = LVCFMT_RIGHT;
	m_Columns[10].isVisible = true;
	
	m_Columns[11].Index = 11;
	strcpy(m_Columns[11].Columns, CResString::ex().getStrTblText(IDS_STRING1419)); // Herst-%
	m_Columns[11].Width = 70;
	m_Columns[11].Align = LVCFMT_RIGHT;
	m_Columns[11].isVisible = true;
	
	m_Columns[12].Index = 12;
	strcpy(m_Columns[12].Columns, CResString::ex().getStrTblText(IDS_STRING1420)); //PBP
	m_Columns[12].Width = 70;
	m_Columns[12].Align = LVCFMT_RIGHT;
	
	m_Columns[13].Index = 13;
	strcpy(m_Columns[13].Columns, CResString::ex().getStrTblText(IDS_STRING1421)); // PublNr
	m_Columns[13].Width = 130;
	m_Columns[13].Align = LVCFMT_RIGHT;
	
	LV_COLUMN lvC;

	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for ( COLUMNS_TYPES* pType = m_Columns; pType->Index != -1; pType++ )
	{
		if (pType->isVisible == false)
			continue;
		
		lvC.iSubItem	= pType->Index;
		lvC.pszText 	= LPTSTR(pType->Columns);
		lvC.fmt			= pType->Align;
		lvC.cx			= pType->Width;

		if ( m_cPRICESBOX.InsertColumn( pType->Index, &lvC ) == -1 )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING327) );
			return FALSE;
		}
	}
	m_cPRICESBOX.SetFullRowSel( TRUE );		// !!!!!!!!!!!!!!!!!!

	return TRUE;
}

// --------------------------------------------------------------------- //
void CArtikelPrices::FillSuchBox( CStringArray &s )
{
	int iSubItem;
	int col = 1;
	int index;

	index = m_cPRICESBOX.GetItemCount();

	if ( m_cPRICESBOX.InsertItem( index, s[0] ) == -1 ) 
		return;

	for (iSubItem = 1; iSubItem < NUM_OF_PRICE_COLUMNS; iSubItem++)
	{
		if (m_Columns[iSubItem].isVisible == false)
			continue;
		
		m_cPRICESBOX.SetItemText(index, col, s[iSubItem].GetBuffer(100));
		s[iSubItem].ReleaseBuffer(-1);
		col++;
	}
}
// --------------------------------------------------------------------- //
void CArtikelPrices::DisableFields()
{
	m_cPREISTYP.EnableWindow(false);
	m_eAEP.EnableWindow(false);
	m_eAGP.EnableWindow(false);
	m_cMWST.EnableWindow(false);
	m_eGUELAB.EnableWindow(false);
	m_eGROSSO.EnableWindow(false);
	m_eAVP.EnableWindow(false);
	m_eHPROZ.EnableWindow(false);
	m_cDISC_DED_YET.EnableWindow(false);
	m_eEAVP.EnableWindow(false);
	m_eERSTATTBETRAG.EnableWindow(false);
	m_ePUBL_NR.EnableWindow(false);
	m_ePBP.EnableWindow(false);
	m_eMAXAEP.EnableWindow(false);
	m_eMAXAVP.EnableWindow(false);
	m_eLBP.EnableWindow(false);
	m_bSAVE.EnableWindow(false);
	m_bNEW.EnableWindow(false);
	m_cPRICESBOX.SetFocus();
}

// --------------------------------------------------------------------- //
void CArtikelPrices::Enable_AVP_Croatia( )
{   
	if (m_pBufArtikel->HERST_PROZENT > 0)
	{
		m_eAVP.EnableWindow( false );
		
		// wenn Prozentsatz sich geändert hat und kein neuer Preis eingegeben, fragen, ob Preise neu gerechnet werden sollen
		if (m_ArtPage1->m_pBufOld->zartikel.HERST_PROZENT != m_pBufArtikel->HERST_PROZENT &&
			m_pBuf[1].DATUMGUELTIGAB <= ::Today())
		{
			// wenn kein neuer Preis eingegeben, fragen, ob der alte übernommen werden soll
			if ( m_pBuf[0].DATUMGUELTIGAB == 0 )
			{
				if (MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING10267) ) == IDYES)
				{
					CopyPrice(1);
					m_HERST_PROZENT = m_pBufArtikel->HERST_PROZENT;
					m_eHPROZ.p_SetInput();
					
					// ggfs. AVP neu berechnen
					Set_Taxe_AVP();
				}
			}
			else
			// ansonsten direkt AVP neu berechnen
			{
				// ggfs. AVP neu berechnen
				Set_Taxe_AVP();
			}
		}
	}
	else
	{
		m_eAVP.EnableWindow( true );
	}
}

// --------------------------------------------------------------------- //
void CArtikelPrices::EnableFields()
{
	// Positionen von preistyp + herst_prozent (Artikel) sind fix
	if (IsCountry("BG") )
		m_cPREISTYP.EnableWindow(true);
	else
		m_cPREISTYP.EnableWindow(false); // but don´t hide

	m_eHPROZ_ART.EnableWindow(true);
	
	int yText	= 55;
	int yEdit	= yText + 20;
	int xStart	= 12;
	int xWidth	= 70;
	short xPos	= 0;
	UINT flags = SWP_NOZORDER|SWP_NOSIZE;
	
	// always 1st column
	m_eGUELAB.EnableWindow(true);
	m_stGUELAB.SetWindowPos(NULL, xStart, yText, 0, 0, flags);
	m_eGUELAB.SetWindowPos (NULL, xStart, yEdit, 0, 0, flags);
	++xPos;
	
	// always 2nd column
	m_eGROSSO.EnableWindow(true);
	m_stGROSSO.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
	m_eGROSSO.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
	++xPos;
	
	//if ((IsCountry("CH") == TRUE) && (IsAGP() == TRUE) && !IsPrewhole()) // AGP check is normally only for prewhole check, which is already there
	if ((IsCountry("CH") == TRUE) && !IsPrewhole())
	{
		m_stAEP.ShowWindow(SW_HIDE);
		m_eAEP.ShowWindow(SW_HIDE);
		m_eAGP.EnableWindow(true);
		m_stAGP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eAGP.SetWindowPos(NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}
	else
	{
		m_stAGP.ShowWindow(SW_HIDE);
		m_eAGP.ShowWindow(SW_HIDE);
		m_eAEP.EnableWindow(true);
		m_stAEP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eAEP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}

	m_eAVP.EnableWindow(true);
	m_stAVP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
	m_eAVP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
	++xPos;

	if ( !IsCountry("F") )
	{
		m_eMAXAEP.ShowWindow(SW_HIDE);
		m_stMAXAEP.ShowWindow(SW_HIDE);
	}
	else
	{
		m_eMAXAEP.EnableWindow(true);
		m_stMAXAEP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eMAXAEP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}

	if ( !IsCountry("F") && !IsCountry("CH") )
	{
		m_eLBP.ShowWindow(SW_HIDE);
		m_stLBP.ShowWindow(SW_HIDE);
	}
	else
	{
		m_eLBP.EnableWindow(true);
		m_stLBP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eLBP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}

	if ( !IsCountry("F") && !IsCountry("BG") )
	{
		m_eMAXAVP.ShowWindow(SW_HIDE);
		m_stMAXAVP.ShowWindow(SW_HIDE);
	}
	else
	{
		m_eMAXAVP.EnableWindow(true);
		m_stMAXAVP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eMAXAVP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}

	if ( !IsCountry("D") )
	{
		m_cDISC_DED_YET.ShowWindow(SW_HIDE);
		m_stDISC_DED_YET.ShowWindow(SW_HIDE);
		m_eEAVP.ShowWindow(SW_HIDE);
		m_stEAVP.ShowWindow(SW_HIDE);
		m_eERSTATTBETRAG.ShowWindow(SW_HIDE);
		m_stERSTATTBETRAG.ShowWindow(SW_HIDE);
	}
	else
	{
		m_eEAVP.EnableWindow(true);
		m_stEAVP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eEAVP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;

		m_eERSTATTBETRAG.EnableWindow(true);
		m_stERSTATTBETRAG.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_eERSTATTBETRAG.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;

		m_cDISC_DED_YET.EnableWindow(true);
		m_stDISC_DED_YET.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_cDISC_DED_YET.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}
	
	m_cMWST.EnableWindow(true);
	m_stMWST.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
	m_cMWST.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
	++xPos;

	m_eHPROZ.EnableWindow(false); // --> in keinem Land editierbar,  but don´t hide!
	m_stHPROZ.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
	m_eHPROZ.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
	++xPos;

	if ( !IsCountry("F") )
	{
		m_ePUBL_NR.ShowWindow(SW_HIDE);
		m_stPUBL_NR.ShowWindow(SW_HIDE);
		m_ePBP.ShowWindow(SW_HIDE);
		m_stPBP.ShowWindow(SW_HIDE);
	}
	else
	{
		m_ePBP.EnableWindow(true);
		m_stPBP.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_ePBP.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;

		m_ePUBL_NR.EnableWindow(true);
		m_stPUBL_NR.SetWindowPos(NULL, xStart + (xPos * xWidth), yText, 0, 0, flags);
		m_ePUBL_NR.SetWindowPos (NULL, xStart + (xPos * xWidth), yEdit, 0, 0, flags);
		++xPos;
	}
		
	m_eHPROZ_ART.p_GetInput();
	if (IsCountry("HR") && m_pBufArtikel->HERST_PROZENT > 0)
		m_eAVP.EnableWindow( false );
	
	m_bSAVE.EnableWindow(true);
	m_eGUELAB.SetFocus();

	EnableNewButton();
}

// --------------------------------------------------------------------- //
void CArtikelPrices::EnableNewButton()
{
	if (m_pBuf[0].DATUMGUELTIGAB == 0)
		m_bNEW.EnableWindow(true);
}

// --------------------------------------------------------------------- //
void CArtikelPrices::EnableCalcButton()
{
	if (IsCountry("D") && *m_pBufArtikel->TAXPFL == '0' && m_pBufArtikel->HERST_PROZENT != 0.0 && 
		m_pBuf[0].DATUMGUELTIGAB == 0 && m_pBuf[1].DATUMGUELTIGAB > 0)
		m_bCALC.EnableWindow(true);
	else
		m_bCALC.EnableWindow(false);
}

// --------------------------------------------------------------------- //
void CArtikelPrices::FillBuffer( int i, CStringArray &s )
{
	s.SetSize( NUM_OF_PRICE_COLUMNS );

	CString tmp;
	char datstr[11];
	
	ConvFromPhoDate  ( datstr, m_pBuf[i].DATUMGUELTIGAB, "tt.mm.jjjj" );
	s[0] = datstr;

	tmp.Format("%.2lf", m_pBuf[i].GROSSO);
	s[1] = tmp;

	//if ((IsCountry("CH") == TRUE) && (IsAGP() == TRUE)) // AGP check is because of Prewholesale
	if ((IsCountry("CH") == TRUE) && (IsPrewhole() == FALSE))
	{
		// take AGP in colum index 2 for CH
		tmp.Format("%.2lf", m_pBuf[i].AGP);
		s[2] = tmp;
	}
	else
	{
		// take AEP in colum index 2 for all other countries
		tmp.Format("%.2lf", m_pBuf[i].AEP);
		s[2] = tmp;
	}

	tmp.Format("%.2lf", m_pBuf[i].AVP);
	s[3] = tmp;

	tmp.Format("%.2lf", m_pBuf[i].EAVP);
	s[4] = tmp;

	tmp.Format("%.2lf", m_pBuf[i].MAXAEP);
	s[5] = tmp;

	tmp.Format("%.2lf", m_pBuf[i].LIEFERBASISPREIS);
	s[6] = tmp;

	tmp.Format("%.2lf", m_pBuf[i].MAXAVP);
	s[7] = tmp;

	tmp.Format("%.2lf", m_pBuf[i].ERSTATTBETRAG);
	s[8] = tmp;

	if ( m_pBuf[i].DISC_DEDUCED_YET == 1 )
		s[9] = CResString::ex().getStrTblText(IDS_YES);
	else
		s[9] = CResString::ex().getStrTblText(IDS_NO);

	if (IsCountry("BG") )
	{
		s[10] = CResString::ex().getStrTblText(IDS_STRING10103);
	}
	// eingelesene Mwst-Saetze in Combo-Box stellen  // 3RD-VAT
	else if (IsCountry("F") || 
			 IsCountry("RS")||
			 IsCountry("HR")||  
			 IsCountry("A"))
	{
		// Mwst-Prozentsätze aus der Taxtab-Klasse holen (jeweilige Landes-Reihenfolge beachten !!)
		double dMwstProz[5];
		CString	CsMwst;
		
		if (m_pBuf[i].DATUMGUELTIGAB == 0)
			m_ArtPage1->m_pTaxTb->GetAllVatRates( AddDayToPhoDate( ::Today(), 1 ),	&dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);
		else
			m_ArtPage1->m_pTaxTb->GetAllVatRates( m_pBuf[i].DATUMGUELTIGAB,			&dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);
		
		CsMwst.Format("%.1f %%", dMwstProz[atoi(m_pBuf[i].KE_MWST)]);
		s[10] = CsMwst;
	}	
	else
	{
		if ( m_pBuf[i].KE_MWST[0] == '0' )
			s[10] = CResString::ex().getStrTblText(IDS_STRING10103);
		else if ( m_pBuf[i].KE_MWST[0] == '1' )
			s[10] = CResString::ex().getStrTblText(IDS_STRING10104);
		else if ( m_pBuf[i].KE_MWST[0] == '2' )
			s[10] = CResString::ex().getStrTblText(IDS_STRING10105);
	}

	tmp.Format("%.2lf", m_pBuf[i].HERST_PROZENT);
	s[11] = tmp;

	tmp.Format("%.2lf", m_pBuf[i].PHARMACY_BASEPRICE);
	s[12] = tmp;
	
	s[13] = m_pBuf[i].PUBLICATIONNUMBER;
	s[13].TrimRight();
}

// --------------------------------------------------------------------- //
class CV_ARTIKELPRICES_Taxe_AEP : public ChValBase
{
public:
	CV_ARTIKELPRICES_Taxe_AEP( CArtikelPrices* pDlg ) 
		: ChValBase( pDlg ){};
	void PostProc( )
	{
		((CArtikelPrices* )m_pWnd)->Set_Taxe_AEP();
		((CArtikelPrices* )m_pWnd)->CalculatePercent( );
	}
};

// --------------------------------------------------------------------- //
class CV_ARTIKELPRICES_Taxe_AVP : public ChValBase
{
public:
	CV_ARTIKELPRICES_Taxe_AVP( CArtikelPrices* pDlg ) 
		: ChValBase( pDlg ){};
	void PostProc( )
	{
		((CArtikelPrices* )m_pWnd)->Set_Taxe_AVP();
		((CArtikelPrices* )m_pWnd)->CalculatePercent( );
	}
};

// --------------------------------------------------------------------- //
class CV_ARTIKELPRICES_Proz_LBP : public ChValBase
{
public:
	CV_ARTIKELPRICES_Proz_LBP( CArtikelPrices* pDlg ) 
		: ChValBase( pDlg ){};
	void PostProc( )
	{
		((CArtikelPrices* )m_pWnd)->Set_Grosso_From_LBP( );
	}
};

// --------------------------------------------------------------------- //
class CV_ARTIKELPRICES_PreisDatum : public ChValBase
{
public:
	CV_ARTIKELPRICES_PreisDatum( CArtikelPrices* pDlg ) 
		: ChValBase( pDlg ){};
	void PostProc( )
	{
		((CArtikelPrices* )m_pWnd)->FillComboBoxVAT( );
		((CArtikelPrices* )m_pWnd)->Set_Taxe_AVP();
	}
};

// --------------------------------------------------------------------- //
class CV_ARTIKELPRICES_Herst_Prozent : public ChValBase
{
public:
	CV_ARTIKELPRICES_Herst_Prozent( CArtikelPrices* pDlg ) 
		: ChValBase( pDlg ){};
	void PostProc( )
	{
		((CArtikelPrices* )m_pWnd)->Set_Herst_Prozent( );

		if (IsCountry("HR"))
		{
			((CArtikelPrices* )m_pWnd)->Enable_AVP_Croatia( );
		}

		((CArtikelPrices* )m_pWnd)->EnableCalcButton();
	}
};


// --------------------------------------------------------------------- //
void CArtikelPrices::Set_Taxe_AEP(  )
{
	if ( m_pBufArtikel->TAXPFL[0] == '0' )
		return;

	if ( m_GROSSO == 0.0 )
		return;

	if ( m_pBufArtikel->TAXPRUEFGROSSO[0] == '1' ) 
		return;

	if (IsCountry("A"))
	{
		m_ArtPage1->m_pTaxTb->CalcAekAustria( m_GROSSO, &m_AEP, 
						m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );	
	}
	else if (IsCountry("F"))
	{
		m_ArtPage1->m_pTaxTb->CalcAekFrance( m_GROSSO, &m_AEP, 
						m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );	
	}
	else if (IsCountry("BG"))
	{
		m_ArtPage1->m_pTaxTb->CalcAekBulgaria( m_GROSSO, &m_AEP, 
						m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0],
						m_PREIS_TYP );
	}
	else
	{
		m_ArtPage1->m_pTaxTb->CalcAek( m_GROSSO, &m_AEP, 
				m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );			// OTCX_RX
	}

	m_eAEP.p_SetInput();

	Set_Taxe_AVP( );
}

// --------------------------------------------------------------------- //
void CArtikelPrices::Set_Taxe_AVP( )
{
	if ( m_pBufArtikel->TAXPFL[0] == '0' && !IsCountry("HR"))		// in Kroatien gibt es kein Taxkennzeichen
		return;

	if (IsCountry("BG") && m_PREIS_TYP == 1)		// in Bulgarien keine Berechnung für Krankenkasse
		return;

	int mwst = 0;

	// 5 Mwst-Sätze in Frankreich
	if (IsCountry("F"))
	{
		if ( m_KE_MWST[0] == '4' )
			mwst = TAXTAB_FR_MWST_4;
		else if ( m_KE_MWST[0] == '3' )
			mwst = TAXTAB_FR_MWST_3;
		else if ( m_KE_MWST[0] == '2' )	
			mwst = TAXTAB_FR_MWST_2;
		else if ( m_KE_MWST[0] == '1' )	
			mwst = TAXTAB_FR_MWST_1;
		else												
			mwst = TAXTAB_FR_MWST_0;
	}
	// 3 Mwst-Sätze in Kroatien
	else if (IsCountry("HR"))
	{
		if ( m_KE_MWST[0] == '2' )
			mwst = TAXTAB_HR_MWST_2;
		else if ( m_KE_MWST[0] == '1' )	
			mwst = TAXTAB_HR_MWST_1;
		else												
			mwst = TAXTAB_HR_MWST_0;
	}
	else  if(IsCountry("A"))// 3RD-VAT
	{
		if (m_KE_MWST[0] == '0')	// Voll
		{
			mwst = TAXTAB_AT_VOLL;
		}
		else if (m_KE_MWST[0] == '1')		// Vermindert
		{
			mwst = TAXTAB_AT_VERMM;
		}
		else if (m_KE_MWST[0] == '2')	// 3RD
		{
			mwst = TAXTAB_AT_3RD;
		}
		else if (m_KE_MWST[0] == '3')	// 0
		{
			mwst = 3;
		}
	}
	else
	{
		if (m_KE_MWST[0] == '0')	// Voll
		{
			mwst = TAXTAB_IS_VOLLMWST;
		}
		else if (m_KE_MWST[0] == '1')		// Vermindert
		{
			mwst = TAXTAB_IS_VERMMWST;
		}
		else	// Ohne
		{
			mwst = TAXTAB_IS_OHNEMWST;
		}
	}

	m_eHPROZ_ART.p_GetInput();
	
	if (IsCountry("A"))
	{
		m_ArtPage1->m_pTaxTb->CalcAvkAustriaMwst( m_AEP, &m_AVP, 
							mwst, m_DATUMGUELTIGAB, 
							m_pBufArtikel->TAXPFL[0], m_pBufArtikel->BTM[0] );
	}
	else if (IsCountry("F"))
	{
		m_ArtPage1->m_pTaxTb->CalcAvkFranceMwst( m_GROSSO, m_AEP, &m_AVP, 
							mwst, m_DATUMGUELTIGAB, 
							m_pBufArtikel->TAXPFL[0] );

		if ( m_GROSSO <= 0.0 )
			m_AVP = 0.0;		// request by France - don´t calculate / show AVP as long as no GEP is entered.
	}
	else if (IsCountry("HR") && m_pBufArtikel->HERST_PROZENT > 0)
	{
		m_ArtPage1->m_pTaxTb->CalcAvkCroatiaMwst( m_AEP, &m_AVP, 
							mwst, m_DATUMGUELTIGAB, 
							m_pBufArtikel->HERST_PROZENT );
	}
	else if (IsCountry("BG"))
	{
		m_ArtPage1->m_pTaxTb->CalcAvkBulgariaMwst( m_GROSSO, &m_AVP, 
							mwst, m_DATUMGUELTIGAB, 
							m_pBufArtikel->TAXPFL[0], m_PREIS_TYP );
	}
	else
	{
		m_ArtPage1->m_pTaxTb->CalcAvkMwst( m_AEP, &m_AVP, 
							mwst, m_DATUMGUELTIGAB,
							m_pBufArtikel->TAXPFL[0] );			// OTCX_RX
	}

	m_eAVP.p_SetInput();
}

// --------------------------------------------------------------------- //
void CArtikelPrices::CalculatePercent( )
{
	double dProz;

	//  nur in Frankreich Großhandel !!!!!
	if (!IsCountry("F") || IsPrewhole() )
		return;
	
	//  nur bei der 1. Preiszeile !!!!!
	if ( GetSelectedRow() != 0 ) 
		return;
	
	// beide Preise müssen gefüllt sein
	if ( m_GROSSO <= 0.0 || m_AEP <= 0.0 )
		return;
	
	dProz = 100 * (1.0 - (m_GROSSO / m_AEP));
	m_pBufArtikel->HERST_PROZENT = dProz;
	m_eHPROZ_ART.p_SetInput();
	
	// auch das entsprechende zartpreis-Feld versorgen
	m_HERST_PROZENT = m_pBufArtikel->HERST_PROZENT; 
	m_eHPROZ.p_SetInput();
}


// --------------------------------------------------------------------- //
void CArtikelPrices::Set_Grosso_From_LBP( )
{
	if (IsCountry("CH") == false)
		return;

	m_eHPROZ_ART.p_GetInput();
	
	double newGrosso = m_LIEFERBASISPREIS - ( m_LIEFERBASISPREIS * m_pBufArtikel->HERST_PROZENT / 100 );	

	if ( (newGrosso <= m_AVP || m_AVP == 0) && m_pBufArtikel->HERST_PROZENT != 0 && m_LIEFERBASISPREIS > 0 )
	{
		m_GROSSO		= newGrosso;
		m_HERST_PROZENT = m_pBufArtikel->HERST_PROZENT; 
		m_eGROSSO.p_SetInput();
		m_eHPROZ.p_SetInput();
	}
}

// --------------------------------------------------------------------- //
void CArtikelPrices::InitPflege(  )
{
// ---
	*m_PUBLICATIONNUMBER = '\0';
	AppendBlanks( m_PUBLICATIONNUMBER, L_ZARTPREIS_PUBLICATIONNUMBER );
	m_ePUBL_NR.SetMask	(ED_CHAR,
                     ED_UPPER,
                     m_PUBLICATIONNUMBER,
                     L_ZARTPREIS_PUBLICATIONNUMBER,
					 new ChMaskChar );
	m_ePUBL_NR.SetMSStandard( TRUE );
	m_ePUBL_NR.SetDialog();

// ---
	*m_KE_MWST = '\0';
	AppendBlanks( m_KE_MWST, L_ZARTPREIS_KE_MWST );
	
	if (IsCountry("F"))
		// Reihenfolge 01243 bewusst, damit die Sätze in der richtigen Reihenfolge angezeigt werden
		m_cMWST.SetMask("01243", m_KE_MWST, 0);
	else if (IsCountry("HR"))
		// Reihenfolge 021 bewusst, damit die Sätze in der richtigen Reihenfolge angezeigt werden
		m_cMWST.SetMask("021", m_KE_MWST, 0);
	else if (IsCountry("BG"))
		m_cMWST.SetMask("0", m_KE_MWST, 0);
	else if (IsCountry("A"))
		m_cMWST.SetMask("0123", m_KE_MWST, 0);
	else
		m_cMWST.SetMask("012", m_KE_MWST, 0);

	m_cMWST.SetMSStandard( TRUE );
	m_cMWST.SetDialog();

// ---
	m_cDISC_DED_YET.SetMask("012", 1, &m_DISC_DEDUCED_YET, 0);
	m_cDISC_DED_YET.SetMSStandard( TRUE );
	m_cDISC_DED_YET.SetDialog();

// ---
	if (IsCountry("BG"))
		m_cPREISTYP.SetMask		("01",			&m_PREIS_TYP ); 
	else
		m_cPREISTYP.SetMask		("0",			&m_PREIS_TYP ); 

	m_cPREISTYP.SetMSStandard( TRUE );
	m_cPREISTYP.SetDialog();

// ---
	m_eHPROZ.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_HERST_PROZENT,
                             L_ZARTPREIS_HERST_PROZENT + 2,
                             N_ZARTPREIS_HERST_PROZENT,
                             new ChMaskDbl );
	m_eHPROZ.SetMSStandard( TRUE );
	m_eHPROZ.SetDialog();


	m_eHPROZ_ART.SetMask	(ED_DBL,
                             ED_NORMAL,
                             &m_pBufArtikel->HERST_PROZENT,
                             L_ZARTIKEL_HERST_PROZENT + 2,
                             N_ZARTIKEL_HERST_PROZENT,
                             new ChMaskDbl,
							 new CV_ARTIKELPRICES_Herst_Prozent( this ) );
	m_eHPROZ_ART.SetMSStandard( TRUE );
	m_eHPROZ_ART.SetDialog();


// ---
	m_eGROSSO.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_GROSSO,
                             L_ZARTPREIS_GROSSO + 1,
                             N_ZARTPREIS_GROSSO,
                             new ChMaskDblPos,
							 new CV_ARTIKELPRICES_Taxe_AEP(this));
	m_eGROSSO.SetMSStandard( TRUE );
	m_eGROSSO.SetDialog();

// ---
	m_eAEP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_AEP,
                             L_ZARTPREIS_AEP + 1,
                             N_ZARTPREIS_AEP,
                             new ChMaskDblPos,
							 new CV_ARTIKELPRICES_Taxe_AVP(this));
	m_eAEP.SetMSStandard( TRUE );
	m_eAEP.SetDialog();

// ---
	m_eAGP.SetMask(ED_DBL,
		ED_NORMAL,
		&m_AGP,
		L_ZARTPREIS_AGP + 1,
		N_ZARTPREIS_AGP,
		new ChMaskDblPos);
	m_eAGP.SetMSStandard(TRUE);
	m_eAGP.SetDialog();

// ---
	m_eAVP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_AVP,
                             L_ZARTPREIS_AVP + 1,
                             N_ZARTPREIS_AVP,
                             new ChMaskDblPos);
	m_eAVP.SetMSStandard( TRUE );
	m_eAVP.SetDialog();

// ---
	m_eEAVP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_EAVP,
                             L_ZARTPREIS_EAVP + 1,
                             N_ZARTPREIS_EAVP,
                             new ChMaskDblPos);
	m_eEAVP.SetMSStandard( TRUE );
	m_eEAVP.SetDialog();

// ---
	m_eMAXAEP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_MAXAEP,
                             L_ZARTPREIS_MAXAEP + 1,
                             N_ZARTPREIS_MAXAEP,
                             new ChMaskDblPos);
	m_eMAXAEP.SetMSStandard( TRUE );
	m_eMAXAEP.SetDialog();

// ---
	m_eMAXAVP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_MAXAVP,
                             L_ZARTPREIS_MAXAVP + 1,
                             N_ZARTPREIS_MAXAVP,
                             new ChMaskDblPos);
	m_eMAXAVP.SetMSStandard( TRUE );
	m_eMAXAVP.SetDialog();

// ---
	m_eLBP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_LIEFERBASISPREIS,
                             L_ZARTPREIS_LIEFERBASISPREIS + 1,
                             N_ZARTPREIS_LIEFERBASISPREIS,
                             new ChMaskDblPos,
							 new CV_ARTIKELPRICES_Proz_LBP( this ));
	m_eLBP.SetMSStandard( TRUE );
	m_eLBP.SetDialog();

// ---
	m_ePBP.SetMask	    (ED_DBL,
                             ED_NORMAL,
                             &m_PHARMACY_BASEPRICE,
                             L_ZARTPREIS_PHARMACY_BASEPRICE + 1,
                             N_ZARTPREIS_PHARMACY_BASEPRICE,
                             new ChMaskDblPos);
	m_ePBP.SetMSStandard( TRUE );
	m_ePBP.SetDialog();

// ---
	m_eERSTATTBETRAG.SetMask (ED_DBL,
                             ED_NORMAL,
                             &m_ERSTATTBETRAG,
                             L_ZARTPREIS_ERSTATTBETRAG + 1,
                             N_ZARTPREIS_ERSTATTBETRAG,
                             new ChMaskDblPos);
	m_eERSTATTBETRAG.SetMSStandard( TRUE );
	m_eERSTATTBETRAG.SetDialog();

// ---
	m_eGUELAB.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_DATUMGUELTIGAB,
                             L_LDATUM,
                             new ChMaskLDate,
							 new CV_ARTIKELPRICES_PreisDatum( this ));
	m_eGUELAB.SetMSStandard( TRUE );
	m_eGUELAB.SetDialog();
}

// --------------------------------------------------------------------- //
void CArtikelPrices::FillComboBoxVAT(long lDatum) 
{
	if (lDatum == 0)
	{
		if (m_DATUMGUELTIGAB == 0)
			lDatum = AddDayToPhoDate( ::Today(), 1 );
		else
			lDatum = m_DATUMGUELTIGAB;
	}

	int sel = m_cMWST.GetCurSel();

	if (sel < 0)
		sel = 0;
	
	if (IsCountry("BG") )
	{
		m_cMWST.ResetContent();
		m_cMWST.AddString(CResString::ex().getStrTblText(IDS_STRING10103));
	}
	// eingelesene Mwst-Saetze in Combo-Box stellen
	else if (IsCountry("F") || 
			IsCountry("HR") || 
			IsCountry("RS") ||
			IsCountry("A"))
	{
		m_cMWST.ResetContent();

		// Mwst-Prozentsätze aus der Taxtab-Klasse holen (jeweilige Landes-Reihenfolge beachten !!)
		double dMwstProz[5];
		CString	CsMwst;
		int	iAnzMwst = 0;

		if (IsCountry("F"))
			iAnzMwst = m_ArtPage1->m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[4], &dMwstProz[3]);
		else if (IsCountry("HR"))
			iAnzMwst = m_ArtPage1->m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[2], &dMwstProz[1], &dMwstProz[3], &dMwstProz[4]);
		else if (IsCountry("RS"))
		{
			iAnzMwst = m_ArtPage1->m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);
			iAnzMwst++;		// <--- damit auch hier der Wert 0,0% noch angezeigt wird
		}
		else if (IsCountry("A"))
		{
			iAnzMwst = m_ArtPage1->m_pTaxTb->GetAllVatRates( lDatum, &dMwstProz[0], &dMwstProz[1], &dMwstProz[2], &dMwstProz[3], &dMwstProz[4]);
			iAnzMwst++;
		}

		for (int i = 0; i < iAnzMwst; i++)
		{
			CsMwst.Format("%.1f %%", dMwstProz[i]);
			m_cMWST.AddString(CsMwst);
		}
	}	
	else
	{
		m_cMWST.ResetContent();
		m_cMWST.AddString(CResString::ex().getStrTblText(IDS_STRING10103));
		m_cMWST.AddString(CResString::ex().getStrTblText(IDS_STRING10104));
		m_cMWST.AddString(CResString::ex().getStrTblText(IDS_STRING10105));
	}

	m_cMWST.SetCurSel(sel);
}

// --------------------------------------------------------------------- //
void CArtikelPrices::FillComboBoxes() 
{
	FillComboBoxVAT(AddDayToPhoDate( ::Today(), 1 ));

// ---
	m_cDISC_DED_YET.ResetContent();
	m_cDISC_DED_YET.AddString(CResString::ex().getStrTblText(IDS_NO)); 
	m_cDISC_DED_YET.AddString(CResString::ex().getStrTblText(IDS_YES)); 
	m_cDISC_DED_YET.AddString(CResString::ex().getStrTblText(IDS_STRING_FORTGELTEND));

// ---

	m_cPREISTYP.ResetContent();
	if (IsCountry("BG"))
	{
		m_cPREISTYP.AddString(CResString::ex().getStrTblText(IDS_STRING500));
		m_cPREISTYP.AddString(CResString::ex().getStrTblText(IDS_STRING501));
	}
	else
		m_cPREISTYP.AddString(CResString::ex().getStrTblText(IDS_STANDARD));
}

// --------------------------------------------------------------------- //
void CArtikelPrices::Set_Herst_Prozent( )
{
	if (IsCountry("CH")) // herst_prozent hier für CH nicht setzen!
		return;

	int i;

	for ( i = 0; i < NUMBER_OF_PRICE ; i++ )
	{
		// in Frankreich immer nur den ersten Prozentsatz updaten
		if ( (m_pBuf[i].DATUMGUELTIGAB > ::Today() || i == 0 ) && (!(IsCountry("F") && i > 0)))
		{
			m_pBuf[i].HERST_PROZENT = m_pBufArtikel->HERST_PROZENT; 
		} 
	}

	m_cPRICESBOX.DeleteAllItems();
	
	CopyPriceBufferToGuiList();

	MarkListPos( 0 );	
}

// --------------------------------------------------------------------- //
void CArtikelPrices::CopyPriceBufferToGuiList()
{
	CStringArray s;

	for ( int i = 0; i < NUMBER_OF_PRICE; i++ )
	{
		FillBuffer( i, s );

		if (i > 0 && 
			m_pBuf[i].DATUMGUELTIGAB == 0 && 
			(i == NUMBER_OF_PRICE - 1 || m_pBuf[i+1].DATUMGUELTIGAB == 0 )) // keine Leerzeilen am Ende
			break;

		FillSuchBox( s );
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CArtikelPrices message handlers

BOOL CArtikelPrices::PreTranslateMessage(MSG* pMsg) 
{
 	if(m_hAccelerator)
    {
        if (::TranslateAccelerator(m_hWnd, m_hAccelerator, pMsg)) 
            return(TRUE);
    }
	
	return CDialogMultiLang::PreTranslateMessage(pMsg);
}

BOOL CArtikelPrices::OnInitDialog() 
{
	CDialogMultiLang::OnInitDialog();

	if ( !InitSuchBox() ) 
		return FALSE;

	CopyPriceBufferToGuiList();

	FillComboBoxes();

	m_eHPROZ_ART.p_SetInput();	

	MarkListPos( 0 );

	EnableCalcButton();

	m_hAccelerator = LoadAccelerators(AfxGetApp()->m_hInstance,
					MAKEINTRESOURCE(IDR_ARTIKEL_PRICES)); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//m_eGUELAB.SetFocus();	
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnPbArtikelPricesCalculate()
{
	if (m_pBuf[1].DATUMGUELTIGAB > ::Today())
		MarkListPos(1); // kein neuer Preissatz, sondern berechnen für den schon existenten Preissatz in der Zukunft
	else
		CopyPrice(1);

	m_HERST_PROZENT = m_pBufArtikel->HERST_PROZENT;
	m_eHPROZ.p_SetInput();

	if (m_HERST_PROZENT > 0.0)
	{
		// AEP aus Grosso berechnen
		m_AEP = PreisAusProzent(m_GROSSO, m_HERST_PROZENT);
	}
	else // m_HERST_PROZENT < 0.0
	{
		// Grosso aus AEP berechnen
		m_GROSSO = PreisAusProzent(m_AEP, m_HERST_PROZENT);
	}

	m_eAEP.p_SetInput();
	m_eGROSSO.p_SetInput();
}

// --------------------------------------------------------------------- //
double CArtikelPrices::PreisAusProzent ( const double preis, const double proz )
{
  double wert;

  wert = preis*proz/100.0;

  wert += preis;
  KaufmRunden( &wert, 2);

  return wert;
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnPbArtikelPricesEnd() 
{
	m_eHPROZ_ART.p_GetInput();
	CDialogMultiLang::OnOK();	
}


// --------------------------------------------------------------------- //
void CArtikelPrices::OnClose() 
{
	m_eHPROZ_ART.p_GetInput();
	// TODO: Add your message handler code here and/or call default
	CDialogMultiLang::OnClose();
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnOK()  
{
	NextDlgCtrl();
}

// --------------------------------------------------------------------- //
void CArtikelPrices::CopySinglePriceToGui(int pos, bool withoutMwst)
{
	strcpy( m_PUBLICATIONNUMBER, m_pBuf[pos].PUBLICATIONNUMBER );
	m_ePUBL_NR.p_SetInput();

	if (withoutMwst == false)
	{
		strcpy( m_KE_MWST, m_pBuf[pos].KE_MWST );
		m_cMWST.p_SetInput();
	}

	m_GROSSO = m_pBuf[pos].GROSSO;
	m_eGROSSO.p_SetInput();

	m_AEP = m_pBuf[pos].AEP;
	m_eAEP.p_SetInput();

	m_AGP = m_pBuf[pos].AGP;
	m_eAGP.p_SetInput();

	m_AVP = m_pBuf[pos].AVP;
	m_eAVP.p_SetInput();

	m_HERST_PROZENT = m_pBuf[pos].HERST_PROZENT;
	m_eHPROZ.p_SetInput();

	m_EAVP = m_pBuf[pos].EAVP;
	m_eEAVP.p_SetInput();

	m_MAXAVP = m_pBuf[pos].MAXAVP;
	m_eMAXAVP.p_SetInput();

	m_PREIS_TYP = m_pBuf[pos].PREIS_TYP;
	m_cPREISTYP.p_SetInput();

	m_LIEFERBASISPREIS = m_pBuf[pos].LIEFERBASISPREIS;
	m_eLBP.p_SetInput();

	m_MAXAEP = m_pBuf[pos].MAXAEP;
	m_eMAXAEP.p_SetInput();

	m_ERSTATTBETRAG = m_pBuf[pos].ERSTATTBETRAG;
	m_eERSTATTBETRAG.p_SetInput();

	m_DISC_DEDUCED_YET = m_pBuf[pos].DISC_DEDUCED_YET;
	m_cDISC_DED_YET.p_SetInput();

	m_PHARMACY_BASEPRICE = m_pBuf[pos].PHARMACY_BASEPRICE;
	m_ePBP.p_SetInput();
}
 
// --------------------------------------------------------------------- //
void CArtikelPrices::OnItemchangedLcArtikelPricesBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int iItem = pNMListView->iItem;

	CopySinglePriceToGui(iItem);
	
	m_DATUMGUELTIGAB = m_pBuf[iItem].DATUMGUELTIGAB;
	
	int pos = GetSelectedRow();
    if ( pos < 0  || // keine Zeile markiert!
		(m_DATUMGUELTIGAB != 0 && m_DATUMGUELTIGAB < AddDayToPhoDate( ::Today(), 1 )) ) // bereits gültige Preise sind nicht änderbar!
	{
		DisableFields(); 

		if (pos > 0)
			EnableNewButton(); // Preis markiert, von dem kopiert werden könnte
	}
	else
	{
		EnableFields();
	}	

	if (m_DATUMGUELTIGAB == 0)
	{
		SetDateTomorrow();
		m_bNEW.EnableWindow(false); // Preis nicht kopierbar
	}
	
	m_eGUELAB.p_SetInput();
	
	*pResult = 0;
}

// --------------------------------------------------------------------- //
void CArtikelPrices::SetDateTomorrow()
{
	if ( m_pBuf[1].DATUMGUELTIGAB <= ::Today() )
		m_DATUMGUELTIGAB = AddDayToPhoDate( ::Today(), 1 );
	else
		m_DATUMGUELTIGAB = AddDayToPhoDate( m_pBuf[1].DATUMGUELTIGAB, 1 );
}


// --------------------------------------------------------------------- //
void CArtikelPrices::AppendBlanks( char *str, int lng )
{
	int slng = static_cast<int>(strlen( str ));
	if ( slng < lng )
		memset( &str[slng], ' ', lng - slng );
	str[lng] = '\0';
}

// --------------------------------------------------------------------- //
void CArtikelPrices::CopyGuiToPriceBuffer(int pos)
{
	m_eGUELAB.p_GetInput();
	m_pBuf[pos].DATUMGUELTIGAB = m_DATUMGUELTIGAB;

	m_eGROSSO.p_GetInput();
	m_pBuf[pos].GROSSO = m_GROSSO;
	
	m_ePUBL_NR.p_GetInput();
	strcpy( m_pBuf[pos].PUBLICATIONNUMBER, m_PUBLICATIONNUMBER );

	m_cMWST.p_GetInput();
	strcpy( m_pBuf[pos].KE_MWST, m_KE_MWST );

	m_cPREISTYP.p_GetInput();
	m_pBuf[pos].PREIS_TYP = m_PREIS_TYP;

	m_cDISC_DED_YET.p_GetInput();
	m_pBuf[pos].DISC_DEDUCED_YET = m_DISC_DEDUCED_YET;

	m_eAEP.p_GetInput();
	m_pBuf[pos].AEP = m_AEP;

	m_eAGP.p_GetInput();
	m_pBuf[pos].AGP = m_AGP;

	m_eAVP.p_GetInput();
	m_pBuf[pos].AVP = m_AVP;

	m_eEAVP.p_GetInput();
	m_pBuf[pos].EAVP = m_EAVP;

	m_eMAXAEP.p_GetInput();
	m_pBuf[pos].MAXAEP = m_MAXAEP;

	m_eMAXAVP.p_GetInput();
	m_pBuf[pos].MAXAVP = m_MAXAVP;

	m_eHPROZ.p_GetInput();
	m_pBuf[pos].HERST_PROZENT = m_HERST_PROZENT;

	m_eLBP.p_GetInput();
	m_pBuf[pos].LIEFERBASISPREIS = m_LIEFERBASISPREIS;

	m_ePBP.p_GetInput();
	m_pBuf[pos].PHARMACY_BASEPRICE = m_PHARMACY_BASEPRICE;

	m_eERSTATTBETRAG.p_GetInput();
	m_pBuf[pos].ERSTATTBETRAG = m_ERSTATTBETRAG;
}

// --------------------------------------------------------------------- //
int CArtikelPrices::GetSelectedRow()
{
	return m_cPRICESBOX.GetNextItem(-1, LVNI_SELECTED);
}

// --------------------------------------------------------------------- //
bool CArtikelPrices::Test_MaxAep_MaxAvp( )
{
	m_eAEP.p_GetInput();
	m_eAVP.p_GetInput();
	m_eMAXAEP.p_GetInput();
	m_eMAXAVP.p_GetInput();
		
	if ( m_AEP > m_MAXAEP && m_MAXAEP > 0.0	)	 
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_AEP_OVER_MAXAEP) );
		m_eMAXAEP.SetFocus();
		return false;
	}

	if ( m_AVP > m_MAXAVP && m_MAXAVP > 0.0 )
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_AVP_OVER_MAXAVP) );
		m_eMAXAVP.SetFocus();
		return false;
	}

	return true;
}

// --------------------------------------------------------------------- //
bool CArtikelPrices::Test_NichtTaxartikel(  )
{
	m_eGROSSO.p_GetInput();
	m_eAEP.p_GetInput();	
	m_eAGP.p_GetInput();
	m_eAVP.p_GetInput();

	// in der Schweiz gibt es keinen AEP
	if (IsCountry("CH"))
	{
		//if (IsAGP() == TRUE) // normally used to differentiate between prewholesale and wholesale
		if (IsPrewhole() == FALSE)
		{
			// GEP > 0, AGP > 0, AVP > GEP && AVP > AGP
			if ((m_GROSSO > 0.0) && (m_AGP > 0.0) && (m_AVP > m_GROSSO) && (m_AVP > m_AGP))
				return true;
			// GEP > 0, AGP = 0, AVP > GEP
			if ((m_GROSSO > 0.0) && (m_AGP == 0.0) && (m_AVP > m_GROSSO))
				return true;
			// GEP = 0, AGP > 0, AVP > AGP
			if ((m_GROSSO == 0.0) && (m_AGP > 0.0) && (m_AVP > m_AGP))
				return true;
			// GEP > 0, AVP = 0
			if ((m_GROSSO > 0.0) && (m_AVP == 0.0))
				return true;
			// AGP > 0, AVP = 0
			if ((m_AGP > 0.0) && (m_AVP == 0.0))
				return true;
		}
	}
	else if (IsCountry("F"))
	{
		// GEP > 0, AEP >= GEP, AVP > AEP
		if (m_GROSSO > 0.0 &&
			m_AEP >= m_GROSSO &&
			m_AVP > m_AEP)
			return true;

		// GEP > = AEP >= GEP , AVP = 0
		if (m_GROSSO > 0.0 &&
			m_AEP >= m_GROSSO &&
			m_AVP == 0.0)
			return true;
	}
	else
	{
		// GEP > 0, AEP > GEP, AVP > AEP
		if ( m_GROSSO >  0.0 &&
			m_AEP    >  m_GROSSO &&
			m_AVP    >  m_AEP   )  
			return true;

		// GEP > 0, AEP > GEP, AVP = 0
		if ( m_GROSSO >  0.0 &&
			m_AEP    >  m_GROSSO &&
			m_AVP    == 0.0   )  
			return true;
	}

	if ( m_pBufArtikel->PREIS0ARTIKEL[0] == '1' )
	{
		// PREIS0ARTIKEL wenn Grosso = 0, AVP = 0 ( vorher zusaetzlich AEP = 0 )
		if ( m_GROSSO == 0.0 &&
			 m_AVP    == 0.0    )
			 return true;
	}

	if ( m_pBufArtikel->NICHTUEBERGH[0] == '1' )
	{
		// GEP = 0, AEP > 0, AVP = 0
		if ( m_GROSSO == 0.0 &&
			 m_AEP    >  0.0 &&
			 m_AVP    == 0.0    )
			 return true;

		// GEP = 0, AEP > 0, AVP > AEP
		if ( m_GROSSO == 0.0 &&
			 m_AEP    >  0.0 &&
			 m_AVP    >  m_AEP )
			 return true;

		if (IsCountry("D")) // IFA liefert für alle Artikel mit bisher Grosso = 0 ab 2011 Grosso = AEP
		{
			// GEP > 0, AEP >= GEP, AVP > AEP
			if ( m_GROSSO >  0.0 &&
				 m_AEP    >=  m_GROSSO &&
				 m_AVP    >  m_AEP   )  
				 return true;

			// GEP > 0, AEP >= GEP, AVP = 0
			if ( m_GROSSO >  0.0 &&
				 m_AEP    >= m_GROSSO &&
				 m_AVP    == 0.0   )  
				 return true;
		}
	}

	// in Kroatien & Bulgarien ist auch GEP = AEP ok
	if (IsCountry("HR") || IsCountry("BG"))
	{
		// GEP > 0, AEP = GEP, AVP = 0
		if ( m_GROSSO	>  0.0 &&
			m_AEP		== m_GROSSO &&
			m_AVP		== 0.0 )  
			return true;

		// GEP > 0, AEP = GEP, AVP > AEP
		if ( m_GROSSO	>  0.0 &&
			m_AEP		== m_GROSSO &&
			m_AVP		>  m_AEP )  
			return true;
	}

	// in Serbien ist auch GEP > AEP ok (pervers !!)
	if (IsCountry("RS"))
	{
		// GEP > 0, AEP <= GEP, AVP = 0
		if ( m_GROSSO	>  0.0 &&
			 m_AEP		<= m_GROSSO &&
			 m_AVP		== 0.0 )  
			 return true;

		// GEP > 0, AEP <= GEP, AVP > AEP
		if ( m_GROSSO	>  0.0 &&
			 m_AEP		<= m_GROSSO &&
			 m_AVP		>  m_AEP )  
			 return true;
	}

	// in Kroatien ist auch AEP = AVP ok
	if (IsCountry("HR"))
	{
		// GEP > 0, AEP > GEP, AVP = AEP
		if ( m_GROSSO	>  0.0 &&
			 m_AEP		>  m_GROSSO &&
			 m_AVP		== m_AEP )  
			 return true;
	}

	MsgBoxOK( CResString::ex().getStrTblText(IDS_PRICE_ERR) );

	m_eGROSSO.SetFocus();

	return false;
}

// --------------------------------------------------------------------- //
bool CArtikelPrices::Test_NichtTaxartikelGesperrt(  )
{
	m_eGROSSO.p_GetInput();
	m_eAEP.p_GetInput();	
	m_eAGP.p_GetInput();
	m_eAVP.p_GetInput();

	// GEP = 0, AEP = 0, AVP >= 0
	if ( m_GROSSO == 0.0 &&
		 m_AEP    == 0.0 &&
		 m_AVP    >= 0.0    )  
		 return true;

	// GEP = 0, AEP >= 0, AVP = 0
	if ( m_GROSSO == 0.0 &&
		 m_AEP    >= 0.0 &&
		 m_AVP    == 0.0    )  
		 return true;

	// GEP = 0, AEP > 0, AVP > AEP
	if ( m_GROSSO == 0.0 &&
		 m_AEP    >  0.0 &&
		 m_AVP    >  m_AEP )  
		 return true;

	// in der Schweiz gibt es keinen AEP
	if (IsCountry("CH"))
	{
		//if (IsAGP() == TRUE) // normally used to differentiate between prewholesale and wholesale
		if (IsPrewhole() == FALSE)
		{
			// GEP > 0, AGP > 0, AVP > GEP && AVP > AGP
			if ((m_GROSSO > 0.0) && (m_AGP > 0.0) && (m_AVP > m_GROSSO) && (m_AVP > m_AGP))
				return true;
			// GEP > 0, AGP = 0, AVP > GEP
			if ((m_GROSSO > 0.0) && (m_AGP == 0.0) && (m_AVP > m_GROSSO))
				return true;
			// GEP = 0, AGP > 0, AVP > AGP
			if ((m_GROSSO == 0.0) && (m_AGP > 0.0) && (m_AVP > m_AGP))
				return true;
			// GEP > 0, AVP = 0
			if ((m_GROSSO > 0.0) && (m_AVP == 0.0))
				return true;
			// AGP > 0, AVP = 0
			if ((m_AGP > 0.0) && (m_AVP == 0.0))
				return true;
		}
	}
	else if (IsCountry("F"))
	{
		// GEP > 0, AEP >= GEP, AVP > AEP
		if (m_GROSSO > 0.0 &&
			m_AEP >= m_GROSSO &&
			m_AVP > m_AEP)
			return true;

		// GEP > = AEP >= GEP , AVP = 0
		if (m_GROSSO > 0.0 &&
			m_AEP >= m_GROSSO &&
			m_AVP == 0.0)
			return true;
	}
	else
	{
		// GEP > 0, AEP >= GEP (muss lt. Hr. Peetz so sein), AVP = 0
		if ( m_GROSSO >  0.0 &&
			 m_AEP    >=  m_GROSSO &&
			 m_AVP    == 0.0   )  
			return true;

		// GEP > 0, AEP > GEP, AVP > AEP
		if ( m_GROSSO >  0.0 &&
			 m_AEP    >  m_GROSSO &&
			 m_AVP    >  m_AEP   )  
			return true;
	}

	// in Kroatien & Bulgarien & Deutschland ist auch GEP = AEP ok
	if (IsCountry("HR") || IsCountry("BG") || IsCountry("D"))
	{
		// GEP > 0, AEP = GEP, AVP = 0
		if ( m_GROSSO	>  0.0 &&
			m_AEP		== m_GROSSO &&
			m_AVP		== 0.0 )  
			return true;

		// GEP > 0, AEP = GEP, AVP > AEP
		if ( m_GROSSO	>  0.0 &&
			m_AEP		== m_GROSSO &&
			m_AVP		>  m_AEP )  
			return true;
	}

	// in Serbien ist auch GEP > AEP ok (pervers !!)
	if (IsCountry("RS"))
	{
		// GEP > 0, AEP <= GEP, AVP = 0
		if ( m_GROSSO	>  0.0 &&
			 m_AEP		<= m_GROSSO &&
			 m_AVP		== 0.0 )  
			 return true;

		// GEP > 0, AEP <= GEP, AVP > AEP
		if ( m_GROSSO	>  0.0 &&
			 m_AEP		<= m_GROSSO &&
			 m_AVP		>  m_AEP )  
			 return true;
	}

	// in Kroatien ist auch AEP = AVP ok
	if (IsCountry("HR"))
	{
		// GEP = 0, AEP > 0, AVP = AEP
		if ( m_GROSSO	== 0.0 &&
			m_AEP		>  0.0 &&
			m_AVP		== m_AEP )  
			return true;

		// GEP > 0, AEP > GEP, AVP = AEP
		if ( m_GROSSO	>  0.0 &&
			 m_AEP		>  m_GROSSO &&
			 m_AVP		== m_AEP )  
			 return true;
	}

	MsgBoxOK( CResString::ex().getStrTblText(IDS_PRICE_ERR) );

	m_eGROSSO.SetFocus();

	return false;
}

// --------------------------------------------------------------------- //
bool CArtikelPrices::Test_PreisAufNull(  )
{
	m_eGROSSO.p_GetInput();
	m_eAEP.p_GetInput();	
	m_eAVP.p_GetInput();

	int pos = GetSelectedRow();

	// wenn Preis0Artikel geaendert auf Preis0Artikel = ja
	// dann muss ein neuer Preis eingegeben werden
	if ( false == m_ArtPage1->NeuGleichAlt( *m_pBufArtikel->PREIS0ARTIKEL, *m_ArtPage1->m_pBufOldZartikel->PREIS0ARTIKEL ) &&
		 *m_pBufArtikel->PREIS0ARTIKEL == '1' )
	{
		// PREIS0ARTIKEL wenn Grosso = 0, AVP = 0 ( vorher zusaetzlich AEP = 0 )
		if ( m_GROSSO > 0.0 ||
			 m_AVP    > 0.0    )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_FREE_ART2) );
			m_eGROSSO.SetFocus();
			return false;
		}

		return true;
	}

	// Normalfall
	// neu ab 24.11.98: wenn ueber GH, dann darf Grosso auf Null gehen
	if ( *m_pBufArtikel->NICHTUEBERGH == '0' )
	{
		if ( m_GROSSO	  == 0.0 && 
			 m_pBuf[pos+1].GROSSO   > 0.0 &&
			 *m_pBufArtikel->PREIS0ARTIKEL == '0' )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_GEP_CHANGE) );
			m_eGROSSO.SetFocus();
			return false;
		}
	}

	// bei Amedis gibt's keinen AEP, also darf der auch 0 sein
	// 05.07.11 Mr Ponudic: "Please enable setting price to 0 for Croatia"
	// 02.05.17 Hellmich-Scheuch: "auch in AT erlauben"
	if (!IsCountry("CH") && !IsCountry("HR") && !IsCountry("A"))
	{
		if ( m_AEP == 0.0 &&
			 m_pBuf[pos+1].AEP > 0.0 &&
			 m_pBuf[pos].DATUMGUELTIGAB == 0)
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_AEP_CHANGE) );
			m_eAEP.SetFocus();
			return false;
		}
	}

	return true;
}

// --------------------------------------------------------------------- //
bool CArtikelPrices::Test_Taxartikel( )
{
	double aep;
	double avp;
	double diff;
	int mwst = 0;
	bool bAepNachTaxe = true;

	m_eGROSSO.p_GetInput();
	m_eAEP.p_GetInput();	
	m_eAVP.p_GetInput();
	m_eGUELAB.p_GetInput();
	m_cPREISTYP.p_GetInput();
	m_cMWST.p_GetInput();

	if ( m_GROSSO == 0.0 )
	{
		if ( m_pBufArtikel->NICHTUEBERGH[0] != '1' )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_GEP_NOT_0) );
			m_eGROSSO.SetFocus();
			return false;
		}
		bAepNachTaxe = false;
	}
	
	//ab 2011: keine AEP- Taxprüfung für NGH- Artikel 
	if ( m_pBufArtikel->NICHTUEBERGH[0] == '1' &&
		 IsCountry("D") )
		bAepNachTaxe = false;

	if ( m_AEP == 0.0 )
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_AEP_NOT_0) );
		m_eAEP.SetFocus();
		return false;
	}

	if ( (m_GROSSO  > m_AEP ||
		  m_GROSSO == m_AEP && !IsCountry("D"))) 
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_AEP_OVER_GEP) );
		m_eAEP.SetFocus();
		return false;
	}

	if ( m_pBufArtikel->TAXPRUEFGROSSO[0] == '1' )
		 bAepNachTaxe = false;

	if ( bAepNachTaxe )
	{
		if (IsCountry("A"))
		{
			m_ArtPage1->m_pTaxTb->CalcAekAustria( m_GROSSO, &aep, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );
		}
		else if (IsCountry("F"))
		{
			m_ArtPage1->m_pTaxTb->CalcAekFrance( m_GROSSO, &aep, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );
		}
		else if (IsCountry("BG"))
		{
			m_ArtPage1->m_pTaxTb->CalcAekBulgaria( m_GROSSO, &aep, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0], m_PREIS_TYP );
		}
		else
		{
			m_ArtPage1->m_pTaxTb->CalcAek( m_GROSSO, &aep, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );			// OTCX_RX
		}

		diff = m_AEP - aep;
		if ( diff < -0.005 || diff > 0.005 )
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_AEP_TAX_ERR) );
			m_eAEP.SetFocus();
			return false;
		}
	}

	// 4 Mwst-Sätze in Frankreich
	if (IsCountry("F"))
	{
		if ( m_KE_MWST[0] == '3' )		
			mwst = TAXTAB_FR_MWST_3;
		else if ( m_KE_MWST[0] == '2' )	
			mwst = TAXTAB_FR_MWST_2;
		else if ( m_KE_MWST[0] == '1' )	
			mwst = TAXTAB_FR_MWST_1;
		else if ( m_KE_MWST[0] == '4' )	
			mwst = TAXTAB_FR_MWST_4;
		else												
			mwst = TAXTAB_FR_MWST_0;
	}
	else if(IsCountry("A"))
	{
		if ( m_KE_MWST[0] == '1' )			// Vermindert
			mwst = TAXTAB_AT_VERMM;
		else if ( m_KE_MWST[0] == '0' )		// Voll
			mwst = TAXTAB_AT_VOLL;
		else if ( m_KE_MWST[0] == '2' )		// 3RD-VAT
			mwst = TAXTAB_AT_3RD;
		else if (m_KE_MWST[0] == '3')		// 0
			mwst = 3;
	}
	else 
	{
		if ( m_KE_MWST[0] == '1' )                      // Vermindert 
			mwst = TAXTAB_IS_VERMMWST; 
		else if ( m_KE_MWST[0] == '0' )         // Voll 
			mwst = TAXTAB_IS_VOLLMWST; 
		else if ( m_KE_MWST[0] == '2' )         // Ohne 
			mwst = TAXTAB_IS_OHNEMWST; 
    }


	if (IsCountry("A"))  // 3RD-VAT
	{
		m_ArtPage1->m_pTaxTb->CalcAvkAustriaMwst( m_AEP, &avp, mwst, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0], m_pBufArtikel->BTM[0] );

	}
	else if (IsCountry("F"))
	{
		m_ArtPage1->m_pTaxTb->CalcAvkFranceMwst( m_GROSSO, m_AEP, &avp, mwst, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0] );	
	}
	else if (IsCountry("BG"))
	{
		m_ArtPage1->m_pTaxTb->CalcAvkBulgariaMwst( m_GROSSO, &avp, mwst, m_DATUMGUELTIGAB, m_pBufArtikel->TAXPFL[0], m_PREIS_TYP );
	}
	else
	{
		m_ArtPage1->m_pTaxTb->CalcAvkMwst( m_AEP, &avp, mwst, m_DATUMGUELTIGAB,	m_pBufArtikel->TAXPFL[0] );			// OTCX_RX
	}

	// keine Taxtabelle für AVP und Preistyp 1 in Bulgarien hinterlegt, also auch keine Prüfung des AVPs
	if (IsCountry("BG") && m_PREIS_TYP == 1)
		return true;

	diff = m_AVP - avp;

	if(diff < -0.005 || diff > 0.005)
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_AVP_TAX_ERR) );
		m_eAVP.SetFocus();
		return false;
	}

	return TRUE;
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnPbArtikelPricesSave() 
{
	m_eHPROZ_ART.p_GetInput();
	int pos;
	if ((pos = GetSelectedRow()) >= 0)
	{
		m_eGUELAB.p_GetInput();
		if (( m_DATUMGUELTIGAB <= ::Today() || 
			 (m_DATUMGUELTIGAB <= m_pBuf[pos + 1].DATUMGUELTIGAB && m_pBuf[pos + 1].DATUMGUELTIGAB > 0)) &&
			 m_DATUMGUELTIGAB > 0		) // Datum = 0 erlaubt, dadurch wird bisheriger Satz in der Zukunft wieder gelöscht
		{
			MsgBoxOK( CResString::ex().getStrTblText(IDS_PREISDATUM) );
			return;
		}

		if (m_DATUMGUELTIGAB > 0 && Test_Preis() == false)
			return;

		if ( m_pBuf[pos].DATUMGUELTIGAB > 0 )
		{
			// Frage (nur bei Änderung, nicht bei Neuanlage): "Preis ändern?"
			if ( MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING1434), MB_ICONQUESTION | MB_DEFBUTTON2 ) == IDNO ) 
				return;
		}
		
		CopyGuiToPriceBuffer(pos);

		if (pos == 0 && IsCountry("F") && m_pBuf[pos].GROSSO < m_pBuf[pos+1].GROSSO) // Neuanlage in Frankreich + Preissenkung
		{
			int delayAep = 0;
			int delayAvp = 0;

			CString sql;
			sql.Format("select delaypharmacyprice, delaypublicprice from cpricevaliddelay where "
						"commoditygroupfrom <= '%s' and commoditygroupto >= '%s' and reimbursement_type = '%s' and produktart = '%s'", 
						m_ArtPage1->m_pBuf->zartwg[1].WARENGRUPPE,
						m_ArtPage1->m_pBuf->zartwg[1].WARENGRUPPE,
						m_ArtPage1->m_pBuf->zartfrance.REIMBURSEMENT_TYPE,
						m_pBufArtikel->PRODUKTART);

			// lesen cpricevaliddelay
			if ( SqlRead(sql, &delayAep, &delayAvp, NULL) == 0 )
			{
				// Frage: "automatische Preisreihe anlegen?"
				if ( MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING1422), MB_ICONQUESTION | MB_DEFBUTTON2 ) == IDYES ) 
				{
			
					// shift ArtikelPreisPuffer
					CString err;
					((CArtikelView* )m_pView)->m_Doc.Shift_Artpreis(2, err); // insgesamt werden in einem Schritt 3 neue Preise angelegt - 
																			 // daher zur bereits für Neuanlagen vorgesehenen Zeile 0 noch 2 weitere Leerzeilen vorne einfügen

					CopyGuiToPriceBuffer(0);
					m_pBuf[0].DATUMGUELTIGAB = AddDayToPhoDate( m_DATUMGUELTIGAB, delayAvp ); // Aktivierung AVP

					CopyGuiToPriceBuffer(1);
					m_pBuf[1].DATUMGUELTIGAB = AddDayToPhoDate( m_DATUMGUELTIGAB, delayAep ); // Aktivierung AEP
					// AVP aus letztem gültigen Preis übernehmen
					m_pBuf[1].AVP = m_pBuf[3].AVP;

					// AEP + AVP aus letztem gültigen Preis übernehmen
					m_pBuf[2].AEP = m_pBuf[3].AEP;
					m_pBuf[2].AVP = m_pBuf[3].AVP;
					
					pos = 2; // ??? gewünscht ???

					// prüfen aller 3 Preisreihen ???
				}
			}
			/*
			else
			{
				MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING1423));
			}
			*/
		}
		
		m_cPRICESBOX.DeleteAllItems();

		CopyPriceBufferToGuiList();

		MarkListPos( pos );	
	}
	else
		MarkListPos( 0 );	
}

// --------------------------------------------------------------------- //
void CArtikelPrices::CopyPrice(int pos)
{
	MarkListPos( 0 );

	SetDateTomorrow();
	m_eGUELAB.p_SetInput();

	CopySinglePriceToGui(pos);
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnPbArtikelPricesNew() 
{
	m_eHPROZ_ART.p_GetInput();

	// kopieren der markierten Zeile als Vorlage für neuen Preis
	int pos = GetSelectedRow();

	CopyPrice(pos);
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnSelchangeCbArtikelMwst()
{
	m_cMWST.p_GetInput();

	// wenn kein neuer Preis eingegeben, fragen, ob der alte übernommen werden soll
	if ( m_pBuf[0].DATUMGUELTIGAB == 0 )
	{
		if (MsgBoxYesNo( CResString::ex().getStrTblText(IDS_TAKE_PRICE) ) == IDYES)
		{
			MarkListPos( 0 );

			SetDateTomorrow();
			m_eGUELAB.p_SetInput();

			CopySinglePriceToGui(1, true);
	
			// ggfs. AVP neu berechnen
			Set_Taxe_AVP();
		}
	}
	else
	// ansonsten direkt AVP neu berechnen
	{
		Set_Taxe_AVP();
	}
}

// --------------------------------------------------------------------- //
bool CArtikelPrices::Test_Preis( )
{
	bool bOk;

	if ( m_pBufArtikel->TAXPFL[0] != '0' && !IsCountry("F"))		// OTCX_RX - keine Prüfung in FR!
	{
		bOk = Test_Taxartikel( );
	}
	else		// NichtTaxartikel
	{
		if ( m_pBufArtikel->ARTIKEL_GESPERRT[0] == '1' )
			bOk = Test_NichtTaxartikelGesperrt( );
		else	
			bOk = Test_NichtTaxartikel( );
	}

	if ( bOk )
		bOk = Test_PreisAufNull( );

	if ( bOk )
		bOk = Test_MaxAep_MaxAvp( );

	return bOk;
}

// --------------------------------------------------------------------- //
void CArtikelPrices::OnSelchangeCbArtikelPreistyp()
{
	CString cErrmld;
	long lStatus;

	// Preise neu lesen und anzeigen
	m_cPREISTYP.p_GetInput();
	m_ArtPage1->m_pBuf->sPreistyp = m_PREIS_TYP;

	lStatus = ((CArtikelView* )m_pView)->m_Doc.ReadRecord_Artpreis( cErrmld );

	if ( !( lStatus == 0 || lStatus == 100 ) ) 
	{
		MsgBoxOK(cErrmld);
		return;
	}

	m_cPRICESBOX.DeleteAllItems();
	
	CopyPriceBufferToGuiList();

	MarkListPos( 0 );	
}
