// DArtikelQuota.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include <kndsel.h>
#include "DKndInf.h"
#include "DKndWahl.h"
#include "DArtInf.h"
#include "DArtDef.h"
#include "DDruckAuftrag.h"
#include "DArtikelQuota.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS 13

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_RIGHT,
    2,  "",  90, LVCFMT_LEFT,
    3,  "", 120, LVCFMT_LEFT,
    4,  "",  90, LVCFMT_LEFT,
    5,  "", 120, LVCFMT_LEFT,
    6,  "",  60, LVCFMT_RIGHT,
    7,  "",  60, LVCFMT_RIGHT,
    8,  "",  60, LVCFMT_LEFT,
    9,  "",  70, LVCFMT_LEFT,
    10, "",  70, LVCFMT_LEFT,
    11, "",   0, LVCFMT_RIGHT,
    12, "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};

// CDArtikelQuota-Dialogfeld

IMPLEMENT_DYNAMIC(CDArtikelQuota, CDialog)
CDArtikelQuota::CDArtikelQuota(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDArtikelQuota::IDD, pParent)
    , m_cArtikel(_T(""))
    , m_cKunde(_T(""))
    , m_cMenge(_T(""))
    , m_cZeit(_T(""))
    , m_CKunde2(_T(""))
    , m_bNoBatch(FALSE)
{
    m_lArtNr = 0;
    m_lKndNr = 0;
    m_lKunde = 0;
    m_lKunde2 = 0;
    m_bDafue = FALSE;
    m_bEKG = FALSE;
}

CDArtikelQuota::~CDArtikelQuota()
{
}

void CDArtikelQuota::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_ARTKELNR, m_cArtikel);
    DDX_Text(pDX, IDC_EDIT_KUNDE, m_cKunde);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_cMenge);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_EDIT_KUNDE, m_edit_Kunde);
    DDX_Control(pDX, IDC_EDIT_ARTKELNR, m_edit_Artikel);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_edit_Menge);
    DDX_Control(pDX, IDC_COMBO_ZEIT, m_combo_Zeit);
    DDX_CBString(pDX, IDC_COMBO_ZEIT, m_cZeit);
    DDX_Control(pDX, IDC_EDIT_KUNDE2, m_edit_Kunde2);
    DDX_Text(pDX, IDC_EDIT_KUNDE2, m_CKunde2);
    DDX_Control(pDX, IDC_CHECK_NOBATCH, m_CB_NoBatch);
    DDX_Check(pDX, IDC_CHECK_NOBATCH, m_bNoBatch);
}


BEGIN_MESSAGE_MAP(CDArtikelQuota, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnBnClickedButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnBnClickedButtonKnd)
    ON_BN_CLICKED(IDC_BUTTON_ART, OnBnClickedButtonArt)
    ON_EN_CHANGE(IDC_EDIT_KUNDE, OnEnChangeEditKunde)
    ON_EN_CHANGE(IDC_EDIT_ARTKELNR, OnEnChangeEditArtkelnr)
    ON_BN_CLICKED(IDC_BUTTON_DEL_ALL_KND, OnBnClickedButtonDelAllKnd)
    ON_BN_CLICKED(IDC_BUTTON_DEL_ALL_ART, OnBnClickedButtonDelAllArt)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_BUTTON_COPY, OnBnClickedButtonCopy)
    ON_EN_CHANGE(IDC_EDIT_KUNDE2, OnEnChangeEditKunde2)
    ON_BN_CLICKED(IDC_BUTTON_COPY2, OnBnClickedButtonCopy2)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnBnClickedButtonDruck)
    ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_BUTTON_ALL_NOBATCH, OnBnClickedButtonAllNobatch)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CDArtikelQuota-Meldungshandler

BOOL CDArtikelQuota::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_BEZOGEN);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_ZEITRAUM);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Columns[10].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Columns[11].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[12].Columns = CResString::ex().getStrTblText(AETXT_NOBATCH);
    if (m_bEKG)
    {
        Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KURZ_EKG);
        Columns[2].Columns = CResString::ex().getStrTblText(AETXT_EKGRUPPE);
    }
    else
    {
        Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
        Columns[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    }
    if (m_bEKG)
    {
        GetDlgItem(IDC_STATIC_IDF)->SetWindowText(CResString::ex().getStrTblText(AETXT_EKGRUPPE));
        GetDlgItem(IDC_BUTTON_DEL_ALL_KND)->SetWindowText(CResString::ex().getStrTblText(AETXT_DEL_ALL_EKG));
        GetDlgItem(IDC_BUTTON_DEL_ALL_ART)->SetWindowText(CResString::ex().getStrTblText(AETXT_DEL_QUOTA));
        CString CStr;
        CStr = CResString::ex().getStrTblText(AETXT_PFLEGE_QUOTA_EKG);
        this->SetWindowText(CStr);
    }
    CenterWindow();

    char cParent[81];
    char cAct[81];
    CWnd* parent;
    parent = this->GetParent();
    this->GetWindowText((LPTSTR)cAct,80);
    GetClassName(parent->m_hWnd,(LPTSTR)cParent,80);
    GetClassName(this->m_hWnd,(LPTSTR)cAct,80);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_MONAT));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_WOCHE));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_TAG));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_UNBEGRENZT));
    m_combo_Zeit.SetCurSel(0);

    GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_COPY)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_KUNDE2)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_KUNDE2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_KND)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_KND)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_ART)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_KIND)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
    /*if (m_bDafue)
        CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO2);
    else
        CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
    */
    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDArtikelQuota::OnBnClickedOk()
{
    UpdateData();
    if (m_cKunde.IsEmpty() && m_cArtikel.IsEmpty())
    {
        if (m_bEKG)
        {
            MsgBoxOK(AETXT_ART_EKG_EING);
            return;
        }
        else
        {
            MsgBoxOK(AETXT_ART_KND_EING);
            return;
        }
    }
    m_lKndNr = 0;
    m_lArtNr = 0;
    m_cEKG.Empty();
    if (!m_cKunde.IsEmpty())
    {
        if (m_bEKG)
        {
            m_cEKG = m_cKunde;
        }
        else
        {
            m_lKndNr = atol(m_cKunde);
        }
    }
    if (!m_cArtikel.IsEmpty())
    {
        CARTAESEL code;
        strcpy(code.s.ARTICLE_CODE,m_cArtikel);
        BeginWaitCursor();
        code.Server( AatartSel_NoByCode );
        EndWaitCursor();
        m_lArtNr = code.s.ARTIKEL_NR;
    }
    GetPage();
}

