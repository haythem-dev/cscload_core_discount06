// daufend.cpp : implementation file
//

#include "stdafx.h"
#include "DAufEnd.h"
#include <kndsel.h>
#include "DSonderFahrt.h"
#include "AeFView.h"
#include <eilbotendruck.h>
#include "invoicesettings.h"
#include <auftraginfo.h>
#include "DShowProforma.h"
#include <verbundcheck.h>
 /* Mist */
#include "DExtraFahrt.h"
#include <touren.h>
#include <orders.h>
#include "DAufTxt.h"

/////////////////////////////////////////////////////////////////////////////
// CDAufEnd dialog


CDAufEnd::CDAufEnd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufEnd::IDD, pParent)
    , m_CT_DD(0)
    , m_bDDOhne(FALSE)
    , m_bNoRabattKonto(FALSE)
{
    m_CBemerkung = _T("");
    m_bKeinAuftrag  = false;
    m_bStdDafueZur  = false;
    m_bManuell      = false;
    m_bMixExist     = false;
    m_bMixShown     = false;
    m_bAnzSonder    = false;
    m_iCombo        = 0;
    m_snrcol_fv     = 0;
    m_srabaep_fv    = 0;
    m_srabavp_fv    = 0;
    m_smail_fv      = 0;
    m_snrcol_kk     = 0;
    m_srabaep_kk    = 0;
    m_srabavp_kk    = 0;
    m_smail_kk      = 0;
    m_bMitRab       = false;
    m_bNoDD         = 1;
}


void CDAufEnd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_PRINT, m_CBPrint);
    DDX_Control(pDX, IDC_COMBO_TOUR, m_CoboxTour);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_EditBemerkung);
    DDX_Control(pDX, IDC_STATIC_MINUTE, m_StaticMin);
    DDX_Control(pDX, IDC_EDIT_MIN, m_EditMin);
    DDX_Control(pDX, IDC_GENERIC2, m_CSpinMin);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_CBemerkung);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DD, m_DT_DD);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DD, m_CT_DD);
    DDX_Control(pDX, IDC_CHECK_DD_OHNE, m_CB_DD_Ohne);
    DDX_Check(pDX, IDC_CHECK_DD_OHNE, m_bDDOhne);
    DDX_Control(pDX, IDC_COMBO_FUTUR, m_CoboxFutur);
    DDX_Control(pDX, IDC_COMBO_NAKT, m_CoboxNakt);
    DDX_Control(pDX, IDC_STATIC_SONDER, m_cs_Sonder);
    DDX_Control(pDX, IDC_COMBO_MIX, m_CoboxMix);
    DDX_Control(pDX, IDC_CHECK_NR_COL, m_CB_nrcol_fv);
    DDX_Control(pDX, IDC_CHECK_RAB_AEP, m_CB_rabaep_fv);
    DDX_Control(pDX, IDC_CHECK_RAB_AVP, m_CB_rabavp_fv);
    DDX_Control(pDX, IDC_CHECK_INV_MAIL, m_CB_mail_fv);
    DDX_Control(pDX, IDC_CHECK_NR_COL_KK, m_CB_nrcol_kk);
    DDX_Control(pDX, IDC_CHECK_RAB_AEP_KK, m_CB_rabaep_kk);
    DDX_Control(pDX, IDC_CHECK_RAB_AVP_KK, m_CB_rabavp_kk);
    DDX_Control(pDX, IDC_CHECK_INV_MAIL_KK, m_CB_mail_kk);
    DDX_Check(pDX, IDC_CHECK_NO_REBATE_ACCOUNT2, m_bNoRabattKonto);
    DDX_Control(pDX, IDC_COMBO_PRICE_FV, m_combo_price_fv);
    DDX_Control(pDX, IDC_COMBO_PRICE_KK, m_combo_price_kk);
}


BEGIN_MESSAGE_MAP(CDAufEnd, CDialogMultiLang)
    ON_BN_CLICKED(IDC_CHECK_NEW_CALL, OnCheckNewCall)
    ON_EN_CHANGE(IDC_EDIT_BEMERKUNG, OnChangeEditBemerkung)
    ON_BN_CLICKED(IDC_RADIO20, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO10, OnRadioSchl)
    ON_CBN_SELCHANGE(IDC_COMBO_TOUR, OnSelchangeComboTour)
    ON_BN_CLICKED(IDC_RADIO21, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO22, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO23, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO24, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO25, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO11, OnRadioSchl)
    ON_BN_CLICKED(IDC_RADIO12, OnRadioSchl)
    ON_BN_CLICKED(IDC_RADIO13, OnRadioSchl)
    ON_BN_CLICKED(IDC_RADIO14, OnRadioSchl)
    ON_BN_CLICKED(IDC_RADIO15, OnRadioSchl)
    ON_BN_CLICKED(IDC_RADIO16, OnRadioSchl)
    ON_BN_CLICKED(IDC_RADIO26, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO27, OnRadioTour)
    ON_BN_CLICKED(IDC_RADIO28, OnRadioTour)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_CBN_SELCHANGE(IDC_COMBO_NAKT, OnCbnSelchangeComboNakt)
    ON_WM_CTLCOLOR()
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DD, OnDtnDatetimechangeDatetimepickerDd)
    ON_CBN_SELCHANGE(IDC_COMBO_MIX, OnCbnSelchangeComboMix)
    ON_BN_CLICKED(IDC_BUTTON_SONDER, OnBnClickedButtonSonder)
    ON_BN_CLICKED(IDC_BUTTON_WERTRECH, OnBnClickedButtonRechwert)
    ON_BN_CLICKED(IDC_CHECK_NR_COL, OnCheckColFV)
    ON_BN_CLICKED(IDC_CHECK_RAB_AEP, OnCheckAEPFV)
    ON_BN_CLICKED(IDC_CHECK_RAB_AVP, OnCheckAVPFV)
    ON_BN_CLICKED(IDC_CHECK_NR_COL_KK, OnCheckColKK)
    ON_BN_CLICKED(IDC_CHECK_RAB_AEP_KK, OnCheckAEPKK)
    ON_BN_CLICKED(IDC_CHECK_RAB_AVP_KK, OnCheckAVPKK)
    ON_CBN_SELCHANGE(IDC_COMBO_PRICE_FV, &CDAufEnd::OnCbnSelchangeComboPriceFv)
    ON_CBN_SELCHANGE(IDC_COMBO_PRICE_KK, &CDAufEnd::OnCbnSelchangeComboPriceKk)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufEnd message handlers

