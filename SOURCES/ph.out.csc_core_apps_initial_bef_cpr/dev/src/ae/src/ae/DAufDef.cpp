// daufdef.cpp : implementation file
//

#include "stdafx.h"
#include "DAufDef.h"
#include "MAufDef.h"
#include <kndsel.h>
#include <customer.h>
#include <serviceorder.h>
#include "AeFView.h"
#include "DTenderWahl.h"
#include "DTenderOrder.h"
#include "DRabattOrder.h"
#include "DViewKnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDAufDef dialog


CDAufDef::CDAufDef(CMAufDef& model, CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufDef::IDD, pParent)
    , _model(model)
    , m_bDelayedDelivery(FALSE)
    , m_CT_DelayedDelivery(0)
    , m_ABemerkung(_T(""))
    , m_IVC(_T(""))
    , m_bNoRabattKonto(FALSE)
    , m_bCashOrder(FALSE)
    , m_OrgInvoice(_T(""))
    , m_OrgInvoice_old(_T(""))
{
    m_bCancel        = true;
    m_bKommiArtManuell = false;
    m_lAutoValuta    = 0L;
    m_bMixExist      = false;
    m_bMixShown      = false;
    m_bAnzSonder     = false;
    m_TourType       = Akt;
    m_bSonder        = false;
    m_bValutaWhenCheckCashOrder = false;

    _impl = boost::make_shared<CDAufDefImpl>(AeGetApp()->GetCountry());
}

void CDAufDef::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_EditBemerkung);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_ABemerkung);
    DDX_Control(pDX, IDC_EDIT_IVC, m_EditIVC);
    DDX_Text(pDX, IDC_EDIT_IVC, m_IVC);
    DDX_Control(pDX, IDC_CHECK_VALUTA, m_CheckValuta);
    DDX_Control(pDX, IDC_STATIC_VALUTA_AUTO, m_cs_ValutaAuto);
    DDX_Control(pDX, IDC_STATIC_VALUTA_DATUM, m_cs_ValutaDatum);
    DDX_Control(pDX, IDC_COMBO_TOUR, m_CoboxTour);
    DDX_Control(pDX, IDC_GENERIC1, m_CspinMonate);
    DDX_Control(pDX, IDC_ST_VAL_MON, m_cs_ValutaMonate);
    DDX_Control(pDX, IDC_EDIT_VAL_MON2, m_EditValuta);
    DDX_Control(pDX, IDC_COMBO_AUF_ART, m_CoboxAufArt);
    DDX_Check(pDX, IDC_CHECK_DD, m_bDelayedDelivery);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DD, m_DT_DelayedDelivery);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DD, m_CT_DelayedDelivery);
    DDX_Control(pDX, IDC_COMBO_TOUR_NAKT, m_CoboxNakt);
    DDX_Control(pDX, IDC_COMBO_FUTUR, m_CoboxFutur);
    DDX_Control(pDX, IDC_STATIC_SONDER_TOUR, m_cs_SonderTour);
    DDX_Control(pDX, IDC_COMBO_SUB_ORDER, m_Cobox_SubOrder);
    DDX_Control(pDX, IDC_COMBO_MIX, m_CoboxMix);
    DDX_Control(pDX, IDC_CHECK_NO_REBATE_ACCOUNT, m_NoRebateAccount);
    DDX_Check(pDX, IDC_CHECK_NO_REBATE_ACCOUNT, m_bNoRabattKonto);
    DDX_Check(pDX, IDC_CHECK_CASH_ORDER, m_bCashOrder);
    DDX_Control(pDX, IDC_EDIT_ORIGINVOICE, m_EditOrgInvoice);
    DDX_Text(pDX, IDC_EDIT_ORIGINVOICE, m_OrgInvoice);
}


BEGIN_MESSAGE_MAP(CDAufDef, CDialogMultiLang)
    ON_WM_CTLCOLOR()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_CHECK_VALUTA, OnCheckValuta)
    ON_EN_CHANGE(IDC_EDIT_BEMERKUNG, OnChangeEditBemerkung)
    ON_EN_CHANGE(IDC_EDIT_IVC, OnChangeEditIVC)
    ON_EN_CHANGE(IDC_EDIT_VAL_MON2, OnChangeEditValMon2)
    ON_CBN_SELCHANGE(IDC_COMBO_AUF_ART, OnSelchangeComboAufArt)
    ON_CBN_SELCHANGE(IDC_COMBO_TOUR, OnSelchangeComboTour)
    ON_CBN_SELCHANGE(IDC_COMBO_TOUR_NAKT, OnSelchangeComboSonder)
    ON_CBN_SELCHANGE(IDC_COMBO_MIX, OnSelchangeComboMix)
    ON_BN_CLICKED(IDC_RADIO10, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO11, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO12, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO13, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO14, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO15, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO16, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO17, OnRadioKomArt)
    ON_BN_CLICKED(IDC_RADIO18, OnRadioKomArt)
    ON_BN_CLICKED(IDC_CHECK_DD, OnCheckDelayedDelivery)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DD, OnDatechangeDelayedDelivery)
    ON_BN_CLICKED(IDC_BUTTON_SONDER, OnBnClickedButtonSonder)
    ON_BN_CLICKED(IDC_CHECK_CASH_ORDER, OnCheckCashOrder)
    ON_EN_CHANGE(IDC_EDIT_ORIGINVOICE, OnChangeEditIVC)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufDef message handlers

BOOL CDAufDef::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    AeGetApp()->m_AeLogging.WriteLine(2, "DAufDef.cpp", "OnInitDialog", "Dialog started");

    RememberInitialValues();
    m_IVC.Format("%d", _model.GetIVC());
    m_ABemerkung = _model.GetABemerkung();
    m_bNoRabattKonto = _model.GetNoRabattKonto() ? TRUE : FALSE;
    m_bCashOrder = _model.GetCashOrder() ? TRUE : FALSE;

    if (_model.GetTenderNo() != 0L)
    {
        DisableCancel();
    }
    if (_model.GetMitRab())
    {
        m_NoRebateAccount.ShowWindow(SW_SHOW);
        m_NoRebateAccount.EnableWindow(GetAeUser().IsChangeRebateCalc() ? TRUE : FALSE);
    }
    else
    {
        ShowAndEnableWindow(IDC_CHECK_NO_REBATE_ACCOUNT, false);
    }

    FillDayTable();

    InitDate();

    ShowAndEnableWindow(IDC_COMBO_SUB_ORDER, false);
    m_cs_SonderTour.ShowWindow(SW_HIDE);
    CheckDlgButton(IDC_CHECK_DD, FALSE);
    VersorgeTouren(m_AArtWished, true);

    CenterWindow();

    if (_model.GetValuta() > 0)
    {
        CheckDlgButton(IDC_CHECK_VALUTA, BST_CHECKED);
    }

    //Valuta
    m_CspinMonate.SetBuddy(&m_EditValuta);

    m_CoboxAufArt.ResetContent();

    GetOrderTypes();

    SetAuftArt();
    SetBuchArt(_model.GetBuchArt().GetAt(0));
    SetKommArt(_model.GetKommArt().GetAt(0));
    SetTourComboOnRadioKomArt();
    CalculateAndSetValutaDatum();

    InitEilBeipackRadio();

    if (_model.GetNeuSetzen()) //Auftragsart muß neu gesetzt werden
    {
        DisableCancel();
        OnOK();
    }
    else if (_model.GetBemerkungEing()) // 'else' to prevent two times MsgBoxOK(IDP_KOPF_BEM_EING)
    {
        DisableCancel();
        MsgBoxOK(IDP_KOPF_BEM_EING);
    }

    InitSonderTourFont();

    if (!IsValutaPossible())
    {
        ShowAndEnableWindow(IDC_STATIC_VALUTA_DATUM, false);
        ShowAndEnableWindow(IDC_CHECK_VALUTA, false);
        ShowAndEnableWindow(IDC_EDIT_VAL_MON2, false);
        ShowAndEnableWindow(IDC_GENERIC1, false);
        ShowAndEnableWindow(IDC_ST_VAL_MON, false);
    }
    m_cs_ValutaMonate.SetWindowText(CResString::ex().getStrTblText(ValutaInDays() ? AETXT_TAGE : AETXT_MONATE));

    if (AeGetApp()->IsBG() && _model.GetShowCashOrder())
    {
        ShowAndEnableWindow(IDC_CHECK_CASH_ORDER, true);
    }

    UpdateData(FALSE);
    AeGetApp()->m_AeLogging.WriteLine(2, "DAufDef.cpp", "OnInitDialog", "Dialog inizialized");
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAufDef::RememberInitialValues()
{
    m_bCashOrderInitial = _model.GetCashOrder();
    m_lIVCInitial = _model.GetIVC();
    m_OrgInvoice_old = m_OrgInvoice;
    m_AArtWished = _model.GetAArt();
    m_bNoRabattKontoInitial = _model.GetNoRabattKonto();
    m_lValutaInitial = _model.GetValuta();
    m_saveTour = _model.GetTour();
}

