// ChAgpBaseView.cpp : implementation file
//

#include "stdafx.h"
#include "Ekzdp.h"

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <hdatum/phodate.h>
#include <phxlib/PhxUtil.h>
#include "znb_gen_li.h"
#include <phxlib/EanTest.h>

#include "AgpView.h"




// Validations
class CV_CAGP_ArtikelNr : public ChValBase
{
public:
	CV_CAGP_ArtikelNr(struct CAGPART* pBuf) : ChValBase(pBuf) {};
	BOOL Validate(BOOL bMeldung)
	{
		long artikel_nr = ((struct CAGPART*)(m_pBuf))->PZN;
		BOOL bOk = artikel_nr != 0 && artikel_nr <= 9999999;

		if (!bOk && bMeldung)
			MsgBoxOK(_T(CResString::ex().getStrTblText(IDS_PZN_NOT_NULL)));

		return bOk;
	}
};

// AgpView 
IMPLEMENT_DYNCREATE(CAgpView, CFormViewMultiLang)

CAgpView::CAgpView()
	: ChPflegeView(IDD)
{
	// Sets next and previous button to False
	m_bNext = FALSE;
	m_bPrev = FALSE;
}

CAgpView::~CAgpView()
{
}

// Data binding with UI controls
void CAgpView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_AGP_PZN, m_AgpPZN);
	DDX_Control(pDX, IDC_ST_AGP_PREIS1, m_agpPreis1);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB1, m_gueltigAb1);
	DDX_Control(pDX, IDC_ST_AGP_PREIS2, m_agpPreis2);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB2, m_gueltigAb2);
	DDX_Control(pDX, IDC_ST_AGP_PREIS3, m_agpPreis3);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB3, m_gueltigAb3);
	DDX_Control(pDX, IDC_ST_AGP_PREIS4, m_agpPreis4);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB4, m_gueltigAb4);
	DDX_Control(pDX, IDC_ST_AGP_PREIS5, m_agpPreis5);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB5, m_gueltigAb5);
	DDX_Control(pDX, IDC_ST_AGP_PREIS6, m_agpPreis6);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB6, m_gueltigAb6);
	DDX_Control(pDX, IDC_ST_AGP_PREIS7, m_agpPreis7);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB7, m_gueltigAb7);
	DDX_Control(pDX, IDC_ST_AGP_PREIS8, m_agpPreis8);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB8, m_gueltigAb8);
	DDX_Control(pDX, IDC_ST_AGP_PREIS9, m_agpPreis9);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB9, m_gueltigAb9);
	DDX_Control(pDX, IDC_ST_AGP_PREIS10, m_agpPreis10);
	DDX_Control(pDX, IDC_ST_AGP_GUELTIGAB10, m_gueltigAb10);

	DDX_Control(pDX, IDC_ST_AGP_DETAILS, m_agpDetails);
}

// MESSAGE handling
BEGIN_MESSAGE_MAP(CAgpView, CFormViewMultiLang)
	ON_MESSAGE(ID_ARTAGP_END, OnArtAgpEnd) // Message from ArtikelAGP view to show artikel details.

END_MESSAGE_MAP()

// Resets AGP controls
void CAgpView::ResetAGPControls()
{
	int anz = 0;
	while (anz < AGPART_ANZ)
	{
		m_agpControls[anz].agpPreis = _T("");
		m_agpControls[anz].gueltigAb = _T("");
		m_agpControls[anz].agpCtl->SetWindowText("");
		m_agpControls[anz].gueltigAbCtl->SetWindowText("");
		anz++;
	}
}

// Initilaize AGP controls
void CAgpView::InitAGPControls()
{

	m_agpControls[0].agpCtl = &m_agpPreis1;
	m_agpControls[1].agpCtl = &m_agpPreis2;
	m_agpControls[2].agpCtl = &m_agpPreis3;
	m_agpControls[3].agpCtl = &m_agpPreis4;
	m_agpControls[4].agpCtl = &m_agpPreis5;
	m_agpControls[5].agpCtl = &m_agpPreis6;
	m_agpControls[6].agpCtl = &m_agpPreis7;
	m_agpControls[7].agpCtl = &m_agpPreis8;
	m_agpControls[8].agpCtl = &m_agpPreis9;
	m_agpControls[9].agpCtl = &m_agpPreis10;

	m_agpControls[0].gueltigAbCtl = &m_gueltigAb1;
	m_agpControls[1].gueltigAbCtl = &m_gueltigAb2;
	m_agpControls[2].gueltigAbCtl = &m_gueltigAb3;
	m_agpControls[3].gueltigAbCtl = &m_gueltigAb4;
	m_agpControls[4].gueltigAbCtl = &m_gueltigAb5;
	m_agpControls[5].gueltigAbCtl = &m_gueltigAb6;
	m_agpControls[6].gueltigAbCtl = &m_gueltigAb7;
	m_agpControls[7].gueltigAbCtl = &m_gueltigAb8;
	m_agpControls[8].gueltigAbCtl = &m_gueltigAb9;
	m_agpControls[9].gueltigAbCtl = &m_gueltigAb10;

	ResetAGPControls();

}