BOOL CDAufEnd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CString Text;
    Text.Format("OrderNo %d", m_lAufnr);
    AeGetApp()->m_AeLogging.WriteLine(1, "CDAufEnd.cpp", "Started", Text);
    if (m_bMitRab)
    {
        GetDlgItem(IDC_CHECK_NO_REBATE_ACCOUNT2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_NO_REBATE_ACCOUNT2)->EnableWindow(GetAeUser().IsChangeRebateCalc() ? TRUE : FALSE);
    }
    else
    {
        GetDlgItem(IDC_CHECK_NO_REBATE_ACCOUNT2)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NO_REBATE_ACCOUNT2)->ShowWindow(SW_HIDE);
    }
    m_bSaveNoRabattKonto = m_bNoRabattKonto;
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_SUNDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_MONDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_TUESDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_WEDNESDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_THURSDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_FRIDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_SATURDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(AETXT_HEUTE).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(AETXT_SONDERTOUR).GetString());

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_sWeekday = (short)zeit.s.WTAG;
    m_lActDatum = zeit.s.DATUM;
    GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
    m_bSonder = false;

    //if (m_lDatumDD > m_lActDatum)
    if (m_lDatumDD > 0)
    {
        CTime anf = CTimeFromDateLongMinTime(zeit.s.DATUM);
        CTime end(2030, 12, 31, 0, 0, 0);
        m_DT_DD.SetRange(&anf, &end);
        CTime zeitDD = CTimeFromDateLongMinTime(m_lDatumDD);
        m_DT_DD.SetTime(&zeitDD);
        //Touren eintragen
        InsTouren();
        SetTour();
        GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
        m_bSonder = false;
        CheckDlgButton(IDC_CHECK_DD_OHNE, FALSE);
        if (m_lDatumDD > m_lActDatum)
        {
            ShowFutur();
            HoleWochenTouren();
            LadeWochenTouren(static_cast<short>(zeitDD.GetDayOfWeek() - 1));
            SetTourFutur();
        }
        else if (m_CoboxTour.GetCount() == 0)
        {
            GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_SHOW);
            ShowSonder();
            m_bSonder = true;
            m_CoboxNakt.SetCurSel(0);
        }
        else
        {
            m_bSonder = false;
        }
    }
    else
    {
        GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DD)->ShowWindow(SW_HIDE);
        CheckDlgButton(IDC_CHECK_DD_OHNE, FALSE);
        GetDlgItem(IDC_CHECK_DD_OHNE)->ShowWindow(SW_HIDE);
        //Touren eintragen
        InsTouren();
        SetTour();
    }
    GetDlgItem(IDC_CHECK_NO_DD)->ShowWindow(SW_HIDE);
    CheckDlgButton(IDC_CHECK_NO_DD, FALSE);

    CenterWindow();

    //Kommiart setzen
    SetKommArt(m_KommArt.GetAt(0));
    OnRadioTour();

    //Abschlußart definieren
    CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO10);
    if (m_cZuGrund.GetAt(ZU_WAHL_STELLER) == '1')
    {
        //Auftragsabschluß sperren - enthaelt noch offene Wahlsteller
        GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO16)->EnableWindow(FALSE);
        CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO12);
    }

    if ((m_cZuGrund.GetAt(ZU_KREDITLIMIT) == '1') && GetAeUser().IsKreditAbschluss())
    {
        if (AeGetApp()->IsKLClose())
        {
            GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_KL));
            GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
        }
        GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_KL));
        GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
    }
    else if ((m_cZuGrund.GetAt(ZU_INTERNET) == '1') && GetAeUser().IsInternetAbschluss())
    {
        GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_IN));
        GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_IN));
        GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
    }
    else if ((m_cZuGrund.GetAt(ZU_BTM) == '1') && GetAeUser().IsAbschlussBTM())
    {
        GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_BTM));
        GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_BTM));
        GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
    }
    else if (m_cZuGrund.GetAt(ZU_NO_QTY_NR) == '1')
    {
        if (m_cZuGrund.GetAt(ZU_WAHL_STELLER) != '1')
        {
            //normale Auftragsabschluß sperren - enthaelt nicht befriedigbare Rabatte
            GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO16)->EnableWindow(FALSE);
            CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO12);
            GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_NO_RAB));
            GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_NO_RAB));
            GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
        }
    }
    else
    {
        GetDlgItem(IDC_RADIO17)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_RADIO18)->ShowWindow(SW_HIDE);
    }
    if (AeGetApp()->KndEilSperre() == '1')
    {
        GetDlgItem(IDC_RADIO21)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO24)->EnableWindow(FALSE);
    }
    long lDefekte = ((CAeFView*)AeGetApp()->m_pViewEing)->GetDefekte();
    CString csAnzPos;
    ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csAnzPos);
    if ((AeGetApp()->MaxPosEil() != 0) && ((atol(csAnzPos) - lDefekte) > AeGetApp()->MaxPosEil()))
    {
        GetDlgItem(IDC_RADIO21)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO24)->EnableWindow(FALSE);
    }

    //Neuer Anruf in n min
    m_CSpinMin.SetBuddy(GetDlgItem(IDC_EDIT_MIN));
    m_CSpinMin.SetRange(1, 2240);
    m_CSpinMin.SetPos(1);
    m_StaticMin.EnableWindow(FALSE);
    m_EditMin.EnableWindow(FALSE);
    m_CSpinMin.EnableWindow(FALSE);
    m_CBPrint.EnableWindow(FALSE);
    if (m_KommArt.GetAt(0) == '2' )
    {
        m_CBPrint.EnableWindow(TRUE);
        if (AeGetApp()->IsSofort())
            m_CBPrint.SetCheck(1);
    }
    if (m_bStdDafueZur)
    {
        CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO12);
    }
    if (!m_bKeinAuftrag) //Kein Auftrag sperren
    {
        GetDlgItem(IDC_RADIO13)->EnableWindow(FALSE);
    }
    else  //Auftragsabschluß sperren
    {
        GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO16)->EnableWindow(FALSE);
        CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO12);
    }
    if (m_cZuGrund.GetAt(ZU_NULL_DOKU) == '1')  //Auftragsabschluß sperren
    {
        GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO16)->EnableWindow(FALSE);
        CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO15);
    }
    OnRadioSchl();
    m_bManuell = false;
    CheckTourDD();

    CFont* pobjCFont = m_cs_Sonder.GetFont();
    LOGFONT lf;
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    CFont objCFont;
    objCFont.CreateFontIndirect(&lf);
    m_cs_Sonder.SetFont(&objCFont);

    bool bShowAndEnableWertRech = (AeGetApp()->IsRS() || AeGetApp()->IsBG());
    GetDlgItem(IDC_BUTTON_WERTRECH)->EnableWindow(bShowAndEnableWertRech ? TRUE : FALSE);
    GetDlgItem(IDC_BUTTON_WERTRECH)->ShowWindow(bShowAndEnableWertRech ? SW_SHOW : SW_HIDE);

    if (AeGetApp()->IsBG())
    {
        m_combo_price_fv.AddString(CResString::ex().getStrTblText(AETXT_PRICE_PRO_NO));
        m_combo_price_fv.AddString(CResString::ex().getStrTblText(AETXT_PRICE_PRO_PRINT));
        m_combo_price_fv.AddString(CResString::ex().getStrTblText(AETXT_PRICE_PRO_NOPRINT));
        m_combo_price_kk.AddString(CResString::ex().getStrTblText(AETXT_PRICE_PRO_NO));
        m_combo_price_kk.AddString(CResString::ex().getStrTblText(AETXT_PRICE_PRO_PRINT));
        m_combo_price_kk.AddString(CResString::ex().getStrTblText(AETXT_PRICE_PRO_NOPRINT));
        if (GetDlgItem(IDC_RADIO10)->IsWindowEnabled())
        {
            CString text;
            ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_EDIT_FV_NETTO)->GetWindowText(text);
            if (atof(text) > 0)
            {
                GetDlgItem(IDC_STATIC_OPTION_BOX)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_OPTION_BOX)->ShowWindow(SW_SHOW);
                bool bRebatemethfreesale = (AeGetApp()->Rebatemethfreesale() == 1);
                GetDlgItem(IDC_CHECK_NR_COL)->EnableWindow(bRebatemethfreesale ? TRUE : FALSE);
                GetDlgItem(IDC_CHECK_NR_COL)->ShowWindow(bRebatemethfreesale ? SW_SHOW : SW_HIDE);
                GetDlgItem(IDC_CHECK_RAB_AEP)->EnableWindow(bRebatemethfreesale ? FALSE : TRUE);
                GetDlgItem(IDC_CHECK_RAB_AEP)->ShowWindow(bRebatemethfreesale ? SW_HIDE : SW_SHOW);
                GetDlgItem(IDC_CHECK_RAB_AVP)->EnableWindow(bRebatemethfreesale ? FALSE : TRUE);
                GetDlgItem(IDC_CHECK_RAB_AVP)->ShowWindow(bRebatemethfreesale ? SW_HIDE : SW_SHOW);
                GetDlgItem( IDC_COMBO_PRICE_FV )->EnableWindow(TRUE);
                GetDlgItem( IDC_COMBO_PRICE_FV )->ShowWindow(SW_SHOW);
                GetDlgItem( IDC_CHECK_INV_MAIL )->EnableWindow(TRUE);
                GetDlgItem( IDC_CHECK_INV_MAIL )->ShowWindow(SW_SHOW);

                CINVOICESETTINGS Settings;
                Settings.SetPreis_typ(0);
                char error_msg[81];
                ::ServerNr(PIPE_AE_SRV, AasrvGetInvoiceSettings, (void*)&Settings.s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
                m_CB_nrcol_fv.SetCheck(Settings.GetWithcolumnnr());
                m_CB_rabaep_fv.SetCheck(Settings.GetDeduction_aep());
                m_CB_rabavp_fv.SetCheck(Settings.GetDeduction_avp());
                m_combo_price_fv.SetCurSel(Settings.GetPrint());
                m_CB_mail_fv.SetCheck(Settings.GetByemail());
                m_snrcol_fv = static_cast<short>(m_CB_nrcol_fv.GetCheck());
                m_srabaep_fv = static_cast<short>(m_CB_rabaep_fv.GetCheck());
                m_srabavp_fv = static_cast<short>(m_CB_rabavp_fv.GetCheck());
                m_sprice_fv = static_cast<short>(m_combo_price_fv.GetCurSel());
                m_smail_fv = static_cast<short>(m_CB_mail_fv.GetCheck());
            }

            ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_EDIT_KK_NETTO)->GetWindowText(text);
            if (atof(text) > 0)
            {
                GetDlgItem(IDC_STATIC_OPTION_BOX_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_OPTION_BOX_KK)->ShowWindow(SW_SHOW);
                bool bRebatemethfreesale = (AeGetApp()->Rebatemethhealthf() == 1);
                GetDlgItem(IDC_CHECK_NR_COL_KK)->EnableWindow(bRebatemethfreesale ? TRUE : FALSE);
                GetDlgItem(IDC_CHECK_NR_COL_KK)->ShowWindow(bRebatemethfreesale ? SW_SHOW : SW_HIDE);
                GetDlgItem(IDC_CHECK_RAB_AEP_KK)->EnableWindow(bRebatemethfreesale ? FALSE : TRUE);
                GetDlgItem(IDC_CHECK_RAB_AEP_KK)->ShowWindow(bRebatemethfreesale ? SW_HIDE : SW_SHOW);
                GetDlgItem(IDC_CHECK_RAB_AVP_KK)->EnableWindow(bRebatemethfreesale ? FALSE : TRUE);
                GetDlgItem(IDC_CHECK_RAB_AVP_KK)->ShowWindow(bRebatemethfreesale ? SW_HIDE : SW_SHOW);
                GetDlgItem(IDC_COMBO_PRICE_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_COMBO_PRICE_KK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CHECK_INV_MAIL_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_CHECK_INV_MAIL_KK)->ShowWindow(SW_SHOW);

                CINVOICESETTINGS Settings;
                Settings.SetPreis_typ(1);
                char error_msg[81];
                ::ServerNr(PIPE_AE_SRV, AasrvGetInvoiceSettings, (void*)&Settings.s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
                m_CB_nrcol_kk.SetCheck(Settings.GetWithcolumnnr());
                m_CB_rabaep_kk.SetCheck(Settings.GetDeduction_aep());
                m_CB_rabavp_kk.SetCheck(Settings.GetDeduction_avp());
                //int test = Settings.GetPrint();
                m_combo_price_kk.SetCurSel(Settings.GetPrint());
                m_CB_mail_kk.SetCheck(Settings.GetByemail());
                m_snrcol_kk = static_cast<short>(m_CB_nrcol_kk.GetCheck());
                m_srabaep_kk = static_cast<short>(m_CB_rabaep_kk.GetCheck());
                m_srabavp_kk = static_cast<short>(m_CB_rabavp_kk.GetCheck());
                m_sprice_kk = static_cast<short>(m_combo_price_kk.GetCurSel());
                m_smail_kk = static_cast<short>(m_CB_mail_kk.GetCheck());
            }
        }
    }
    if (AeGetApp()->IsBG())
    {
        // In BG kein check auf offene Auftraege bei folgenden Auftragsarten
        if ( (m_AArt == "MP") ||
             (m_AArt == "TO") ||
             (m_AArt == "S1") ||
             (m_AArt == "S2") ||
             (m_AArt == "S3") ||
             (m_AArt == "S4") ||
             (m_AArt == "S5") )
        {
            GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
        }
        // In BG bei RO kein zurueckstellen
        if (m_AArt == "RO")
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO18, m_bKeinAuftrag ? IDC_RADIO13 : IDC_RADIO10);
            GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO12)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
        }
    }
    if (AeGetApp()->IsIBTdirect() && !ptrDoc->m_bAllItemsInList)
    {
        BeginWaitCursor();
        ptrDoc->DelPosListe();  //Loeschen der Positionsliste
        for (;;)
        {
            CAUFPOSBUCH aufposbuch;
            aufposbuch.Server(AasrvSelpos, PIPE_AE_SRV);
            if (aufposbuch.rc != SRV_OK)
                break;
            ptrDoc->AddPosition(aufposbuch.s);
        }
        ptrDoc->m_bAllItemsInList = true;
        EndWaitCursor();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAufEnd::InsTouren()
{
    //Tour
    CString STour;  //Tour für Ausgabe formatiert
    CString Tour;   //Tournummer
    CKNDTOUREN kndtouren;
    m_CoboxTour.ResetContent();
    m_CoboxNakt.ResetContent();
    m_CoboxMix.ResetContent();
    for (;;)
    {
        kndtouren.Server(AasrvGettouren, PIPE_AE_SRV);
        if (kndtouren.rc != SRV_OK)
            break;
        Tour = kndtouren.s.TOURID;
        if (kndtouren.s.KZAUTOZUORD[0] == '1')
        {
            TourToString(Tour, STour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], 7);
        }
        else
        {
            TourToString(Tour, STour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], 8);
        }
        m_CoboxMix.AddString(STour);
        if (kndtouren.s.KZAUTOZUORD[0] == '1')
        {
            m_CoboxTour.AddString(STour);
        }
        else
        {
            m_bMixExist = true;
            m_CoboxNakt.AddString(STour);
        }
    }
    if (m_CoboxTour.GetCount() == 0)
    {
        m_CoboxMix.ResetContent();
        m_bMixExist = false;
        HoleWochenTouren();
        LadeWochenTouren(9);
        if (m_CoboxNakt.GetCount() > 0)
        {
            ShowSonder();
            m_bSonder = true;
        }
        else
        {
            ShowFutur();
            m_bSonder = false;
        }
    }
}

