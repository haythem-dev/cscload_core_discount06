// DQuotaKlasse.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include "DArtDef.h"
#include "DQuotaKlasse.h"


// CDQuotaKlasse-Dialogfeld

IMPLEMENT_DYNAMIC(CDQuotaKlasse, CDialog)
CDQuotaKlasse::CDQuotaKlasse(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDQuotaKlasse::IDD, pParent)
    , m_cArtikelnr(_T(""))
    , m_cKlasse(_T(""))
    , m_cMenge(_T(""))
    , m_cZeit(_T(""))
    , m_DT_Von(0)
    , m_DT_Bis(0)
    , m_bNoBatch(FALSE)
{
    m_bDafue = FALSE;
    m_iFunktion = 0;
    m_lArtikel = 0;
}

CDQuotaKlasse::~CDQuotaKlasse()
{
}

void CDQuotaKlasse::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ARTNR, m_edit_Artikelnr);
    DDX_Text(pDX, IDC_EDIT_ARTNR, m_cArtikelnr);
    DDX_Control(pDX, IDC_EDIT_KLASSE, m_edit_Klasse);
    DDX_Text(pDX, IDC_EDIT_KLASSE, m_cKlasse);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_edit_Menge);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_cMenge);
    DDX_CBString(pDX, IDC_COMBO_ZEIT, m_cZeit);
    DDX_Control(pDX, IDC_COMBO_ZEIT, m_combo_Zeit);
    DDX_Control(pDX, IDC_DT_VON, m_CT_Von);
    DDX_DateTimeCtrl(pDX, IDC_DT_VON, m_DT_Von);
    DDX_Control(pDX, IDC_DT_BIS, m_CT_Bis);
    DDX_DateTimeCtrl(pDX, IDC_DT_BIS, m_DT_Bis);
    DDX_DateTimeCtrl(pDX, IDC_DT_VON, m_DT_Von);
    DDX_DateTimeCtrl(pDX, IDC_DT_BIS, m_DT_Bis);
    DDX_Check(pDX, IDC_CHECK_NOBATCH, m_bNoBatch);
}


BEGIN_MESSAGE_MAP(CDQuotaKlasse, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_ARTNR, OnBnClickedButtonArtnr)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_EN_CHANGE(IDC_EDIT_ARTNR, OnEnChangeEditArtnr)
    ON_EN_CHANGE(IDC_EDIT_KLASSE, OnEnChangeEditKlasse)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnEnChangeEditMenge)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnBnClickedButtonUpd)
    ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDQuotaKlasse::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CDQuotaKlasse-Meldungshandler

void CDQuotaKlasse::OnBnClickedButtonArtnr()
{
    CDArtDef dlgArtDef;
    dlgArtDef.m_CMatchCode = m_CArt;
    m_CArt.Empty();
    if (dlgArtDef.DoModal() != IDOK)
    {
        m_lArtikel = 0L;
        return;
    }
    m_lArtikel = dlgArtDef.GetArtNr();
    m_cArtikelnr = dlgArtDef.GetArticleCode();
    GetDlgItem(IDC_EDIT_ARTNR)->SetWindowText(m_cArtikelnr);
}

void CDQuotaKlasse::OnBnClickedOk()
{
    m_sFunktion = 0;
    UpdateInsert();
}

