// DFilialpartner.cpp : implementation file
//

#include "stdafx.h"
#include "DFilialpartner.h"
#include <filialpartner.h>

#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  50, LVCFMT_LEFT,
    2,  "", 130, LVCFMT_LEFT,
    3,  "",  60, LVCFMT_LEFT,
    4,  "",  50, LVCFMT_LEFT,
    5,  "",  50, LVCFMT_LEFT,
    6,  "",  80, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDFilialpartner dialog


CDFilialpartner::CDFilialpartner(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDFilialpartner::IDD, pParent), CPageBrowser(ZEILEN)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_FIL_NAME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_BGA_NR);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_RECHNER_NAME);
}

void CDFilialpartner::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDFilialpartner, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_EIGEN, OnButtonEigen)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDFilialpartner message handlers

BOOL CDFilialpartner::OnInitDialog()
    {
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDFilialpartner::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CFILIALPARTNER filialpartner;
    int fetch_rel;
    ppString Partner_name;
    ppString Rechner_name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, fetch_rel))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        filialpartner.Sel(fetch_rel);
        m_bCursorOpen = true;   //Datenbankcurser offen
        fetch_rel = 1;          //normaler Fetch
        if (filialpartner.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)  //kein Satz gefunden
            {
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1].Format("%d", filialpartner.GetFilialnr());
        s[2] = filialpartner.GetName(Partner_name);
        s[3].Format("%ld", filialpartner.GetBganr());
        s[4].Format("%ld", filialpartner.GetSupport_from());
        s[5].Format("%ld", filialpartner.GetSupport_until());
        s[6] = filialpartner.GetRechner_name(Rechner_name);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return false;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDFilialpartner::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDFilialpartner::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CFILIALPARTNER filialpartner;
    BeginWaitCursor();
    filialpartner.CloseCursor();
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDFilialpartner::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDFilialpartner::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDFilialpartnerUpd dlgFilialpartnerUpd;
        dlgFilialpartnerUpd.m_CFilialNr = m_ListCtl.GetItemText(pos, 1);
        dlgFilialpartnerUpd.m_CFilialName = m_ListCtl.GetItemText(pos, 2);
        dlgFilialpartnerUpd.m_CBGA = m_ListCtl.GetItemText(pos, 3);
        dlgFilialpartnerUpd.m_CVon = m_ListCtl.GetItemText(pos, 4);
        dlgFilialpartnerUpd.m_CBis = m_ListCtl.GetItemText(pos, 5);
        dlgFilialpartnerUpd.m_CRechner = m_ListCtl.GetItemText(pos, 6);
        if (dlgFilialpartnerUpd.DoModal() == IDOK)
        {
            CloseCursor();
            GetPage();
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDFilialpartner::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDFilialpartner::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDFilialpartner::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDFilialpartner::OnButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
        return;
    if (MsgBoxYesNo(IDP_SOLL_FP_DELETE) == IDNO)
        return;

    CFILIALPARTNER filialpartner;
    filialpartner.SetFilialnr(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 1))));
    filialpartner.Delete();
}

void CDFilialpartner::OnButtonNew()
{
    CDFilialpartnerUpd dlgFilialpartnerUpd;
    if (dlgFilialpartnerUpd.DoModal() == IDOK)
    {
        CloseCursor();
        GetPage();
    }
}

void CDFilialpartner::OnButtonUpdate()
{
    SelectEintrag();
}

void CDFilialpartner::OnButtonEigen()
{
    CDFilialpartnerUpd dlgFilialpartnerUpd;
    dlgFilialpartnerUpd.m_CFilialNr.Format("%d", AeGetApp()->FilialNr());
    dlgFilialpartnerUpd.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDFilialpartnerUpd dialog


CDFilialpartnerUpd::CDFilialpartnerUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDFilialpartnerUpd::IDD, pParent)
{
    m_CBGA = _T("");
    m_CBis = _T("");
    m_CFilialNr = _T("");
    m_CVon = _T("");
    m_CFilialName = _T("");
    m_CStaticZeiten = _T("");
    m_CRechner = _T("");
}


void CDFilialpartnerUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_RECHNER, m_EditRechner);
    DDX_Control(pDX, IDC_STATIC_ZEITEN, m_StaticZeiten);
    DDX_Control(pDX, IDC_EDIT_VON, m_EditVon);
    DDX_Control(pDX, IDC_EDIT_FILI_NR, m_EditFilialNr);
    DDX_Control(pDX, IDC_EDIT_FILI_NAME, m_EditFilialName);
    DDX_Control(pDX, IDC_EDIT_BISZ, m_EditBis);
    DDX_Control(pDX, IDC_EDIT_BGA, m_EditBGA);
    DDX_Text(pDX, IDC_EDIT_BGA, m_CBGA);
    DDX_Text(pDX, IDC_EDIT_BISZ, m_CBis);
    DDX_Text(pDX, IDC_EDIT_FILI_NR, m_CFilialNr);
    DDX_Text(pDX, IDC_EDIT_VON, m_CVon);
    DDX_Text(pDX, IDC_EDIT_FILI_NAME, m_CFilialName);
    DDX_Text(pDX, IDC_STATIC_ZEITEN, m_CStaticZeiten);
    DDX_Text(pDX, IDC_EDIT_RECHNER, m_CRechner);
}


BEGIN_MESSAGE_MAP(CDFilialpartnerUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BGA, OnChangeEditBga)
    ON_EN_CHANGE(IDC_EDIT_BISZ, OnChangeEditBisz)
    ON_EN_CHANGE(IDC_EDIT_FILI_NAME, OnChangeEditFiliName)
    ON_EN_CHANGE(IDC_EDIT_FILI_NR, OnChangeEditFiliNr)
    ON_EN_CHANGE(IDC_EDIT_VON, OnChangeEditVon)
    ON_EN_CHANGE(IDC_EDIT_RECHNER, OnChangeEditRechner)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDFilialpartnerUpd message handlers