void CDArtikelQuota::OnBnClickedButtonInsert()
{
    UpdateData();
    CDArtikelQuotaUpd dlgArtikelQuotaUpd;
    dlgArtikelQuotaUpd.m_bUpdate = FALSE;
    dlgArtikelQuotaUpd.m_bEKG = m_bEKG;
    dlgArtikelQuotaUpd.m_CKunde = m_cKunde;
    dlgArtikelQuotaUpd.m_CArtikel = m_cArtikel;
    dlgArtikelQuotaUpd.m_CMenge = m_cMenge;
    dlgArtikelQuotaUpd.m_iZeitraum = m_combo_Zeit.GetCurSel();
    if (dlgArtikelQuotaUpd.DoModal() == IDCANCEL) return;
    BeginWaitCursor();
    CARTAESEL code;
    strcpy(code.s.ARTICLE_CODE, dlgArtikelQuotaUpd.m_CArtikel);
    code.s.CODE_TYPE = 0;
    code.Server(AatartSel_NoByCode);
    if (code.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_Artikel.SetFocus();
        EndWaitCursor();
        return;
    }
    EndWaitCursor();
    m_cKunde = dlgArtikelQuotaUpd.m_CKunde;

    SetValidity(dlgArtikelQuotaUpd.m_iZeitraum);

    if (m_bEKG)
    {
        m_QuotaEKG.SetBranchno(AeGetApp()->VzNr());
        m_QuotaEKG.SetPharmacygroupid(dlgArtikelQuotaUpd.m_CKunde);
        m_QuotaEKG.SetArticleno(code.s.ARTIKEL_NR);
        m_QuotaEKG.SetQuota(atol(dlgArtikelQuotaUpd.m_CMenge));
        m_QuotaEKG.SetKumqty(0);
        m_QuotaEKG.SetDatefrom(dlgArtikelQuotaUpd.m_lDatumvon);
        m_QuotaEKG.SetDateto(dlgArtikelQuotaUpd.m_lDatumbis);
        m_QuotaEKG.SetUid_anlage(GetAeUser().GetUID());
        m_QuotaEKG.SetSnobatchchange(dlgArtikelQuotaUpd.m_bNoBatch ? '1' : ' ');
        if (m_QuotaEKG.Insert() == 0)
        {
            m_lArtNr = code.s.ARTIKEL_NR;
            m_cEKG = m_cKunde;
        }
    }
    else
    {
        m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
        m_ArtikelQuota.SetCustomerno(atol(dlgArtikelQuotaUpd.m_CKunde));
        m_ArtikelQuota.SetPharmacygroupid(" ");
        m_ArtikelQuota.SetArticleno(code.s.ARTIKEL_NR);
        m_ArtikelQuota.SetQuota(atol(dlgArtikelQuotaUpd.m_CMenge));
        m_ArtikelQuota.SetKumqty(0);
        m_ArtikelQuota.SetDatefrom(dlgArtikelQuotaUpd.m_lDatumvon);
        m_ArtikelQuota.SetDateto(dlgArtikelQuotaUpd.m_lDatumbis);
        m_ArtikelQuota.SetUid_anlage(GetAeUser().GetUID());
        m_ArtikelQuota.SetSdafuequota(' ');
        m_ArtikelQuota.SetSnobatchchange(dlgArtikelQuotaUpd.m_bNoBatch ? '1' : ' ');
        if (m_ArtikelQuota.Insert() == 0)
        {
            m_lArtNr = code.s.ARTIKEL_NR;
            m_lKndNr = atol(m_cKunde);
        }
    }

    GetPage();
}

void CDArtikelQuota::SetValidity(int timeRange)
{
    char validity;
    switch (timeRange)
    {
    case 0:
        validity = 'M';
        break;
    case 1:
        validity = 'W';
        break;
    case 2:
        validity = 'T';
        break;
    default:
        validity = 'U';
        break;
    }

    if (m_bEKG)
    {
        m_QuotaEKG.SetValidity(validity);
    }
    else
    {
        m_ArtikelQuota.SetValidity(validity);
    }
}

