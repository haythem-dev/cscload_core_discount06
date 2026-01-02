// ArtikelPage6BG.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage6BG.h"
#include "ArtikelView.h"
#include "ServerDatum.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <phxlib/PhxUtil.h>

#include <phxlib/DformSelCtrl.h>

#include <libscsvoodoo/libscsvoodoo.h>

// CArtikelPage6BG-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage6BG, CPropertyPageMultiLang)

// CArtikelPage6BG::CArtikelPage6BG()
CArtikelPage6BG::CArtikelPage6BG() : ChPflegePage(CArtikelPage6BG::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
	//m_GepnaVal = 0.0;
}

CArtikelPage6BG::~CArtikelPage6BG()
{
}

void CArtikelPage6BG::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage6BG)
	DDX_Control(pDX, IDC_ED_ARTIKEL_MINISTRY_PRODUCT_CODE, m_MINISTRY_PRODUCT_CODE);
	DDX_Control(pDX, IDC_STATIC_REGISTER_BG, m_ST_REGISTER_BG);
	DDX_Control(pDX, IDC_ED_REGISTER_BG, m_REGISTER_BG);
	DDX_Control(pDX, IDC_STATIC_INN_BG, m_ST_INN_BG);
	DDX_Control(pDX, IDC_ED_INN_BG, m_INN_BG);
	DDX_Control(pDX, IDC_STATIC_REGNO_BG, m_ST_REGNO_BG);
	DDX_Control(pDX, IDC_ED_REGISTERNUMBER_BG, m_REGNO_BG);
	DDX_Control(pDX, IDC_STATIC_REGNAME_BG, m_ST_REGNAME_BG);
	DDX_Control(pDX, IDC_ED_REGNAME_BG, m_REGNAME_BG);
	DDX_Control(pDX, IDC_STATIC_MAH_BG, m_ST_MAH_BG);
	DDX_Control(pDX, IDC_ED_MAH_BG, m_MAH_BG);
	DDX_Control(pDX, IDC_STATIC_PRODUCER_BG, m_ST_PRODUCER_BG);
	DDX_Control(pDX, IDC_ED_PRODUCER_BG, m_PRODUCER_BG);
	DDX_Control(pDX, IDC_STATIC_REGLICENCE_BG, m_ST_REGLICENCE_BG);
	DDX_Control(pDX, IDC_ED_REGLICENCE_BG, m_REGLICENCE_BG);
	DDX_Control(pDX, IDC_STATIC_GueltigAb_BG, m_ST_GueltigAb_BG);
	DDX_Control(pDX, IDC_STATIC_PP_BG, m_ST_PP_BG);
	DDX_Control(pDX, IDC_STATIC_MWP_BG, m_ST_MWP_BG);
	DDX_Control(pDX, IDC_STATIC_MRP_BG, m_ST_MRP_BG);
	DDX_Control(pDX, IDC_STATIC_REFPREIS_BG, m_ST_REFPREIS_BG);
	DDX_Control(pDX, IDC_STATIC_LETZTEAENDERUNG_BG, m_ST_LETZTEAENDERUNG_BG);
	DDX_Control(pDX, IDC_ED_GueltigAb_BG, m_GueltigAb_BG);
	DDX_Control(pDX, IDC_ED_PP_BG, m_PP_BG);
	DDX_Control(pDX, IDC_ED_MWP_BG, m_MWP_BG);
	DDX_Control(pDX, IDC_ED_MRP_BG, m_MRP_BG);
	DDX_Control(pDX, IDC_ED_REFPREIS_BG, m_REFPREIS_BG);
	DDX_Control(pDX, IDC_ED_LETZTEAENDERUNG_BG, m_LETZTEAENDERUNG_BG);
	DDX_Control(pDX, IDC_ED_GueltigAb_BG2, m_GueltigAb_BG2);
	DDX_Control(pDX, IDC_ED_PP_BG2, m_PP_BG2);
	DDX_Control(pDX, IDC_ED_MWP_BG2, m_MWP_BG2);
	DDX_Control(pDX, IDC_ED_MRP_BG2, m_MRP_BG2);
	DDX_Control(pDX, IDC_ED_REFPREIS_BG2, m_REFPREIS_BG2);
	DDX_Control(pDX, IDC_ED_LETZTEAENDERUNG_BG2, m_LETZTEAENDERUNG_BG2);
	DDX_Control(pDX, IDC_ED_GueltigAb_BG3, m_GueltigAb_BG3);
	DDX_Control(pDX, IDC_ED_PP_BG3, m_PP_BG3);
	DDX_Control(pDX, IDC_ED_MWP_BG3, m_MWP_BG3);
	DDX_Control(pDX, IDC_ED_MRP_BG3, m_MRP_BG3);
	DDX_Control(pDX, IDC_ED_REFPREIS_BG3, m_REFPREIS_BG3);
	DDX_Control(pDX, IDC_ED_LETZTEAENDERUNG_BG3, m_LETZTEAENDERUNG_BG3);
	DDX_Control(pDX, IDC_ED_GueltigAb_BG4, m_GueltigAb_BG4);
	DDX_Control(pDX, IDC_ED_PP_BG4, m_PP_BG4);
	DDX_Control(pDX, IDC_ED_MWP_BG4, m_MWP_BG4);
	DDX_Control(pDX, IDC_ED_MRP_BG4, m_MRP_BG4);
	DDX_Control(pDX, IDC_ED_REFPREIS_BG4, m_REFPREIS_BG4);
	DDX_Control(pDX, IDC_ED_LETZTEAENDERUNG_BG4, m_LETZTEAENDERUNG_BG4);
	DDX_Control(pDX, IDC_STATIC_NHIFCODE_BG, m_ST_NHIFCODE_BG);
	DDX_Control(pDX, IDC_ED_NHIFCODE__BG, m_NHIFCODE_BG);
	DDX_Control(pDX, IDC_STATIC_GueltigAbII_BG, m_ST_GueltigAbII_BG);
	DDX_Control(pDX, IDC_STATIC_NHIFPREIS_BG, m_ST_NHIFPREIS_BG);
	DDX_Control(pDX, IDC_ED_GUELTIGABII__BG, m_GueltigAbII_BG);
	DDX_Control(pDX, IDC_ED_NHIFPREIS_BG, m_NHIFPREIS_BG);
	DDX_Control(pDX, IDC_ED_GUELTIGABII__BG2, m_GueltigAbII_BG2);
	DDX_Control(pDX, IDC_ED_NHIFPREIS_BG2, m_NHIFPREIS_BG2);

	//}}AFX_DATA_MAP

	// Font aendern (erst hier, weil erst nach DoDataExchange die Member gefüllt ist
	CEkZdpApp* pApp = (CEkZdpApp*)AfxGetApp();
	m_pConstantFont = pApp->GetConstantFont();
	m_REGISTER_BG.SetFont(m_pConstantFont);
	m_INN_BG.SetFont(m_pConstantFont);
	m_REGNO_BG.SetFont(m_pConstantFont);
	m_REGNAME_BG.SetFont(m_pConstantFont);
	m_MAH_BG.SetFont(m_pConstantFont);
	m_PRODUCER_BG.SetFont(m_pConstantFont);
	m_REGLICENCE_BG.SetFont(m_pConstantFont);
}