void CDFilialpartnerUpd::OnChangeEditBga()
{
    AllgWertKontr(&m_EditBGA, MAXIMUM_IDF);
}

void CDFilialpartnerUpd::OnChangeEditBisz()
{
    AllgWertKontr(&m_EditBis, MAXIMUM_END_ZEIT);
}

void CDFilialpartnerUpd::OnChangeEditFiliName()
{
    AllgLaengeKontr(&m_EditFilialName, L_FILIALPARTNER_NAME,AeGetApp()->Modus());
}

void CDFilialpartnerUpd::OnChangeEditFiliNr()
{
    AllgWertKontr(&m_EditFilialNr, MAXIMUM_FILIALE);
}

void CDFilialpartnerUpd::OnChangeEditVon()
{
    AllgWertKontr(&m_EditVon, MAXIMUM_END_ZEIT);
}

BOOL CDFilialpartnerUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (!m_CFilialNr.IsEmpty())
    {
        m_EditFilialNr.EnableWindow(FALSE);
        if (AeGetApp()->FilialNr() == atoi(m_CFilialNr))
        {
            CFILIALZEITEN zeit;
            m_CFilialName = AeGetApp()->FilialName();
            zeit.SetFilialnr(AeGetApp()->FilialNr());
            zeit.SelZeiten();
            m_CStaticZeiten = CResString::ex().getStrTblText(AETXT_CLOSE_TIME);
            m_CVon.Format("%ld", zeit.GetClosed_from());
            m_CBis.Format("%ld", zeit.GetClosed_until());
            m_EditFilialName.EnableWindow(FALSE);
            m_EditBGA.EnableWindow(FALSE);
            m_EditRechner.EnableWindow(FALSE);
        }
        UpdateData(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDFilialpartnerUpd::OnOK()
{
    UpdateData();

    CFILIALPARTNER filialpartner;
    if (m_CFilialNr.IsEmpty())
    {
        MsgBoxOK(IDP_FP_FILINR_EINGEBEN);
        GetDlgItem(IDC_EDIT_FILI_NR)->SetFocus();
        return;
    }
    if ((atoi(m_CFilialNr) != AeGetApp()->FilialNr()) && m_CBGA.IsEmpty())
    {
        MsgBoxOK(IDP_FP_BGANR_EINGEBEN);
        GetDlgItem(IDC_EDIT_BGA)->SetFocus();
        return;
    }
    if ((atoi(m_CFilialNr) != AeGetApp()->FilialNr()) && m_CRechner.IsEmpty())
    {
        MsgBoxOK(IDP_FP_RECHNER_EINGEBEN);
        GetDlgItem(IDC_EDIT_RECHNER)->SetFocus();
        return;
    }
    if (m_CFilialName.IsEmpty())
    {
        MsgBoxOK(IDP_FP_FILINAME_EINGEBEN);
        GetDlgItem(IDC_EDIT_FILI_NAME)->SetFocus();
        return;
    }
    if ((atoi(m_CFilialNr) == AeGetApp()->FilialNr()) && m_EditFilialNr.IsWindowEnabled())
    {
        MsgBoxOK(IDP_FP_FILINR_EINGEBEN_EIGEN);
        GetDlgItem(IDC_EDIT_FILI_NR)->SetFocus();
        return;
    }
    if (m_CVon.IsEmpty())
    {
        MsgBoxOK(IDP_FP_ZEIT_EINGEBEN);
        GetDlgItem(IDC_EDIT_VON)->SetFocus();
        return;
    }
    if (m_CBis.IsEmpty())
    {
        MsgBoxOK(IDP_FP_ZEIT_EINGEBEN);
        GetDlgItem(IDC_EDIT_BISZ)->SetFocus();
        return;
    }
    long std = atol(m_CBis) / 100;
    long min = atol(m_CBis) % 100;
    if ((std > 23) || (min > 59))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_BISZ)->SetFocus();
        return;
    }
    std = atol(m_CVon) / 100;
    min = atol(m_CVon) % 100;
    if ((std > 23) || (min > 59))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_VON)->SetFocus();
        return;
    }
    if ((atol(m_CVon) >= atol(m_CBis)) && (atol(m_CVon) != 0))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_BISZ)->SetFocus();
        return;
    }
    filialpartner.SetFilialnr(static_cast<short>(atoi(m_CFilialNr)));
    filialpartner.SetName(m_CFilialName);
    filialpartner.SetRechner_name(m_CRechner);
    filialpartner.SetBganr(atol(m_CBGA));
    filialpartner.SetSupport_from(atol(m_CVon));
    filialpartner.SetSupport_until(atol(m_CBis));

    if (atoi(m_CFilialNr) == AeGetApp()->FilialNr())
    {
        CFILIALZEITEN zeit;
        zeit.SetFilialnr(static_cast<short>(atoi(m_CFilialNr)));
        zeit.SetClosed_from(atol(m_CVon));
        zeit.SetClosed_until(atol(m_CBis));
        zeit.UpdateZeiten();
    }
    else if (m_EditFilialNr.IsWindowEnabled())
    {
        filialpartner.Insert();
    }
    else
    {
        filialpartner.Update();
    }

    CDialogMultiLang::OnOK();
}

void CDFilialpartnerUpd::OnChangeEditRechner()
{
    AllgLaengeKontr(&m_EditRechner, L_FILIALPARTNER_RECHNER_NAME, AeGetApp()->Modus());
}