void CDAufDef::FillDayTable()
{
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_SUNDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_MONDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_TUESDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_WEDNESDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_THURSDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_FRIDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_SATURDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(AETXT_HEUTE).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(AETXT_SONDERTOUR).GetString());
}

void CDAufDef::InitDate()
{
    CTM datetime;
    datetime.Server(AafilGetdatetime);
    m_lActDatum = datetime.s.DATUM;
    m_sWeekday = (short)datetime.s.WTAG;

    long tempdate = m_lActDatum;
    CTime begin = ConvertDate(tempdate);

    CTime end(2030, 12, 31, 0, 0, 0); // TODO: hard coded year really good ???

    m_DT_DelayedDelivery.SetRange(&begin, &end);

    char error_msg[81];
    tempdate = (_model.GetDatumDelayedDelivery() > 0) ? _model.GetDatumDelayedDelivery() : AllgAddDate(tempdate, 1, error_msg);
    CTime dateDelayedDelivery = ConvertDate(tempdate);
    m_DT_DelayedDelivery.SetTime(&dateDelayedDelivery);

    if (_model.GetDatumDelayedDelivery() > m_lActDatum)
    {
        m_bDelayedDelivery = TRUE;
    }
}

void CDAufDef::GetOrderTypes()
{
    bool isBatch = IsBatch();
    bool isSub = _model.GetGebucht() && GetOrderType().IsMustSubOrder(AeGetApp()->VzNr(), _model.GetAArt().GetString()) ? true : false;

    //Auftragsart
    CAUFARTES aufartes;
    // Kundenfelder müssen nicht versorgt werden,
    // da die Daten über das aktuelle Object versorgt werden
    aufartes.s.IDFNR = _model.GetIdfNr();
    aufartes.s.KUNDENNR = _model.GetIdfNr();
    aufartes.s.VERTRIEBSZENTRUMNR = _model.GetVzNr();

    for (;;)
    {
        aufartes.Server(AasrvGetaartes, PIPE_AE_SRV);
        if (aufartes.rc != SRV_OK)
            break;

        if ((AeGetApp()->IsMSV3() || isBatch) && (_model.GetAArt() != aufartes.s.KDAUFTRAGART)) //bei MSV3 oder gebuchter Charge kein wechseln der Auftagsart
        {
            continue;
        }

        if (AeGetApp()->IsBG())
        {
            //Check auf Rabatteingabe erlaubt
            if (!GetAeUser().IsDiscountUp() && GetOrderType().IsNatraAufArt(AeGetApp()->VzNr_Kunde(), aufartes.s.KDAUFTRAGART))
            {
                continue;
            }
            //Check auf bereits gebucht und Tenderauftrag
            if ((_model.GetAArt() == "RO") && (_model.GetAArt() != aufartes.s.KDAUFTRAGART))
            {
                continue;
            }
        }
        if (_model.GetGebucht() && (_impl->RemoveBGOrderTypes(_model.GetAArt(), aufartes.s.KDAUFTRAGART) || _impl->RemoveBGAndRSOrderTypes(_model.GetAArt(), aufartes.s.KDAUFTRAGART)))
        {
            continue;
        }
        //Check ob Auftragart mit Subordertype
        if (isSub)
        {
            if (_model.GetAArt() != aufartes.s.KDAUFTRAGART)
            {
                continue;
            }

            AddOrderType(aufartes.s);
            CString sub = aufartes.s.KDAUFTRAGART;
            HoleSubOrder(sub);
            m_Cobox_SubOrder.SelectString(-1, _model.GetSubType());
            break;
        }
        // pruefen ob mit Subordertype und ob diese vorhanden
        if (aufartes.s.SMUSTSUBORDER[0] == '1')
        {
            if (_model.GetGebucht())
            {
                continue;
            }

            CCSTDISCCONT cst;
            cst.SetBranchno(_model.GetVzNr());
            cst.SetCustomerno(_model.GetIdfNr());
            cst.SetOrder_type(aufartes.s.KDAUFTRAGART);
            if (cst.SelList() != SRV_OK)
            {
                cst.CloseCursor();
                continue;
            }
            cst.CloseCursor();
        }
        AddOrderType(aufartes.s);
    }
}

bool CDAufDef::IsBatch()
{
    CAUFPOSBUCH aufposbuch;
    bool isBatch = false;
    if (_model.GetDoc()->m_bAllItemsInList)
    {
        AUFPOSBUCH* ptrPos = _model.GetDoc()->GetPosListe(); //Zeiger auf Beginn der Liste
        for (; ptrPos != NULL; ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL))
        {
            if (ptrPos == NULL)
                break;
            if (ptrPos->CHARGENNR[0] != ' ')
                isBatch = true;
        }
    }
    else
    {
        BeginWaitCursor();
        _model.GetDoc()->DelPosListe(); //Loeschen der Positionsliste
        for (;;)
        {
            aufposbuch.Server(AasrvSelpos, PIPE_AE_SRV);
            if (aufposbuch.rc != SRV_OK)
                break;
            _model.GetDoc()->AddPosition(aufposbuch.s);
            if (aufposbuch.s.CHARGENNR[0] != ' ')
                isBatch = true;
        }
        _model.GetDoc()->m_bAllItemsInList = true;
    }
    return isBatch;
}

void CDAufDef::InitEilBeipackRadio()
{
    if (AeGetApp()->KndEilSperre() == '1')
    {
        GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
    }
    CString csAnzPos;
    ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csAnzPos);
    if ((AeGetApp()->MaxPosEil() != 0) && (atol(csAnzPos) > AeGetApp()->MaxPosEil()))
    {
        GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
    }
}

void CDAufDef::InitSonderTourFont()
{
    CFont* pobjCFont = m_cs_SonderTour.GetFont();

    LOGFONT lf;
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;

    CFont objCFont;
    objCFont.CreateFontIndirect(&lf);

    m_cs_SonderTour.SetFont(&objCFont);
}

void CDAufDef::AddOrderType(AUFARTES& aufartes)
{
    CString AAVal;
    AAVal.Format("%s%03d", aufartes.KDAUFTRAGART, aufartes.VALUTAMONATE);
    m_aAArten.Add(AAVal);
    CString AArt;
    AArt.Format("%s - %s", aufartes.KDAUFTRAGART, aufartes.BEZEICHNUNG);
    m_CoboxAufArt.AddString(AArt);
}

bool CDAufDef::IsValutaPossible()
{
    return AeGetApp()->IsNoValuta()
        || (AeGetApp()->IsBG() &&
            ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgKnd->GetCreditLimitValue1() <= 0 &&
            ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgKnd->GetCreditLimitValue2() <= 0)
        ? false : true;
}

void CDAufDef::SetAuftArt()
{
    if (m_CoboxAufArt.SelectString(-1, _model.GetAArt()) == CB_ERR)
    {
        m_CoboxAufArt.SetCurSel(0);
    }
    UpdateOnChangeAufArt();
}

void CDAufDef::SetKommArt(char cKommArt)
{
    //Kommisionierart
    if      (cKommArt == '0' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO10);
    else if (cKommArt == '3' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO11);
    else if (cKommArt == '4' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO12);
    else if (cKommArt == '5' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO13);
    else if (cKommArt == '6' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO14);
    else if (cKommArt == '1' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO15);
    else if (cKommArt == '8' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO17);
    else if (cKommArt == '7' )  CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO18);
    else if (cKommArt == '2' )
    {
        CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO16);
    }
    else CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO10);

    SetTourComboOnRadioKomArt();
}

void CDAufDef::SetBuchArt(char cBuchArt)
{
    //Buchungsart
    if      (cBuchArt == '0')  CheckRadioButton(IDC_RADIO20, IDC_RADIO23, IDC_RADIO20);
    else if (cBuchArt == '4')  CheckRadioButton(IDC_RADIO20, IDC_RADIO23, IDC_RADIO21);
    else if (cBuchArt == '3')  CheckRadioButton(IDC_RADIO20, IDC_RADIO23, IDC_RADIO22);
    else if (cBuchArt == '2')  CheckRadioButton(IDC_RADIO20, IDC_RADIO23, IDC_RADIO23);
    else                       CheckRadioButton(IDC_RADIO20, IDC_RADIO23, IDC_RADIO20);
}

