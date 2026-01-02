// DAufFrText.cpp : implementation file
//

#include "stdafx.h"
#include "AeDoc.h"
#include "DAufFrText.h"
#include "AeFView.h"

/////////////////////////////////////////////////////////////////////////////
// CDAufFrText dialog


CDAufFrText::CDAufFrText(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufFrText::IDD, pParent)
{
    m_CEinheit = _T("");
    m_lMenge = 0;
    m_CBezeichnung = _T("");
    m_CDarreichform = _T("");
    m_CText = _T("");
    m_dAEP = _T("");
    m_dDrabProz = _T("");
    m_dDrabDM = _T("");
    m_dGEP = _T("");
    m_CPorto = _T("");
    m_CApoDiNl = _T("");
    ptrDoc = NULL;
    PosNr = -1;     //Neuerfassung
}


void CDAufFrText::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_WG, m_ComboWg);
    DDX_Control(pDX, IDC_EDIT_PORTO, m_EditPorto);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_EditText);
    DDX_Control(pDX, IDC_EDIT_GEP, m_EditGEP);
    DDX_Control(pDX, IDC_EDIT_DRAB_PROZ, m_EditDrabProz);
    DDX_Control(pDX, IDC_EDIT_DRAB_DM, m_EditDrabDM);
    DDX_Control(pDX, IDC_EDIT_DARR, m_EditDarreichform);
    DDX_Control(pDX, IDC_EDIT_BEZEI, m_EditBezeichnung);
    DDX_Control(pDX, IDC_EDIT_AEP, m_EditAEP);
    DDX_Control(pDX, IDC_EDIT_EINHEIT, m_EditEinheit);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_EditMenge);
    DDX_Text(pDX, IDC_EDIT_EINHEIT, m_CEinheit);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_lMenge);
    DDX_Text(pDX, IDC_EDIT_BEZEI, m_CBezeichnung);
    DDX_Text(pDX, IDC_EDIT_DARR, m_CDarreichform);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Text(pDX, IDC_EDIT_AEP, m_dAEP);
    DDX_Text(pDX, IDC_EDIT_DRAB_PROZ, m_dDrabProz);
    DDX_Text(pDX, IDC_EDIT_DRAB_DM, m_dDrabDM);
    DDX_Text(pDX, IDC_EDIT_GEP, m_dGEP);
    DDX_Text(pDX, IDC_EDIT_PORTO, m_CPorto);
    DDX_Text(pDX, IDC_STATIC_DINL, m_CApoDiNl);
    DDX_Control(pDX, IDC_COMBO_TAX, m_ComboTax);
    DDX_Control(pDX, IDC_COMBO_PRISO, m_ComboPriso);
}


BEGIN_MESSAGE_MAP(CDAufFrText, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_AEP, OnChangeEditAep)
    ON_EN_CHANGE(IDC_EDIT_BEZEI, OnChangeEditBezei)
    ON_EN_CHANGE(IDC_EDIT_DARR, OnChangeEditDarr)
    ON_EN_CHANGE(IDC_EDIT_DRAB_DM, OnChangeEditDrabDm)
    ON_EN_CHANGE(IDC_EDIT_DRAB_PROZ, OnChangeEditDrabProz)
    ON_EN_CHANGE(IDC_EDIT_EINHEIT, OnChangeEditEinheit)
    ON_EN_CHANGE(IDC_EDIT_GEP, OnChangeEditGep)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnChangeEditMenge)
    ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
    ON_BN_CLICKED(IDC_RADIO12, OnRadioFakturieren)
    ON_BN_CLICKED(IDC_BUTTON_GELOESCHT, OnButtonGeloescht)
    ON_EN_CHANGE(IDC_EDIT_PORTO, OnChangeEditPorto)
    ON_BN_CLICKED(IDC_BUTTON_SCHLIESSEN, OnButtonSchliessen)
    ON_BN_CLICKED(IDC_BUTTON_DISPONIEREN, OnButtonDisponieren)
    ON_BN_CLICKED(IDC_BUTTON_AUFNEHMEN, OnButtonAufnehmen)
    ON_BN_CLICKED(IDC_BUTTON_INFOTEXT, OnButtonInfotext)
    ON_BN_CLICKED(IDC_RADIO10, OnRadioFakturieren)
    ON_BN_CLICKED(IDC_RADIO11, OnRadioFakturieren)
    ON_BN_CLICKED(IDC_RADIO13, OnRadioFakturieren)
    ON_BN_CLICKED(IDC_RADIO14, OnRadioFakturieren)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufFrText message handlers