BEGIN_MESSAGE_MAP(CArtikelPage6BG, CPropertyPageMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage6BG::MakeDialog()
{
	m_dlg.InitDialog(m_REGISTER_BG);
	m_Pos_REGISTER_BG = m_dlg.GetFieldNumber();
	m_dlg.InitDialog(m_INN_BG);
	m_dlg.InitDialog(m_REGNO_BG);
	m_dlg.InitDialog(m_REGNAME_BG);
	m_dlg.InitDialog(m_MAH_BG);
	m_dlg.InitDialog(m_PRODUCER_BG);
	m_dlg.InitDialog(m_REGLICENCE_BG);
	m_dlg.InitDialog(m_GueltigAb_BG);
	m_dlg.InitDialog(m_PP_BG);
	m_dlg.InitDialog(m_MWP_BG);
	m_dlg.InitDialog(m_MRP_BG);
	m_dlg.InitDialog(m_REFPREIS_BG);
	m_dlg.InitDialog(m_LETZTEAENDERUNG_BG);
	m_dlg.InitDialog(m_GueltigAb_BG2);
	m_dlg.InitDialog(m_PP_BG2);
	m_dlg.InitDialog(m_MWP_BG2);
	m_dlg.InitDialog(m_MRP_BG2);
	m_dlg.InitDialog(m_REFPREIS_BG2);
	m_dlg.InitDialog(m_LETZTEAENDERUNG_BG2);
	m_dlg.InitDialog(m_GueltigAb_BG3);
	m_dlg.InitDialog(m_PP_BG3);
	m_dlg.InitDialog(m_MWP_BG3);
	m_dlg.InitDialog(m_MRP_BG3);
	m_dlg.InitDialog(m_REFPREIS_BG3);
	m_dlg.InitDialog(m_LETZTEAENDERUNG_BG3);
	m_dlg.InitDialog(m_GueltigAb_BG4);
	m_dlg.InitDialog(m_PP_BG4);
	m_dlg.InitDialog(m_MWP_BG4);
	m_dlg.InitDialog(m_MRP_BG4);
	m_dlg.InitDialog(m_REFPREIS_BG4);
	m_dlg.InitDialog(m_LETZTEAENDERUNG_BG4);
	m_dlg.InitDialog(m_NHIFCODE_BG);
	m_dlg.InitDialog(m_GueltigAbII_BG);
	m_dlg.InitDialog(m_NHIFPREIS_BG);
	m_dlg.InitDialog(m_GueltigAbII_BG2);
	m_dlg.InitDialog(m_NHIFPREIS_BG2);
	m_dlg.InitDialog(m_MINISTRY_PRODUCT_CODE);

	m_nMaxFields = m_dlg.GetFieldNumber();
}

void CArtikelPage6BG::InitPflege(CWnd *pView)
{
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView*)pView)->GetBuffer();
	m_pBufZartikel = &m_Buf->zartikel;
	m_pBufCNhifCode = &m_Buf->zartwg[16]; // art = H
	m_pBufMinistryProductCode = &m_Buf->carticlecodes[22];	// code_type = 23
	m_pBufCRegisters = &m_Buf->cregisters;

	for (int i = 0; i < NUMBER_OF_PRICES_REGISTERS; i++)
		m_pBufCRegistersPrices[i] = &m_Buf->cregistersprices[i];


	for (int i = 0; i < NUMBER_OF_PRICES_NHIF; i++)
		m_pBufCNhifPrices[i] = &m_Buf->cnhifprices[i];

	MakeDialog();

	m_MINISTRY_PRODUCT_CODE.SetMask(ED_CHAR,
		ED_UPPER,
		m_pBufMinistryProductCode->ARTICLE_CODE,
		25,
		new ChMaskChar);

	m_REGISTER_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->REGISTERID,
					L_CREGISTERS_REGISTERID,
					new ChMaskChar);

	m_INN_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->INTERNONPROPNAME,
					L_CREGISTERS_INTERNONPROPNAME,
					new ChMaskChar);

	m_REGNO_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->REGISTERNUMBER,
					L_CREGISTERS_REGISTERNUMBER,
					new ChMaskChar);

	m_REGNAME_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->REGISTERNAME,
					L_CREGISTERS_REGISTERNAME,
					new ChMaskChar);

	m_MAH_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->MARKETINGAUTHHOLDER,
					L_CREGISTERS_MARKETINGAUTHHOLDER,
					new ChMaskChar);

	m_PRODUCER_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->PRODUCER,
					L_CREGISTERS_PRODUCER,
					new ChMaskChar);

	m_REGLICENCE_BG.SetMask(ED_CHAR,
					ED_UPPER,
					m_pBufCRegisters->LICENCEINFO,
					L_CREGISTERS_LICENCEINFO,
					new ChMaskChar);

	 m_GueltigAb_BG.SetMask(ED_LDATE,
					ED_NORMAL,
					&m_pBufCRegistersPrices[0]->DATEVALIDFROM,
					10,
					new ChMaskNum);

	m_PP_BG.SetMask(ED_DBL,
					ED_NORMAL,
					&m_pBufCRegistersPrices[0]->PRODUCERPRICE,
					L_CREGISTERSPRICES_PRODUCERPRICE + 1,
					N_CREGISTERSPRICES_PRODUCERPRICE,
		new ChMaskDblPos);

	m_MWP_BG.SetMask(ED_DBL,
					ED_NORMAL,
					&m_pBufCRegistersPrices[0]->MAXWHOLESALEPRICE,
					L_CREGISTERSPRICES_MAXWHOLESALEPRICE + 1,
					N_CREGISTERSPRICES_MAXWHOLESALEPRICE,
					new ChMaskDblPos);

	m_MRP_BG.SetMask(ED_DBL,
					ED_NORMAL,
					&m_pBufCRegistersPrices[0]->MAXRETAILPRICE,
					L_CREGISTERSPRICES_MAXRETAILPRICE + 1,
					N_CREGISTERSPRICES_MAXRETAILPRICE,
					new ChMaskDblPos);

	m_REFPREIS_BG.SetMask(ED_DBL,
					ED_NORMAL,
					&m_pBufCRegistersPrices[0]->REFERENCEPRICE,
					L_CREGISTERSPRICES_REFERENCEPRICE + 1,
					N_CREGISTERSPRICES_REFERENCEPRICE,
					new ChMaskDblPos);

	m_LETZTEAENDERUNG_BG.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[0]->DATELASTCHANGE,
		10,
		new ChMaskNum);

	m_GueltigAb_BG2.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[1]->DATEVALIDFROM,
		10,
		new ChMaskNum);

	m_PP_BG2.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[1]->PRODUCERPRICE,
		L_CREGISTERSPRICES_PRODUCERPRICE + 1,
		N_CREGISTERSPRICES_PRODUCERPRICE,
		new ChMaskDblPos);

	m_MWP_BG2.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[1]->MAXWHOLESALEPRICE,
		L_CREGISTERSPRICES_MAXWHOLESALEPRICE + 1,
		N_CREGISTERSPRICES_MAXWHOLESALEPRICE,
		new ChMaskDblPos);

	m_MRP_BG2.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[1]->MAXRETAILPRICE,
		L_CREGISTERSPRICES_MAXRETAILPRICE + 1,
		N_CREGISTERSPRICES_MAXRETAILPRICE,
		new ChMaskDblPos);

	m_REFPREIS_BG2.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[1]->REFERENCEPRICE,
		L_CREGISTERSPRICES_REFERENCEPRICE + 1,
		N_CREGISTERSPRICES_REFERENCEPRICE,
		new ChMaskDblPos);

	m_LETZTEAENDERUNG_BG2.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[1]->DATELASTCHANGE,
		10,
		new ChMaskNum);

	m_GueltigAb_BG3.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[2]->DATEVALIDFROM,
		10,
		new ChMaskNum);

	m_PP_BG3.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[2]->PRODUCERPRICE,
		L_CREGISTERSPRICES_PRODUCERPRICE + 1,
		N_CREGISTERSPRICES_PRODUCERPRICE,
		new ChMaskDblPos);

	m_MWP_BG3.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[2]->MAXWHOLESALEPRICE,
		L_CREGISTERSPRICES_MAXWHOLESALEPRICE + 1,
		N_CREGISTERSPRICES_MAXWHOLESALEPRICE,
		new ChMaskDblPos);

	m_MRP_BG3.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[2]->MAXRETAILPRICE,
		L_CREGISTERSPRICES_MAXRETAILPRICE + 1,
		N_CREGISTERSPRICES_MAXRETAILPRICE,
		new ChMaskDblPos);

	m_REFPREIS_BG3.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[2]->REFERENCEPRICE,
		L_CREGISTERSPRICES_REFERENCEPRICE + 1,
		N_CREGISTERSPRICES_REFERENCEPRICE,
		new ChMaskDblPos);

	m_LETZTEAENDERUNG_BG3.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[2]->DATELASTCHANGE,
		10,
		new ChMaskNum);


	m_GueltigAb_BG4.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[3]->DATEVALIDFROM,
		10,
		new ChMaskNum);

	m_PP_BG4.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[3]->PRODUCERPRICE,
		L_CREGISTERSPRICES_PRODUCERPRICE + 1,
		N_CREGISTERSPRICES_PRODUCERPRICE,
		new ChMaskDblPos);

	m_MWP_BG4.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[3]->MAXWHOLESALEPRICE,
		L_CREGISTERSPRICES_MAXWHOLESALEPRICE + 1,
		N_CREGISTERSPRICES_MAXWHOLESALEPRICE,
		new ChMaskDblPos);

	m_MRP_BG4.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[3]->MAXRETAILPRICE,
		L_CREGISTERSPRICES_MAXRETAILPRICE + 1,
		N_CREGISTERSPRICES_MAXRETAILPRICE,
		new ChMaskDblPos);

	m_REFPREIS_BG4.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCRegistersPrices[3]->REFERENCEPRICE,
		L_CREGISTERSPRICES_REFERENCEPRICE + 1,
		N_CREGISTERSPRICES_REFERENCEPRICE,
		new ChMaskDblPos);

	m_LETZTEAENDERUNG_BG4.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCRegistersPrices[3]->DATELASTCHANGE,
		10,
		new ChMaskNum);


	m_NHIFCODE_BG.SetMask(ED_CHAR,
		ED_UPPER,
		m_pBufCNhifCode->WARENGRUPPE,
		5,
		new ChMaskChar);

	m_GueltigAbII_BG.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCNhifPrices[0]->DATEVALIDFROM,
		10,
		new ChMaskNum);

	m_NHIFPREIS_BG.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCNhifPrices[0]->NHIFPRICE,
		L_CNHIFPRICES_NHIFPRICE + 1,
		N_CNHIFPRICES_NHIFPRICE,
		new ChMaskDblPos);

	m_GueltigAbII_BG2.SetMask(ED_LDATE,
		ED_NORMAL,
		&m_pBufCNhifPrices[1]->DATEVALIDFROM,
		10,
		new ChMaskNum);

	m_NHIFPREIS_BG2.SetMask(ED_DBL,
		ED_NORMAL,
		&m_pBufCNhifPrices[1]->NHIFPRICE,
		L_CNHIFPRICES_NHIFPRICE + 1,
		N_CNHIFPRICES_NHIFPRICE,
		new ChMaskDblPos);

	m_bInitialized = TRUE;
}