void CDAufDef::InitTourCombos(CString& AArt)
{
    //Tour
    CKNDTOUREN kndtouren;
    kndtouren.s.IDFNR = _model.GetIdfNr();
    kndtouren.s.KUNDENNR = _model.GetIdfNr();
    kndtouren.s.VERTRIEBSZENTRUMNR = _model.GetVzNr();
    strcpy(kndtouren.s.KDAUFTRAGART, AArt);
    m_CoboxTour.ResetContent();
    m_CoboxNakt.ResetContent();
    m_CoboxMix.ResetContent();
    for (;;)
    {
        kndtouren.Server(AasrvGettouren, PIPE_AE_SRV);
        if (kndtouren.rc != SRV_OK)
            break;
        CString tour = kndtouren.s.TOURID;
        CString formattedTour = TourToString(tour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], (kndtouren.s.KZAUTOZUORD[0] == '1' ? 7 : 8));
        m_CoboxMix.AddString(formattedTour);
        if (kndtouren.s.KZAUTOZUORD[0] == '1')
        {
            m_CoboxTour.AddString(formattedTour);
        }
        else
        {
            m_bMixExist = true;
            m_CoboxNakt.AddString(formattedTour);
        }
    }
    if (GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArt.GetString()))
    {
        m_CoboxTour.GetCount() == 0 ? ShowSonder() : ShowAkt();
    }
    else if (m_CoboxTour.GetCount() == 0)
    {
        m_bMixExist = false;
        m_CoboxMix.ResetContent();
        ReadWeektours(AArt);
        InitFuturComboForWholeWeek();
        m_bSonder = m_CoboxNakt.GetCount() > 0 ? true : false;
        m_bSonder ? ShowSonder() : ShowFutur();
    }
    UpdateData(FALSE);
}

CString CDAufDef::TourToString(const CString& tour, long fahrzeit, char cKA, short sWeekday)
{
    CString str;

    str = tour.Left(2);
    int h = atol(str);
    int ah = h + (fahrzeit / 60);

    str = tour.Mid(2, 2);
    int min = atol(str);
    int amin = min + (fahrzeit % 60);

    if (amin > 59)
    {
        ++ah;
        amin -= 60;
    }
    if (ah > 23)
    {
        ah -= 24;
    }

    CString formattedTour;
    formattedTour.Format("%02d:%02d % 11.11s% 2.2s% 7.7s%02d:%02d % 5.5s % 2.2s: %c  %s                       %d",
        h,
        min,
        CResString::ex().getStrTblText(AETXT_UHR_BHF).GetString(),
        tour.Right(2).GetString(),
        CResString::ex().getStrTblText(AETXT_SP_ANKUNFT).GetString(),
        ah,
        amin,
        CResString::ex().getStrTblText(AETXT_UHR).GetString(),
        CResString::ex().getStrTblText(AETXT_KZ_KOMMIART).GetString(),
        cKA,
        m_Tagtab[sWeekday].GetString(),
        sWeekday);

    return formattedTour;
}

void CDAufDef::StringToTour(char* tour, const CString& formattedTour)
{
    CString tourid;
    tourid.Format("%s%s%s", formattedTour.Left(2), formattedTour.Mid(3, 2), formattedTour.Mid(17, 2));
    strcpy(tour, tourid.GetString());
}

void CDAufDef::SetTourCombo()
{
    CString tour = TourToString(_model.GetTour(), 0, ' ', 7);
    CString tourComparer = tour.Left(18);
    int iPos = m_CoboxTour.SelectString(-1, tourComparer);
    if (iPos != CB_ERR)
    {
        m_CoboxTour.SetCurSel(iPos);
        m_CoboxTour.UpdateWindow();
    }
    else if (m_CoboxMix.SelectString(-1, tourComparer) != CB_ERR)
    {
        ShowMixAndResetSelection();
        ShowAndEnableWindow(IDC_BUTTON_SONDER, true);
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
        m_bMixShown = true;
        m_CoboxMix.SelectString(-1, tourComparer);
    }
    else if (m_CoboxNakt.SelectString(-1, tourComparer) == CB_ERR)
    {
        if (m_TourType == Akt)
        {
            ShowAktAndResetSelection();
        }
        else if (m_TourType == Sonder)
        {
            ShowSonderAndResetSelection();
        }
        else if (m_TourType == Futur)
        {
            ShowFuturAndResetSelection();
        }
        else
        {
            ShowMixAndResetSelection();
        }
    }
}