void CDAufEnd::SetTour()
{
    CString STour;
    TourToString(m_Tour, STour, 0, ' ', 7);
    int iPos = m_CoboxTour.SelectString(-1, STour.Left(18));
    if (iPos == CB_ERR)
    {
        if (m_CoboxMix.SelectString(-1, STour.Left(18)) == CB_ERR)
        {
            ShowAkt();
            m_CoboxTour.SetCurSel(0);
        }
        else
        {
            OnBnClickedButtonSonder();
            m_CoboxMix.SelectString(-1, STour.Left(18));
        }
    }
    else
    {
        ShowAkt();
        m_CoboxTour.SetCurSel(iPos);
    }
    CheckTourDD();
}

void CDAufEnd::SetTourFutur()
{
    CString STour;
    TourToString(m_Tour,STour, 0, ' ',7);
    if (m_CoboxFutur.SelectString(-1, STour.Left(18)) == CB_ERR)
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

void CDAufEnd::TourToString(CString& Tour, CString& STour, long Fahrzeit, char cKA, short sWeekday)
{
        char str[81];
        strncpy(str, Tour, 2);
        str[2] = '\0';
        int h = atol(str);
        STour  = str;
        STour += ":";
        strncpy(str, Tour.Right(4), 2);
        str[2] = '\0';
        int min = atol(str);
        int ah = h + Fahrzeit / 60;
        int amin = min + Fahrzeit % 60;
        if (amin > 59)
        {
            ah += 1;
            amin -= 60;
        }
        if (ah > 23)
        {
            ah -= 24;
        }
        STour.Format("%02d:%02d %11.11s%2s%7s%02d:%02d %5s %2s: %c  %s                       %d",
            h,
            min,
            CResString::ex().getStrTblText(AETXT_UHR_BHF).GetString(),
            Tour.Right(2).GetString(),
            CResString::ex().getStrTblText(AETXT_SP_ANKUNFT).GetString(),
            ah,
            amin,
            CResString::ex().getStrTblText(AETXT_UHR).GetString(),
            CResString::ex().getStrTblText(AETXT_KZ_KOMMIART).GetString(),
            cKA,
            m_Tagtab[sWeekday].GetString(),
            sWeekday);
}

void CDAufEnd::StringToTour(char* tour, CString& STour)
{
    strncpy(tour, STour, 2);
    strncpy(tour + 2, (const char*)STour + 3, 2);
    strncpy(tour + 4, (const char*)STour + 17, 2);
    tour[6] = '\0';
}

void CDAufEnd::SetKommArt(char cKommArt)
{
    //Kommisionierart
    if      (cKommArt == '0')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO20);
    else if (cKommArt == '3')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO21);
    else if (cKommArt == '4')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO22);
    else if (cKommArt == '5')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO23);
    else if (cKommArt == '6')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO24);
    else if (cKommArt == '1')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO25);
    else if (cKommArt == '2')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO26);
    else if (cKommArt == '8')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO27);
    else if (cKommArt == '7')  CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO28);
    else                       CheckRadioButton(IDC_RADIO20, IDC_RADIO28, IDC_RADIO20);
}