BOOL CDAufFrText::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_SONSTIGE));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_GUEG));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_WEIN));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_SCHAUMWEIN));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_SPIRITUOSEN));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_ALKOHOL));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_DELIKATESSEN));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_GESCHENKE));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_DOKU));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_DIENST));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_TRANSKO));
    m_ComboWg.AddString(CResString::ex().getStrTblText(AETXT_INVENTUR));

    if (AeGetApp()->IsDE())
    {
        m_ComboPriso.AddString(CResString::ex().getStrTblText(AETXT_NO_ZENTRAL));
        m_ComboPriso.AddString(CResString::ex().getStrTblText(AETXT_ZENTRAL_ART));
        m_ComboPriso.SetCurSel(0);
    }

    double dTax;
    CString Tax;
    char cStd;
    int rc;

    m_iStd = 0;
    for (int i = 0;; i++)
    {
        rc = AeGetApp()->GetTaxRates(i, cStd, dTax);
        if (rc == -1)
            break;
        Tax.Format("%0.2lf %%", dTax);
        m_ComboTax.AddString(Tax);
        if (cStd == '1')
            m_iStd = i;
    }
    m_ComboTax.SetCurSel(m_iStd);
    ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_AA)->GetWindowText(m_cAArt);
    if (m_cAArt == "SV")
    {
        GetDlgItem(IDC_BUTTON_DISPONIEREN)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
    }
    if (PosNr != -1)
    {
        BeginWaitCursor();
        CAUFPOSBUCH aufposbuch;
        aufposbuch.s.POSNR = PosNr;
        aufposbuch.Server(AasrvInfposnr, PIPE_AE_SRV);
        EndWaitCursor();
        AllgEntfSpaces(aufposbuch.s.ARTIKEL_NAME);
        AllgEntfSpaces(aufposbuch.s.EINHEIT);
        AllgEntfSpaces(aufposbuch.s.DARREICHFORM);
        AllgEntfSpaces(aufposbuch.s.BEMERKUNG);
        m_CBezeichnung  = aufposbuch.s.ARTIKEL_NAME;
        m_CEinheit      = aufposbuch.s.EINHEIT;
        m_CDarreichform = aufposbuch.s.DARREICHFORM;
        m_CText         = aufposbuch.s.BEMERKUNG;
        m_dAEP.Format("%.2f", aufposbuch.s.PREISEKAPO);
        m_dGEP.Format("%.2f", aufposbuch.s.PREISEKGROSSO);
        m_lMenge        = aufposbuch.s.MENGEBESTELLT;
        m_dDrabDM.Format("%.2f", aufposbuch.s.RABATTFESTDM);
        m_dDrabProz.Format("%.2f", aufposbuch.s.RABATTFEST);
        AllgCStrCharToChar(m_dAEP,      '.', ',');
        AllgCStrCharToChar(m_dGEP,      '.', ',');
        AllgCStrCharToChar(m_dDrabDM,   '.', ',');
        AllgCStrCharToChar(m_dDrabProz, '.', ',');
        if (aufposbuch.s.KZAPODINL[0] == ITEM_APO_DISPO)
            m_CApoDiNl = CResString::ex().getStrTblText(AETXT_DISPO);
        else if (aufposbuch.s.KZAPODINL[0] == ITEM_APO_NACHL)
            m_CApoDiNl = CResString::ex().getStrTblText(AETXT_NACHL);
        else if (aufposbuch.s.KZINFOTEXT[0] == '1')
            m_CApoDiNl = CResString::ex().getStrTblText(AETXT_INFO);
        else
            m_CApoDiNl = " ";
        UpdateData(FALSE);
        if (aufposbuch.s.PREISEKAPO!=0 || aufposbuch.s.PREISEKGROSSO!=0)
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO12);
            InitMitWert();
            m_ComboWg.SetCurSel(m_ComboWg.FindString(0, aufposbuch.s.WARENGRUPPEEIGEN));
            if (AeGetApp()->IsDE())
            {
                m_ComboPriso.SetCurSel(aufposbuch.s.KZPRISO[0] == '1' ? 1 : 0);
            }
        }
        else if (aufposbuch.s.STATUS == ITEM_STAT_DISPO)
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO10);
            InitOhneWert();
        }
        else if (aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFERN)
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO11);
            InitOhneWert();
        }
        else if (aufposbuch.s.STATUS == ITEM_STAT_NORMAL)
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO13);
            InitOhneWert();
        }
        else
            FehlerBehandlung(-1, "DAufFrText: CDAufFrText::OnInitDialog() 1");

        if (aufposbuch.s.KZINFOTEXT[0] == '1')
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO14);
        }

        m_ComboTax.SetCurSel(atoi(aufposbuch.s.MWSTSCHLUESSEL));

        CheckDlgButton(IDC_CHECK_TAX, aufposbuch.s.TAXPFLICHTIG[0] == '1' ? TRUE : FALSE);
        CheckDlgButton(IDC_CHECK_RABATT, aufposbuch.s.RABATTFAEHIG[0] == '1' ? TRUE  :FALSE);
    }
    else
    {
        if (AeGetApp()->IsDE())
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO12);  //Funktionskennzeichen fakturieren setzen
            InitMitWert();
        }
        else if (m_cAArt == "SV")
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO12);  //Funktionskennzeichen fakturieren setzen
            InitMitWert();
        }
        else
        {
            CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO10);  //Funktionskennzeichen disponieren setzen
            InitOhneWert();
        }
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDAufFrText::OnOK()
{
}