void CDAufDef::ShowAndSelectTourFutur()
{
    ShowFutur();

    CString tour = TourToString(_model.GetTour(), 0,' ',7);
    if (m_CoboxFutur.SelectString(-1, tour.Left(18)) == CB_ERR)
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

void CDAufDef::SetValuta(int mon)
{
    if (mon == 0)
    {
        CheckDlgButton(IDC_CHECK_VALUTA, FALSE);
        m_CheckValuta.EnableWindow(FALSE);
        EnableValutaControls(false);
        return;
    }

    if (!m_CheckValuta.IsWindowEnabled())
    {
        m_CheckValuta.EnableWindow();
    }

    m_CspinMonate.SetRange(0, static_cast<short>(mon));
    m_CspinMonate.SetPos((mon >= 1) ? 1 : mon);

    if (_model.GetValuta())
    {
        EnableValutaControls(true);
        CheckDlgButton(IDC_CHECK_VALUTA, TRUE);
        CString valuta;
        valuta.Format("%d", _model.GetValuta());
        m_EditValuta.SetWindowText(valuta);
    }
    else
    {
        EnableValutaControls(false);
    }
}

void CDAufDef::OnCheckValuta()
{
    bool bValutaChecked = IsDlgButtonChecked(IDC_CHECK_VALUTA) ? true : false;
    UpdateValuta(bValutaChecked);
}

void CDAufDef::UpdateValuta(bool bValutaChecked)
{
    EnableValutaControls(bValutaChecked);
    if (bValutaChecked)
    {
        m_EditValuta.SetFocus();
        m_EditValuta.SetSel( 0, -1, FALSE );
        CalculateAndSetValutaDatum();
        CheckDlgButton(IDC_CHECK_CASH_ORDER, BST_UNCHECKED);
    }
}

void CDAufDef::EnableValutaControls(bool bValutaChecked)
{
    BOOL bValutaChecked_ = bValutaChecked ? TRUE : FALSE;
    m_cs_ValutaMonate.EnableWindow(bValutaChecked_);
    m_EditValuta.EnableWindow(bValutaChecked_);
    m_CspinMonate.EnableWindow(bValutaChecked_);
    m_cs_ValutaDatum.ShowWindow(bValutaChecked ? SW_SHOW : SW_HIDE);
}

void CDAufDef::OnOK()
{
    UpdateData();

    _model.SetABemerkung(m_ABemerkung.Left(MAXIMUM_AUFT_BEM).Trim());
    _model.SetNoRabattKonto(m_bNoRabattKonto ? true : false);
    _model.SetCashOrder(m_bCashOrder ? true : false);

    CAUFTRAG auftrag;

    if (!WriteOrder(auftrag))
    {
        return;
    }
    DisableCancel(); // From now on there could be changes inside order, we need to reset a stable order state. So no Cancel anymore.

    if (!WriteCashRebate(auftrag) || !WriteOrderRemark(auftrag))
    {
        return;
    }

    WriteIVCVoucherNo(auftrag);

    WriteOriginalInvoiceNo(auftrag);

    WriteDelayedDelivery(auftrag);

    if (!WriteTour(auftrag))
    {
        return;
    }

    if (!WriteValuta(auftrag) || !WriteCashOrder(auftrag))
    {
        if (auftrag.s.STATUS == ITEM_STAT_KREDITLIMIT)          //Kreditlimit ueberschritten
        {
            MsgBoxOK(IsDlgButtonChecked(IDC_CHECK_VALUTA) ? AETXT_NO_VAL_KL : AETXT_KREDITLIMIT);
        }
        return;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DAufDef.cpp", "OnOK", "Order changed close dialog");
    CDialogMultiLang::OnOK();
}

bool CDAufDef::WriteOrder(CAUFTRAG& auftrag)
{
    if (!SetRemarks(auftrag.s) || !SetOrderType(auftrag.s))
    {
        return false;
    }
    SetCommiType(auftrag.s);
    SetBookingType(auftrag.s);
    SetSubOrderType(auftrag.s);

    AeGetApp()->m_AeLogging.WriteLine(2, "DAufDef.cpp", "OnOK", "Change order start");
    auftrag.Server(AasrvChangeorder, PIPE_AE_SRV); //Auftrags- und Buchungsart setzen
    if (auftrag.rc < SRV_OK)
    {
        return false;
    }
    SetValuesOnChangeOrder(auftrag.s);

    return true;;
}

bool CDAufDef::SetRemarks(AUFTRAG& auftrag)
{
    //Bemerkung setzen

    strcpy(auftrag.BEMERKUNGEN, _model.GetABemerkung());

    int anz = AeGetApp()->GetAnzForbiddenWords();
    for (int i = 0; i < anz; ++i)
    {
        if (_model.GetABemerkung().Find(AeGetApp()->GetForbiddenWords(i)) != -1)
        {
            CString cStr;
            cStr.Format(CResString::ex().getStrTblText(AETXT_FORBIDDEN), AeGetApp()->GetForbiddenWords(i).GetString());
            MsgBoxOK(cStr);
            m_EditBemerkung.SetFocus();
            return false;
        }
    }

    if (_model.GetBemerkungEing() && _model.GetABemerkung().IsEmpty())
    {
        MsgBoxOK(IDP_KOPF_BEM_EING);
        m_EditBemerkung.SetFocus();
        return false;
    }

    return true;
}

bool CDAufDef::SetOrderType(AUFTRAG& auftrag)
{
    //Auftragsart bestimmen
    CString ordertype;
    m_CoboxAufArt.GetLBText(m_CoboxAufArt.GetCurSel(), ordertype);
    ordertype = ordertype.Left(2);
    strcpy(auftrag.KDAUFTRAGART, ordertype);

    if (AeGetApp()->IsBG())
    {
        bool natra = GetOrderType().IsNatraAufArt(AeGetApp()->VzNr_Kunde(), auftrag.KDAUFTRAGART);
        AeGetApp()->IsNatraEingabe = natra;

        bool noPromo = GetOrderType().IsAufArtNoPromo(AeGetApp()->VzNr_Kunde(), auftrag.KDAUFTRAGART);
        AeGetApp()->IsAuftNoPromo = noPromo;
    }
    auftrag.TENDERNO = 0;
    if ((ordertype == "TO") || (ordertype == "TI"))
    {
        if (_model.GetTenderNo() == 0)
        {
            MsgBoxOK(AETXT_NO_TENDER);
            return false;
        }
        auftrag.TENDERNO = _model.GetTenderNo();
    }
    else if ((ordertype == "RO") && (AeGetApp()->RODateFrom() == 0))
    {
        CDRabattOrder ro;
        if (ro.DoModal() == IDCANCEL)
        {
            MsgBoxOK(AETXT_NO_RO_PARAM);
            return false;
        }
        AeGetApp()->RODateFrom = ConvertDate(ro.m_CT_DatumVon);

        CString zuGrund = _model.GetZuGrund();
        zuGrund.SetAt(ZU_KREDITLIMIT, '0');
        _model.SetZuGrund(zuGrund);
    }

    return true;
}

void CDAufDef::SetCommiType(AUFTRAG& auftrag)
{
    //Kommissionierart bestimmen
    CString value;
    int id = GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18);
    switch (id)
    {
    case IDC_RADIO10:
        value = "0";
        break;
    case IDC_RADIO11:
        value = "3";
        break;
    case IDC_RADIO12:
        value = "4";
        break;
    case IDC_RADIO13:
        value = "5";
        break;
    case IDC_RADIO14:
        value = "6";
        break;
    case IDC_RADIO15:
        value = "1";
        break;
    case IDC_RADIO16:
        value = "2";
        break;
    case IDC_RADIO17:
        value = "8";
        break;
    case IDC_RADIO18:
        value = "7";
        break;
    default:
        value = "0";
        break;
    }

    strcpy_s(auftrag.KOART, value.GetString());
}

void CDAufDef::SetBookingType(AUFTRAG& auftrag)
{
    //Buchungsart bestimmen
    CString value;
    int id = GetCheckedRadioButton(IDC_RADIO20, IDC_RADIO23);
    switch (id)
    {
    case IDC_RADIO20:
        value = "0";
        break;
    case IDC_RADIO21:
        value = "4";
        break;
    case IDC_RADIO22:
        value = "3";
        break;
    case IDC_RADIO23:
        value = "2";
        break;
    default:
        value = "0";
        break;
    }

    strcpy_s(auftrag.BUCHART, value.GetString());
}

void CDAufDef::SetSubOrderType(AUFTRAG& auftrag)
{
    //Check ob Auftragart mit Subordertype
    if (GetOrderType().IsMustSubOrder(AeGetApp()->VzNr(), auftrag.KDAUFTRAGART))
    {
        CString subtype;
        int subsel = m_Cobox_SubOrder.GetCurSel();
        if (subsel != CB_ERR)
        {
            m_Cobox_SubOrder.GetLBText(subsel,subtype);
        }
        AeGetApp()->ActEKGrp = subtype.Right(3);
        auftrag.SUB_ORDER_TYPE[0] = subtype.GetAt(0);
        auftrag.SUB_ORDER_TYPE[1] = subtype.GetAt(1);
        auftrag.SUB_ORDER_TYPE[2] = subtype.GetAt(2);
        auftrag.SUB_ORDER_TYPE[3] = '\0';
    }
    else
    {
        AeGetApp()->ActEKGrp = "";
        auftrag.SUB_ORDER_TYPE[0] = '\0';
    }
}

void CDAufDef::SetValuesOnChangeOrder(AUFTRAG& auftrag)
{
    _model.SetKommArt(auftrag.KOART);
    _model.SetBuchArt(auftrag.BUCHART);
    _model.SetAArt(auftrag.KDAUFTRAGART);
    AllgEntfSpaces(auftrag.SUB_ORDER_TYPE);
    _model.SetSubType(auftrag.SUB_ORDER_TYPE);
    AllgEntfSpaces(auftrag.BEMERKUNGEN);
    _model.SetTour(auftrag.TOURID);
    _model.SetDeliveryDate(auftrag.DELIVERYDATE);
    _model.SetAnzDef(auftrag.ANZDEFEKTUB);
    _model.SetBalance(auftrag.BALANCE);
    _model.SetBalance2(auftrag.BALANCE2);
}

bool CDAufDef::WriteCashRebate(CAUFTRAG& auftrag)
{
    if (m_bNoRabattKontoInitial != _model.GetNoRabattKonto())
    {
        auftrag.s.NORABATTKONTO[0] = _model.GetNoRabattKonto() ? '1' : '0';
        auftrag.Server(AasrvSetCashRebate, PIPE_AE_SRV); //Kunde will Rechnungsrabatt
        if (auftrag.rc < SRV_OK)
        {
            return false;
        }
    }
    return true;
}

bool CDAufDef::WriteOrderRemark(CAUFTRAG& auftrag)
{
    auftrag.Server(AasrvChangeOrdBem, PIPE_AE_SRV);   //Bemerkung setzen
    if (auftrag.rc < SRV_OK)
    {
        return false;
    }

    return true;
}

void CDAufDef::WriteIVCVoucherNo(CAUFTRAG& auftrag)
{
    //Check ob Auftragart mit IVC-Nummer
    if (!GetOrderType().IsAufArtIVCNo(AeGetApp()->VzNr(), _model.GetAArt().GetString()))
    {
        _model.SetIVC(0L);
        m_IVC.Empty();
        m_EditIVC.SetWindowTextA(m_IVC);
    }
    else
    {
        _model.SetIVC(atol(m_IVC));
    }
    if (m_lIVCInitial != _model.GetIVC())
    {
        auftrag.s.RELATIONNO = _model.GetIVC();
        auftrag.Server(AasrvSetIVCVoucherNo, PIPE_AE_SRV);    //IVC-Nummer setzen
    }
}

void CDAufDef::WriteOriginalInvoiceNo(CAUFTRAG& auftrag)
{
    //Check ob Auftragart mit orginal-Rechnungs-Nummer
    if (!GetOrderType().IsAufArtOriginalInvoiceNo(AeGetApp()->VzNr(), _model.GetAArt().GetString()))
    {
        m_OrgInvoice.Empty();
        m_EditOrgInvoice.SetWindowTextA(m_OrgInvoice);
    }
    if (m_OrgInvoice_old != m_OrgInvoice)
    {
        auftrag.s.RELATIONNO = atol(m_OrgInvoice);
        auftrag.Server(AasrvSetOriginalInvoiceNo, PIPE_AE_SRV);   //orginal-Rechnungs-Nummer setzen
    }
}

bool CDAufDef::WriteValuta(CAUFTRAG& auftrag)
{
    //Valuta setzen
    if (IsDlgButtonChecked(IDC_CHECK_VALUTA))
    {
        CString valuta;
        m_EditValuta.GetWindowText(valuta);
        _model.SetValuta(atol(valuta));
        long date = GetDatumValuta();
        _model.SetDatumValuta(date);
    }
    else
    {
        _model.SetValuta(0L);
        _model.SetDatumValuta(0L);
    }

    if (_model.GetValuta() == m_lValutaInitial)
    {
        return true; // Valuta did not change
    }

    auftrag.s.VALUTAMONATE = _model.GetValuta();
    auftrag.Server(AasrvChangeValuta, PIPE_AE_SRV);
    return auftrag.rc >= SRV_OK ? true : false;
}

long CDAufDef::GetDatumValuta()
{
    // hier wieder valutomonauto abziehen, werden spaeter in orderclose dazugerechnet
    CString cdatum;
    m_cs_ValutaDatum.GetWindowText(cdatum);

    long ljahr = atol(cdatum.Right(4));
    long lmonat = atol(cdatum.Mid(3, 2));
    long ltag = atol(cdatum.Left(2));

    if ((m_lAutoValuta != 0) && (_model.GetBatchschreiben() != 9) && (_model.GetBatchschreiben() != 10))
    {
        lmonat -= m_lAutoValuta;
        CalculateYearChange(lmonat, ljahr);
    }
    return GetDate(ljahr, lmonat, ltag);
}

void CDAufDef::WriteDelayedDelivery(CAUFTRAG& auftrag)
{
    //Verzoegerte Auslieferung
    if (IsDlgButtonChecked(IDC_CHECK_DD))
    {
        long newDelayedDelivery = ConvertDate(m_CT_DelayedDelivery);
        if (newDelayedDelivery != _model.GetDatumDelayedDelivery())
        {
            auftrag.s.DATUMAUSLIEFERUNG = newDelayedDelivery;
            auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
            _model.SetDatumDelayedDelivery(newDelayedDelivery);
        }
    }
    else if (_model.GetDatumDelayedDelivery() > 0)
    {
        auftrag.s.DATUMAUSLIEFERUNG = m_lActDatum;
        auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
        _model.SetDatumDelayedDelivery(m_lActDatum);
    }
    else
    {
        _model.SetDatumDelayedDelivery(0L);
    }
}

bool CDAufDef::WriteTour(CAUFTRAG& auftrag)
{
    //Tour setzen
    if (auftrag.s.KOART[0] == '2') //2 entspr. keine Kommi
    {
        _model.SetTour("");
        _model.SetDeliveryDate(0L);
    }
    else
    {
        CComboBox* pComboBox;
        switch (m_TourType)
        {
        case Futur:
            pComboBox = &m_CoboxFutur;
            break;
        case Akt:
            pComboBox = &m_CoboxTour;
            break;
        case Mix:
            pComboBox = &m_CoboxMix;
            break;
        case Sonder:
        default:
            pComboBox = &m_CoboxNakt;
            break;
        }
        CString tour;
        int toursel = pComboBox->GetCurSel();
        if (toursel != CB_ERR)
        {
            pComboBox->GetLBText(toursel, tour);
        }
        else
        {
            tour = "";
        }
        if (tour.GetLength() >= 18)
        {
            StringToTour(auftrag.s.TOURID, tour);
            auftrag.Server(AasrvChangeTour, PIPE_AE_SRV);
            if (auftrag.rc < SRV_OK)
            {
                return false;
            }
            _model.SetTour(auftrag.s.TOURID);
            _model.SetDeliveryDate(auftrag.s.DELIVERYDATE);
        }
        else
        {
            auftrag.s.TOURID[0] = '\0';
            if (tour.GetLength() >= 1)
            {
                MsgBoxOK(IDP_NO_TOURID);
            }
        }
    }
    ((CAeFView*)AeGetApp()->m_pViewEing)->SetTimerTour((atol(auftrag.s.TOURID) / 100) * 100);

    return true;
}

bool CDAufDef::WriteCashOrder(CAUFTRAG& auftrag)
{
    if (m_bCashOrderInitial != _model.GetCashOrder())
    {
        auftrag.s.PAYMENTTYPE[0] = _model.GetCashOrder() ? 'C' : 'Z';
        auftrag.Server(AasrvSetOrderToCash, PIPE_AE_SRV);
        if (auftrag.s.STATUS == ITEM_STAT_KREDITLIMIT)          //Kreditlimit ueberschritten
        {
            return false;
        }
    }
    return true;
}

void CDAufDef::DisableCancel()
{
    m_bCancel = false;
    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
}

void CDAufDef::OnChangeEditBemerkung()
{
    if (AeGetApp()->IsRS())
    {
        if (!AllgCheckPrintableSign(&m_EditBemerkung)) return;
    }
    AllgLaengeKontr(&m_EditBemerkung, MAXIMUM_AUFT_BEM, AeGetApp()->Modus());
}

void CDAufDef::OnChangeEditValMon2()
{
    int wert = MAXIMUM_MON_VALUTA;
    if (ValutaInDays())
    {
        wert *= 30;
    }
    AllgWertKontr(&m_EditValuta, wert);
    CalculateAndSetValutaDatum();
    CheckDlgButton(IDC_CHECK_CASH_ORDER, BST_UNCHECKED);
}

void CDAufDef::OnCancel()
{
    if (m_bCancel)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DAufDef.cpp", "OnCancel", "Cancel dialog");
        CDialogMultiLang::OnCancel();
    }
}