void CArtikelPage6BG::SetDialog(BOOL bDialog)
{
	m_dlg.SetDialog(bDialog);
}

void CArtikelPage6BG::SetMSStandard(BOOL bStandard)
{
	m_dlg.SetMSStandard(bStandard);
}

void CArtikelPage6BG::EnableFields(BOOL bEnab)
{
	m_dlg.EnableFields(bEnab);
	DisableSpecial();
}

void CArtikelPage6BG::DisableSpecial()
{
	m_REGISTER_BG.EnableWindow(false);
	m_INN_BG.EnableWindow(false);
	m_REGNO_BG.EnableWindow(false);
	m_REGNAME_BG.EnableWindow(false);
	m_MAH_BG.EnableWindow(false);
	m_PRODUCER_BG.EnableWindow(false);
	m_REGLICENCE_BG.EnableWindow(false);
	m_GueltigAb_BG.EnableWindow(false);
	m_PP_BG.EnableWindow(false);
	m_MWP_BG.EnableWindow(false);
	m_MRP_BG.EnableWindow(false);
	m_REFPREIS_BG.EnableWindow(false);
	m_LETZTEAENDERUNG_BG.EnableWindow(false);
	m_LETZTEAENDERUNG_BG.EnableWindow(false);
	m_GueltigAb_BG2.EnableWindow(false);
	m_PP_BG2.EnableWindow(false);
	m_MWP_BG2.EnableWindow(false);
	m_MRP_BG2.EnableWindow(false);
	m_REFPREIS_BG2.EnableWindow(false);
	m_LETZTEAENDERUNG_BG2.EnableWindow(false);
	m_GueltigAb_BG3.EnableWindow(false);
	m_PP_BG3.EnableWindow(false);
	m_MWP_BG3.EnableWindow(false);
	m_MRP_BG3.EnableWindow(false);
	m_REFPREIS_BG3.EnableWindow(false);
	m_LETZTEAENDERUNG_BG3.EnableWindow(false);
	m_GueltigAb_BG4.EnableWindow(false);
	m_PP_BG4.EnableWindow(false);
	m_MWP_BG4.EnableWindow(false);
	m_MRP_BG4.EnableWindow(false);
	m_REFPREIS_BG4.EnableWindow(false);
	m_LETZTEAENDERUNG_BG4.EnableWindow(false);
	m_GueltigAbII_BG.EnableWindow(false);
	m_NHIFPREIS_BG.EnableWindow(false);
	m_GueltigAbII_BG2.EnableWindow(false);
	m_NHIFPREIS_BG2.EnableWindow(false);
}