void CDAufFrText::OnButtonSchliessen()
{
    if (!UpdateData())
        return;

    CAUFPOSBUCH aufposbuch;
    aufposbuch.s.KZINFOTEXT[0] = '0';
    aufposbuch.s.KZINFOTEXT[1] = '\0';
    aufposbuch.s.KZAUFGENOMMEN[0] = '0';
    aufposbuch.s.KZAUFGENOMMEN[1] = '\0';

    if (m_lMenge > WARN_BUCH_MENGE)
    {
        MsgBoxOK(IDP_WARN_MENGE);
    }
    //Daten einlesen
    if (m_CBezeichnung.IsEmpty())
    {
        MsgBoxOK(IDP_NO_BEZEICHNUG);
        m_EditBezeichnung.SetFocus();
        m_EditBezeichnung.SetSel(0, -1, FALSE);
        return;
    }
    if (m_lMenge == 0)
    {
        MsgBoxOK(IDP_MENGE_EINGEBEN);
        m_EditMenge.SetFocus();
        m_EditMenge.SetSel(0, -1, FALSE);
        return;
    }
    AllgStrCopy(aufposbuch.s.ARTIKEL_NAME,   m_CBezeichnung,  L_AUFPOSBUCH_ARTIKEL_NAME);
    AllgStrCopy(aufposbuch.s.EINHEIT,        m_CEinheit,      L_AUFPOSBUCH_EINHEIT);
    AllgStrCopy(aufposbuch.s.DARREICHFORM,   m_CDarreichform, L_AUFPOSBUCH_DARREICHFORM);
    AllgStrCopy(aufposbuch.s.BEMERKUNG,      m_CText,         L_AUFPOSBUCH_BEMERKUNG);
    AllgCStrCharToChar(m_dAEP,      ',', '.');
    AllgCStrCharToChar(m_dGEP,      ',', '.');
    AllgCStrCharToChar(m_dDrabDM,   ',', '.');
    AllgCStrCharToChar(m_dDrabProz, ',', '.');
    aufposbuch.s.PREISEKAPO      = atof(m_dAEP);
    aufposbuch.s.PREISEKGROSSO   = atof(m_dGEP);
    aufposbuch.s.MENGEBESTELLT   = m_lMenge;
    aufposbuch.s.RABATTFESTDM    = atof(m_dDrabDM);
    aufposbuch.s.RABATTFEST      = atof(m_dDrabProz);
    aufposbuch.s.ARTIKEL_NR      = ITEM_ARTNR_FREITEXT;

    if (IsDlgButtonChecked(IDC_RADIO12) && (aufposbuch.s.PREISEKAPO == 0 || aufposbuch.s.PREISEKGROSSO == 0))
    {
        MsgBoxOK(IDP_FRTEXT_NO_WERTE);
        return;
    }
    CString WG;
    if (aufposbuch.s.PREISEKAPO != 0)
    {
        if (m_ComboWg.GetCurSel() == CB_ERR)
        {
            MsgBoxOK(IDP_FRTXT_NO_WG);
            return;
        }
        else
        {
            m_ComboWg.GetLBText(m_ComboWg.GetCurSel(), WG);
        }
        if (AeGetApp()->IsDE())
        {
            CString csText;
            if (m_ComboPriso.GetCurSel() == CB_ERR)
            {
                MsgBoxOK(IDP_PRISO_JN);
                return;
            }
            else
            {
                csText.Format("%d", m_ComboPriso.GetCurSel());
                aufposbuch.s.KZPRISO[0] = csText.GetAt(0);
            }
        }
    }
    if (aufposbuch.s.PREISEKAPO != 0)
    {
        if (aufposbuch.s.PREISEKAPO < aufposbuch.s.PREISEKGROSSO)
        {
            MsgBoxOK(AETXT_AEP_GEP);
            return;
        }
        if (aufposbuch.s.PREISEKAPO > 2 * aufposbuch.s.PREISEKGROSSO)
        {
            CString csText;
            csText.Format(CResString::ex().getStrTblText(IDP_PREISE_KORREKT), m_dAEP.GetString(), m_dGEP.GetString());
            if (MsgBoxYesNo(csText) != IDYES)
                return;
        }
        else if (AeGetApp()->IsDE())
        {
            if (IsDlgButtonChecked(IDC_CHECK_TAX))
            {
                if (AeGetApp()->FixZuschlag() == 0.0)
                {
                    CPARAMETER param;
                    param.SetFilialnr(0);
                    param.SetProgrammname("ORDERENTRY");
                    param.SetZweck("TAXSPANNE");
                    param.SetParametername("FIXZUSCHLAG");
                    if (!param.SelParameter()) AeGetApp()->FixZuschlag = (static_cast<double>(param.GetWert()) / 100);
                    param.SetParametername("PROZENTZUSCHLAG");
                    if (!param.SelParameter()) AeGetApp()->ProzentZuschlag = (static_cast<double>(param.GetWert()) / 100);
                    param.SetParametername("BEGRENZUNG");
                    if (!param.SelParameter()) AeGetApp()->Begrenzung = (static_cast<double>(param.GetWert()) / 100);
                }
                double Taxwert = ((aufposbuch.s.PREISEKGROSSO * (100 + AeGetApp()->ProzentZuschlag())) / 100) + AeGetApp()->FixZuschlag(); //GEP + 3,15% + 0,70 €
                CString csText;
                csText.Format("%0.2lf", Taxwert);
                double calcaep = atof(csText);
                if ((calcaep - aufposbuch.s.PREISEKGROSSO) > (AeGetApp()->Begrenzung() + AeGetApp()->FixZuschlag()))
                {
                    calcaep = aufposbuch.s.PREISEKGROSSO + (AeGetApp()->Begrenzung() + AeGetApp()->FixZuschlag());
                }
                if (aufposbuch.s.PREISEKAPO > calcaep)
                {
                    csText.Format(CResString::ex().getStrTblText(AETXT_TAXSPANNE_GROSS), aufposbuch.s.PREISEKGROSSO, aufposbuch.s.PREISEKAPO, calcaep);
                    if (MsgBoxYesNo(csText) != IDYES)
                        return;
                }
                else if (aufposbuch.s.PREISEKAPO < calcaep)
                {
                    csText.Format(CResString::ex().getStrTblText(AETXT_TAXSPANNE_KLEIN), aufposbuch.s.PREISEKGROSSO, aufposbuch.s.PREISEKAPO, calcaep);
                    if (MsgBoxYesNo(csText) != IDYES)
                        return;
                }
            }
        }
    }
    AllgStrCopy(aufposbuch.s.WARENGRUPPEEIGEN, WG, L_AUFPOSBUCH_WARENGRUPPEEIGEN);

    //Buchungsart setzen
    if      (IsDlgButtonChecked(IDC_RADIO10)) { aufposbuch.s.STATUS = ITEM_STAT_DISPO; }
    else if (IsDlgButtonChecked(IDC_RADIO11)) { aufposbuch.s.STATUS = ITEM_STAT_NACHLIEFERN; }
    else if (IsDlgButtonChecked(IDC_RADIO12)) { aufposbuch.s.STATUS = ITEM_STAT_NORMAL; }
    else if (IsDlgButtonChecked(IDC_RADIO13)) { aufposbuch.s.STATUS = ITEM_STAT_NORMAL; }
    else if (IsDlgButtonChecked(IDC_RADIO14)) { aufposbuch.s.STATUS = ITEM_STAT_NORMAL;
                                                aufposbuch.s.KZINFOTEXT[0] = '1'; }
    else
        FehlerBehandlung(-1,"DAufFrText: CDAufFrText::OnOK() 1");

    //MWSt setzen
    sprintf(aufposbuch.s.MWSTSCHLUESSEL, "%d", m_ComboTax.GetCurSel());

    //Taxpflicht, Rabattfaehigkeit setzen
    aufposbuch.s.TAXPFLICHTIG[0] = IsDlgButtonChecked(IDC_CHECK_TAX) ? '1' : '0';
    aufposbuch.s.TAXPFLICHTIG[1] = '\0';
    aufposbuch.s.RABATTFAEHIG[0] = IsDlgButtonChecked(IDC_CHECK_RABATT) ? '1' : '0';
    aufposbuch.s.RABATTFAEHIG[1] = '\0';

    //Buchung
    BeginWaitCursor();
    if (PosNr == -1)
    {
        aufposbuch.Server(AasrvWritetextpos, PIPE_AE_SRV);
        if (aufposbuch.rc < SRV_OK)
            return;
        ptrDoc->AddPosition(aufposbuch.s);
        AllgCStrCharToChar(m_CPorto, ',', '.');
        if (IsDlgButtonChecked(IDC_RADIO12) && atof(m_CPorto) > 0.0)
        {
            aufposbuch.buf_default();
            if (AeGetApp()->IsCH())
            {
                AllgStrCopy(aufposbuch.s.ARTIKEL_NAME, CResString::ex().getStrTblText(AETXT_PORTO_VERPACKUNG_KLEINMENGE), L_AUFPOSBUCH_ARTIKEL_NAME);
            }
            else
            {
                AllgStrCopy(aufposbuch.s.ARTIKEL_NAME, CResString::ex().getStrTblText(AETXT_PORTO_VERPACKUNG), L_AUFPOSBUCH_ARTIKEL_NAME);
            }
            aufposbuch.s.PREISEKAPO      = atof(m_CPorto);
            aufposbuch.s.PREISEKGROSSO   = aufposbuch.s.PREISEKAPO - 0.01;
            aufposbuch.s.MENGEBESTELLT   = 1;
            aufposbuch.s.ARTIKEL_NR      = ITEM_ARTNR_FREITEXT;
            aufposbuch.s.STATUS = ITEM_STAT_NORMAL;
            //MWSt setzen
            sprintf(aufposbuch.s.MWSTSCHLUESSEL, "%d", m_iStd);

            //Taxpflicht, Rabattfaehigkeit setzen
            aufposbuch.s.TAXPFLICHTIG[0] =  '0';
            aufposbuch.s.TAXPFLICHTIG[1] = '\0';
            aufposbuch.s.RABATTFAEHIG[0] =  '0';
            aufposbuch.s.RABATTFAEHIG[1] = '\0';
            if (AeGetApp()->IsDE())
            {
                CString csText;
                csText.Format("%d", m_ComboPriso.GetCurSel());
                aufposbuch.s.KZPRISO[0] = csText.GetAt(0);
            }
            aufposbuch.Server(AasrvWritetextpos, PIPE_AE_SRV);
            if (aufposbuch.rc < SRV_OK)
                MsgBoxOK(IDS_FEHLER_PORTO_VERP);
            ptrDoc->AddPosition(aufposbuch.s);
        }
    }
    else
    {
        aufposbuch.s.POSNR = PosNr;
        aufposbuch.Server(AasrvChangetextpos, PIPE_AE_SRV);
        if (aufposbuch.rc < SRV_OK)
            return;
        ptrDoc->UpdPosition(PosNr, aufposbuch.s);
    }
    //Kopfinformationen aktualisieren
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(
        aufposbuch.s.ANZPOS,
        aufposbuch.s.WERTAUFTRAG,
        aufposbuch.s.WERTLIEFERUNG,
        aufposbuch.s.WERTZEILEN,
        aufposbuch.s.BALANCE,
        aufposbuch.s.BALANCE2 );
    EndWaitCursor();

    CDialogMultiLang::OnOK();
}