void CDAufDef::OnSelchangeComboAufArt()
{
    UpdateOnChangeAufArt();
}

void CDAufDef::UpdateOnChangeAufArt()
{
    //Auftragsart
    CAUFARTES aufartes;

    //Auftragsart bestimmen
    CString AArt;
    m_CoboxAufArt.GetLBText(m_CoboxAufArt.GetCurSel(), AArt);
    CString AArtkurz = AArt.Left(2);
    m_AArtWished = AArtkurz;
    if (AeGetApp()->IsBG())
    {
        _model.SetServType(0L);
        if (m_AArtWished.GetAt(0) == 'S')    //Service-Auftragsart
        {
            CSERVICEORDER serviceorder;
            serviceorder.SetOrder_type(m_AArtWished);
            if (serviceorder.SelType())
            {
                CString CStr;
                CStr.Format(CResString::ex().getStrTblText(AETXT_NO_SERVICE), m_AArtWished.GetString());
                MsgBoxOK(CStr);
                m_CoboxAufArt.SelectString(-1, _model.GetAArt());
                return;
            }
            _model.SetServType(serviceorder.GetServicetypeno());
        }
    }

    //Check ob Auftragart mit IVC-Nummer
    ShowAndEnableWindow(IDC_EDIT_IVC, IDC_STATIC_IVC,
        GetOrderType().IsAufArtIVCNo(AeGetApp()->VzNr(), AArtkurz.GetString()) ? true : false);

    //Check ob Auftragart mit Orginal-Rechnungs-Nummer
    ShowAndEnableWindow(IDC_EDIT_ORIGINVOICE, IDC_STATIC_ORIGINVOICE,
        GetOrderType().IsAufArtOriginalInvoiceNo(AeGetApp()->VzNr(), AArtkurz.GetString()) ? true : false);

    //Check ob Auftragart mit Subordertype
    if (GetOrderType().IsMustSubOrder(AeGetApp()->VzNr(), AArtkurz.GetString()))
    {
        ShowAndEnableWindow(IDC_COMBO_SUB_ORDER, (HoleSubOrder(AArtkurz) > 0) ? true : false);
    }

    //Check ob Auftragart ohne verzoegerte Auslieferung
    ShowAndEnableWindow(IDC_CHECK_DD, IDC_DATETIMEPICKER_DD,
        GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArtkurz.GetString()) ? false : true);

    //Einstellung Standard Auftrags- bzw. Buchungsart
    CString cBuchArt;
    CString cKommArt;
    CString cTourId;
    AeGetApp()->m_KombiAKBArt.GetStandardOrderKomb(AArt.Left(2), cKommArt, cBuchArt, cTourId, _model.GetVzNr());
    SetBuchArt(cBuchArt.GetAt(0));
    SetKommArt(cKommArt.GetAt(0));
    m_CoboxAufArt.GetLBText(m_CoboxAufArt.GetCurSel(),AArt);
    VersorgeTouren(m_AArtWished);
    //Einstellung Standard-tour
    cTourId.TrimRight();
    _model.SetTour(cTourId.IsEmpty() ? m_saveTour : cTourId);
    if ((_model.GetDatumDelayedDelivery() > m_lActDatum) && IsDlgButtonChecked(IDC_CHECK_DD))
    {
        ShowAndSelectTourFutur();
    }
    else
    {
        SetTourCombo();
    }

    //Bei ursprünglicher Auftragsart auch ursprüngliche Kommi und Buchungsart eintragen
    if (_model.GetAArt() == AArt.Left(2))
    {
        SetBuchArt( _model.GetBuchArt().GetAt(0) );
        SetKommArt( _model.GetKommArt().GetAt(0) );
    }
    BeginWaitCursor();
    aufartes.s.IDFNR = _model.GetIdfNr();
    aufartes.s.KUNDENNR = _model.GetIdfNr();
    aufartes.s.VERTRIEBSZENTRUMNR = _model.GetVzNr();
    strcpy(aufartes.s.KDAUFTRAGART,AArt.Left(2));
    aufartes.Server(AaauftSel_valutatage);
    if (aufartes.rc == SRV_OK)
    {
        m_sValutaTage = (short)aufartes.s.VALUTAMONATE;
        m_cs_ValutaAuto.ShowWindow(SW_SHOW);
        CString valuta;
        valuta.Format(CResString::ex().getStrTblText(IDS_AUTO_VALUTA_TAGE),aufartes.s.VALUTAMONATE);
        m_cs_ValutaAuto.SetWindowText(valuta);
    }
    else
    {
        aufartes.Server(AaauftSel_valutaauto);
        m_lAutoValuta = aufartes.s.VALUTAMONATE;
        if ((aufartes.rc != SRV_OK) || (aufartes.s.VALUTAMONATE == 0))
        {
            m_cs_ValutaAuto.ShowWindow(SW_HIDE);
        }
        else
        {
            CString valuta;
            valuta.Format(CResString::ex().getStrTblText(IDS_AUTO_VALUTA), aufartes.s.VALUTAMONATE);
            m_cs_ValutaAuto.SetWindowText(valuta);
            m_cs_ValutaAuto.ShowWindow(SW_SHOW);
        }
    }

    EndWaitCursor();

    int maxAA = m_aAArten.GetSize();
    for (int i = 0; i < maxAA; ++i)
    {
        CString cStr = m_aAArten[i];
        if (AArt.Left(2) == cStr.Left(2))
        {
            // Calculate new valuta (days/monthes)
            int mon = atol(cStr.Right(3));
            if ((m_lAutoValuta != 0) && (_model.GetBatchschreiben() != 9) && (_model.GetBatchschreiben() != 10))
            {
                mon -= m_lAutoValuta;
            }
            if (ValutaInDays())
            {
                long ltag;
                long lmonat;
                long ljahr;
                GetDate(m_lActDatum, ljahr, lmonat, ltag);

                CTime actualdatum(ljahr, lmonat, ltag, 2, 0, 0);
                lmonat += mon;
                CalculateYearChange(ljahr, lmonat);
                CTime valutadatum(ljahr, lmonat, ltag, 2, 0, 0);
                CTimeSpan spanne = valutadatum - actualdatum;
                // in BG und RS Valuta in Tagen
                mon = (int)spanne.GetDays();
            }
            SetValuta(mon);
        }
    }
    if ((m_AArtWished == "TO") || (m_AArtWished == "TI"))
    {
        int iStaat = 0;
        AeGetApp()->IsTOStaat = false;
        if (AeGetApp()->IsBG())
        {
            // in BG auswaehlen Staats- oder Krankenhaustender
            if (MsgBoxYesNo(AETXT_STAATS_TENDER) == IDYES)
            {
                AeGetApp()->IsTOStaat = true;
                iStaat = 1;
                // Bei Staatstender immer TO - TI kommt aus Tenderverwaltung
                m_AArtWished = "TO";
                if (m_CoboxAufArt.SelectString(-1, m_AArtWished) == CB_ERR)
                {
                    m_CoboxAufArt.SetCurSel(0);
                }
            }

        }
        if (_model.GetTenderNo() == 0)
        {
            CDTenderWahl dlgTenderWahl;
            dlgTenderWahl.m_sVz = _model.GetVzNr();
            dlgTenderWahl.m_lKnd = _model.GetKndNr();
            dlgTenderWahl.m_iStaat = iStaat;
            if (dlgTenderWahl.DoModal() != IDCANCEL)
            {
                _model.SetTenderNo(dlgTenderWahl.m_lTenderNo);
                if (!iStaat)
                {
                    if (!dlgTenderWahl.m_cContract.IsEmpty())
                    {
                        m_AArtWished = "TI";
                        if (m_CoboxAufArt.SelectString(-1, m_AArtWished) == CB_ERR)
                        {
                            m_CoboxAufArt.SetCurSel(0);
                        }
                    }
                    else
                    {
                        if (m_AArtWished == "TI")
                        {
                            MsgBoxOK(AETXT_NO_CONTRACT);
                            _model.SetTenderNo(0L);
                        }
                    }
                }
            }
        }
    }
    if (m_AArtWished == "CV")    //Collectiv Orders
    {
        CTime heute = ConvertDate(m_lActDatum, 2);
        CTimeSpan jahr(365, 0, 0, 0);
        m_CT_DelayedDelivery = heute + jahr;

        UpdateData(FALSE);
        CheckDlgButton(IDC_CHECK_DD, TRUE);
        OnCheckDelayedDelivery();
    }
}