void CDArtikelQuota::OnBnClickedButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDArtikelQuotaUpd dlgArtikelQuotaUpd;
        dlgArtikelQuotaUpd.m_bUpdate = TRUE;
        dlgArtikelQuotaUpd.m_bEKG = m_bEKG;
        dlgArtikelQuotaUpd.m_CKunde = m_ListCtl.GetItemText(pos, 1);
        dlgArtikelQuotaUpd.m_CArtikel = m_ListCtl.GetItemText(pos, 3);
        dlgArtikelQuotaUpd.m_CMenge = m_ListCtl.GetItemText(pos, 6);
        dlgArtikelQuotaUpd.m_bNoBatch = (m_ListCtl.GetItemText(pos, 12) == "1") ? TRUE : FALSE;
        if (m_ListCtl.GetItemText(pos, 8) == CResString::ex().getStrTblText(AETXT_MONAT))
        {
            dlgArtikelQuotaUpd.m_iZeitraum = 0;
        }
        else if (m_ListCtl.GetItemText(pos, 8) == CResString::ex().getStrTblText(AETXT_WOCHE))
        {
            dlgArtikelQuotaUpd.m_iZeitraum = 1;
        }
        else if (m_ListCtl.GetItemText(pos, 8) == CResString::ex().getStrTblText(AETXT_TAG))
        {
            dlgArtikelQuotaUpd.m_iZeitraum = 2;
        }
        else
        {
            dlgArtikelQuotaUpd.m_iZeitraum = 3;
        }
        dlgArtikelQuotaUpd.m_lDatumvon = atol(m_ListCtl.GetItemText(pos, 9).Left(2))
                        + atol(m_ListCtl.GetItemText(pos, 9).Mid(3,2)) * 100
                        + atol(m_ListCtl.GetItemText(pos, 9).Right(4)) * 10000;
        dlgArtikelQuotaUpd.m_lDatumbis = atol(m_ListCtl.GetItemText(pos, 10).Left(2))
                        + atol(m_ListCtl.GetItemText(pos, 10).Mid(3,2)) * 100
                        + atol(m_ListCtl.GetItemText(pos, 10).Right(4)) * 10000;
        if (dlgArtikelQuotaUpd.DoModal() == IDCANCEL) return;
        BeginWaitCursor();
        CARTAESEL code;
        strcpy(code.s.ARTICLE_CODE, dlgArtikelQuotaUpd.m_CArtikel);
        code.s.CODE_TYPE = 0;
        code.Server( AatartSel_NoByCode );
        if (code.rc != SRV_OK)
        {
            MsgBoxOK(AETXT_NO_ARTICLECODE);
            m_edit_Artikel.SetFocus();
            EndWaitCursor();
            return;
        }
        EndWaitCursor();

        SetValidity(dlgArtikelQuotaUpd.m_iZeitraum);

        if (m_bEKG)
        {
            m_QuotaEKG.SetBranchno(AeGetApp()->VzNr());
            m_QuotaEKG.SetPharmacygroupid(m_ListCtl.GetItemText(pos, 1));
            m_QuotaEKG.SetArticleno(code.s.ARTIKEL_NR);
            m_QuotaEKG.SetQuota(atol(dlgArtikelQuotaUpd.m_CMenge));
            m_QuotaEKG.SetKumqty(atol(m_ListCtl.GetItemText(pos, 7)));
            m_QuotaEKG.SetDatefrom(dlgArtikelQuotaUpd.m_lDatumvon);
            m_QuotaEKG.SetDateto(dlgArtikelQuotaUpd.m_lDatumbis);
            m_QuotaEKG.SetUid_anlage(GetAeUser().GetUID());
            if (m_QuotaEKG.Update() == 0)
                GetPage();
        }
        else
        {
            m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
            m_ArtikelQuota.SetCustomerno(atol(m_ListCtl.GetItemText(pos, 1)));
            m_ArtikelQuota.SetPharmacygroupid(" ");
            m_ArtikelQuota.SetArticleno(code.s.ARTIKEL_NR);
            m_ArtikelQuota.SetQuota(atol(dlgArtikelQuotaUpd.m_CMenge));
            m_ArtikelQuota.SetKumqty(atol(m_ListCtl.GetItemText(pos, 7)));
            m_ArtikelQuota.SetUid_anlage(GetAeUser().GetUID());
            m_ArtikelQuota.SetDatefrom(dlgArtikelQuotaUpd.m_lDatumvon);
            m_ArtikelQuota.SetDateto(dlgArtikelQuotaUpd.m_lDatumbis);
            m_ArtikelQuota.SetSdafuequota(m_bDafue ? '1' : ' ');
            if (m_ArtikelQuota.Update() == 0)
                GetPage();
        }
    }
}

void CDArtikelQuota::OnBnClickedButtonDelete()
{
    UpdateData();
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CMAXARTICLEQUOTA max;
        BeginWaitCursor();
        CARTAESEL code;
        strcpy(code.s.ARTICLE_CODE,m_ListCtl.GetItemText(pos, 3));
        code.s.CODE_TYPE = 0;
        code.Server( AatartSel_NoByCode );
        if (code.rc != SRV_OK)
        {
            MsgBoxOK(AETXT_NO_ARTICLECODE);
            m_edit_Artikel.SetFocus();
            EndWaitCursor();
            return;
        }
        EndWaitCursor();
        max.SetArticleno(code.s.ARTIKEL_NR);
        if (!max.SelMax())
        {
            MsgBoxOK(AETXT_NO_DEL);
            return;
        }
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            if (m_bEKG)
            {
                m_QuotaEKG.SetBranchno(AeGetApp()->VzNr());
                m_QuotaEKG.SetPharmacygroupid(m_ListCtl.GetItemText(pos, 1));
                m_QuotaEKG.SetArticleno(code.s.ARTIKEL_NR);
                if (m_QuotaEKG.Delete() == 0)
                    GetPage();
            }
            else
            {
                m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
                m_ArtikelQuota.SetCustomerno(atol(m_ListCtl.GetItemText(pos, 1)));
                m_ArtikelQuota.SetArticleno(code.s.ARTIKEL_NR);
                m_ArtikelQuota.SetSdafuequota(m_bDafue ? '1' : ' ');
                if (m_ArtikelQuota.Delete() == 0)
                    GetPage();
            }
        }
    }
}

void CDArtikelQuota::OnBnClickedButtonKnd()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        m_lKunde = 0;
        return;
    }
    m_lKunde = dlgKndWahl.GetIdfNr();
    m_CMC.Empty();
}

void CDArtikelQuota::OnBnClickedButtonArt()
{
    CDArtDef dlgArtDef;
    dlgArtDef.m_CMatchCode = m_CArt;
    m_CArt.Empty();
    if (dlgArtDef.DoModal() != IDOK)
    {
        m_lArtikel = 0;
        return;
    }
    m_CArt = dlgArtDef.GetArticleCode();
    m_CArt.TrimRight(' ');
    m_lArtikel = dlgArtDef.GetArtNr();
}