void CDAufEnd::OnCheckNewCall()
{
    if (IsDlgButtonChecked(IDC_CHECK_NEW_CALL))
    {
        m_StaticMin.EnableWindow();
        m_EditMin.EnableWindow();
        m_CSpinMin.EnableWindow();
    }
    else
    {
        m_StaticMin.EnableWindow(FALSE);
        m_EditMin.EnableWindow(FALSE);
        m_CSpinMin.EnableWindow(FALSE);
    }
}

void CDAufEnd::OnOK()
{
    CString woher = "CDAufEnd::OnOK";

    UpdateData();

    CString Text;
    Text.Format("OrderNo %d", m_lAufnr);
    AeGetApp()->m_AeLogging.WriteLine(1, "CDAufEnd.cpp", "OnOK", Text);

    int id = GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18);
    if (id == IDC_RADIO10)
    {
        if (GetOrderType().IsAufArtMustHeadline(AeGetApp()->VzNr(), m_AArt.GetString()))
        {
            if (AeGetApp()->AnzKopfFuss() == 0)
            {
                MsgBoxOK(AETXT_MUSS_KOPF);
                CDAufTxt textdlg;
                textdlg.DoModal();
                if (AeGetApp()->AnzKopfFuss() == 0)
                {
                    return;
                }
            }
        }

    }
    if (AeGetApp()->IsBG())
    {
        if (GetDlgItem(IDC_RADIO10)->IsWindowEnabled())
        {
            char error_msg[81];
            int rc = 0;
            CINVOICESETTINGS Settings;
            CString text;
            ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_EDIT_FV_NETTO)->GetWindowText(text);
            if (atof(text) > 0.0)
            {
                if (   m_snrcol_fv != static_cast<short>(m_CB_nrcol_fv.GetCheck())
                    || m_srabaep_fv != static_cast<short>(m_CB_rabaep_fv.GetCheck())
                    || m_srabavp_fv != static_cast<short>(m_CB_rabavp_fv.GetCheck())
                    || m_sprice_fv != static_cast<short>(m_combo_price_fv.GetCurSel())
                    || m_smail_fv != static_cast<short>(m_CB_mail_fv.GetCheck()) )
                {
                    Settings.SetPreis_typ(0);
                    Settings.SetWithcolumnnr(static_cast<short>(m_CB_nrcol_fv.GetCheck()));
                    Settings.SetDeduction_aep(static_cast<short>(m_CB_rabaep_fv.GetCheck()));
                    Settings.SetDeduction_avp(static_cast<short>(m_CB_rabavp_fv.GetCheck()));
                    Settings.SetPrint(static_cast<short>(m_combo_price_fv.GetCurSel()));
                    Settings.SetByemail(static_cast<short>(m_CB_mail_fv.GetCheck()));
                    rc = ::ServerNr(PIPE_AE_SRV, AasrvWriteInvoiceSettings, (void*)&Settings.s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
                }
            }
            ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_EDIT_KK_NETTO)->GetWindowText(text);
            if (atof(text) > 0.0)
            {
                if (   m_snrcol_kk != m_CB_nrcol_kk.GetCheck()
                    || m_srabaep_kk != m_CB_rabaep_kk.GetCheck()
                    || m_srabavp_kk != m_CB_rabavp_kk.GetCheck()
                    || m_sprice_kk != m_combo_price_kk.GetCurSel()
                    || m_smail_kk != m_CB_mail_kk.GetCheck() )
                {
                    Settings.SetPreis_typ(1);
                    Settings.SetWithcolumnnr(static_cast<short>(m_CB_nrcol_kk.GetCheck()));
                    Settings.SetDeduction_aep(static_cast<short>(m_CB_rabaep_kk.GetCheck()));
                    Settings.SetDeduction_avp(static_cast<short>(m_CB_rabavp_kk.GetCheck()));
                    Settings.SetPrint(static_cast<short>(m_combo_price_kk.GetCurSel()));
                    Settings.SetByemail(static_cast<short>(m_CB_mail_kk.GetCheck()));
                    rc = ::ServerNr(PIPE_AE_SRV, AasrvWriteInvoiceSettings, (void*)&Settings.s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
                }
            }
        }
    }
    int anz = AeGetApp()->GetAnzForbiddenWords();
    for (int i = 0; i < anz; i++)
    {
        if (m_CBemerkung.Find(AeGetApp()->GetForbiddenWords(i)) != -1)
        {
            CString CStr;
            CStr.Format(CResString::ex().getStrTblText(AETXT_FORBIDDEN), AeGetApp()->GetForbiddenWords(i).GetString());
            MsgBoxOK(CStr);
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_BEMERKUNG));
            return;
        }
    }

    id = GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18);
    if      (id == IDC_RADIO10) m_Status = ORD_ERFASST;
    else if (id == IDC_RADIO11) m_Status = ORD_ZURUECKGESTELLT;
    else if (id == IDC_RADIO12) m_Status = ORD_ZURUECKGEST_DAFUE;
    else if (id == IDC_RADIO13) m_Status = ORD_KEIN_AUFTRAG;
    else if (id == IDC_RADIO14) m_Status = ORD_WEITERER_AUFTRAG;
    else if (id == IDC_RADIO15) m_Status = ORD_STORNIERT;
    else if (id == IDC_RADIO17) m_Status = ORD_UNBEDINGT;
    else if (id == IDC_RADIO18) m_Status = ORD_STORNO_UNBEDINGT;
    else                        m_Status = ORD_ERFASST;

    if (m_lDatumDD > m_lActDatum && (m_Status == ORD_ERFASST || m_Status == ORD_WEITERER_AUFTRAG))
    {
        if (IsDlgButtonChecked(IDC_CHECK_DD_OHNE))
        {
            m_Status = ORD_ZU_DD_OHNE;
        }
        else
        {
            m_Status = ORD_ZU_CLEAR_DD_OHNE;
        }
    }

    if (m_cZuGrund.GetAt(ZU_INVENTUR_HERST) == '1')
    {
        AeGetApp()->ClearZUGrund(ZU_INVENTUR_HERST);
        m_cZuGrund.SetAt(ZU_INVENTUR_HERST, '0');
    }
    if (m_cZuGrund.GetAt(ZU_INVENTUR_KONSIG) == '1')
    {
        AeGetApp()->ClearZUGrund(ZU_INVENTUR_KONSIG);
        m_cZuGrund.SetAt(ZU_INVENTUR_KONSIG, '0');
    }

    if (m_Status == ORD_STORNIERT)
    {
        if (m_cZuGrund.GetAt(ZU_NULL_DOKU) != '1')  //bei Nulldoku sofort stornieren
        {
            if (MsgBoxYesNo(IDP_SOLL_STORNO) != IDYES)
                return;
            //Test auf abgearbeitete Verbundpositionen
            if (AeGetApp()->IsIBTdirect() || AeGetApp()->IsNlSofort() || AeGetApp()->IsDispoSofort())
            {

                if (AeGetApp()->IsIBTdirect())
                {
                    CAUFTRAG checkvb;
                    checkvb.s.KDAUFTRAGNR = m_lAufnr;
                    checkvb.s.VERTRIEBSZENTRUMNR = m_VzNr;
                    checkvb.Server(AasrvIBTOrderPosDone, PIPE_AE_SRV);
                    if (checkvb.rc == SRV_SQLNOTFOUND)
                    {
                        if (MsgBoxYesNo(IDP_SOLL_STORNO_OHNE_IBT) != IDYES)
                            return;
                    }
                }
                if (AeGetApp()->IsNlSofort() || AeGetApp()->IsDispoSofort())
                {
                    CAUFTRAG checkspecial;
                    checkspecial.s.KDAUFTRAGNR = m_lAufnr;
                    checkspecial.s.VERTRIEBSZENTRUMNR = m_VzNr;
                    checkspecial.Server(AasrvOrderSpecialPosDone, PIPE_AE_SRV);
                    if (checkspecial.rc == SRV_SQLNOTFOUND)
                    {
                        if (MsgBoxYesNo(IDP_SOLL_STORNO_OHNE_NL_DISPO) != IDYES)
                            return;
                    }
                }
            }
        }
    }

    //Auftragsart bestimmen
    CAUFTRAG auftrag;
    auftrag.s.KDAUFTRAGART[0] = m_AArt.GetAt(0);
    auftrag.s.KDAUFTRAGART[1] = m_AArt.GetAt(1);
    auftrag.s.KDAUFTRAGART[2] = '\0';

    //Kommisionierart bestimmen
    id = GetCheckedRadioButton(IDC_RADIO20, IDC_RADIO28);
    if      (id == IDC_RADIO20) strcpy(auftrag.s.KOART, "0");
    else if (id == IDC_RADIO21) strcpy(auftrag.s.KOART, "3");
    else if (id == IDC_RADIO22) strcpy(auftrag.s.KOART, "4");
    else if (id == IDC_RADIO23) strcpy(auftrag.s.KOART, "5");
    else if (id == IDC_RADIO24) strcpy(auftrag.s.KOART, "6");
    else if (id == IDC_RADIO25) strcpy(auftrag.s.KOART, "1");
    else if (id == IDC_RADIO26) strcpy(auftrag.s.KOART, "2");
    else if (id == IDC_RADIO27) strcpy(auftrag.s.KOART, "8");
    else if (id == IDC_RADIO28) strcpy(auftrag.s.KOART, "7");
    else strcpy(auftrag.s.KOART, "0");

    if (m_Status == ORD_ERFASST || m_Status == ORD_WEITERER_AUFTRAG)
    {
        CString csAnzPos;
        ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_ZLN)->GetWindowText(csAnzPos);
        if (AeGetApp()->PosZu() != 0)
        {
            if (atol(csAnzPos) > AeGetApp()->PosZu())
            {
                CString CStr;
                CStr.Format(CResString::ex().getStrTblText(AETXT_ZUVIELE_POS), atol(csAnzPos));
                if (MsgBoxYesNo(CStr) != IDYES)
                    return;
            }
        }
        if ((auftrag.s.KOART[0] == '1' || auftrag.s.KOART[0] == '2') && strcmp(auftrag.s.KDAUFTRAGART, "DI") && strcmp(auftrag.s.KDAUFTRAGART, "MD"))
        {
            if (MsgBoxYesNo(IDP_SOLL_KEINE_KOMMI) != IDYES)
                return;
        }
    }

    //Buchungsart bestimmen
    auftrag.s.BUCHART[0] = m_BuchArt.GetAt(0);
    auftrag.s.BUCHART[1] = '\0';

    //Sub-Order-Type setzen
    AllgStrCopy(auftrag.s.SUB_ORDER_TYPE, m_SubType, L_AUFTRAG_SUB_ORDER_TYPE);

    //Bemerkung setzen
    AllgStrCopy(auftrag.s.BEMERKUNGEN, m_CBemerkung, L_AUFTRAG_BEMERKUNGEN);
    AllgEntfSpaces(auftrag.s.BEMERKUNGEN);

    BeginWaitCursor();

    auftrag.Server(AasrvChangeorder, PIPE_AE_SRV); //Auftrags- und Buchungsart setzen
    if (auftrag.rc >= SRV_OK)
    {
        m_KommArt   = auftrag.s.KOART;
        m_BuchArt   = auftrag.s.BUCHART;
        m_AArt      = auftrag.s.KDAUFTRAGART;
        AllgEntfSpaces(auftrag.s.BEMERKUNGEN);
        m_Tour      = auftrag.s.TOURID;
    }
    else
    {
        return;
    }

    if (m_bSaveNoRabattKonto != m_bNoRabattKonto)
    {
        if (m_bNoRabattKonto)
        {
            auftrag.s.NORABATTKONTO[0] = '1';
        }
        else
        {
            auftrag.s.NORABATTKONTO[0] = '0';
        }
        auftrag.Server(AasrvSetCashRebate, PIPE_AE_SRV); //Kunde will Rechnungsrabatt
        if (auftrag.rc >= SRV_OK)
        {
        }
        else
        {
            return;
        }
    }

    if ( m_Status == ORD_ERFASST ||
         m_Status == ORD_WEITERER_AUFTRAG ||
         (m_Status == ORD_ZU_CLEAR_DD_OHNE && m_lActDatum == m_lDatumDD) )
    {
        if (   (!strcmp(auftrag.s.KDAUFTRAGART,"S3") || !strcmp(auftrag.s.KDAUFTRAGART,"S2"))
            && !AeGetApp()->IsBG() )
        {
/* Mist */
            if (AeGetApp()->IsDE())
            {
                CDExtraFahrt extra;
                extra.m_AArt = auftrag.s.KDAUFTRAGART;
                extra.m_CSonst = m_CBemerkung;
                if (extra.DoModal() == IDCANCEL)
                    return;
                m_CBemerkung = CResString::ex().getStrTblText(IDS_SONDERFAHRT);
                m_CBemerkung += extra.m_CSonst;
                m_EditBemerkung.SetWindowText(m_CBemerkung);
                AllgStrCopy(auftrag.s.BEMERKUNGEN, m_CBemerkung, L_AUFTRAG_BEMERKUNGEN);
                AllgEntfSpaces(auftrag.s.BEMERKUNGEN);
            }
            else
/* Mist */
            {
                CDSonderFahrt sonder;
                sonder.m_CSonst = m_CBemerkung;
                if (sonder.DoModal() == IDCANCEL)
                    return;
                m_CBemerkung = CResString::ex().getStrTblText(IDS_SONDERFAHRT);
                m_CBemerkung += sonder.m_CSonst;
                m_EditBemerkung.SetWindowText(m_CBemerkung);
                AllgStrCopy(auftrag.s.BEMERKUNGEN, m_CBemerkung, L_AUFTRAG_BEMERKUNGEN);
                AllgEntfSpaces(auftrag.s.BEMERKUNGEN);
            }
        }
    }
    auftrag.Server(AasrvChangeOrdBem, PIPE_AE_SRV);
    if (auftrag.rc >= SRV_OK)
    {
        AllgEntfSpaces(auftrag.s.BEMERKUNGEN);
        m_CBemerkung = auftrag.s.BEMERKUNGEN;
    }
    if (m_lDatumDD > m_lActDatum)
    {
        long newDD = (m_CT_DD.GetYear()*10000+
                m_CT_DD.GetMonth()*100+
                m_CT_DD.GetDay());
        if (m_Status == ORD_UNBEDINGT)
        {
            if (newDD == AeGetApp()->GetCurrentDate())
            {
                auftrag.s.DATUMAUSLIEFERUNG = 0;
                auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
            }
            else if (newDD != m_lDatumDD)
            {
                auftrag.s.DATUMAUSLIEFERUNG = newDD;
                auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
            }
        }
        else if (newDD != m_lDatumDD)
        {
            auftrag.s.DATUMAUSLIEFERUNG = newDD;
            auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
        }
    }
    else
    {
        if (IsDlgButtonChecked(IDC_CHECK_NO_DD))
        {
            if (m_bNoDD == 1)
            {
                auftrag.s.STATUS = 0;
                auftrag.Server(AasrvSetNoSeperate, PIPE_AE_SRV);
            }
        }
        else
        {
            if (m_bNoDD == 0)
            {
                auftrag.s.STATUS = 1;
                auftrag.Server(AasrvSetNoSeperate, PIPE_AE_SRV);
            }
        }
    }

    //Tour setzen
    if (auftrag.s.KOART[0] == '2' || m_Status == ORD_ZURUECKGESTELLT ||
        m_Status == ORD_ZURUECKGEST_DAFUE || m_Status == ORD_KEIN_AUFTRAG ||
        m_Status == ORD_STORNIERT)    //2 entspr. keine Kommi
    {
        m_Tour = "";
    }
    else
    {
        CString Tour;
        int toursel;
        if (m_iCombo == 2)
        {
            toursel = m_CoboxFutur.GetCurSel();
            if (toursel != CB_ERR)
            {
                m_CoboxFutur.GetLBText(toursel,Tour);
            }
            else
            {
                Tour = "";
            }
        }
        else if (m_iCombo == 0)
        {
            toursel = m_CoboxTour.GetCurSel();
            if (toursel != CB_ERR)
            {
                m_CoboxTour.GetLBText(toursel,Tour);
            }
            else
            {
                Tour = "";
            }
        }
        else if (m_iCombo == 3)
        {
            toursel = m_CoboxMix.GetCurSel();
            if (toursel != CB_ERR)
            {
                m_CoboxMix.GetLBText(toursel,Tour);
            }
            else
            {
                Tour = "";
            }
        }
        else
        {
            toursel = m_CoboxNakt.GetCurSel();
            if (toursel != CB_ERR)
            {
                m_CoboxNakt.GetLBText(toursel,Tour);
            }
            else
            {
                Tour = "";
            }
        }
        if (Tour.GetLength() >= 18)
        {
            StringToTour(auftrag.s.TOURID, Tour);
            auftrag.Server(AasrvChangeTour, PIPE_AE_SRV);
            if (auftrag.rc >= SRV_OK)
            {
                m_Tour = auftrag.s.TOURID;
            }
            else
            {
                return;
            }
        }
        else
        {
            auftrag.s.TOURID[0] = '\0';
            if (Tour.GetLength() >= 1)
                MsgBoxOK(IDP_NO_TOURID);
        }
    }
    auftrag.s.STATUS = GetStatus();
    if (m_CBPrint.GetCheck())
    {
        auftrag.Server(AasrvSetprintdirect, PIPE_AE_SRV);
    }
    if (AeGetApp()->ProAufnr() > 0)
    {
        char error_msg[80];
        CPROLINK pro;
        ::buf_default((void *)&pro.s, PROLINK_BES, PROLINK_ANZ);
        pro.SetDatum(AeGetApp()->ProDatum());
        pro.SetDateproforma(AeGetApp()->ProDatum());
        pro.SetKdauftragnr(AeGetApp()->ProAufnr());
        pro.SetKdauftragnrpro(AeGetApp()->ProAufnr());
        pro.SetInvoicenumberpro(AeGetApp()->ProInvoiceno());
        ::ServerNr(PIPE_AE_SRV, AasrvWriteProLink, (void*)&pro.s, PROLINK_BES, PROLINK_ANZ, error_msg);
        if ((AeGetApp()->ProDatum() > 0))
        {
            pro.Insert();
        }
        else
        {
            CPROLINKACT proact;
            ::buf_default((void*)&proact.s, PROLINKACT_BES, PROLINKACT_ANZ);
            proact.SetKdauftragnr(AeGetApp()->ProAufnr());
            proact.SetKdauftragnrpro(AeGetApp()->ProAufnr());
            proact.SetDateproforma(m_lActDatum);
            proact.SetInvoicenumberpro(AeGetApp()->ProInvoiceno());
            proact.Insert();
        }
    }

    if (AeGetApp()->IsBG() || !AeGetApp()->IsNoKippzeit())
    {
        if ( auftrag.s.DATUMAUSLIEFERUNG <= m_lActDatum &&
             (m_Status == ORD_ERFASST || m_Status == ORD_WEITERER_AUFTRAG) )
        {
            auftrag.Server(AasrvCheckKippzeit, PIPE_AE_SRV);
            if (auftrag.rc != SRV_OK)
            {
                if (MsgBoxYesNo(AETXT_KIPPZEIT_VORBEI, MB_ICONEXCLAMATION | MB_DEFBUTTON2) != IDYES)
                    return;
            }
        }
    }
    if (!AeGetApp()->IsMSV3())
    {
        if (GetOrderType().IsAufArtDefaultKennung(m_VzNr, auftrag.s.KDAUFTRAGART))
        {
            auftrag.s.SETORDERLABEL[0] = '1';
        }
    }
    auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
    if (auftrag.rc >= SRV_OK)
    {
        if (AeGetApp()->IsBG())
        {
            m_cZuGrund = auftrag.s.ZUGRUND;
            if (auftrag.s.ZUGRUND[ZU_NO_QTY_NR] == '1' || auftrag.s.ZUGRUND[ZU_WAHL_STELLER] == '1')
            {
                MsgBoxOK(AETXT_PROMO_FEHLER);
                CDialogMultiLang::OnOK();
            }
            else if (auftrag.s.ZUGRUND[ZU_NO_CICS] == '1')
            {
                GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
                GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
                GetDlgItem(IDC_RADIO15)->EnableWindow(FALSE);
                GetDlgItem(IDC_RADIO16)->EnableWindow(FALSE);
                CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO12);
                MsgBoxOK(AETXT_NO_CICS);
                return;
            }
        }
        if (m_Status != ORD_WEITERER_AUFTRAG)
        {
#ifdef _NEWHIPATH
            ptrDoc->SetModifiedFlag(FALSE); //Auftrag nicht mehr offen setzen, weil sich die Events evtl. ueberholen
            if (AeGetApp()->m_ProCenter.IsHiPathPause() && !AeGetApp()->m_ProCenter.IsHiPathUserBusy())
            {
                if (AeGetApp()->m_ProCenter.IsHiPathLogon())
                {
                    if (AeGetApp()->IsExitPostProcEnabled())
                    {
                        AeGetApp()->m_AeTrace.WriteTrace(woher, "CDAufEnd1", "AcdAgentExitPostProc");
                        AeGetApp()->m_ProCenter.AcdAgentExitPostProc(AeGetApp()->RequeueCount());
                    }
                    else
                    {
                        if (AeGetApp()->m_ProCenter.IsHiPathOtherWork())
                        {
                            AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
                            AeGetApp()->m_ProCenter.SetHiPathOtherWork(FALSE);
                            AeGetApp()->m_AeTrace.WriteTrace(woher, "CDAufEnd1", "IsHiPathOtherWork");
                        }
                        else
                        {
                            AeGetApp()->m_AeTrace.WriteTrace(woher, "CDAufEnd1", "Not enabled");
                        }
                    }
                }
            }
            else if (AeGetApp()->m_ProCenter.IsHiPathLogon())
            {
                if (AeGetApp()->m_ProCenter.IsHiPathOtherWork())
                {
                    AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
                    AeGetApp()->m_ProCenter.SetHiPathOtherWork(FALSE);
                    AeGetApp()->m_AeTrace.WriteTrace(woher, "CDAufEnd", "IsHiPathOtherWork");
                }
                if (AeGetApp()->IsExitPostProcEnabled())
                {
                    AeGetApp()->m_AeTrace.WriteTrace(woher, "CDAufEnd", "AcdAgentExitPostProc");
                    AeGetApp()->m_ProCenter.AcdAgentExitPostProc(AeGetApp()->RequeueCount());
                    AeGetApp()->m_ProCenter.SetHiPathUserBusy(FALSE);
                    AeGetApp()->m_ProCenter.SetHiPathWorking(FALSE);
                    AeGetApp()->m_ProCenter.SetHiPathPauseWished(FALSE);
            }
                else
                {
                    AeGetApp()->m_AeTrace.WriteTrace(woher, "CDAufEnd", "Not enabled");
                }
        }
#else
            AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
#endif
        }

        if (AeGetApp()->FilialNr() != AeGetApp()->FilialNrActual())
        {
            AeGetApp()->SetFilialNrActual(AeGetApp()->FilialNr());
        }
        CDialogMultiLang::OnOK();
    }
    if (auftrag.rc == -2)
    {
        auftrag.Server(AasrvGetOrderInfo, PIPE_AE_SRV);
        m_cZuGrund = auftrag.s.ZUGRUND;
        if (m_cZuGrund.GetAt(ZU_HIGH_VALUE) == '1')
        {
            MsgBoxOK(IDP_WARN_HOHER_WERT);
        }
        else if (m_cZuGrund.GetAt(ZU_KREDITLIMIT) == '1' && AeGetApp()->IsCrema())
        {
            GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_KL));
            GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);

            MsgBoxOK(AeGetApp()->IsDE() ? AETXT_AUF_ZU_KL_DE : AETXT_AUF_ZU_KL);

            auftrag.s.STATUS = m_Status = ORD_ZURUECKGESTELLT;
            auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
            CDialogMultiLang::OnOK();
        }
        else if (m_cZuGrund.GetAt(ZU_KREDITLIMIT) == '1' && GetAeUser().IsKreditAbschluss())
        {
            if (AeGetApp()->IsKLClose())
            {
                GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_KL));
                GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
            }
            GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_KL));
            GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
        }
        else if (m_cZuGrund.GetAt(ZU_INTERNET) == '1' && GetAeUser().IsInternetAbschluss())
        {
            GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_IN));
            GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_IN));
            GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
        }
        else if (m_cZuGrund.GetAt(ZU_BTM) == '1' && GetAeUser().IsAbschlussBTM())
        {
            GetDlgItem(IDC_RADIO17)->SetWindowText(CResString::ex().getStrTblText(AETXT_AB_BTM));
            GetDlgItem(IDC_RADIO18)->SetWindowText(CResString::ex().getStrTblText(AETXT_ST_BTM));
            GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
        }
        else
        {
            GetDlgItem(IDC_RADIO17)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_RADIO18)->ShowWindow(SW_HIDE);
        }
    }
    AeGetApp()->ProAufnr = 0;
    AeGetApp()->ProDatum = 0;
    AeGetApp()->ProInvoiceno = "";
}