void CDAufFrText::OnChangeEditAep()
{
    AllgWedDezimalKontr(&m_EditAEP,L_AUFPOSBUCH_PREISEKAPO,N_AUFPOSBUCH_PREISEKAPO);
}

void CDAufFrText::OnChangeEditBezei()
{
    AllgLaengeKontr(&m_EditBezeichnung, L_AUFPOSBUCH_ARTIKEL_NAME,AeGetApp()->Modus());
}

void CDAufFrText::OnChangeEditDarr()
{
    AllgLaengeKontr(&m_EditDarreichform, L_AUFPOSBUCH_DARREICHFORM,AeGetApp()->Modus());
}

void CDAufFrText::OnChangeEditDrabDm()
{
    AllgWedDezimalKontr(&m_EditDrabDM,L_AUFPOSBUCH_RABATTFESTDM-2,N_AUFPOSBUCH_RABATTFESTDM);
}

void CDAufFrText::OnChangeEditDrabProz()
{
    AllgWedDezimalKontr(&m_EditDrabProz,L_AUFPOSBUCH_RABATTFEST,N_AUFPOSBUCH_RABATTFEST);
}

void CDAufFrText::OnChangeEditEinheit()
{
    AllgLaengeKontr(&m_EditEinheit, L_AUFPOSBUCH_EINHEIT,AeGetApp()->Modus());
}