void CDArtikelQuota::OnEnChangeEditKunde()
{
    CString str;
    m_edit_Kunde.GetWindowText(str);            //IDF lesen
    if (str.IsEmpty())
        return;                                 //Feld ist leer
    char chN = str[str.GetLength() -1];         //letztes Zeichen lesen
    if (m_bEKG)
    {
        AllgLaengeKontr(&m_edit_Kunde, L_ARTICLEQUOTAEKG_PHARMACYGROUPID,AeGetApp()->Modus());
    }
    else
    {
        if ((str.GetLength()) == 1 && !isdigit(chN))
        {
            m_CMC = str;
            OnBnClickedButtonKnd();
            m_cKunde.Format("%ld",m_lKunde);
            GetDlgItem(IDC_EDIT_KUNDE)->SetWindowText(m_cKunde);
            m_edit_Kunde.SetFocus();
            m_edit_Kunde.SetSel( 0, -1, FALSE );
            m_edit_Kunde.SetSel( -1, 0, FALSE );        //Selektion aufheben
            return;
        }
        AllgWertKontr(&m_edit_Kunde, MAXIMUM_IDF);
    }
}

void CDArtikelQuota::OnEnChangeEditArtkelnr()
{
    CString str;
    m_edit_Artikel.GetWindowText(str);                  //PZN lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() -1];                 //letztes Zeichen lesen
    if ((str.GetLength() == 1) && !isdigit(chN))
    {
        m_CArt = str;
        OnBnClickedButtonArt();
        //m_cArtikel.Format("%ld",m_lArtikel);
        GetDlgItem(IDC_EDIT_ARTKELNR)->SetWindowText(m_CArt);
        m_edit_Artikel.SetFocus();
        m_edit_Artikel.SetSel( 0, -1, FALSE );
        m_edit_Artikel.SetSel( -1, 0, FALSE );          //Selektion aufheben
        return;
    }
    //AllgWertKontr(&m_edit_Artikel, MAXIMUM_ART_NR);
}