void CDAufEnd::OnChangeEditBemerkung()
{
    if (AeGetApp()->IsRS())
    {
        if (!AllgCheckPrintableSign(&m_EditBemerkung))
            return;
    }
    AllgLaengeKontr(&m_EditBemerkung, MAXIMUM_AUFT_BEM,AeGetApp()->Modus());
}

void CDAufEnd::OnRadioTour()
{
    if (GetCheckedRadioButton(IDC_RADIO20, IDC_RADIO28) == IDC_RADIO26)
    {
        GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_TOUR)->EnableWindow(FALSE);
    }
    else
    {
        if (m_bSonder)
        {
            GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
        }
        else
        {
            GetDlgItem(IDC_COMBO_TOUR)->EnableWindow();
        }
    }
    m_bManuell = true;
}

void CDAufEnd::OnRadioSchl()
{
    if ( GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18) == IDC_RADIO11 ||
         GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18) == IDC_RADIO12 ||
         GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18) == IDC_RADIO13 ||
         GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18) == IDC_RADIO18 ||
         GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18) == IDC_RADIO18 )
    {
        GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_TOUR)->EnableWindow(FALSE);
    }
    else
    {
        if (m_bSonder)
        {
            GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
        }
        else
        {
            if (m_bMixShown)
            {
                GetDlgItem(IDC_COMBO_MIX)->EnableWindow();
            }
            else
            {
                GetDlgItem(IDC_COMBO_TOUR)->EnableWindow();
            }
        }
    }
}