void CDAufDef::OnRadioKomArt()
{
    SetTourComboOnRadioKomArt();
    m_bKommiArtManuell = true;
}

void CDAufDef::SetTourComboOnRadioKomArt()
{
    bool showTour = (GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18) == IDC_RADIO16) ? false : true;

    if (m_TourType == Akt)
    {
        ShowAndEnableWindow(IDC_COMBO_TOUR, showTour);
    }
    else if (m_TourType == Sonder)
    {
        ShowAndEnableWindow(IDC_COMBO_TOUR_NAKT, showTour);
    }
    else if (m_TourType == Futur)
    {
        ShowAndEnableWindow(IDC_COMBO_FUTUR, showTour);
    }
    else if (m_TourType == Mix)
    {
        ShowAndEnableWindow(IDC_COMBO_MIX, showTour);
    }

    m_cs_SonderTour.ShowWindow(showTour && (m_TourType == Sonder) ? SW_SHOW : SW_HIDE);
    GetDlgItem(IDC_STATIC_TOUR)->EnableWindow(showTour ? TRUE : FALSE);
}

HBRUSH CDAufDef::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (   (pWnd == &m_cs_ValutaAuto)
        || (pWnd == &m_CoboxFutur) )
    {
        pDC->SetTextColor(RGB(0, 0, 200));
    }
    else if (   (pWnd == &m_cs_SonderTour)
             || (pWnd == &m_CoboxNakt) )
    {
        pDC->SetTextColor(RGB(200, 0, 0));
    }
    else if (pWnd == &m_CoboxMix)
    {
        pDC->SetTextColor(RGB((m_bAnzSonder ? 200 : 0), 0, 0));
    }
    return hbr;
}

void CDAufDef::OnSelchangeComboTour()
{
    CString tour;
    if (!GetTour(m_CoboxTour, tour))
    {
        return;
    }
    SetKommArt42(tour);
    CString tour17 = FormatTour17(tour);
    _model.SetTour(tour17);
    m_saveTour = _model.GetTour();
}

bool CDAufDef::GetTour(CComboBox& combo, CString& tour)
{
    int toursel = combo.GetCurSel();
    if (toursel == CB_ERR)
    {
        return false;
    }
    combo.GetLBText(toursel, tour);
    return true;
}

CString CDAufDef::FormatTour17(CString tour)
{
    char ctour[10];
    if (tour.GetLength() >= 17)
    {
        StringToTour(ctour, tour);
        return ctour;
    }
    return tour;
}

void CDAufDef::SetKommArt42(CString tour)
{
    if (m_bKommiArtManuell || (tour.GetLength() < 42) || (tour.GetAt(42) == ' '))
    {
        return;
    }
    SetKommArt(tour.GetAt(42));
}

LRESULT CDAufDef::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    char wert[2];
    if (((LPMSG)lpMsg)->wParam >= VK_NUMPAD0 && ((LPMSG)lpMsg)->wParam <= VK_NUMPAD9)
        sprintf(wert, "%01d", ((LPMSG)lpMsg)->wParam - VK_NUMPAD0);
    else if (((LPMSG)lpMsg)->wParam >= '0' && ((LPMSG)lpMsg)->wParam <= '9')
        sprintf(wert, "%01d", ((LPMSG)lpMsg)->wParam - '0');
    else
        return 0L;
    if (GetFocus() == &m_CoboxAufArt)
    {
        SetKommArt(wert[0]);
        OnRadioKomArt();
        GetDlgItem(IDC_RADIO10)->SetFocus();
        return 1L;
    }
    else if (GetFocus() == GetDlgItem(IDC_RADIO10))
    {
        SetBuchArt(wert[0]);
        return 1L;
    }
    return 0L;
}