// Initilaize AGP controls
void CAgpView::FillAGPControls()
{
	ResetAGPControls();
	int anz = 0;
	char datstr[20];
	while (anz < m_nAgpAnzl)
	{
		m_AgpArtData = m_Doc.GetAgpData(anz);
		sprintf(datstr, " %.2ld.%.2ld.%.4ld", m_AgpArtData->GUELTIG_AB % 100, (m_AgpArtData->GUELTIG_AB % 10000) / 100, m_AgpArtData->GUELTIG_AB / 10000);
		m_agpControls[anz].gueltigAb += datstr;


		sprintf(datstr, " %.2f", m_AgpArtData->AGP);
		m_agpControls[anz].agpPreis += datstr;

		m_agpControls[anz].agpCtl->SetWindowText(m_agpControls[anz].agpPreis);
		m_agpControls[anz].gueltigAbCtl->SetWindowText(m_agpControls[anz].gueltigAb);
		anz++;
	}
}

void CAgpView::MakeDialog()
{
	m_Pos_FirstKey = m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog(m_AgpPZN);

	m_nMaxFields = m_dlg.GetFieldNumber();

	InitAGPControls();

}


void CAgpView::SetDialog(BOOL bDialog)
{
	m_dlg.SetDialog(bDialog);
}

void CAgpView::EnableFields(BOOL bEnab)
{
	m_dlg.EnableFields(m_Pos_FirstKey, m_Pos_LastKey, !bEnab);
	m_dlg.EnableFields(m_Pos_FirstField, m_nMaxFields - 1, bEnab);
}

void CAgpView::ShowFields()
{
m_dlg.ShowFields();

}

void CAgpView::DataExchangeToBuffer()
{
	m_dlg.DataExchangeToBuffer();
}

BOOL CAgpView::IsLastKeyFocus()
{
	return GetFocus() == GetDlgItem(IDC_LAST_KEY);
}



// Steuerung
void CAgpView::GotoFirstKey()
{
	m_dlg.SetFocus(m_Pos_FirstKey);
}

void CAgpView::GotoFirstField()
{
	m_dlg.SetFocus(m_Pos_FirstField);
}

void CAgpView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer(m_Pos_FirstKey, m_Pos_LastKey);
}

void CAgpView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer(m_Pos_FirstKey, m_Pos_LastKey);
}

void CAgpView::InitPflege()
{
	m_pDlgAgp = &((CEkZdpApp*)AfxGetApp())->m_pDlgAgp;
	
	// CAgpView* pThisView = this;

	m_pBuf = m_Doc.GetBuffer();

	MakeDialog();
	
	m_AgpPZN.SetMask(ED_LONG,
					 ED_NORMAL,
					 &m_pBuf->cagpart.PZN,
					 7,
					 new ChMaskNum,
					 new CV_CAGP_ArtikelNr(&m_pBuf->cagpart));

	SetDialog();
}

int CAgpView::CloseSuche()
{
	return 0;
}
void CAgpView::SetMSStandard(BOOL bStandard)
{
	m_dlg.SetMSStandard(bStandard);
}
int CAgpView::SucheSatz()
{
	// creates the dialog if not already created
	((CEkZdpApp*)AfxGetApp())->GotoAgp(1);
	return 0;
	
}

void CAgpView::ReleaseAgp()
{
	((CEkZdpApp*)AfxGetApp())->ReleaseAgp();

	m_bNext = FALSE;
	m_bPrev = FALSE;
	CEkZdpApp *theApp = (CEkZdpApp *)AfxGetApp();
	theApp->SetRecordSearch(m_bNext, m_bPrev);
}