void CDAufEnd::OnSelchangeComboTour()
{
    CString Tour;
    int toursel = m_CoboxTour.GetCurSel();
    if (toursel != CB_ERR)
    {
        m_CoboxTour.GetLBText(toursel,Tour);
    }
    else
    {
        return;
    }
    if (Tour.GetLength() >= 42)
    {
        if (!m_bManuell) //Wenn KA manuell geändert, keine automatische Umstellung
        {
            if (Tour.GetAt(42) != ' ')
            {
                SetKommArt(Tour.GetAt(42));
            }
            else
            {
                SetKommArt(m_KommArt.GetAt(0));
            }
        }
    }
    CheckTourDD();
}

LRESULT CDAufEnd::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    char wert[2];
    if (((LPMSG)lpMsg)->wParam >= VK_NUMPAD0 && ((LPMSG)lpMsg)->wParam <= VK_NUMPAD9)
        sprintf(wert, "%01d", ((LPMSG)lpMsg)->wParam - VK_NUMPAD0);
    else if (((LPMSG)lpMsg)->wParam >= '0' && ((LPMSG)lpMsg)->wParam <= '9')
        sprintf(wert, "%01d", ((LPMSG)lpMsg)->wParam - '0');
    else
        return 0L;
    if (GetFocus() == GetDlgItem(IDC_RADIO10))
    {
        SetKommArt(wert[0]);
        OnRadioTour();
        GetDlgItem(IDC_RADIO10)->SetFocus();
        return 1L;
    }
    return 0L;
}