void CDAufDef::CalculateAndSetValutaDatum()
{
    long ltag;
    long lmonat;
    long ljahr;
    GetCurrentValutaDate(ljahr, lmonat, ltag);

    // Valuta from input
    CString cValuta;
    m_EditValuta.GetWindowText(cValuta);
    long lValuta = atol(cValuta);
    long lValutaDiff = lValuta - _model.GetValuta();

    // Calculate new valuta date
    long autoValuta = (m_lAutoValuta != 0) && (_model.GetBatchschreiben() != 9) && (_model.GetBatchschreiben() != 10) ? m_lAutoValuta : 0L;

    long ldatum;
    if (ValutaInDays())
    {
        // In these countries lValutaDiff is in DAYS
        CTime valutadatum(ljahr, lmonat, ltag, 2, 0, 0);
        CTimeSpan spanne(lValutaDiff, 0, 0, 0);
        valutadatum += spanne;
        ltag = valutadatum.GetDay();
        lmonat = valutadatum.GetMonth();
        ljahr = valutadatum.GetYear();
        lmonat += autoValuta;
        CalculateYearChange(ljahr, lmonat);
        CTime valutadatumNeu(ljahr, lmonat, ltag, 2, 0, 0);
        ldatum = ConvertDate(valutadatumNeu);
    }
    else
    {
        // In all other countries lValutaDiff is in MONTHES
        lmonat += autoValuta + lValutaDiff;
        CalculateYearChange(ljahr, lmonat);
        ldatum = GetDate(ljahr, lmonat, ltag);
    }

    char cdatum[11];
    AllgDatumLong2CharTTMMJJJJ(ldatum, cdatum);
    m_cs_ValutaDatum.SetWindowText(cdatum);
}

void CDAufDef::GetCurrentValutaDate(long& year, long& month, long& day)
{
    long date = (_model.GetDatumValuta() == 0) ? m_lActDatum : _model.GetDatumValuta();

    GetDate(date, year, month, day);
}

void CDAufDef::CalculateYearChange(long& year, long& month)
{
    if (month > 12)
    {
        ++year;
        month -= 12;
    }
    else if (month < 1)
    {
        --year;
        month += 12;
    }
}

void CDAufDef::OnCheckDelayedDelivery()
{
    UpdateTourComboOnDelayedDelivery();
}

void CDAufDef::UpdateTourComboOnDelayedDelivery()
{
    UpdateData();

    if (IsDlgButtonChecked(IDC_CHECK_DD))
    {
        m_DT_DelayedDelivery.ShowWindow(SW_SHOW);
        ReadWeektours(m_AArtWished);
        CTimeSpan y(1,0,0,0);

        for (int i = 0; i < 6; ++i)
        {
            InitFuturComboOnDelayedDeliveryDate();

            if (m_CoboxFutur.GetCount() > 0)
            {
                break;
            }

            m_CT_DelayedDelivery += y;
        }
        SetTourComboOnDelayedDeliveryDate();
    }
    else
    {
        m_DT_DelayedDelivery.ShowWindow(SW_HIDE);
        if (m_CoboxTour.GetCount() == 0)
        {
            m_bSonder = true;
            if (ShowSonderAndResetSelection() == CB_ERR)
            {
                MsgBoxOK(IDP_NO_TOURID);
            }
            else
            {
                UpdateTourOnSonder();
            }
        }
        else
        {
            ShowAktAndResetSelection();
            m_bSonder = false;
        }
    }
    UpdateData(FALSE);
}

void CDAufDef::OnDatechangeDelayedDelivery(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    UpdateData();

    InitFuturComboOnDelayedDeliveryDate();

    SetTourComboOnDelayedDeliveryDate();

    *pResult = 0L;
}

void CDAufDef::SetTourComboOnDelayedDeliveryDate()
{
    long newDelayedDeliveryDate = ConvertDate(m_CT_DelayedDelivery);
    if (newDelayedDeliveryDate > m_lActDatum)
    {
        ShowFuturAndResetSelection();
        m_bSonder = false;
    }
    else if (!ShowSonderOnEmptyAkt())
    {
        ShowAktAndResetSelection();
        m_bSonder = false;
    }
}

// return true if successful
bool CDAufDef::ShowSonderOnEmptyAkt()
{
    if (m_CoboxTour.GetCount() == 0)
    {
        ShowSonderAndResetSelection();
        m_bSonder = true;
        return true;
    }
    return false;
}

void CDAufDef::OnSelchangeComboSonder()
{
    UpdateTourOnSonder();
}

void CDAufDef::UpdateTourOnSonder()
{
    CString tour;
    if (!GetTour(m_CoboxNakt, tour))
    {
        return;
    }
    SetKommArt42(tour);
    CString tour17 = FormatTour17(tour);
    _model.SetTour(tour17);
    m_saveTour = _model.GetTour();
}

void CDAufDef::ReadWeektours(CString& AArt)
{
    //Tour
    CKNDTOUREN kndtouren;
    kndtouren.s.IDFNR = _model.GetIdfNr();
    kndtouren.s.KUNDENNR = _model.GetIdfNr();
    kndtouren.s.VERTRIEBSZENTRUMNR = _model.GetVzNr();
    strcpy(kndtouren.s.KDAUFTRAGART, AArt);
    m_aWochentouren.RemoveAll();
    for (;;)
    {
        kndtouren.Server(AasrvGetWeektouren, PIPE_AE_SRV);
        if (kndtouren.rc != SRV_OK)
            break;
        CString tour = kndtouren.s.TOURID;  //Tournummer
        CString formattedTour = TourToString(tour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], kndtouren.s.WEEKDAY);
        m_aWochentouren.Add(formattedTour);
    }
}

void CDAufDef::InitFuturComboOnDelayedDeliveryDate()
{
    CTime dateDelayedDelivery = (m_CT_DelayedDelivery > 0) ? m_CT_DelayedDelivery : ConvertDate(_model.GetDatumDelayedDelivery(), 0);
    InitFuturCombo(static_cast<short>(dateDelayedDelivery.GetDayOfWeek() - 1));
}

void CDAufDef::InitFuturComboForWholeWeek()
{
    InitFuturCombo(9);
}

void CDAufDef::InitFuturCombo(short sWeekday)
{
    //Tour
    m_CoboxFutur.ResetContent();
    for (int i = 0; i < m_aWochentouren.GetCount(); ++i)
    {
        if (   (sWeekday == 9) // fill m_CoboxFutur with every available tour
            || (sWeekday == atoi(m_aWochentouren.GetAt(i).Right(1))) )
        {
            m_CoboxFutur.AddString(m_aWochentouren.GetAt(i));
        }
    }
    if (sWeekday == 9)
    {
        CString weekday;
        weekday.Format("%d", m_sWeekday);
        if (!SetFuturCurSel(weekday, 50))
        {
            SetFuturCurSel(weekday, 48);
        }
    }
    else
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

bool CDAufDef::SetFuturCurSel(CString weekday, int iChar)
{
    CString csTour;
    for (int i = 0; i < m_CoboxFutur.GetCount(); ++i)
    {
        m_CoboxFutur.GetLBText(i, csTour);
        if (weekday[0] < csTour.GetAt(iChar))
        {
            m_CoboxFutur.SetCurSel(i);
            return true;
        }
    }
    return false;
}

int CDAufDef::HoleSubOrder(CString &AArt)
{
    CCSTDISCCONT cst;
    int i = 0;
    cst.SetBranchno(_model.GetVzNr());
    cst.SetCustomerno(_model.GetIdfNr());
    cst.SetOrder_type(AArt);
    m_Cobox_SubOrder.ResetContent();
    while (cst.SelList() == SRV_OK)
    {
        CString sub;
        ppString type;
        ppString ekgr;
        sub.Format("%3s  %6s: %02d  %6s: %3s",
            cst.GetSub_order_type(type),
            CResString::ex().getStrTblText(AETXT_VALUTA).GetString(),
            cst.GetValuta_days(),
            CResString::ex().getStrTblText(AETXT_EK_GRP).GetString(),
            cst.GetPharmacygroupid(ekgr) );
        if (_model.GetGebucht() && (_model.GetSubType() != type))
        {
            continue;
        }
        m_Cobox_SubOrder.AddString(sub);
        ++i;
    }
    cst.CloseCursor();
    ShowAndEnableWindow(IDC_COMBO_SUB_ORDER, (i == 0 ? false : true));
    if ((i != 0) && (m_Cobox_SubOrder.SelectString(-1, _model.GetSubType()) == CB_ERR))
    {
        m_Cobox_SubOrder.SetCurSel(0);
    }
    return i;
}

void CDAufDef::OnBnClickedButtonSonder()
{
    ShowAndEnableWindow(IDC_BUTTON_SONDER, true);
    if (m_bMixShown)
    {
        m_bSonder ? ShowSonder() : ShowAkt();
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
        m_bMixShown = false;
    }
    else
    {
        ShowMixAndResetSelection();
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
        m_bMixShown = true;
    }
}

void CDAufDef::OnSelchangeComboMix()
{
    UpdateTourOnMix();
}

void CDAufDef::UpdateTourOnMix()
{
    CString tour;
    if (!GetTour(m_CoboxNakt, tour))
    {
        return;
    }
    SetKommArt42(tour);
    CString tourtyp = tour.Mid(45, m_Tagtab.GetAt(8).GetLength());
    m_bAnzSonder = m_Tagtab.GetAt(8) == tourtyp ? true : false;
}

void CDAufDef::ShowAktAndResetSelection()
{
    ShowAkt();
    m_CoboxTour.SetCurSel(0);
}

void CDAufDef::ShowAkt()
{
    m_TourType = Akt;
    m_cs_SonderTour.ShowWindow(SW_HIDE);
    ShowAndEnableWindow(IDC_COMBO_TOUR_NAKT, false);
    ShowAndEnableWindow(IDC_COMBO_MIX, false);
    ShowAndEnableWindow(IDC_COMBO_TOUR, true);
    ShowAndEnableWindow(IDC_COMBO_FUTUR, false);
    ShowAndEnableWindow(IDC_BUTTON_SONDER, m_bMixExist);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxTour.GetCurSel() == CB_ERR)
    {
        m_CoboxTour.SetCurSel(0);
    }
}