void CArtikelPage6BG::ShowFields()
{
	m_dlg.ShowFields();
}

void CArtikelPage6BG::SetValidation(BOOL bValid)
{
	m_dlg.SetValidation(bValid);
}

void CArtikelPage6BG::DataExchangeToBuffer()
{
	m_dlg.DataExchangeToBuffer();
}

void CArtikelPage6BG::ActivateField(int nr)
{
	m_dlg.ActivateField(nr);
}

BOOL CArtikelPage6BG::Validate(BOOL bMeldung)
{
	SetValidation(TRUE);
	bMeldung = true;
	return bMeldung; //bOk;
}

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage6BG::EndValidate(int *ind, BOOL bMeldung)
{
	BOOL bOk = true;
	if (bMeldung)
		*ind = 0;

	return bOk;
}


BOOL CArtikelPage6BG::OnSetActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnSetActive();
	if (bOk && m_bInitialized)
	{
		ShowFields();
		((CArtikelView*)m_pView)->Set_WasActive();
		EnableFields(((CArtikelView*)m_pView)->AreFieldsEnabled());
		GetParent()->SendMessage(WM_USER + 10);
		SetValidation(TRUE);
	}
	return bOk;
}


BOOL CArtikelPage6BG::OnKillActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if (bOk)
	{
		SetValidation(FALSE);
		DataExchangeToBuffer();
	}
	return bOk;
}
