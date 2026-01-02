// DDelayedCst.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "allg.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "DKndWahl.h"
#include <customer.h>
#include "DDelayedCstUpd.h"
#include "DDelayedCst.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     10

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 100, LVCFMT_LEFT,
    2,  "",  60, LVCFMT_LEFT,
    3,  "",  60, LVCFMT_LEFT,
    4,  "",  60, LVCFMT_LEFT,
    5,  "", 100, LVCFMT_LEFT,
    6,  "",  40, LVCFMT_LEFT,
    7,  "",  40, LVCFMT_LEFT,
    8,  "",  40, LVCFMT_LEFT,
    9,  "",  40, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDDelayedCst-Dialogfeld

IMPLEMENT_DYNAMIC(CDDelayedCst, CDialog)
CDDelayedCst::CDDelayedCst(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDDelayedCst::IDD, pParent)
    , m_CKdNr(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[2].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_TAG_DELAY);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_BTM);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_KK);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_K08);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_K20);
    m_sVzNr = 0;
    m_lKndNr = 0;
}

CDDelayedCst::~CDDelayedCst()
{
}

void CDDelayedCst::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_KDNR, m_Edit_KdNr);
    DDX_Text(pDX, IDC_EDIT_KDNR, m_CKdNr);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDDelayedCst, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_KDNR, OnEnChangeEditKdnr)
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON_INS, OnBnClickedButtonIns)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnBnClickedButtonUpd)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

// CDDelayedCst-Meldungshandler

BOOL CDDelayedCst::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_SUNDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_MONDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_TUESDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_WEDNESDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_THURSDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_FRIDAY).GetString());
    m_Tagtab.Add((char*)CResString::ex().getStrTblText(IDS_SATURDAY).GetString());

    if (m_sVzNr == 0)
    {
        m_sBranchno = (AeGetApp()->VzNr());
    }
    else
    {
        m_sBranchno = m_sVzNr;
        m_CKdNr.Format("%d", m_lKndNr);
        GetDlgItem(IDC_EDIT_KDNR)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_KDNR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
        if (!GetAeUser().IsPflegeDD())
        {
            GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_INS)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_UPD)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_DEL)->ShowWindow(SW_HIDE);
        }
        UpdateData(FALSE);
        GetPage();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDDelayedCst::OnEnChangeEditKdnr()
{
    CString str;

    m_Edit_KdNr.GetWindowText(str);                 //IDF lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        m_Edit_KdNr.SetWindowText("");              //IDF löschen
        OnBnClickedButton1();
        return;
    }
    AllgWertKontr(&m_Edit_KdNr, MAXIMUM_IDF);
}

void CDDelayedCst::OnBnClickedButton1()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    m_CMC.Empty();
    BOOL bSave = GetAeUser().IsMehrVz();
    GetAeUser().SetIsMehrVz(FALSE); // nur eigenes VZ

    if (dlgKndWahl.DoModal() != IDOK)
    {
        GetAeUser().SetIsMehrVz(bSave);
        return;
    }
    GetAeUser().SetIsMehrVz(bSave);
    m_CKdNr.Format("%ld", dlgKndWahl.GetIdfNr());
    GetDlgItem(IDC_EDIT_KDNR)->SetWindowText(m_CKdNr);
    m_Edit_KdNr.SetFocus();
    m_Edit_KdNr.SetSel(0, -1, FALSE);
    m_Edit_KdNr.SetSel(-1, 0, FALSE);           //Selektion aufheben
    GetPage();
}