void CDAufEnd::CheckTourDD()
{
    if ((AeGetApp()->UseTourManagerCst() == 2) || (AeGetApp()->IsKndDD() && (m_lDatumDD <= m_lActDatum)))
    {
        CCHECKORDERNODD noDD;
        CString Tour;
        int toursel;
        long lZeitTour;
        char cTour[7];
        noDD.SetCscorderno(m_lAufnr);
        m_bNoDD = noDD.CheckNoDD();
        if (m_bMixShown)
        {
            toursel = m_CoboxMix.GetCurSel();
        }
        else if (m_bSonder)
        {
            toursel = m_CoboxNakt.GetCurSel();
        }
        else
        {
            toursel = m_CoboxTour.GetCurSel();
        }
        if (toursel != CB_ERR)
        {
            if (m_bMixShown)
            {
                m_CoboxMix.GetLBText(toursel, Tour);
            }
            else if (m_bSonder)
            {
                m_CoboxNakt.GetLBText(toursel, Tour);
            }
            else
            {
                m_CoboxTour.GetLBText(toursel, Tour);
            }
            StringToTour(cTour, Tour);
            lZeitTour = atol(cTour) / 100;
            if (AeGetApp()->IsKndDD() && (m_lDatumDD <= m_lActDatum))
            {
                if (lZeitTour > AeGetApp()->ZeitDD())
                {
                    GetDlgItem(IDC_CHECK_NO_DD)->ShowWindow(SW_SHOW);
                    if (lZeitTour == 4759)
                    {
                        CheckDlgButton(IDC_CHECK_NO_DD, TRUE);
                    }
                    else if (!m_bNoDD)
                    {
                        CheckDlgButton(IDC_CHECK_NO_DD, TRUE);
                    }
                    else
                    {
                        CheckDlgButton(IDC_CHECK_NO_DD, FALSE);
                    }
                }
                else
                {
                    GetDlgItem(IDC_CHECK_NO_DD)->ShowWindow(SW_HIDE);
                    CheckDlgButton(IDC_CHECK_NO_DD, FALSE);
                }
            }
            else if (m_lDatumDD <= m_lActDatum)
            {
                CTOURPLANPFLEGE pflege;
                pflege.SetDatumkommi(m_lActDatum);
                pflege.SetVertriebszentrumnr(m_VzNr);
                pflege.SetKundennr(m_KndNr);
                pflege.SetTourid(cTour);
                if (!pflege.SelTour())
                {
                    if (!pflege.GetIsbtm() || !pflege.GetIsk08() || !pflege.GetIsk20() || !pflege.GetIskk())
                    {
                        GetDlgItem(IDC_CHECK_NO_DD)->ShowWindow(SW_SHOW);
                        if (lZeitTour == 4759)
                        {
                            CheckDlgButton(IDC_CHECK_NO_DD, TRUE);
                        }
                        else if (!m_bNoDD)
                        {
                            CheckDlgButton(IDC_CHECK_NO_DD, TRUE);
                        }
                        else
                        {
                            CheckDlgButton(IDC_CHECK_NO_DD, FALSE);
                        }
                    }
                    else
                    {
                        GetDlgItem(IDC_CHECK_NO_DD)->ShowWindow(SW_HIDE);
                        CheckDlgButton(IDC_CHECK_NO_DD, FALSE);
                    }
                }
            }
        }
    }
    else
    {
        GetDlgItem(IDC_CHECK_NO_DD)->ShowWindow(SW_HIDE);
        CheckDlgButton(IDC_CHECK_NO_DD, FALSE);
    }
}

void CDAufEnd::OnCbnSelchangeComboNakt()
{
    CString Tour;
    int toursel = m_CoboxTour.GetCurSel();
    if (toursel != CB_ERR)
    {
        m_CoboxTour.GetLBText(toursel,Tour);
    }
    else
    {
        return;
    }
    if (Tour.GetLength() >= 42)
    {
        if (!m_bManuell) //Wenn KA manuell geändert, keine automatische Umstellung
        {
            if (Tour.GetAt(42) != ' ')
            {
                SetKommArt(Tour.GetAt(42));
            }
            else
            {
                SetKommArt(m_KommArt.GetAt(0));
            }
        }
    }
    CheckTourDD();
}

HBRUSH CDAufEnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_SONDER)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SONDER_TOUR)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_COMBO_TOUR_NAKT)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_COMBO_FUTUR)
        pDC->SetTextColor(RGB(0, 0, 200));
    else if (pWnd->GetDlgCtrlID() == IDC_COMBO_MIX)
    {
        if (m_bAnzSonder)
        {
            pDC->SetTextColor(RGB(200, 0, 0));
        }
        else
        {
            pDC->SetTextColor(RGB(0, 0, 0));
        }
    }

    return hbr;
}

void CDAufEnd::OnDtnDatetimechangeDatetimepickerDd(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    UpdateData();
    LadeWochenTouren(static_cast<short>(m_CT_DD.GetDayOfWeek() - 1));
    long newDD = (m_CT_DD.GetYear() * 10000 +
                  m_CT_DD.GetMonth() * 100 +
                  m_CT_DD.GetDay());
    if (newDD > m_lActDatum)
    {
        ShowFutur();
        m_bSonder = false;
        m_CoboxFutur.SetCurSel(0);
    }
    else if (m_CoboxTour.GetCount() == 0)
    {
        ShowSonder();
        m_bSonder = true;
        m_CoboxNakt.SetCurSel(0);
    }
    else
    {
        ShowAkt();
        m_bSonder = false;
        m_CoboxTour.SetCurSel(0);
    }

    *pResult = 0L;
}