int CAgpView::NextSatz()
{
	int status = 0;

	if (PrimeKeyOfNextRecord())
	{
		CString cErrmld;
		KeySetInput();

		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		m_nAgpAnzl = m_Doc.GetPznAGPZeile(cErrmld);
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();

		if (m_nAgpAnzl > 0)
		{
			ResetAGPControls();
			FillAGPControls();
			ShowFields();
			GotoFirstKey();
			status = 1;
		}
		else
		{
			MsgBoxOK(cErrmld);
			status = 0;
		}
	}
	m_bNext = status == 1;

	if (status == 1)
		m_bPrev = TRUE;

	return status;
}

int CAgpView::PrevSatz()
{
	int status = 0;
	if (PrimeKeyOfPrevRecord())
	{
		CString cErrmld;
		KeySetInput();

		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		m_nAgpAnzl = m_Doc.GetPznAGPZeile(cErrmld);
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();

		if (m_nAgpAnzl > 0)
		{
			ResetAGPControls();
			FillAGPControls();
			ShowFields();
			GotoFirstKey();
			status = 1;
		}
		else
		{
			MsgBoxOK(cErrmld);
			status = 0;
		}
	}

	m_bPrev = status == 1;

	if (status == 1)
		m_bNext = TRUE;

	return status;
}

int CAgpView::BearbeiteSatz()
{
	// Nothing to do here as details are not editable.
	return 0;
}

int CAgpView::SpeichereSatz()
{
	// Nothing to do here as details are not editable.
	return 0;
}

int CAgpView::LoescheSatz()
{
	// Nothing to do here as details are not editable.
	return 0;
}

int CAgpView::UndoSatz()
{
	// Nothing to do here as details are not editable.
	if (m_nStatus == 0)
	{
		m_Doc.FreeBufferDesc();
		CloseSuche();
		return 0;
	}
	m_nStatus = 0;
	EnableFields(FALSE);
	GotoFirstKey();
	return 1;
}

void CAgpView::CopySatz()
{
	// Nothing to do here as details are not editable.
}

void CAgpView::CutSatz()
{
	// Nothing to do here as details are not editable.

}

void CAgpView::PasteSatz()
{
	// Nothing to do here as details are not editable.

}

void CAgpView::InitPflegeDocument(char* Anwender)
{
	m_Doc.InitPflegeDesc(Anwender);
}

void CAgpView::ReleasePflegeDocument()
{
	((CEkZdpApp*)AfxGetApp())->ReleaseAgp();

	m_pBuf->cagpart.AGP_NR = 0;
	m_bNext = FALSE;
	m_bPrev = FALSE;
	CEkZdpApp *theApp = (CEkZdpApp *)AfxGetApp();
	theApp->SetRecordSearch(m_bNext, m_bPrev);
}
void CAgpView::OnInitialUpdate()
{
	CFormViewMultiLang::OnInitialUpdate();

	InitPflege();
	m_Doc.InitPflegeDesc(((CEkZdpApp *)AfxGetApp())->GetRefToAnwender());
	m_nStatus = 0;
}

// Suchbox
//--------------------------------------------------------------------//
BOOL CAgpView::PrimeKeyOfSelectedRecord()
{
	BOOL bOk;
	bOk = FALSE;
	if (*m_pDlgAgp != NULL)
	{
		long AGPNr;
		long Pzn;
		long GueltigAb;
		if ((*m_pDlgAgp)->
			PrimeKeyOfSelectedRecord(&AGPNr, &Pzn, &GueltigAb) == 0)
		{
			m_pBuf->cagpart.AGP_NR = AGPNr;
			m_pBuf->cagpart.PZN = Pzn;
			m_pBuf->cagpart.GUELTIG_AB = GueltigAb;
			bOk = TRUE;			
		}
	}
	return bOk;
}

//--------------------------------------------------------------------//
BOOL CAgpView::PrimeKeyOfNextRecord()
{
	BOOL bOk;
	bOk = FALSE;
	if (*m_pDlgAgp != NULL)
	{
		long AGPNr;
		long Pzn;
		long GueltigAb;  
		if ((*m_pDlgAgp)->PrimeKeyOfNextRecord(&AGPNr, &Pzn, &GueltigAb) == 0)
		{
			m_pBuf->cagpart.AGP_NR = AGPNr;
			m_pBuf->cagpart.PZN = Pzn;
			m_pBuf->cagpart.GUELTIG_AB = GueltigAb;
			bOk = TRUE;			
		}
	}
	return bOk;
}