void CDArtikelQuota::GetPage()
{
    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;
    //

    char Out1[11];
    char Out2[11];
    ppString cApo;
    ppString cEKG;
    ppString cEKGName;
    ppString cArtikel;
    ppString cEinheit;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    CARTAESEL artaesel;
    BeginWaitCursor();
    if (m_bEKG)
    {
        m_QuotaEKG.SetBranchno(AeGetApp()->VzNr());
        m_QuotaEKG.SetPharmacygroupid(m_cEKG);
        m_QuotaEKG.SetArticleno(m_lArtNr);
        m_QuotaEKG.SetSnobatchchange(m_bNoBatch ? '1' : ' ');
    }
    else
    {
        m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
        m_ArtikelQuota.SetCustomerno(m_lKndNr);
        m_ArtikelQuota.SetArticleno(m_lArtNr);
        m_ArtikelQuota.SetSdafuequota(m_bDafue ? '1' : ' ');
        m_ArtikelQuota.SetSnobatchchange(m_bNoBatch ? '1' : ' ');
    }
    CLetterMan kb;
    for (int sw = 0;sw == 0;)
    {
        if (m_bEKG)
        {
            if (m_lArtNr != 0)
            {
                if (m_QuotaEKG.SelArticle())
                    break;
            }
            else
            {
                if (m_QuotaEKG.SelListEKG() != SRV_OK)
                    break;
            }
            s[0] = kb.Next();
            s[1] = m_QuotaEKG.GetPharmacygroupid(cEKG);
            s[2] = m_QuotaEKG.GetGroup_name(cEKGName);
            artaesel.s.ARTIKEL_NR = m_QuotaEKG.GetArticleno();
            artaesel.Server( AatartSel_Preferred );
            AllgEntfSpaces(artaesel.s.ARTICLE_CODE);
            s[3] = artaesel.s.ARTICLE_CODE;
            s[4] = m_QuotaEKG.GetEinheit(cEinheit);
            s[5] = m_QuotaEKG.GetArtikel_name(cArtikel);
            s[6].Format("%d", m_QuotaEKG.GetQuota());
            s[7].Format("%d", m_QuotaEKG.GetKumqty());
            s[8] = GetTimeRangeHeader(m_QuotaEKG.GetValidity());
            AllgDatumLong2CharTTMMJJJJ(m_QuotaEKG.GetDatefrom(), Out1);
            s[9] = Out1;
            AllgDatumLong2CharTTMMJJJJ(m_QuotaEKG.GetDateto(), Out2);
            s[10] = Out2;
            s[11].Format("%d", m_QuotaEKG.GetArticleno());
            s[12].Format("%c", m_QuotaEKG.GetSnobatchchange());
        }
        else
        {
            if (m_lKndNr != 0)
            {
                if (m_lArtNr != 0)
                {
                    if (m_ArtikelQuota.SelQuota())
                        break;
                    sw = 1;
                }
                else
                {
                    if (m_ArtikelQuota.SelListKnd() != SRV_OK)
                        break;
                    GetDlgItem(IDC_BUTTON_COPY)->EnableWindow();
                    GetDlgItem(IDC_BUTTON_COPY)->ShowWindow(SW_SHOW);
                }
            }
            else
            {
                if (m_ArtikelQuota.SelListArt() != SRV_OK)
                    break;
            }
            s[0] = kb.Next();
            s[1].Format("%d", m_ArtikelQuota.GetCustomerno());
            s[2] = m_ArtikelQuota.GetMatchcode(cApo);
            artaesel.s.ARTIKEL_NR = m_ArtikelQuota.GetArticleno();
            artaesel.Server(AatartSel_Preferred);
            AllgEntfSpaces(artaesel.s.ARTICLE_CODE);
            s[3] = artaesel.s.ARTICLE_CODE;
            s[4] = m_ArtikelQuota.GetEinheit(cEinheit);
            s[5] = m_ArtikelQuota.GetArtikel_name(cArtikel);
            s[6].Format("%d", m_ArtikelQuota.GetQuota());
            s[7].Format("%d", m_ArtikelQuota.GetKumqty());
            s[8] = GetTimeRangeHeader(m_ArtikelQuota.GetValidity());
            if (m_ArtikelQuota.GetDatefrom() == 0)
            {
                s[9].Empty();
            }
            else
            {
                AllgDatumLong2CharTTMMJJJJ(m_ArtikelQuota.GetDatefrom(), Out1);
                s[9] = Out1;
            }
            if (m_ArtikelQuota.GetDateto() == 0)
            {
                s[10].Empty();
            }
            else
            {
                AllgDatumLong2CharTTMMJJJJ(m_ArtikelQuota.GetDateto(), Out2);
                s[10] = Out2;
            }
            s[11].Format("%d", m_ArtikelQuota.GetArticleno());
            s[12].Format("%c", m_ArtikelQuota.GetSnobatchchange());
        }

        // wichtig für Sort
        lvi.lParam = (LPARAM)m_ListCtl.GetItemCount();

        if (!CListCtrlHelper::InsertItem(m_ListCtl, NUM_COLUMNS, s, lvi))
        {
            EndWaitCursor();
            return;
        }
        // wichtig für Sort
        ++lvi.iItem;
    }
    if (m_bEKG)
    {
        m_QuotaEKG.CloseCursor();
    }
    else
    {
        m_ArtikelQuota.CloseCursor();
    }
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK( IDP_NO_DATA );
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

/*static*/
CString CDArtikelQuota::GetTimeRangeHeader(char validity)
{
    switch (validity)
    {
    case 'M':
        return CResString::ex().getStrTblText(AETXT_MONAT).GetString();
    case 'W':
        return CResString::ex().getStrTblText(AETXT_WOCHE).GetString();
    case 'T':
        return CResString::ex().getStrTblText(AETXT_TAG).GetString();
    default:
        return CResString::ex().getStrTblText(AETXT_UNBEGRENZT).GetString();
    }
}

void CDArtikelQuota::OnBnClickedButtonDelAllKnd()
{
    UpdateData();
    if (m_bEKG)
    {
        if (m_cEKG.IsEmpty())
        {
            if (!m_cKunde.IsEmpty())
            {
                m_cEKG = m_cKunde;
            }
            else
            {
                MsgBoxOK(IDP_MUSS_EKG);
                return;
            }
        }
    }
    else
    {
        if (m_lKndNr == 0)
        {
            if (!m_cKunde.IsEmpty())
            {
                m_lKndNr = atol(m_cKunde);
            }
            else
            {
                MsgBoxOK(IDP_MUSS_KUNDENNR);
                return;
            }
        }
    }
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
    {
        if (m_bEKG)
        {
            m_QuotaEKG.SetBranchno(AeGetApp()->VzNr());
            m_QuotaEKG.SetPharmacygroupid(m_cEKG);
            m_QuotaEKG.SetArticleno(m_lArtNr);
            if (m_QuotaEKG.DeleteAllEKG() == 0)
                GetPage();
        }
        else
        {
            m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
            m_ArtikelQuota.SetCustomerno(m_lKndNr);
            m_ArtikelQuota.SetArticleno(m_lArtNr);
            m_ArtikelQuota.SetSdafuequota(m_bDafue ? '1' : ' ');
            if (m_ArtikelQuota.DeleteAllKnd() == 0)
                GetPage();
        }
    }
}

void CDArtikelQuota::OnBnClickedButtonDelAllArt()
{
    UpdateData();
    CARTAESEL artaesel;
    BeginWaitCursor();
    strcpy(artaesel.s.ARTICLE_CODE,m_cArtikel);
    artaesel.Server( AatartSel_NoByCode );
    EndWaitCursor();
    if (artaesel.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_Artikel.SetFocus();
        return;
    }
    m_lArtNr = artaesel.s.ARTIKEL_NR;
    CMAXARTICLEQUOTA max;
    max.SetArticleno(m_lArtNr);
    if (!max.SelMax())
    {
        MsgBoxOK(AETXT_NO_DEL);
        return;
    }
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
    {
        if (m_bEKG)
        {
            m_QuotaEKG.SetBranchno(AeGetApp()->VzNr());
            m_QuotaEKG.SetArticleno(m_lArtNr);
            if (m_QuotaEKG.Delete() == 0)
                GetPage();
        }
        else
        {
            m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
            m_ArtikelQuota.SetArticleno(m_lArtNr);
            m_ArtikelQuota.SetSdafuequota(m_bDafue ? '1' : ' ');
            if (m_ArtikelQuota.DeleteAllArt() == 0)
                GetPage();
        }
    }
}

LRESULT CDArtikelQuota::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        if (m_bEKG)
        {
            return 0L;
        }

        //Ausgabe der Kundeninformationen
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString str = m_ListCtl.GetItemText(pos, 1);
            long kndNr = atol(str);
            CKndInf dlgKndInf;
            dlgKndInf.SetIdfNr(kndNr);
            dlgKndInf.SetKndNr(kndNr);
            dlgKndInf.SetKndVz(AeGetApp()->VzNr());
            dlgKndInf.DoModal();
        }
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString str = m_ListCtl.GetItemText(pos, 11);
            long artNr = atol(str);
            CDArtInf dlgArtInf;
            dlgArtInf.SetArtNr(artNr);
            dlgArtInf.SetFilialNr(AeGetApp()->VzNr());
            dlgArtInf.DoModal();
        }
        return 1L;
    }
   return 0L;
}

void CDArtikelQuota::OnBnClickedButtonCopy()
{
    GetDlgItem(IDC_EDIT_KUNDE2)->EnableWindow();
    GetDlgItem(IDC_EDIT_KUNDE2)->ShowWindow(SW_SHOW);
    m_edit_Kunde2.SetFocus();
    m_edit_Kunde2.SetSel(0, -1, FALSE);
    m_edit_Kunde2.SetSel(-1, 0, FALSE);               //Selektion aufheben
}