void CDAufFrText::OnChangeEditPorto()
{
    AllgWedDezimalKontr(&m_EditPorto,L_AUFPOSBUCH_PREISEKAPO-2,N_AUFPOSBUCH_PREISEKAPO);
}

void CDAufFrText::OnChangeEditGep()
{
    AllgWedDezimalKontr(&m_EditGEP,L_AUFPOSBUCH_PREISEKGROSSO-2,N_AUFPOSBUCH_PREISEKGROSSO);
}

void CDAufFrText::OnChangeEditMenge()
{
    AllgWertKontr(&m_EditMenge, MAXIMUM_BUCH_MENGE);
}

void CDAufFrText::OnChangeEditText()
{
    AllgLaengeKontr(&m_EditText, MAXIMUM_POS_BEM,AeGetApp()->Modus());
}

void CDAufFrText::OnRadioFakturieren()
{
    WPARAM button = GetCurrentMessage()->wParam;
    CheckRadioButton(IDC_RADIO10,IDC_RADIO14,button);
    if (IsDlgButtonChecked(IDC_RADIO12))
    {
        InitMitWert();
    }
    else
    {
        InitOhneWert();
    }
}

void CDAufFrText::InitOhneWert()
{
        m_EditGEP.SetWindowText("");
        m_EditPorto.SetWindowText("");
        m_EditDrabProz.SetWindowText("");
        m_EditDrabDM.SetWindowText("");
        m_EditAEP.SetWindowText("");
        CheckDlgButton(IDC_CHECK_RABATT,FALSE);
        m_EditGEP.EnableWindow(FALSE);
        m_EditPorto.EnableWindow(FALSE);
        m_EditDrabProz.EnableWindow(FALSE);
        m_EditDrabDM.EnableWindow(FALSE);
        m_EditAEP.EnableWindow(FALSE);
        m_ComboWg.EnableWindow(FALSE);
        m_ComboPriso.EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_RABATT)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_TAX)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_AEP)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_GEP)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PORTO)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_DRDM)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_DRPROZ)->EnableWindow(FALSE);
        m_ComboTax.EnableWindow(FALSE);
        if (m_cAArt == "SV")
        {
            GetDlgItem(IDC_BUTTON_DISPONIEREN)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
        }
        else
        {
            GetDlgItem(IDC_BUTTON_DISPONIEREN)->EnableWindow();
        }
        GetDlgItem(IDC_BUTTON_AUFNEHMEN)->EnableWindow();
        CheckDlgButton(IDC_CHECK_TAX,TRUE);
        m_ComboWg.SetCurSel(0);
}