void CDQuotaKlasse::UpdateInsert()
{
    UpdateData();
    if (m_cMenge.IsEmpty())
    {
        MsgBoxOK(IDP_MENGE_EINGEBEN);
        m_edit_Menge.SetFocus();
        return;
    }
    if (m_cArtikelnr.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        m_edit_Artikelnr.SetFocus();
        return;
    }
    CARTAESEL artaesel;
    BeginWaitCursor();
    strcpy(artaesel.s.ARTICLE_CODE, m_cArtikelnr);
    artaesel.Server(AatartSel_NoByCode);
    EndWaitCursor();
    if (artaesel.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_Artikelnr.SetFocus();
        return;
    }
    m_lArtikel = artaesel.s.ARTIKEL_NR;
    CMAXARTICLEQUOTA max;
    max.SetArticleno(m_lArtikel);
    if (!max.SelMax())
    {
        if (max.GetMaxquota() < atol(m_cMenge))
        {
            CString CStr;
            CStr.Format(CResString::ex().getStrTblText(AETXT_MAX_QUOTA), max.GetMaxquota());
            MsgBoxOK(CStr);
            return;
        }
    }
    if (m_iFunktion == 1)
    {
        m_Quota.SetKzkdklasse(m_cKlasse);
    }
    else
    {
        CString cKlasse;

        cKlasse = m_cKlasse;
        cKlasse += "%";
        m_Quota.SetKzkdklasse(cKlasse);
    }
    m_Quota.SetBranchno(AeGetApp()->VzNr());
    m_Quota.SetArticleno(m_lArtikel);
    m_Quota.SetQuota(atol(m_cMenge));
    if (m_DT_Von.GetTime() > m_DT_Bis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DT_VON));
        return;
    }
    m_Quota.SetDatefrom(m_DT_Von.GetYear() * 10000
                      + m_DT_Von.GetMonth()*100
                      + m_DT_Von.GetDay());
    m_Quota.SetDateto(m_DT_Bis.GetYear()*10000
                    + m_DT_Bis.GetMonth()*100
                    + m_DT_Bis.GetDay());
    if (m_combo_Zeit.GetCurSel() == 0)
        m_Quota.SetValidity('M');
    else if (m_combo_Zeit.GetCurSel() == 1)
        m_Quota.SetValidity('W');
    else
        m_Quota.SetValidity('T');
    m_Quota.SetUid_anlage(GetAeUser().GetUID());
    if (m_bDafue)
        m_Quota.SetSdafuequota('1');
    else
        m_Quota.SetSdafuequota(' ');
    if (m_bNoBatch)
        m_Quota.SetSnobatchchange('1');
    else
        m_Quota.SetSnobatchchange(' ');
    if (m_sFunktion == 0)
    {
        if (m_iFunktion == 1)
        {
            if (!m_Quota.InsertKundeEKG())
            {
                CString CStr;
                CStr.Format(CResString::ex().getStrTblText(AETXT_INSERTED), m_Quota.GetCustomerno());
                MsgBoxOK(CStr);
            }
        }
        else
        {
            if (IsDlgButtonChecked(IDC_CHECK_INTERN))
            {
                if (!m_Quota.InsertKlasse09())
                {
                    CString CStr;
                    CStr.Format(CResString::ex().getStrTblText(AETXT_INSERTED), m_Quota.GetCustomerno());
                    MsgBoxOK(CStr);
                }
            }
            else
            {
                if (!m_Quota.InsertKlasse())
                {
                    CString CStr;
                    CStr.Format(CResString::ex().getStrTblText(AETXT_INSERTED), m_Quota.GetCustomerno());
                    MsgBoxOK(CStr);
                }
            }
        }
    }
    else
    {
        if (m_iFunktion == 1)
        {
            if (!m_Quota.UpdateKundeEKG())
            {
                CString CStr;
                CStr.Format(CResString::ex().getStrTblText(AETXT_UPDATED), m_Quota.GetCustomerno());
                MsgBoxOK(CStr);
            }
        }
        else
        {
            if (IsDlgButtonChecked(IDC_CHECK_INTERN))
            {
                if (!m_Quota.UpdateQuota09())
                {
                    CString CStr;
                    CStr.Format(CResString::ex().getStrTblText(AETXT_UPDATED), m_Quota.GetCustomerno());
                    MsgBoxOK(CStr);
                }
            }
            else
            {
                if (!m_Quota.UpdateQuota())
                {
                    CString CStr;
                    CStr.Format(CResString::ex().getStrTblText(AETXT_UPDATED), m_Quota.GetCustomerno());
                    MsgBoxOK(CStr);
                }
            }
        }
    }
}

BOOL CDQuotaKlasse::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_MONAT));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_WOCHE));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_TAG));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_UNBEGRENZT));
    m_combo_Zeit.SetCurSel(0);
    GetDlgItem(IDC_STATIC_KIND)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);

    if (m_iFunktion == 1)
    {
        GetDlgItem(IDC_STATIC_KLASSE)->SetWindowText(CResString::ex().getStrTblText(AETXT_EKGRUPPE));
        GetDlgItem(IDC_STATIC_PCT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_INTERN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_INTERN)->EnableWindow(FALSE);
        this->SetWindowText(CResString::ex().getStrTblText(AETXT_QUOTA_KND_EKG));
    }
    else
    {
        GetDlgItem(IDC_BUTTON_DEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
    }

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_DT_Von = CTimeFromDateLongMaxTime(zeit.s.DATUM);
    m_DT_Bis = CTime(2099, 12, 31, 23, 59, 59);

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDQuotaKlasse::OnEnChangeEditArtnr()
{
    CString str;

    m_edit_Artikelnr.GetWindowText(str);                //PZN lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CArt = str;
        OnBnClickedButtonArtnr();
        GetDlgItem(IDC_EDIT_ARTNR)->SetWindowText(m_cArtikelnr);
        m_edit_Klasse.SetFocus();
        m_edit_Klasse.SetSel(0, -1, FALSE);
        m_edit_Klasse.SetSel(-1, 0, FALSE);             //Selektion aufheben
    }
}

void CDQuotaKlasse::OnEnChangeEditKlasse()
{
    AllgLaengeKontr(&m_edit_Klasse, m_iFunktion == 1 ? 3 : 2, AeGetApp()->Modus());
}

void CDQuotaKlasse::OnEnChangeEditMenge()
{
    AllgWertKontr(&m_edit_Menge, MAXIMUM_BUCH_MENGE);
}

void CDQuotaKlasse::OnBnClickedButtonUpd()
{
    m_sFunktion = 1;
    UpdateInsert();
}

void CDQuotaKlasse::OnBnClickedRadio1()
{
    m_bDafue = (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) == IDC_RADIO1) ? FALSE : TRUE;
}

void CDQuotaKlasse::OnBnClickedButtonDel()
{
    UpdateData();
    CARTAESEL artaesel;
    BeginWaitCursor();
    strcpy(artaesel.s.ARTICLE_CODE, m_cArtikelnr);
    artaesel.Server(AatartSel_NoByCode);
    EndWaitCursor();
    if (artaesel.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_Artikelnr.SetFocus();
        return;
    }
    m_lArtikel = artaesel.s.ARTIKEL_NR;
    m_Quota.SetBranchno(AeGetApp()->VzNr());
    m_Quota.SetArticleno(m_lArtikel);
    m_Quota.SetKzkdklasse(m_cKlasse);
    if (!m_Quota.DeleteKundeEKG())
    {
        CString CStr;
        CStr.Format(CResString::ex().getStrTblText(AETXT_DELETED), m_Quota.GetCustomerno());
        MsgBoxOK(CStr);
    }
}