int CDAufDef::ShowSonderAndResetSelection()
{
    ShowSonder();
    return m_CoboxNakt.SetCurSel(0);
}

void CDAufDef::ShowSonder()
{
    m_TourType = Sonder;
    m_cs_SonderTour.ShowWindow(SW_SHOW);
    ShowAndEnableWindow(IDC_COMBO_TOUR_NAKT, true);
    ShowAndEnableWindow(IDC_COMBO_MIX, false);
    ShowAndEnableWindow(IDC_COMBO_TOUR, false);
    ShowAndEnableWindow(IDC_COMBO_FUTUR, false);
    ShowAndEnableWindow(IDC_BUTTON_SONDER, false);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxNakt.GetCurSel() == CB_ERR)
    {
        m_CoboxNakt.SetCurSel(0);
    }
}

void CDAufDef::ShowFuturAndResetSelection()
{
    ShowFutur();
    m_CoboxFutur.SetCurSel(0);
}

void CDAufDef::ShowFutur()
{
    m_TourType = Futur;
    m_cs_SonderTour.ShowWindow(SW_HIDE);
    ShowAndEnableWindow(IDC_COMBO_TOUR_NAKT, false);
    ShowAndEnableWindow(IDC_COMBO_MIX, false);
    ShowAndEnableWindow(IDC_COMBO_TOUR, false);
    ShowAndEnableWindow(IDC_COMBO_FUTUR, true);
    ShowAndEnableWindow(IDC_BUTTON_SONDER, false);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxFutur.GetCurSel() == CB_ERR)
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

void CDAufDef::ShowMixAndResetSelection()
{
    ShowMix();
    m_CoboxMix.SetCurSel(0);
}

void CDAufDef::ShowMix()
{
    m_TourType = Mix;
    m_cs_SonderTour.ShowWindow(SW_HIDE);
    ShowAndEnableWindow(IDC_COMBO_TOUR_NAKT, false);
    ShowAndEnableWindow(IDC_COMBO_MIX, true);
    ShowAndEnableWindow(IDC_COMBO_TOUR, false);
    ShowAndEnableWindow(IDC_COMBO_FUTUR, false);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
    UpdateTourOnMix();
}

void CDAufDef::VersorgeTouren(CString &AArt, bool initial /*=false*/)
{
    if (initial)
    {
        m_bSonder = false;
    }

    InitTourCombos(AArt);
    SetTourCombo();

    if (_model.GetDatumDelayedDelivery() > 0)
    {
        ReadWeektours(AArt);

        InitFuturComboOnDelayedDeliveryDate();

        if (_model.GetDatumDelayedDelivery() > m_lActDatum)
        {
            if (GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArt.GetString()))
            {
                ShowAndEnableWindow(IDC_CHECK_DD, IDC_DATETIMEPICKER_DD, false);
            }
            else
            {
                CheckDlgButton(IDC_CHECK_DD, TRUE);
                ShowAndEnableWindow(IDC_CHECK_DD, true);
                m_DT_DelayedDelivery.ShowWindow(SW_SHOW);
                ShowAndSelectTourFutur();
            }
        }
        else if (!ShowSonderOnEmptyAkt())
        {
            m_cs_SonderTour.ShowWindow(SW_HIDE);
            m_bSonder = false;
        }
    }
    else
    {
        if (GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArt.GetString()))
        {
            ShowAndEnableWindow(IDC_CHECK_DD, IDC_DATETIMEPICKER_DD, false);
            if (m_CoboxTour.GetCount() == 0)
            {
                ShowSonder();
            }
            else
            {
                ShowAkt();
            }
        }
        else
        {
            CheckDlgButton(IDC_CHECK_DD, FALSE);
            ShowAndEnableWindow(IDC_CHECK_DD, true);
            m_DT_DelayedDelivery.ShowWindow(SW_HIDE);
            ReadWeektours(AArt);
            if (m_CoboxTour.GetCount() == 0)
            {
                if (m_aWochentouren.IsEmpty())
                {
                    ShowSonder();
                }
                else
                {
                    CheckDlgButton(IDC_CHECK_DD, TRUE);
                    UpdateTourComboOnDelayedDelivery();
                }
            }
            else
            {
                ShowAkt();
            }
        }
    }
    ShowAndEnableWindow(IDC_BUTTON_SONDER, m_bMixExist && (_model.GetDatumDelayedDelivery() <= m_lActDatum));
}

void CDAufDef::OnCheckCashOrder()
{
    if (IsDlgButtonChecked(IDC_CHECK_CASH_ORDER))
    {
        m_bValutaWhenCheckCashOrder = IsDlgButtonChecked(IDC_CHECK_VALUTA) ? true : false;
        if (m_bValutaWhenCheckCashOrder)
        {
            CheckDlgButton(IDC_CHECK_VALUTA, BST_UNCHECKED);
            UpdateValuta(false);
        }
    }
    else
    {
        if (IsValutaPossible() && m_bValutaWhenCheckCashOrder)
        {
            m_bValutaWhenCheckCashOrder = false;
            CheckDlgButton(IDC_CHECK_VALUTA, BST_CHECKED);
            UpdateValuta(true);
        }
    }
}

void CDAufDef::OnChangeEditIVC()
{
    AllgWertKontr(&m_EditIVC, INT_MAX);
}

void CDAufDef::OnChangeEditOrgInvoice()
{
    AllgWertKontr(&m_EditOrgInvoice, INT_MAX);
}

void CDAufDef::ShowAndEnableWindow(int nID1, int nID2, bool show)
{
    ShowAndEnableWindow(nID1, show);
    ShowAndEnableWindow(nID2, show);
}

void CDAufDef::ShowAndEnableWindow(int nID, bool show)
{
    if (show)
    {
        GetDlgItem(nID)->ShowWindow(SW_SHOW);
        GetDlgItem(nID)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(nID)->ShowWindow(SW_HIDE);
        GetDlgItem(nID)->EnableWindow(FALSE);
    }
}

bool CDAufDef::ValutaInDays()
{
    return AeGetApp()->IsRS() || AeGetApp()->IsBG() || AeGetApp()->IsDE() ? true : false;
}

CTime CDAufDef::ConvertDate(long date, int addHours /*=0*/)
{
    long day;
    long month;
    long year;
    GetDate(date, year, month, day);
    CTime cDate(year, month, day, addHours, 0, 0);
    return cDate;
}

void CDAufDef::GetDate(const long date, long& year, long& month, long& day)
{
    day = date % 100L;
    month = (date / 100L) % 100L;
    year = date / 10000L;
}

long CDAufDef::ConvertDate(CTime cDate)
{
    return GetDate(cDate.GetYear(), cDate.GetMonth(), cDate.GetDay());
}

long CDAufDef::GetDate(const long year, const long month, const long day)
{
    return (year * 10000L) + (month * 100L) + day;
}