void CDArtikelQuota::OnEnChangeEditKunde2()
{
    CString str;
    m_edit_Kunde2.GetWindowText(str);                   //IDF lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength( ) - 1];               //letztes Zeichen lesen
    if ((str.GetLength() == 1) && !isdigit(chN))
    {
        m_CMC = str;
        OnBnClickedButtonKnd();
        m_lKunde2 = m_lKunde;
        m_CKunde2.Format("%ld", m_lKunde);
        GetDlgItem(IDC_EDIT_KUNDE2)->SetWindowText(m_CKunde2);
        m_edit_Kunde2.SetFocus();
        m_edit_Kunde2.SetSel(0, -1, FALSE);
        m_edit_Kunde2.SetSel(-1, 0, FALSE);           //Selektion aufheben
        GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow();
        return;
    }
    AllgWertKontr(&m_edit_Kunde2, MAXIMUM_IDF);
    GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow();
}

void CDArtikelQuota::OnBnClickedButtonCopy2()
{
    UpdateData();
    if (m_lKunde2 == 0)
    {
        CKNDAUSKU kndausku;
        kndausku.s.KUNDENNR = kndausku.s.IDFNR = atol(m_CKunde2);
        kndausku.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
        kndausku.Server(AakundeSel_ausku);
        if (kndausku.rc < SRV_OK)
        {
            MsgBoxOK(IDP_KEIN_KUNDE);
            m_edit_Kunde2.SetFocus();
            m_edit_Kunde2.SetSel(0, -1, FALSE);
            m_edit_Kunde2.SetSel(-1, 0, FALSE);               //Selektion aufheben
            GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow(FALSE);
            return;
        }
        m_lKunde2 = kndausku.s.KUNDENNR;
    }
    CARTIKELQUOTAPF Quota;
    Quota.SetBranchno(AeGetApp()->VzNr());
    Quota.SetCustomerno(m_lKndNr);
    Quota.SetWert(m_lKunde2);
    Quota.SetUid_anlage(GetAeUser().GetUID());
    Quota.SetSdafuequota(m_bDafue ? '1' : ' ');
    if (!Quota.CopyQuota())
    {
        CString str;
        str.Format(CResString::ex().getStrTblText(AETXT_INSERTED), Quota.GetCustomerno());
        MsgBoxOK(str);
    }
    GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow(FALSE);
    m_edit_Kunde2.SetFocus();
    m_edit_Kunde2.SetSel(0, -1, FALSE);
    //m_edit_Kunde2.SetSel(-1, 0, FALSE);         //Selektion aufheben
    m_lKunde2 = 0;
}

void CDArtikelQuota::OnBnClickedButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CString liste;

    char underline[111];
    memset(underline,'-',110);
    underline[110] = '\0';

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    char datum[11];
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, datum);
    CString name;
    this->GetWindowText(name);
    liste.Format("%s", name.GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);

    liste = m_bEKG ? GetHeaderLineTitlesEKG() : GetHeaderLineTitles();
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);

    liste = GetBottomLine(datum);
    druckAuftrag.AddFussZeile(liste);

    int maxpos = m_ListCtl.GetItemCount();
    for (int pos = 0; pos < maxpos; pos++)
    {
        liste = GetPositionLine(pos);
        druckAuftrag.AddPosZeile(liste);
    }

    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

/*static*/
CString CDArtikelQuota::GetHeaderLineTitlesEKG()
{
    CString list;
    list.Format("%-7.7s %-12.12s %-7.7s %-9.9s %-30.30s %-5.5s %-5.5s %-9.9s",
        CResString::ex().getStrTblText(AETXT_KURZ_EKG).GetString(),
        CResString::ex().getStrTblText(AETXT_EKGRUPPE).GetString(),
        CResString::ex().getStrTblText(AETXT_PZN).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
        CResString::ex().getStrTblText(AETXT_BEZOGEN).GetString(),
        CResString::ex().getStrTblText(AETXT_ZEITRAUM).GetString()
    );
    return list;
}

/*static*/
CString CDArtikelQuota::GetHeaderLineTitles()
{
    CString list;
    list.Format("%-7.7s %-12.12s %-7.7s %-9.9s %-30.30s %-5.5s %-5.5s %-9.9s",
        CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKE).GetString(),
        CResString::ex().getStrTblText(AETXT_PZN).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
        CResString::ex().getStrTblText(AETXT_BEZOGEN).GetString(),
        CResString::ex().getStrTblText(AETXT_ZEITRAUM).GetString()
    );
    return list;
}

CString CDArtikelQuota::GetPositionLine(int pos)
{
    CString list;
    list.Format("%-7.7s %-12.12s %-7.7s %-9.9s %-30.30s %-5.5s %-5.5s %-9.9s",
        m_ListCtl.GetItemText(pos, 1).GetString(),
        m_ListCtl.GetItemText(pos, 2).GetString(),
        m_ListCtl.GetItemText(pos, 3).GetString(),
        m_ListCtl.GetItemText(pos, 4).GetString(),
        m_ListCtl.GetItemText(pos, 5).GetString(),
        m_ListCtl.GetItemText(pos, 6).GetString(),
        m_ListCtl.GetItemText(pos, 7).GetString(),
        m_ListCtl.GetItemText(pos, 8).GetString()
    );
    return list;
}

/*static*/
CString CDArtikelQuota::GetBottomLine(CString date)
{
    CString list;
    list.Format("%s%%d                                        %s: %s",
        CResString::ex().getStrTblText(AETXT_SEITE),
        CResString::ex().getStrTblText(AETXT_DATUM),
        date
    );
    return list;
}

void CDArtikelQuota::OnBnClickedRadio1()
{
    m_bDafue = (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) == IDC_RADIO1) ? FALSE : TRUE;
}