void CDAufEnd::HoleWochenTouren()
{
    if (m_aWochentouren.IsEmpty())
    {
        //Tour
        CString STour;      //Tour für Ausgabe formatiert
        CString Tour;       //Tournummer
        CKNDTOUREN kndtouren;
        kndtouren.s.IDFNR = m_IdfNr;
        kndtouren.s.KUNDENNR = m_IdfNr;
        kndtouren.s.VERTRIEBSZENTRUMNR = m_VzNr;
        m_aWochentouren.RemoveAll();
        for (;;)
        {
            kndtouren.Server(AasrvGetWeektouren, PIPE_AE_SRV);
            if (kndtouren.rc != SRV_OK)
                break;
            Tour = kndtouren.s.TOURID;
            TourToString(Tour, STour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], kndtouren.s.WEEKDAY);
            m_aWochentouren.Add(STour);
        }
    }
}

void CDAufEnd::LadeWochenTouren(short sWeekday)
{
    //Tour
    m_CoboxFutur.ResetContent();
    for (int i = 0; i < m_aWochentouren.GetCount(); i++)
    {
        if (sWeekday == 9)
        {
            m_CoboxFutur.AddString(m_aWochentouren.GetAt(i));
        }
        else
        {
            if (atoi(m_aWochentouren.GetAt(i).Right(1)) == sWeekday)
            {
                m_CoboxFutur.AddString(m_aWochentouren.GetAt(i));
            }
        }
    }
    if (sWeekday == 9)
    {
        char cWeekday[2];
        int i;
        CString csTour;
        sprintf(cWeekday, "%d", m_sWeekday);
        for (i = 0; i < m_CoboxFutur.GetCount(); i++)
        {
            m_CoboxFutur.GetLBText(i, csTour);
            if (cWeekday[0] < csTour.GetAt(50))
            {
                m_CoboxFutur.SetCurSel(i);
                i = 99;
                break;
            }
        }
        if (i < 99)
        {
            sprintf(cWeekday, "%d", m_sWeekday - 7);
            for (i = 0;i < m_CoboxFutur.GetCount();i++)
            {
                m_CoboxFutur.GetLBText(i, csTour);
                if (cWeekday[0] < csTour.GetAt(48))
                {
                    m_CoboxFutur.SetCurSel(i);
                    break;
                }
            }
        }
    }
    else
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

void CDAufEnd::ShowAkt()
{
    m_iCombo = 0;
    GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_NAKT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_NAKT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_bMixExist)
    {
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    }
    if (m_CoboxTour.GetCurSel() == CB_ERR)
        m_CoboxTour.SetCurSel(0);
}

void CDAufEnd::ShowSonder()
{
    m_iCombo = 1;
    GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_NAKT)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_NAKT)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxNakt.GetCurSel() == CB_ERR)
        m_CoboxNakt.SetCurSel(0);
}

void CDAufEnd::ShowFutur()
{
    m_iCombo = 2;
    GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_NAKT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_NAKT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxFutur.GetCurSel() == CB_ERR)
        m_CoboxFutur.SetCurSel(0);
}

void CDAufEnd::ShowMix()
{
    m_iCombo = 3;
    GetDlgItem(IDC_STATIC_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_NAKT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_NAKT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
    OnCbnSelchangeComboMix();
}

void CDAufEnd::OnCbnSelchangeComboMix()
{
    CString Tour;
    int toursel = m_CoboxMix.GetCurSel();
    if (toursel != CB_ERR)
    {
        m_CoboxMix.GetLBText(toursel, Tour);
    }
    else
    {
        return;
    }
    if (Tour.GetLength() >= 42)
    {
        if (!m_bManuell)    //Wenn KA manuell geändert, keine automatische Umstellung
        {
            if (Tour.GetAt(42) != ' ')
            {
                SetKommArt(Tour.GetAt(42));
            }
            else
            {
                SetKommArt(m_KommArt.GetAt(0));
            }
        }
    }
    CString Tourtyp = Tour.Mid(45, m_Tagtab.GetAt(8).GetLength());
    m_bAnzSonder = (m_Tagtab.GetAt(8) == Tourtyp) ? true : false;
        
    CheckTourDD();
}

void CDAufEnd::OnBnClickedButtonSonder()
{
    if (m_bMixShown)
    {
        if (m_bSonder)
        {
            ShowSonder();
        }
        else
        {
            ShowAkt();
        }
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
        m_bMixShown = false;
    }
    else
    {
        ShowMix();
        m_CoboxMix.SetCurSel(0);
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
        m_bMixShown = true;
    }
}
void CDAufEnd::OnBnClickedButtonRechwert()
{

    if (AeGetApp()->IsBG())
    {
        CDShowProforma dlgShowProforma;
        dlgShowProforma.DoModal();
        return;
    }

    CAUFPOSBUCH aufposbuch;
    BeginWaitCursor();

    aufposbuch.Server(AasrvProforma, PIPE_AE_SRV); // proforma Lieferwert berechnen
    if (aufposbuch.rc >= SRV_OK)
    {
        CString cs;
        cs.Format("%.2lf", aufposbuch.s.WERTLIEFERUNG);
        ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_PROFORMA)->ShowWindow(SW_SHOW);
        ((CAeFView *)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_RECHWERT)->ShowWindow(SW_SHOW);
        ((CAeFView *)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_PROFORMA)->EnableWindow(TRUE);
        ((CAeFView *)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_RECHWERT)->EnableWindow(TRUE);
        ((CAeFView *)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_RECHWERT)->SetWindowText(cs);
        //Kopfinformationen aktualisieren
        ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(
                    aufposbuch.s.ANZPOS,
                    aufposbuch.s.WERTAUFTRAG,
                    aufposbuch.s.WERTLIEFERUNG,
                    aufposbuch.s.WERTZEILEN,
                    aufposbuch.s.BALANCE,
                    aufposbuch.s.BALANCE2 );
        ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerteBG(
                    aufposbuch.s.WERTNETTO_FV,
                    aufposbuch.s.WERTTAX_FV,
                    aufposbuch.s.WERTNETTO_KK,
                    aufposbuch.s.WERTTAX_KK,
                    aufposbuch.s.WERTNETTO_EH,
                    aufposbuch.s.WERTTAX_EH,
                    aufposbuch.s.WERTEXCLUSIVE );
        CDialogMultiLang::OnCancel();
    }
}

void CDAufEnd::OnCheckColFV()
{
    if (m_CB_nrcol_fv.GetCheck() == BST_CHECKED)
    {
        m_CB_rabaep_fv.SetCheck(BST_UNCHECKED);
        m_CB_rabavp_fv.SetCheck(BST_UNCHECKED);
    }
}

void CDAufEnd::OnCheckAEPFV()
{
    if (m_CB_rabaep_fv.GetCheck() == BST_CHECKED)
    {
        m_CB_nrcol_fv.SetCheck(BST_UNCHECKED);
        m_combo_price_fv.SetCurSel(0);
    }
}

void CDAufEnd::OnCheckAVPFV()
{
    if (m_CB_rabavp_fv.GetCheck() == BST_CHECKED)
    {
        m_CB_nrcol_fv.SetCheck(BST_UNCHECKED);
        m_CB_rabaep_fv.SetCheck(BST_CHECKED);
        m_combo_price_fv.SetCurSel(0);
    }
}

void CDAufEnd::OnCheckColKK()
{
    if (m_CB_nrcol_kk.GetCheck() == BST_CHECKED)
    {
        m_CB_rabaep_kk.SetCheck(BST_UNCHECKED);
        m_CB_rabavp_kk.SetCheck(BST_UNCHECKED);
    }
}

void CDAufEnd::OnCheckAEPKK()
{
    if (m_CB_rabaep_kk.GetCheck() == BST_CHECKED)
    {
        m_CB_nrcol_kk.SetCheck(BST_UNCHECKED);
        m_combo_price_kk.SetCurSel(0);
    }
}

void CDAufEnd::OnCheckAVPKK()
{
    if (m_CB_rabavp_kk.GetCheck() == BST_CHECKED)
    {
        m_CB_nrcol_kk.SetCheck(BST_UNCHECKED);
        m_CB_rabaep_kk.SetCheck(BST_CHECKED);
        m_combo_price_kk.SetCurSel(0);
    }
}

void CDAufEnd::OnCbnSelchangeComboPriceFv()
{
    if (m_combo_price_fv.GetCurSel() > 0)
    {
        m_CB_rabaep_fv.SetCheck(BST_UNCHECKED);
        m_CB_rabavp_fv.SetCheck(BST_UNCHECKED);
    }
}

void CDAufEnd::OnCbnSelchangeComboPriceKk()
{
    if (m_combo_price_kk.GetCurSel() > 0)
    {
        m_CB_rabaep_kk.SetCheck(BST_UNCHECKED);
        m_CB_rabavp_kk.SetCheck(BST_UNCHECKED);
    }
}