void CDDelayedCst::OnBnClickedButtonIns()
{
    UpdateData();
    if (m_CKdNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    CDDelayedCstUpd upd;
    upd.m_lKdNr = atol(m_CKdNr);
    upd.m_pTagtab = &m_Tagtab;
    if (upd.DoModal() == IDOK)
    {
        char cTag[21];
        char cTour[21];
        CString CTag;
        CString CTour;
        int i;
        m_Cst.SetBranchno(m_sBranchno);
        m_Cst.SetCustomerno(atol(m_CKdNr));
        for (i = 0; i < 7; i++)
        {
            if (upd.m_CWTag == m_Tagtab.GetAt(i))
                break;
        }
        m_Cst.SetWeekday(static_cast<short>(i));
        m_Cst.SetTime(atol(upd.m_CTourMax)/100);
        m_Cst.SetTourid(upd.m_CTour);
        m_Cst.SetActiv(upd.m_bAktiv ? '1' : '0');
        sscanf(upd.m_CTour, "%s%s", cTag, cTour);
        CTag = cTag;
        CTour = cTour;
        for (i = 0; i < 7; i++)
        {
            if (CTag == m_Tagtab.GetAt(i))
                break;
        }
        m_Cst.SetDelayedweekday(static_cast<short>(i));
        m_Cst.SetTourid(CTour);
        m_Cst.SetActiv(upd.m_bAktiv ? '1' : '0');
        m_Cst.SetNarcotic(upd.m_bBTM ? '1' : '0');
        m_Cst.SetColdchain(upd.m_bKK ? '1' : '0');
        m_Cst.SetCool08(upd.m_bK08 ? '1' : '0');
        m_Cst.SetCool20(upd.m_bK20 ? '1' : '0');
        m_Cst.Insert();
        GetPage();
    }
}

void CDDelayedCst::OnBnClickedButtonUpd()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString CStr;
        CString CStr2;
        CDDelayedCstUpd upd;
        upd.m_lKdNr = atol(m_CKdNr);
        upd.m_Tag = m_ListCtl.GetItemText(pos, 1);
        CStr  = m_ListCtl.GetItemText(pos, 2);
        upd.m_CTourMax = CStr.Left(2) + CStr.Mid(3,2);
        upd.m_CTour = m_ListCtl.GetItemText(pos, 3);
        upd.m_CDDTour = m_ListCtl.GetItemText(pos, 3);
        if (m_ListCtl.GetItemText(pos, 4).GetAt(0) == '1')
            upd.m_bAktiv = TRUE;
        else
            upd.m_bAktiv = FALSE;
        upd.m_pTagtab = &m_Tagtab;
        upd.m_CDDTag = m_ListCtl.GetItemText(pos, 5);
        if (m_ListCtl.GetItemText(pos, 6).GetAt(0) == '1')
            upd.m_bBTM = TRUE;
        else
            upd.m_bBTM = FALSE;
        if (m_ListCtl.GetItemText(pos, 7).GetAt(0) == '1')
            upd.m_bKK = TRUE;
        else
            upd.m_bKK = FALSE;
        if (m_ListCtl.GetItemText(pos, 8).GetAt(0) == '1')
            upd.m_bK08 = TRUE;
        else
            upd.m_bK08 = FALSE;
        if (m_ListCtl.GetItemText(pos, 9).GetAt(0) == '1')
            upd.m_bK20 = TRUE;
        else
            upd.m_bK20 = FALSE;
        if (upd.DoModal() == IDOK)
        {
            char cTag[21];
            char cTour[21];
            int i;
            m_Cst.SetBranchno(m_sBranchno);
            m_Cst.SetCustomerno(atol(m_CKdNr));
            for (i = 0; i < 7; i++)
            {
                if (upd.m_CWTag == m_Tagtab.GetAt(i))
                    break;
            }
            m_Cst.SetWeekday(static_cast<short>(i));
            m_Cst.SetTime(atol(upd.m_CTourMax) / 100);
            sscanf(upd.m_CTour, "%20s%20s", cTag, cTour);
            CStr = cTag;
            CStr2 = cTour;
            for (i = 0; i < 7; i++)
            {
                if (CStr == m_Tagtab.GetAt(i))
                    break;
            }
            m_Cst.SetDelayedweekday(static_cast<short>(i));
            m_Cst.SetTourid(CStr2);
            m_Cst.SetActiv(upd.m_bAktiv ? '1' : '0');
            m_Cst.SetNarcotic(upd.m_bBTM ? '1' : '0');
            m_Cst.SetColdchain(upd.m_bKK ? '1' : '0');
            m_Cst.SetCool08(upd.m_bK08 ? '1' : '0');
            m_Cst.SetCool20(upd.m_bK20 ? '1' : '0');
            m_Cst.Update();
            GetPage();
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDDelayedCst::OnBnClickedButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            int i;
            m_Cst.SetBranchno(m_sBranchno);
            m_Cst.SetCustomerno(atol(m_CKdNr));
            for (i = 0; i < 7; i++)
            {
                if (m_ListCtl.GetItemText(pos, 1) == m_Tagtab.GetAt(i))
                    break;
            }
            m_Cst.SetWeekday(static_cast<short>(i));
            m_Cst.Delete();
            GetPage();
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDDelayedCst::OnBnClickedOk()
{
    UpdateData();
    if (m_CKdNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    GetPage();
}

void CDDelayedCst::GetPage()
{
    char time[6];
    ppString csTour;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    m_Cst.SetBranchno(m_sBranchno);
    m_Cst.SetCustomerno(atol(m_CKdNr));
    CLetterMan kb;
    for (;;)
    {
        if (m_Cst.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%s", m_Tagtab.GetAt(m_Cst.GetWeekday()).GetString());
        s[2] = AllgTourTimeToCharHHMM(m_Cst.GetTime(), time);
        m_Cst.GetTourid(csTour);
        s[3] = csTour;
        s[4].Format("%c", m_Cst.GetActiv());
        s[5].Format("%s", m_Tagtab.GetAt(m_Cst.GetDelayedweekday()).GetString());
        s[6].Format("%c", m_Cst.GetNarcotic());
        s[7].Format("%c", m_Cst.GetColdchain());
        s[8].Format("%c", m_Cst.GetCool08());
        s[9].Format("%c", m_Cst.GetCool20());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_Cst.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDDelayedCst::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        if (m_sBranchno == 0)
        {
            MsgBoxOK(IDP_MUSS_KUNDENNR);
            return 1L;                      //Message wird nicht weitergeleitet
        }
        if (atol(m_CKdNr) == 0)
        {
            MsgBoxOK(IDP_MUSS_KUNDENNR);
            return 1L;                      //Message wird nicht weitergeleitet
        }
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(atol(m_CKdNr));
        dlgKndInf.SetKndVz(m_sBranchno);
        dlgKndInf.DoModal();
        return 1L;                          //Message wird nicht weitergeleitet
    }
    return 0;
}