void CDArtikelQuota::OnBnClickedButtonAllNobatch()
{
    char Out1[11];
    char Out2[11];
    ppString cApo;
    ppString cEKG;
    ppString cEKGName;
    ppString cArtikel;
    ppString cEinheit;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    CARTAESEL artaesel;
    m_ArtikelQuota.SetBranchno(AeGetApp()->VzNr());
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_ArtikelQuota.SelListAllNoBat() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%d", m_ArtikelQuota.GetCustomerno());
        s[2] = m_ArtikelQuota.GetMatchcode(cApo);
        artaesel.s.ARTIKEL_NR = m_ArtikelQuota.GetArticleno();
        artaesel.Server(AatartSel_Preferred);
        AllgEntfSpaces(artaesel.s.ARTICLE_CODE);
        s[3] = artaesel.s.ARTICLE_CODE;
        s[4] = m_ArtikelQuota.GetEinheit(cEinheit);
        s[5] = m_ArtikelQuota.GetArtikel_name(cArtikel);
        s[6].Format("%d", m_ArtikelQuota.GetQuota());
        s[7].Format("%d", m_ArtikelQuota.GetKumqty());
        s[8] = GetTimeRangeHeader(m_ArtikelQuota.GetValidity());
        if (m_ArtikelQuota.GetDatefrom() == 0)
        {
            s[9].Empty();
        }
        else
        {
            AllgDatumLong2CharTTMMJJJJ(m_ArtikelQuota.GetDatefrom(), Out1);
            s[9] = Out1;
        }
        if (m_ArtikelQuota.GetDateto() == 0)
        {
            s[10].Empty();
        }
        else
        {
            AllgDatumLong2CharTTMMJJJJ(m_ArtikelQuota.GetDateto(), Out2);
            s[10] = Out2;
        }
        s[11].Format("%d", m_ArtikelQuota.GetArticleno());
        s[12].Format("%c", m_ArtikelQuota.GetSnobatchchange());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
}
// DArtikelQuota.cpp : Implementierungsdatei
//




// CDArtikelQuotaUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDArtikelQuotaUpd, CDialog)
CDArtikelQuotaUpd::CDArtikelQuotaUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDArtikelQuotaUpd::IDD, pParent)
    , m_CKunde(_T(""))
    , m_CArtikel(_T(""))
    , m_CMenge(_T(""))
    , m_CZeit(_T(""))
    , m_CT_Von(0)
    , m_CT_Bis(0)
    , m_bNoBatch(FALSE)
{
    m_lDatumvon = 0;
    m_lDatumbis = 0;
    m_bUpdate = FALSE;
    m_iZeitraum = 0;
}

CDArtikelQuotaUpd::~CDArtikelQuotaUpd()
{
}

void CDArtikelQuotaUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_KUNDE, m_CKunde);
    DDX_Text(pDX, IDC_EDIT_ARTKELNR, m_CArtikel);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Control(pDX, IDC_COMBO_ZEIT, m_combo_Zeit);
    DDX_CBString(pDX, IDC_COMBO_ZEIT, m_CZeit);
    DDX_Control(pDX, IDC_DT_VON, m_DT_Von);
    DDX_DateTimeCtrl(pDX, IDC_DT_VON, m_CT_Von);
    DDX_Control(pDX, IDC_DT_BIS, m_DT_Bis);
    DDX_DateTimeCtrl(pDX, IDC_DT_BIS, m_CT_Bis);
    DDX_Control(pDX, IDC_EDIT_ARTKELNR, m_edit_artikelnr);
    DDX_Control(pDX, IDC_EDIT_KUNDE, m_edit_Kunde);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_edit_Menge);
    DDX_Check(pDX, IDC_CHECK_NOBATCH, m_bNoBatch);
}


BEGIN_MESSAGE_MAP(CDArtikelQuotaUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_KUNDE, OnEnChangeEditKunde)
    ON_EN_CHANGE(IDC_EDIT_ARTKELNR, OnEnChangeEditArtkelnr)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnBnClickedButtonKnd)
    ON_BN_CLICKED(IDC_BUTTON_ART, OnBnClickedButtonArt)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDArtikelQuotaUpd-Meldungshandler

BOOL CDArtikelQuotaUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CString CStr;
    if (m_bEKG)
    {
        GetDlgItem(IDC_STATIC_IDF)->SetWindowText(CResString::ex().getStrTblText(AETXT_EKGRUPPE));
        CStr = CResString::ex().getStrTblText(m_bUpdate ? AETXT_QUOTA_UPDATE_EKG : AETXT_QUOTA_INSERT_EKG);
    }
    else
    {
        CStr = CResString::ex().getStrTblText(m_bUpdate ? AETXT_QUOTA_UPDATE : AETXT_QUOTA_INSERT);
    }
    SetWindowText(CStr);

    if (m_bUpdate)
    {
        GetDlgItem(IDC_EDIT_KUNDE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_KND)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_ARTKELNR)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_ART)->EnableWindow(FALSE);
    }
    GetDlgItem(IDC_BUTTON_KND)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_KND)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_ART)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_ART)->ShowWindow(SW_HIDE);

    if ((m_lDatumvon == 0) && !m_bUpdate)
    {
        CTM zeit;
        zeit.Server(AafilGetdatetime);
        m_lDatumvon = zeit.s.DATUM;
        m_lDatumbis = 20991231;
    }
    m_CT_Von = CTimeFromDateLongMaxTime(m_lDatumvon);
    m_CT_Bis = CTimeFromDateLongMaxTime(m_lDatumbis);

    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_MONAT));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_WOCHE));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_TAG));
    m_combo_Zeit.AddString(CResString::ex().getStrTblText(AETXT_UNBEGRENZT));
    m_combo_Zeit.SetCurSel(m_iZeitraum);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDArtikelQuotaUpd::OnEnChangeEditKunde()
{
    CString str;
    m_edit_Kunde.GetWindowText(str);                // IDF lesen
    if (str.IsEmpty())
        return;                                     // Feld ist leer
    char chN = str[str.GetLength() - 1];            // letztes Zeichen lesen
    if (m_bEKG)
    {
        AllgLaengeKontr(&m_edit_Kunde, L_ARTICLEQUOTAEKG_PHARMACYGROUPID, AeGetApp()->Modus());
    }
    else
    {
        if ((str.GetLength() == 1) && !isdigit(chN))
        {
            m_CMC = str;
            OnBnClickedButtonKnd();
            m_CKunde.Format("%ld", m_lKunde);
            GetDlgItem(IDC_EDIT_KUNDE)->SetWindowText(m_CKunde);
            m_edit_Kunde.SetFocus();
            m_edit_Kunde.SetSel(0, -1, FALSE);
            m_edit_Kunde.SetSel(-1, 0, FALSE);      //Selektion aufheben
            return;
        }
        AllgWertKontr(&m_edit_Kunde, MAXIMUM_IDF);
    }
}

