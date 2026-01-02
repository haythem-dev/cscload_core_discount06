#include "hPflegePage.h"
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>
#include <eklibs/hamfcs/hDlgComboBox.h>
//#include <hDlgMultiComboBox.h>
#include <phxlib/RdDform.h>

#pragma once

#define NUMBER_OF_PRICES_REGISTERS 4
#define NUMBER_OF_PRICES_NHIF 2
// CArtikelPage6BG-Dialogfeld

class CArtikelPage6BG : public ChPflegePage
{
	DECLARE_DYNCREATE(CArtikelPage6BG)

public:
	CArtikelPage6BG();
	virtual ~CArtikelPage6BG();

	// Dialog Data
	//{{AFX_DATA(CArtikelPage4)
	enum { IDD = IDD_ARTIKEL_6BG };
	ChDlgEdit m_REGISTER_BG;
	CStatic m_ST_REGISTER_BG;
	CStatic m_ST_INN_BG;
	ChDlgEdit m_INN_BG;
	CStatic m_ST_REGNO_BG;
	ChDlgEdit m_REGNO_BG;
	CStatic m_ST_REGNAME_BG;
	ChDlgEdit m_REGNAME_BG;
	CStatic m_ST_MAH_BG;
	ChDlgEdit m_MAH_BG;
	CStatic m_ST_PRODUCER_BG;
	ChDlgEdit m_PRODUCER_BG;
	CStatic m_ST_REGLICENCE_BG;
	ChDlgEdit m_REGLICENCE_BG;
	CStatic m_ST_GueltigAb_BG;
	CStatic m_ST_PP_BG;
	CStatic m_ST_MWP_BG;
	CStatic m_ST_MRP_BG;
	CStatic m_ST_REFPREIS_BG;
	CStatic m_ST_LETZTEAENDERUNG_BG;
	ChDlgEdit m_GueltigAb_BG;
	ChDlgEdit m_PP_BG;
	ChDlgEdit m_MWP_BG;
	ChDlgEdit m_MRP_BG;
	ChDlgEdit m_REFPREIS_BG;
	ChDlgEdit m_LETZTEAENDERUNG_BG;
	ChDlgEdit m_GueltigAb_BG2;
	ChDlgEdit m_PP_BG2;
	ChDlgEdit m_MWP_BG2;
	ChDlgEdit m_MRP_BG2;
	ChDlgEdit m_REFPREIS_BG2;
	ChDlgEdit m_LETZTEAENDERUNG_BG2;
	ChDlgEdit m_GueltigAb_BG3;
	ChDlgEdit m_PP_BG3;
	ChDlgEdit m_MWP_BG3;
	ChDlgEdit m_MRP_BG3;
	ChDlgEdit m_REFPREIS_BG3;
	ChDlgEdit m_LETZTEAENDERUNG_BG3;
	ChDlgEdit m_GueltigAb_BG4;
	ChDlgEdit m_PP_BG4;
	ChDlgEdit m_MWP_BG4;
	ChDlgEdit m_MRP_BG4;
	ChDlgEdit m_REFPREIS_BG4;
	ChDlgEdit m_LETZTEAENDERUNG_BG4;
	CStatic m_ST_NHIFCODE_BG;
	ChDlgEdit m_NHIFCODE_BG;
	CStatic m_ST_GueltigAbII_BG;
	CStatic m_ST_NHIFPREIS_BG;

	ChDlgEdit m_GueltigAbII_BG;
	ChDlgEdit m_NHIFPREIS_BG;

	ChDlgEdit m_GueltigAbII_BG2;
	ChDlgEdit m_NHIFPREIS_BG2;

	ChDlgEdit m_MINISTRY_PRODUCT_CODE;
	//}}AFX_DATA

public:
	void InitPflege(CWnd *pView);
	void EnableFields(BOOL bEnable);
	void DisableSpecial();
	void ShowFields();
	void SetDialog(BOOL bDialog = TRUE);
	void DataExchangeToBuffer();
	void SetValidation(BOOL bValid);
	BOOL Validate(BOOL bMeldung);
	BOOL EndValidate(int *ind, BOOL bMeldung);
	void ActivateField(int nr);
	void SetMSStandard(BOOL bStandard);

private:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	void MakeDialog();

private:
	// Dialogdaten

	ChDlg m_dlg;

	UINT m_nStatus;
	int  m_nMaxFields;
	int  m_Pos_REGISTER_BG;

	CWnd *m_pView;
	struct CREGISTERS		*m_pBufCRegisters;
	struct CREGISTERSPRICES	*m_pBufCRegistersPrices[NUMBER_OF_PRICES_REGISTERS];
	struct CNHIFPRICES	*m_pBufCNhifPrices[NUMBER_OF_PRICES_NHIF];
	struct ZARTIKEL			*m_pBufZartikel;
	struct ZARTWG			*m_pBufCNhifCode;
	struct CARTICLECODES	*m_pBufMinistryProductCode;

	BOOL m_bInitialized;
	CFont* m_pConstantFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:

};