void CDAufFrText::InitMitWert()
{
        m_EditGEP.EnableWindow();
        m_EditDrabProz.EnableWindow();
        m_EditDrabDM.EnableWindow();
        m_EditAEP.EnableWindow();
        m_ComboWg.EnableWindow();
        if (AeGetApp()->IsDE())
        {
            m_ComboPriso.EnableWindow();
        }
        GetDlgItem(IDC_CHECK_RABATT)->EnableWindow();
        GetDlgItem(IDC_CHECK_TAX)->EnableWindow();
        GetDlgItem(IDC_STATIC_AEP)->EnableWindow();
        GetDlgItem(IDC_STATIC_GEP)->EnableWindow();
        GetDlgItem(IDC_STATIC_DRDM)->EnableWindow();
        GetDlgItem(IDC_STATIC_DRPROZ)->EnableWindow();
        m_ComboTax.EnableWindow();
        GetDlgItem(IDC_BUTTON_DISPONIEREN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_AUFNEHMEN)->EnableWindow(FALSE);
        if (PosNr == -1)
        {
            m_EditPorto.EnableWindow();
            GetDlgItem(IDC_STATIC_PORTO)->EnableWindow();
        }
        else
        {
            m_EditPorto.SetWindowText("");
            m_EditPorto.EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_PORTO)->EnableWindow(FALSE);
        }
        GetDlgItem(IDC_BUTTON_AUFNEHMEN)->EnableWindow();
        CheckDlgButton(IDC_CHECK_TAX,TRUE);
        m_ComboWg.SetCurSel(0);
}

void CDAufFrText::OnButtonGeloescht()
{
    CString Geloescht;
    Geloescht = CResString::ex().getStrTblText(IDP_FRTEXT_GELOESCHT);
    GetDlgItem(IDC_EDIT_BEZEI)->SetWindowText(Geloescht);
    CheckRadioButton(IDC_RADIO10,IDC_RADIO14,IDC_RADIO13);
    InitOhneWert();
    OnOK();
}

void CDAufFrText::OnButtonDisponieren()
{
    CheckRadioButton(IDC_RADIO10,IDC_RADIO14,IDC_RADIO10);
    OnButtonSchliessen();
}

void CDAufFrText::OnButtonAufnehmen()
{
    OnButtonSchliessen();
}

void CDAufFrText::OnButtonInfotext()
{
    if (IsDlgButtonChecked(IDC_RADIO12))
    {
        if (MsgBoxYesNo(IDP_INFO_OHNE_WERT) == IDNO)
        {
            return;
        }
        else
        {
            InitOhneWert();
        }
    }
    CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO14);
    OnButtonSchliessen();
}