void CDArtikelQuotaUpd::OnEnChangeEditArtkelnr()
{
    CString str;
    m_edit_artikelnr.GetWindowText(str);            // PZN lesen
    if (str.IsEmpty())
        return;                                     // Feld ist leer
    char chN = str[str.GetLength() - 1];            // letztes Zeichen lesen
    if ((str.GetLength() == 1) && !isdigit(chN))
    {
        m_CArt = str;
        OnBnClickedButtonArt();
        m_CArtikel.Format("%ld", m_lArtikel);
        GetDlgItem(IDC_EDIT_ARTKELNR)->SetWindowText(m_CArtikel);
        m_edit_artikelnr.SetFocus();
        m_edit_artikelnr.SetSel(0, -1, FALSE);
        m_edit_artikelnr.SetSel(-1, 0, FALSE);      //Selektion aufheben
        return;
    }
    AllgWertKontr(&m_edit_artikelnr, MAXIMUM_ART_NR);
}

void CDArtikelQuotaUpd::OnBnClickedButtonKnd()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        m_lKunde = 0;
        return;
    }
    m_lKunde = dlgKndWahl.GetIdfNr();
    m_CMC.Empty();
}

void CDArtikelQuotaUpd::OnBnClickedButtonArt()
{
    CDArtDef dlgArtDef;
    dlgArtDef.m_CMatchCode = m_CArt;
    m_CArt.Empty();
    if (dlgArtDef.DoModal() != IDOK)
    {
        m_lArtikel = 0;
        return;
    }
    m_CArt = dlgArtDef.GetArticleCode();
}

void CDArtikelQuotaUpd::OnBnClickedOk()
{
    UpdateData();
    if (m_CKunde.IsEmpty())
    {
        if (m_bEKG)
        {
            MsgBoxOK(IDP_MUSS_EKG);
            m_edit_Kunde.SetFocus();
            m_edit_Kunde.SetSel(0, -1, FALSE);
            return;
        }
        /*else
        {
            MsgBoxOK(IDP_MUSS_KUNDENNR);
            m_edit_Kunde.SetFocus();
            m_edit_Kunde.SetSel( 0, -1, FALSE );
            return;
        }*/
    }
    if (m_CArtikel.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        m_edit_artikelnr.SetFocus();
        m_edit_artikelnr.SetSel(0, -1, FALSE);
        return;
    }
    if (m_CMenge.IsEmpty())
    {
        MsgBoxOK(AETXT_MENGENEINGABE);
        m_edit_Menge.SetFocus();
        m_edit_Menge.SetSel(0, -1, FALSE);
        return;
    }
    if (m_CT_Von.GetTime() > m_CT_Bis.GetTime())
    {
        MsgBoxOK(AETXT_DATE_VON_BIS);
        m_DT_Von.SetFocus();
        return;
    }
    CMAXARTICLEQUOTA max;
    max.SetArticleno(atol(m_CArtikel));
    if (!max.SelMax() && (max.GetMaxquota() < atol(m_CMenge)))
    {
        MsgBoxOK(AETXT_MAX_QUOTA);
        return;
    }
    m_iZeitraum = m_combo_Zeit.GetCurSel();
    m_lDatumvon = m_CT_Von.GetYear()*10000
                + m_CT_Von.GetMonth()*100
                + m_CT_Von.GetDay();
    m_lDatumbis = m_CT_Bis.GetYear()*10000
                + m_CT_Bis.GetMonth()*100
                + m_CT_Bis.GetDay();
    CDialogMultiLang::OnOK();
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareQuotaListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return 1;
    return -1;
}

int CALLBACK CompareQuotaListeLong(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    long feld1 = atol(s->GetAt(lParam1));
    long feld2 = atol(s->GetAt(lParam2));
    if (feld1 == feld2)
        return 0;
    if (feld1 > feld2)
        return 1;
    return -1;
}

int CALLBACK CompareQuotaListeDate(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    long feld1 = atol(s->GetAt(lParam1).Left(2)) +
                 atol(s->GetAt(lParam1).Mid(3,2))*100 +
                 atol(s->GetAt(lParam1).Right(4))*10000;
    long feld2 = atol(s->GetAt(lParam2).Left(2)) +
                 atol(s->GetAt(lParam2).Mid(3,2))*100 +
                 atol(s->GetAt(lParam2).Right(4))*10000;
    if (feld1 == feld2)
        return 0;
    if (feld1 > feld2)
        return 1;
    return -1;
}

void CDArtikelQuota::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    //LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    //Wegen Sort
    LV_ITEM lvi;
    //
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int col = pNMListView->iSubItem;
    int max = m_ListCtl.GetItemCount();
    CStringArray s;
    s.SetSize(max);
    for (int index = 0; index < max; index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;      //muss gesetzt sein, um lParam abzuholen
        m_ListCtl.GetItem(&lvi);    //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl.GetItemText(index,col);
    }
    if (col == 6 || col == 7)
        m_ListCtl.SortItems(CompareQuotaListeLong, (LPARAM)&s);
    else if (col == 10 || col == 11)
        m_ListCtl.SortItems(CompareQuotaListeDate, (LPARAM)&s);
    else
        m_ListCtl.SortItems(CompareQuotaListe, (LPARAM)&s);

    *pResult = 0L;
}