//--------------------------------------------------------------------//
BOOL CAgpView::PrimeKeyOfPrevRecord()
{
	BOOL bOk;
	bOk = FALSE;
	if (*m_pDlgAgp != NULL)
	{
		long AGPNr;
		long Pzn;
		long GueltigAb;
		if ((*m_pDlgAgp)->PrimeKeyOfPrevRecord(&AGPNr, &Pzn, &GueltigAb) == 0)
		{
			m_pBuf->cagpart.AGP_NR = AGPNr;
			m_pBuf->cagpart.PZN = Pzn;
			m_pBuf->cagpart.GUELTIG_AB = GueltigAb;
			bOk = TRUE;
		}
	}
	return bOk;
}

void CAgpView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class

	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		if (pActivateView != pDeactiveView)
		{
			m_bChanged = FALSE;  // noch keine Aenderung
			GotoFirstKey();

			// oeffnet die AGP-Suche, wenn noch nicht geoffnet
			if (*m_pDlgAgp == NULL)
				SucheSatz();
			else
			{
				CEkZdpApp *theApp = (CEkZdpApp *)AfxGetApp();
				theApp->SetRecordSearch(m_bNext, m_bPrev);
			}
		}
	}
}

// Fills AgpImport Details
void CAgpView::FillAgpImportDetails()
{
	CString importDetail;
	char datstr[40];

	importDetail = _T("");
	m_agpDetails.SetWindowText("");

	sprintf(datstr, " AGP Nr: %ld \n", m_pBuf->cagpoart.AGP_NR);
	importDetail += datstr;

	sprintf(datstr, " Datum Anlage: %.2ld.%.2ld.%.4ld %.2ld:%.2ld:%.2ld\n", m_pBuf->cagpoart.DATUM_ANLAGE % 100, (m_pBuf->cagpoart.DATUM_ANLAGE % 10000) / 100, 
		m_pBuf->cagpoart.DATUM_ANLAGE / 10000, m_pBuf->cagpoart.ZEIT_ANLAGE / 10000, (m_pBuf->cagpoart.ZEIT_ANLAGE % 10000) / 100, m_pBuf->cagpoart.ZEIT_ANLAGE % 100);
	importDetail += datstr;
	
	importDetail += " Anwender: ";
	importDetail += m_pBuf->cagpoart.ANWENDER;
	importDetail += "\n";

	importDetail += " Status: ";
	importDetail += (*m_pDlgAgp)->GetTransactionStatus(m_pBuf->cagpoart.TXN_STATUS);
	m_agpDetails.SetWindowText(importDetail);
}

// Get Agp Import details.
void CAgpView::GetAgpImportDetail()
{
	CString cErrmld;
	long lStatus;

	((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.GetAgpImportDetail(cErrmld);
	((CEkZdpApp*)AfxGetApp())->EndWaitAction();
	
	if (lStatus != 0)
	{
		MsgBoxOK(cErrmld);
	}
	else
	{
		FillAgpImportDetails();
	}

}

// Receives message from ArtikelAGP
LRESULT CAgpView::OnArtAgpEnd(WPARAM wParam, LPARAM)
{
	CEkZdpApp *theApp = (CEkZdpApp *)AfxGetApp();
	if (wParam == IDOK)
	{
		(*m_pDlgAgp)->ShowWindow(SW_HIDE);

		if (theApp->GetActView() != this)
			theApp->OnAGP();
		// 2 mal
		if (theApp->GetActView() != this)
			theApp->OnAGP();

		m_bNext = TRUE;
		m_bPrev = TRUE;

		theApp->SetRecordSearch(m_bNext, m_bPrev);

		if (PrimeKeyOfSelectedRecord())
		{
			CString cErrmld;
			KeySetInput();
			GetAgpImportDetail();
			((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
			m_nAgpAnzl = m_Doc.GetPznAGPZeile(cErrmld);
			((CEkZdpApp*)AfxGetApp())->EndWaitAction();
			
			if (m_nAgpAnzl > 0)
			{
				ResetAGPControls();
				FillAGPControls();
				ShowFields();
			}
			else
			{
				MsgBoxOK(cErrmld);				
			}
		}
	}
	else
	{
		ReleaseAgp();
	}
	GotoFirstKey();

	return 0;
}
