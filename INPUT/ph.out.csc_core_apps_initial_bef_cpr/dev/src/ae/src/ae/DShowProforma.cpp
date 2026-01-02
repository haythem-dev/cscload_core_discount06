// DShowProforma.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DShowProforma.h"
#include <verbundcheck.h>
#include <artikel.h>
#include <customer.h>
#include "MainFrm.h"

//Definitionen Bearbeitet
#define DONE_YES    0
#define DONE_NO     1

//Definitionen Positionsarten
#define AUFTRAG_FV  2
#define AUFTRAG_KK  3
#define AUFTRAG_EH  4



// CDShowProforma-Dialogfeld

IMPLEMENT_DYNAMIC(CDShowProforma, CDialog)
CDShowProforma::CDShowProforma(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDShowProforma::IDD, pParent)
    , m_CBruttoFV(_T(""))
    , m_CRabFV(_T(""))
    , m_CBruttoKK(_T(""))
    , m_CBruttoEH(_T(""))
    , m_CRabKK(_T(""))
    , m_CRabEH(_T(""))
    , m_CNettoKK(_T(""))
    , m_CNettoFV(_T(""))
    , m_CNettoEH(_T(""))
{
    m_ListFV = new CSOListCtrl;
    assert(m_ListFV);
    m_ListKK = new CSOListCtrl;
    assert(m_ListKK);
    m_ListEH = new CSOListCtrl;
    assert(m_ListEH);
    m_lKndNr = 0;
    m_bFV = FALSE;
    m_bKK = FALSE;
    m_bEH = FALSE;
    m_ChangeCol = FALSE;
    m_NoChangeCol = TRUE;
    m_anzFV = 0;
    m_anzKK = 0;
    m_anzEH = 0;
}

CDShowProforma::~CDShowProforma()
{
    delete m_ListFV;
    m_ListFV = NULL;
    delete m_ListKK;
    m_ListKK = NULL;
    delete m_ListEH;
    m_ListEH = NULL;
}

void CDShowProforma::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_FV, *m_ListFV);
    DDX_Control(pDX, IDC_LIST_KK, *m_ListKK);
    DDX_Control(pDX, IDC_LIST_EH, *m_ListEH);
    DDX_Text(pDX, IDC_EDIT_FV_BRUTTO, m_CBruttoFV);
    DDX_Text(pDX, IDC_EDIT_FV_TAX, m_CRabFV);
    DDX_Text(pDX, IDC_EDIT_KK_BRUTTO, m_CBruttoKK);
    DDX_Text(pDX, IDC_EDIT_EH_BRUTTO, m_CBruttoEH);
    DDX_Text(pDX, IDC_EDIT_KK_TAX, m_CRabKK);
    DDX_Text(pDX, IDC_EDIT_EH_TAX, m_CRabEH);
    DDX_Text(pDX, IDC_EDIT_KK_NETTO, m_CNettoKK);
    DDX_Text(pDX, IDC_EDIT_FV_NETTO, m_CNettoFV);
    DDX_Text(pDX, IDC_EDIT_EH_NETTO, m_CNettoEH);
}


BEGIN_MESSAGE_MAP(CDShowProforma, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(HDN_ITEMCHANGED, 0, OnHdnItemchangedListFv)
END_MESSAGE_MAP()

// CDShowProforma-Meldungshandler

BOOL CDShowProforma::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    // prepare the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK);
    idResources.push_back(IDI_ICON_NO);
    idResources.push_back(IDI_ICON_FV);
    idResources.push_back(IDI_ICON_KK);
    idResources.push_back(IDI_ICON_EH);
    idResources.push_back(IDI_ICON_PP);
    idResources.push_back(IDI_ICON_TP);
    idResources.push_back(IDI_ICON_NO_RAB);
    idResources.push_back(IDI_ICON_L5);

    CAUFPOSBUCH aufposbuch;
    bool first = true;

    BeginWaitCursor();

    //Ausgeben Werte Freiverkauf
    aufposbuch.s.PREIS_TYP = 0;
    m_ListFV->DeleteAllItems();
    CLetterMan kb;
    for (int pos = 0; ; pos++)
    {
        aufposbuch.Server(AasrvProforma, PIPE_AE_SRV); // proforma Lieferwert berechnen
        if (aufposbuch.rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        else if (aufposbuch.rc == SRV_OK)
        {
            if (first)
            {
                first = false;
                m_bFV = TRUE;
                GetDlgItem(IDC_LIST_FV)->EnableWindow(TRUE);
                GetDlgItem(IDC_LIST_FV)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_FV)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_BRUTTO)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_NETTO)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_MWST)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_BRUTTO)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_NETTO)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_MWST)->EnableWindow(TRUE);
                GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(SW_SHOW);
                DWORD dwOldBits = m_ListFV->GetExtendedStyle();
                dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;
                m_ListFV->SetExtendedStyle(dwOldBits);

                m_ListFV->init();

                // create the small icon image list
                CListCtrlHelper::CreateAndSetImageList(*m_ListFV, m_ImageSmall, idResources);

                char text[81];

                sprintf(text, "%.2f", aufposbuch.s.WERTNETTO_FV);
                GetDlgItem(IDC_EDIT_FV_NETTO)->SetWindowText(text);
                sprintf(text, "%.2f", aufposbuch.s.WERTTAX_FV);
                GetDlgItem(IDC_EDIT_FV_TAX)->SetWindowText(text);
                sprintf(text, "%.2f", aufposbuch.s.WERTNETTO_FV + aufposbuch.s.WERTTAX_FV);
                GetDlgItem(IDC_EDIT_FV_BRUTTO)->SetWindowText(text);
            }
            FillList(pos, &aufposbuch.s, m_ListFV, kb.Next());
            m_anzFV = pos + 1;
        }
    }

    //Ausgeben Werte Krankenkasse
    first = true;
    aufposbuch.s.PREIS_TYP = 1;
    m_ListKK->DeleteAllItems();
    kb.Reset();
    for (int pos = 0; ; pos++)
    {
        aufposbuch.Server(AasrvProforma, PIPE_AE_SRV); // proforma Lieferwert berechnen
        if (aufposbuch.rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        else if (aufposbuch.rc == SRV_OK)
        {
            if (first)
            {
                first = false;
                m_bKK = TRUE;
                GetDlgItem(IDC_LIST_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_LIST_KK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_BRUTTO_KK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_NETTO_KK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_MWST_KK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_BRUTTO_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_NETTO_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_MWST_KK)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_SHOW);
                DWORD dwOldBits = m_ListKK->GetExtendedStyle();
                dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;
                m_ListKK->SetExtendedStyle(dwOldBits);

                m_ListKK->init();

                // create the small icon image list
                CListCtrlHelper::CreateAndSetImageList(*m_ListKK, m_ImageSmall, idResources);

                char text[81];

                sprintf(text, "%.2f", aufposbuch.s.WERTNETTO_KK);
                GetDlgItem(IDC_EDIT_KK_NETTO)->SetWindowText(text);
                sprintf(text, "%.2f", aufposbuch.s.WERTTAX_KK);
                GetDlgItem(IDC_EDIT_KK_TAX)->SetWindowText(text);
                sprintf(text, "%.2f", aufposbuch.s.WERTNETTO_KK + aufposbuch.s.WERTTAX_KK);
                GetDlgItem(IDC_EDIT_KK_BRUTTO)->SetWindowText(text);
            }
            FillList(pos, &aufposbuch.s, m_ListKK, kb.Next());
            m_anzKK = pos + 1;
        }
    }

    //Ausgeben Werte Einzelhandel
    first = true;
    aufposbuch.s.PREIS_TYP = 2;
    m_ListEH->DeleteAllItems();
    kb.Reset();
    for (int pos = 0; ; pos++)
    {
        aufposbuch.Server(AasrvProforma, PIPE_AE_SRV); // proforma Lieferwert berechnen
        if (aufposbuch.rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        else if (aufposbuch.rc == SRV_OK)
        {
            if (first)
            {
                first = false;
                m_bEH = TRUE;
                GetDlgItem(IDC_LIST_EH)->EnableWindow(TRUE);
                GetDlgItem(IDC_LIST_EH)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_BRUTTO_EH)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_NETTO_EH)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_MWST_EH)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_BRUTTO_EH)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_NETTO_EH)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_MWST_EH)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_SHOW);
                DWORD dwOldBits = m_ListEH->GetExtendedStyle();
                dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;
                m_ListEH->SetExtendedStyle(dwOldBits);

                m_ListEH->init();

                // create the small icon image list
                CListCtrlHelper::CreateAndSetImageList(*m_ListEH, m_ImageSmall, idResources);

                char text[81];

                sprintf(text, "%.2f", aufposbuch.s.WERTNETTO_EH);
                GetDlgItem(IDC_EDIT_EH_NETTO)->SetWindowText(text);
                sprintf(text, "%.2f", aufposbuch.s.WERTTAX_EH);
                GetDlgItem(IDC_EDIT_EH_TAX)->SetWindowText(text);
                sprintf(text, "%.2f", aufposbuch.s.WERTNETTO_EH + aufposbuch.s.WERTTAX_EH);
                GetDlgItem(IDC_EDIT_EH_BRUTTO)->SetWindowText(text);
            }
            FillList(pos, &aufposbuch.s, m_ListEH, kb.Next());
            m_anzEH = pos + 1;
        }
    }

    EndWaitCursor();

    if (m_bFV)
    {
        m_ListFV->SetFocus();
    }
    else if (m_bKK)
    {
        m_ListKK->SetFocus();
    }
    else if (m_bEH)
    {
        m_ListEH->SetFocus();
    }
    else
    {
        MsgBoxOK(IDP_NO_DATA);
        CDialogMultiLang::OnCancel();
    }
    SetColumnWidthUser("CDShowProforma", KEY_PATH, COL_ANZ_LIST);
    ChangeColumnWidth();
    RepositionWindow();
    m_NoChangeCol = FALSE;

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDShowProforma::FillList(int pos, AUFPOSBUCH* ptrPos, CSOListCtrl* ListCtl, char* kb)
{
    int kz;
    char str[81];
    CString cstr;

    if (   ptrPos->ARTICLE_NO_PACK > 0
        || AllgBitleisteN((Bitleiste)ptrPos->ETPOSSCHALTER2, 11))
    {
        kz = DONE_NO;
    }
    else if (ptrPos->PREIS_TYP == 0)
    {
        kz = AUFTRAG_FV;
    }
    else if (ptrPos->PREIS_TYP == 1)
    {
        kz = AUFTRAG_KK;
    }
    else kz = AUFTRAG_EH;
    if (ListCtl->InsertItem(pos, cstr, kz) == -1)
        return;

    ListCtl->SetItemText(pos, COL_KB, kb);
    ListCtl->SetItemText(pos, COL_AMGE, _ltoa(ptrPos->MENGEBESTELLT, str, 10));
    ListCtl->SetItemText(pos, COL_BMGE, _ltoa(ptrPos->MENGEGELIEFERT + ptrPos->MENGE, str, 10));
    ListCtl->SetItemText(pos, COL_NRME, _ltoa(ptrPos->MENGENATRA, str, 10));
    ListCtl->SetItemText(pos, COL_VERBME, _ltoa(ptrPos->MENGE, str, 10)); //Verbundmenge
    if (ptrPos->KZAUFGENOMMEN[0] == '1') ListCtl->SetItemText(pos, COL_UMGESCHL, CResString::ex().getStrTblText(AETXT_KZ_JA));
    else ListCtl->SetItemText(pos, COL_UMGESCHL, "");
    AllgEntfSpaces(ptrPos->EINHEIT);
    ListCtl->SetItemText(pos, COL_EINHEIT, ptrPos->EINHEIT);
    if      (ptrPos->STATUS == ITEM_STAT_ZUGESAGT)      cstr = "ZU";
    else if (ptrPos->STATUS == ITEM_STAT_DISPO)         cstr = "DI";
    else if (ptrPos->STATUS == ITEM_STAT_NACHLIEFERN)   cstr = "NL";
    else if (ptrPos->KZINFOTEXT[0] == '1')              cstr = "IT";
    else                                                cstr = "";
    ListCtl->SetItemText(pos, COL_FU, cstr);
    AllgEntfSpaces(ptrPos->ARTIKEL_LANGNAME);
    AllgEntfSpaces(ptrPos->ARTIKEL_NAME);
    AllgEntfSpaces(ptrPos->BEMERKUNG);
    if (AeGetApp()->IsBG())
    {
        if (strlen(ptrPos->ARTIKEL_LANGNAME) > 0)
            ListCtl->SetItemText(pos, COL_ARTIKELNAME, ptrPos->ARTIKEL_LANGNAME);
        else if (strlen(ptrPos->ARTIKEL_NAME) > 0)
            ListCtl->SetItemText(pos, COL_ARTIKELNAME, ptrPos->ARTIKEL_NAME);
        else
            ListCtl->SetItemText(pos, COL_ARTIKELNAME, ptrPos->BEMERKUNG);
    }
    else if (strlen(ptrPos->ARTIKEL_NAME) > 0)
        ListCtl->SetItemText(pos, COL_ARTIKELNAME, ptrPos->ARTIKEL_NAME);
    else
        ListCtl->SetItemText(pos, COL_ARTIKELNAME, ptrPos->BEMERKUNG);
    AllgEntfSpaces(ptrPos->DARREICHFORM);
    ListCtl->SetItemText(pos, COL_DAF, ptrPos->DARREICHFORM);
    AllgEntfSpaces(ptrPos->KURZBEZKONDI);
    ListCtl->SetItemText(pos, COL_KENNZEICHEN, ptrPos->KURZBEZKONDI);
    ListCtl->SetItemText(pos, COL_PA, ptrPos->POSART);
    if (ptrPos->ARTICLE_CODE[0] == ' ')     // wenn articlecode noch nicht versorgt, dann artikelnr
    {
        ListCtl->SetItemText(pos, COL_ARTICLE_CODE, _ltoa((ptrPos->ARTIKEL_NR), str, 10));
    }
    else
    {
        ListCtl->SetItemText(pos, COL_ARTICLE_CODE, ptrPos->ARTICLE_CODE);
    }
    ListCtl->SetItemText(pos, COL_PNR, _ltoa(ptrPos->POSNR, str, 10));
    if (ptrPos->ARTIKEL_NR == -1)
    {
        if (ptrPos->KZAPODINL[0] == ITEM_APO_DISPO)
            ListCtl->SetItemText(pos, COL_PZN, CResString::ex().getStrTblText(AETXT_DISPO));
        else if (ptrPos->KZAPODINL[0] == ITEM_APO_NACHL)
            ListCtl->SetItemText(pos, COL_PZN, CResString::ex().getStrTblText(AETXT_NACHL));
        else
            ListCtl->SetItemText(pos, COL_PZN, " ");
    }
    else
        ListCtl->SetItemText(pos, COL_PZN, _ltoa((ptrPos->ARTIKEL_NR), str, 10));
    if (AeGetApp()->IsBG())
    {
        double dTax;
        char cStd;
        AeGetApp()->GetTaxRates(ptrPos->TAXLEVEL, cStd, dTax);
        if (ptrPos->ARTIKEL_NR == -1)
        {
            cstr.Format("%.2lf", (ptrPos->PREISEKAPO * (100 + dTax) / 100));
        }
        else
        {
            cstr.Format("%.2lf", (ptrPos->PREISFAKTUR * (100 + dTax) / 100));
        }
        if (ptrPos->PREIS_TYP == 0)
        {
            kz = AUFTRAG_FV;
        }
        else if (ptrPos->PREIS_TYP == 1)
        {
            kz = AUFTRAG_KK;
        }
        else kz = AUFTRAG_EH;

        CListCtrlHelper::SetImageItemSelected(*ListCtl, pos, kz);
    }
    else
    {
        cstr.Format("%.2lf", ptrPos->PREISEKAPO);
    }
    ListCtl->SetItemText(pos, COL_PREIS, cstr);
    cstr.Format("%.2lf", ptrPos->DISCOUNTVALUEPCT);
    ListCtl->SetItemText(pos, COL_RABATT, cstr);
    cstr.Format("%.2lf", ptrPos->DISCOUNTVALPCTMAN);
    ListCtl->SetItemText(pos, COL_RABATT_MAN, cstr);
    ListCtl->SetItemText(pos, COL_BEMERK, ptrPos->BEMERKUNG);
    cstr.Format("%.2lf", ptrPos->PREISVKAPO);
    ListCtl->SetItemText(pos, COL_AVP, cstr);
    ListCtl->SetItemText(pos, COL_CHARGE, ptrPos->CHARGENNR);
    cstr.Format("%d", ptrPos->PROMOTYP);
    ListCtl->SetItemText(pos, COL_PROMOTYP, cstr);
    cstr.Format("%d", ptrPos->PROMOTION_NO);
    ListCtl->SetItemText(pos, COL_PROMONR, cstr);
    cstr.Format("%d", ptrPos->PHARMACYGROUPID);
    ListCtl->SetItemText(pos, COL_PHARMACYGROUPID, cstr);
    cstr.Format("%d", ptrPos->DISCOUNTGRPNO);
    ListCtl->SetItemText(pos, COL_DISCOUNTGRPNO, cstr);
    cstr.Format("%d", ptrPos->BASEQTY);
    ListCtl->SetItemText(pos, COL_BASEQTY, cstr);
    cstr.Format("%.2lf", ptrPos->BASE_VALUE);
    ListCtl->SetItemText(pos, COL_BASE_VALUE, cstr);
    ListCtl->SetItemText(pos, COL_VERBUND, "");
    if (ptrPos->PROMOTION_NO > 0)
    {
        if (ptrPos->PROMOTYP == 1)
        {
            ListCtl->setItemColor(pos, RGB(0, 0, 0), RGB(255, 85, 0));
        }
        else if (ptrPos->PROMOTYP == 2)
        {
            ListCtl->setItemColor(pos, RGB(0, 0, 0), RGB(255, 00, 0));
        }
        else
        {
            ListCtl->setItemColor(pos, RGB(0, 0, 0), RGB(255, 80, 80));
        }
    }
}

void CDShowProforma::OnDestroy()
{
    GetDlgItem(IDC_LIST_FV)->EnableWindow(TRUE);
    GetDlgItem(IDC_LIST_FV)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LIST_KK)->EnableWindow(TRUE);
    GetDlgItem(IDC_LIST_KK)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LIST_EH)->EnableWindow(TRUE);
    GetDlgItem(IDC_LIST_EH)->ShowWindow(SW_SHOW);
    WriteColumnWidthUser("CDShowProforma", KEY_PATH, COL_ANZ_LIST);
    CDialogMultiLang::OnDestroy();
}

// Vom User eingestellte Spaltenbreiten aus Win-DB
void CDShowProforma::SetColumnWidthUser(char* name, char* keypath, int anz)
{
    HKEY hKey;
    char szBuffer[250 + 1];
    DWORD len = sizeof(szBuffer) - 1;
    if (RegOpenKey(HKEY_CURRENT_USER, keypath, &hKey) == ERROR_SUCCESS)
    {
        long xx = RegQueryValueEx(hKey, name, 0, NULL, (BYTE*)szBuffer, &len);
        if (xx == ERROR_SUCCESS)
        {
            // Werte gefunden
            szBuffer[len] = '\0';
            int width, pos;
            CString Spalten = szBuffer;
            for (int i = 0; i < anz; i++)
            {
                if (sscanf(Spalten, "%d", &width) == 0) break;
                m_Spalten[i] = width;
                if ((pos = Spalten.Find(", ")) == -1) break;
                Spalten = Spalten.Right(Spalten.GetLength() - pos - 2);
            }
        }
        else
        {
            for (int i = 0; i < anz; i++)
            {
                m_Spalten[i] = m_ListFV->GetColumnWidth(i);
            }
        }
        RegCloseKey(hKey);
    }
}

// Vom User eingestellte Spaltenbreiten in Win-DB
void CDShowProforma::WriteColumnWidthUser(char* name, char* keypath, int anz)
{
    HKEY hKey;
    CString szBuffer;
    CString szNext;
    for (int i = 0; i < anz; i++)
    {
        if (!i) szBuffer.Format("%d", m_Spalten[i]);
        else
        {
            szNext.Format(", %d", m_Spalten[i]);
            szBuffer += szNext;
        }
    }
    if (RegCreateKey(HKEY_CURRENT_USER, keypath, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, name, 0, REG_SZ, (BYTE*)szBuffer.operator LPCTSTR(), szBuffer.GetLength());
        RegCloseKey(hKey);
    }
}

void CDShowProforma::OnHdnItemchangedListFv(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    //Methode dient zur Vereinheitlichung der Spaltenbreiten der 3 Listboxen
    //Listcontrol Freiverkauf geaendert ?
    if (m_ChangeCol || m_NoChangeCol)
    {
        *pResult = 0L;
        return;
    }
    m_ChangeCol = TRUE;
    if (m_bFV)
    {
        for (int i = 0; i < COL_ANZ_LIST; i++)
        {
            if (m_ListFV->GetColumnWidth(i) != m_Spalten[i])
            {
                for (int j = 0; j < COL_ANZ_LIST; j++)
                {
                    m_Spalten[j] = m_ListFV->GetColumnWidth(j);
                }
                *pResult = 0L;
                ChangeColumnWidth();
                return;
            }
        }
    }
    //Listcontrol Krankenkasse geaendert ?
    if (m_bKK)
    {
        for (int i = 0;i < COL_ANZ_LIST;i++)
        {
            if (m_ListKK->GetColumnWidth(i) != m_Spalten[i])
            {
                for (int j = 0; j < COL_ANZ_LIST; j++)
                {
                    m_Spalten[j] = m_ListKK->GetColumnWidth(j);
                }
                *pResult = 0L;
                ChangeColumnWidth();
                return;
            }
        }
    }
    //Listcontrol Einzelhandel geaendert ?
    if (m_bEH)
    {
        for (int i = 0; i < COL_ANZ_LIST; i++)
        {
            if (m_ListEH->GetColumnWidth(i) != m_Spalten[i])
            {
                for (int j = 0; j < COL_ANZ_LIST; j++)
                {
                    m_Spalten[j] = m_ListEH->GetColumnWidth(j);
                }
                *pResult = 0L;
                ChangeColumnWidth();
                return;
            }
        }
    }
    *pResult = 0L;
}

void CDShowProforma::ChangeColumnWidth()
{
    for (int i = 0; i < COL_ANZ_LIST; i++)
    {
        m_ListFV->SetColumnWidth(i, m_Spalten[i]);
    }
    if (m_bKK)
    {
        for (int i = 0; i < COL_ANZ_LIST; i++)
        {
            m_ListKK->SetColumnWidth(i, m_Spalten[i]);
        }
    }
    if (m_bEH)
    {
        for (int i = 0; i < COL_ANZ_LIST; i++)
        {
            m_ListEH->SetColumnWidth(i, m_Spalten[i]);
        }
    }
    m_ChangeCol = FALSE;
}

void CDShowProforma::RepositionWindow()
{
    //aktuelle Werte
    CRect rectWin;

    //Freiverkauf
    CRect rectStaticFV;
    CRect rectListFV;
    CRect rectStaticBruttoFV;
    CRect rectStaticTaxFV;
    CRect rectStaticNettoFV;
    CRect rectEditBruttoFV;
    CRect rectEditTaxFV;
    CRect rectEditNettoFV;

    //Krankenkasse
    CRect rectStaticKK;
    CRect rectListKK;
    CRect rectStaticBruttoKK;
    CRect rectStaticTaxKK;
    CRect rectStaticNettoKK;
    CRect rectEditBruttoKK;
    CRect rectEditTaxKK;
    CRect rectEditNettoKK;

    //Einzelhandel
    CRect rectStaticEH;
    CRect rectListEH;
    CRect rectStaticBruttoEH;
    CRect rectStaticTaxEH;
    CRect rectStaticNettoEH;
    CRect rectEditBruttoEH;
    CRect rectEditTaxEH;
    CRect rectEditNettoEH;

    //Startwerte
    CRect rectStartStaticFV;
    CRect rectStartListFV;
    CRect rectStartStaticBruttoFV;
    CRect rectStartStaticTaxFV;
    CRect rectStartStaticNettoFV;
    CRect rectStartEditBruttoFV;
    CRect rectStartEditTaxFV;
    CRect rectStartEditNettoFV;

    //Dialog
    int iAbstandStatic;
    int iAbstandList;
    int iAbstandBrutto;
    int iAbstandNetto;
    int iAbstandTax;
    int iHeight;
    int iItemHeight;

    const int iZeilenGesamt = 42;
    const int iZeilenMin = 4;
    int iAnz = m_anzFV + m_anzKK + m_anzEH;
    if (iAnz == 0)
    {
        iAnz = 1; // Devider must not be 0 !!!
    }

    int iZeilenFV = (m_anzFV * iZeilenGesamt) / iAnz;
    int iZeilenKK = (m_anzKK * iZeilenGesamt) / iAnz;
    int iZeilenEH = (m_anzEH * iZeilenGesamt) / iAnz;

    if (iZeilenFV > 0 && iZeilenFV < iZeilenMin) iZeilenFV = iZeilenMin;    //Bei vorhandenen Daten mindestens 3 Zeilen in Listbox
    if (iZeilenKK > 0 && iZeilenKK < iZeilenMin) iZeilenKK = iZeilenMin;    //Bei vorhandenen Daten mindestens 3 Zeilen in Listbox
    if (iZeilenEH > 0 && iZeilenEH < iZeilenMin) iZeilenEH = iZeilenMin;    //Bei vorhandenen Daten mindestens 3 Zeilen in Listbox

    if ((iZeilenFV + iZeilenKK + iZeilenEH) > iZeilenGesamt)
    {
        const int Abzug = iZeilenFV + iZeilenKK + iZeilenEH - iZeilenGesamt;
        if (iZeilenFV > iZeilenKK)
        {
            if (iZeilenFV > iZeilenEH)
            {
                iZeilenFV -= Abzug;
            }
            else
            {
                iZeilenEH -= Abzug;
            }
        }
        else
        {
            if (iZeilenKK > iZeilenEH)
            {
                iZeilenKK -= Abzug;
            }
            else
            {
                iZeilenEH -= Abzug;
            }
        }

    }

    if ((iZeilenFV + iZeilenKK + iZeilenEH) < iZeilenGesamt)
    {
        const int Zuschlag = iZeilenGesamt - (iZeilenFV + iZeilenKK + iZeilenEH);
        if (iZeilenFV > iZeilenKK)
        {
            if (iZeilenFV > iZeilenEH)
            {
                iZeilenFV += Zuschlag;
            }
            else
            {
                iZeilenEH += Zuschlag;
            }
        }
        else
        {
            if (iZeilenKK > iZeilenEH)
            {
                iZeilenKK += Zuschlag;
            }
            else
            {
                iZeilenEH += Zuschlag;
            }
        }
    }
    if (iZeilenFV == iZeilenKK && iZeilenFV == iZeilenEH) return;   //nichts zu Aendern

    GetWindowRect(&rectWin);
    //nur Freiverkauf
    if (iZeilenFV == iZeilenGesamt)
    {
        m_ListFV->GetWindowRect(&rectListFV);
        m_ListKK->GetWindowRect(&rectListKK);
        m_ListEH->GetWindowRect(&rectListEH);
        GetDlgItem(IDC_STATIC_FV)->GetWindowRect(&rectStaticFV);
        GetDlgItem(IDC_STATIC_NETTO_EH)->GetWindowRect(&rectStaticNettoEH);
        GetDlgItem(IDC_STATIC_MWST_EH)->GetWindowRect(&rectStaticTaxEH);
        GetDlgItem(IDC_STATIC_BRUTTO_EH)->GetWindowRect(&rectStaticBruttoEH);
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->GetWindowRect(&rectEditBruttoEH);
        GetDlgItem(IDC_EDIT_EH_TAX)->GetWindowRect(&rectEditTaxEH);
        GetDlgItem(IDC_EDIT_EH_NETTO)->GetWindowRect(&rectEditNettoEH);

        //Listcontrol
        rectListFV.SetRect(rectListFV.TopLeft().x, rectListFV.TopLeft().y, rectListEH.BottomRight().x, rectListEH.BottomRight().y);
        ScreenToClient(rectListFV);
        m_ListFV->MoveWindow(rectListFV, true);

        //Ueberschrift bleibt
        /*GetDlgItem(IDC_STATIC_FV)->GetWindowRect( &rectStaticFV );
        rectStaticFV.SetRect(rectStaticFV.TopLeft().x, rectStaticFV.TopLeft().y, rectStaticFV.BottomRight().x, rectStaticFV.BottomRight().y);
        ScreenToClient( rectStaticKK );
        GetDlgItem(IDC_STATIC_KK)->MoveWindow(rectStaticKK,true);
        */

        //Static Brutto
        GetDlgItem(IDC_STATIC_BRUTTO_EH)->GetWindowRect(&rectStaticBruttoEH);
        rectStaticBruttoFV.SetRect(rectStaticBruttoEH.TopLeft().x, rectStaticBruttoEH.TopLeft().y, rectStaticBruttoEH.BottomRight().x, rectStaticBruttoEH.BottomRight().y);
        ScreenToClient(rectStaticBruttoFV);
        GetDlgItem(IDC_STATIC_BRUTTO)->MoveWindow(rectStaticBruttoFV, true);

        //Static Rabatt
        GetDlgItem(IDC_STATIC_MWST_EH)->GetWindowRect(&rectStaticTaxEH);
        rectStaticTaxFV.SetRect(rectStaticTaxEH.TopLeft().x, rectStaticTaxEH.TopLeft().y, rectStaticTaxEH.BottomRight().x, rectStaticTaxEH.BottomRight().y);
        ScreenToClient(rectStaticTaxFV);
        GetDlgItem(IDC_STATIC_MWST)->MoveWindow(rectStaticTaxFV, true);

        //Static Netto
        GetDlgItem(IDC_STATIC_NETTO_EH)->GetWindowRect(&rectStaticNettoEH);
        rectStaticNettoFV.SetRect(rectStaticNettoEH.TopLeft().x, rectStaticNettoEH.TopLeft().y, rectStaticNettoEH.BottomRight().x, rectStaticNettoEH.BottomRight().y);
        ScreenToClient(rectStaticNettoFV);
        GetDlgItem(IDC_STATIC_NETTO)->MoveWindow(rectStaticNettoFV, true);

        //Edit Brutto
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->GetWindowRect(&rectEditBruttoEH);
        rectEditBruttoFV.SetRect(rectEditBruttoEH.TopLeft().x, rectEditBruttoEH.TopLeft().y, rectEditBruttoEH.BottomRight().x, rectEditBruttoEH.BottomRight().y);
        ScreenToClient(rectEditBruttoFV);
        GetDlgItem(IDC_EDIT_FV_BRUTTO)->MoveWindow(rectEditBruttoFV, true);

        //Edit Rabatt
        GetDlgItem(IDC_EDIT_EH_TAX)->GetWindowRect(&rectEditTaxEH);
        rectEditTaxFV.SetRect(rectEditTaxEH.TopLeft().x, rectEditTaxEH.TopLeft().y, rectEditTaxEH.BottomRight().x, rectEditTaxEH.BottomRight().y);
        ScreenToClient(rectEditTaxFV);
        GetDlgItem(IDC_EDIT_FV_TAX)->MoveWindow(rectEditTaxFV, true);

        //Edit Netto
        GetDlgItem(IDC_EDIT_EH_NETTO)->GetWindowRect(&rectEditNettoEH);
        rectEditNettoFV.SetRect(rectEditNettoEH.TopLeft().x, rectEditNettoEH.TopLeft().y, rectEditNettoEH.BottomRight().x, rectEditNettoEH.BottomRight().y);
        ScreenToClient(rectEditNettoFV);
        GetDlgItem(IDC_EDIT_FV_NETTO)->MoveWindow(rectEditNettoFV, true);

        return;
    }

    //nur Krankenkasse
    if (iZeilenKK == iZeilenGesamt)
    {
        m_ListFV->GetWindowRect(&rectListFV);
        m_ListKK->GetWindowRect(&rectListKK);
        m_ListEH->GetWindowRect(&rectListEH);
        GetDlgItem(IDC_STATIC_FV)->GetWindowRect(&rectStaticFV);
        GetDlgItem(IDC_STATIC_NETTO_EH)->GetWindowRect(&rectStaticNettoEH);
        GetDlgItem(IDC_STATIC_MWST_EH)->GetWindowRect(&rectStaticTaxEH);
        GetDlgItem(IDC_STATIC_BRUTTO_EH)->GetWindowRect(&rectStaticBruttoEH);
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->GetWindowRect(&rectEditBruttoEH);
        GetDlgItem(IDC_EDIT_EH_TAX)->GetWindowRect(&rectEditTaxEH);
        GetDlgItem(IDC_EDIT_EH_NETTO)->GetWindowRect(&rectEditNettoEH);

        //Listcontrol
        rectListKK.SetRect(rectListFV.TopLeft().x, rectListFV.TopLeft().y, rectListEH.BottomRight().x, rectListEH.BottomRight().y);
        ScreenToClient(rectListKK);
        m_ListKK->MoveWindow(rectListKK, true);

        //Ueberschrift
        GetDlgItem(IDC_STATIC_FV)->GetWindowRect(&rectStaticFV);
        rectStaticKK.SetRect(rectStaticFV.TopLeft().x, rectStaticFV.TopLeft().y, rectStaticFV.BottomRight().x, rectStaticFV.BottomRight().y);
        ScreenToClient(rectStaticKK);
        GetDlgItem(IDC_STATIC_KK)->MoveWindow(rectStaticKK, true);

        //Static Brutto
        GetDlgItem(IDC_STATIC_BRUTTO_EH)->GetWindowRect(&rectStaticBruttoEH);
        rectStaticBruttoKK.SetRect(rectStaticBruttoEH.TopLeft().x, rectStaticBruttoEH.TopLeft().y, rectStaticBruttoEH.BottomRight().x, rectStaticBruttoEH.BottomRight().y);
        ScreenToClient(rectStaticBruttoKK);
        GetDlgItem(IDC_STATIC_BRUTTO_KK)->MoveWindow(rectStaticBruttoKK, true);

        //Static Rabatt
        GetDlgItem(IDC_STATIC_MWST_EH)->GetWindowRect(&rectStaticTaxEH);
        rectStaticTaxKK.SetRect(rectStaticTaxEH.TopLeft().x, rectStaticTaxEH.TopLeft().y, rectStaticTaxEH.BottomRight().x, rectStaticTaxEH.BottomRight().y);
        ScreenToClient(rectStaticTaxKK);
        GetDlgItem(IDC_STATIC_MWST_KK)->MoveWindow(rectStaticTaxKK, true);

        //Static Netto
        GetDlgItem(IDC_STATIC_NETTO_EH)->GetWindowRect(&rectStaticNettoEH);
        rectStaticNettoKK.SetRect(rectStaticNettoEH.TopLeft().x, rectStaticNettoEH.TopLeft().y, rectStaticNettoEH.BottomRight().x, rectStaticNettoEH.BottomRight().y);
        ScreenToClient(rectStaticNettoKK);
        GetDlgItem(IDC_STATIC_NETTO_KK)->MoveWindow(rectStaticNettoKK, true);

        //Edit Brutto
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->GetWindowRect(&rectEditBruttoEH);
        rectEditBruttoKK.SetRect(rectEditBruttoEH.TopLeft().x, rectEditBruttoEH.TopLeft().y, rectEditBruttoEH.BottomRight().x, rectEditBruttoEH.BottomRight().y);
        ScreenToClient(rectEditBruttoKK);
        GetDlgItem(IDC_EDIT_KK_BRUTTO)->MoveWindow(rectEditBruttoKK, true);

        //Edit Rabatt
        GetDlgItem(IDC_EDIT_EH_TAX)->GetWindowRect(&rectEditTaxEH);
        rectEditTaxKK.SetRect(rectEditTaxEH.TopLeft().x, rectEditTaxEH.TopLeft().y, rectEditTaxEH.BottomRight().x, rectEditTaxEH.BottomRight().y);
        ScreenToClient(rectEditTaxKK);
        GetDlgItem(IDC_EDIT_KK_TAX)->MoveWindow(rectEditTaxKK, true);

        //Edit Netto
        GetDlgItem(IDC_EDIT_EH_NETTO)->GetWindowRect(&rectEditNettoEH);
        rectEditNettoKK.SetRect(rectEditNettoEH.TopLeft().x, rectEditNettoEH.TopLeft().y, rectEditNettoEH.BottomRight().x, rectEditNettoEH.BottomRight().y);
        ScreenToClient(rectEditNettoKK);
        GetDlgItem(IDC_EDIT_KK_NETTO)->MoveWindow(rectEditNettoKK, true);

        return;
    }

    //nur Einzelhandel
    if (iZeilenEH == iZeilenGesamt)
    {
        m_ListFV->GetWindowRect(&rectListFV);
        m_ListKK->GetWindowRect(&rectListKK);
        m_ListEH->GetWindowRect(&rectListEH);
        GetDlgItem(IDC_STATIC_FV)->GetWindowRect(&rectStaticFV);
        GetDlgItem(IDC_STATIC_NETTO_EH)->GetWindowRect(&rectStaticNettoEH);
        GetDlgItem(IDC_STATIC_MWST_EH)->GetWindowRect(&rectStaticTaxEH);
        GetDlgItem(IDC_STATIC_BRUTTO_EH)->GetWindowRect(&rectStaticBruttoEH);
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->GetWindowRect(&rectEditBruttoEH);
        GetDlgItem(IDC_EDIT_EH_TAX)->GetWindowRect(&rectEditTaxEH);
        GetDlgItem(IDC_EDIT_EH_NETTO)->GetWindowRect(&rectEditNettoEH);

        //Listcontrol
        rectListEH.SetRect(rectListFV.TopLeft().x, rectListFV.TopLeft().y, rectListEH.BottomRight().x, rectListEH.BottomRight().y);
        ScreenToClient(rectListEH);
        m_ListEH->MoveWindow(rectListEH, true);

        //Ueberschrift
        GetDlgItem(IDC_STATIC_FV)->GetWindowRect(&rectStaticFV);
        rectStaticEH.SetRect(rectStaticFV.TopLeft().x, rectStaticFV.TopLeft().y, rectStaticFV.BottomRight().x, rectStaticFV.BottomRight().y);
        ScreenToClient(rectStaticEH);
        GetDlgItem(IDC_STATIC_EH)->MoveWindow(rectStaticEH, true);

        //Wertfelder bleiben

        return;
    }

    //Startwerte
    GetDlgItem(IDC_STATIC_FV)->GetWindowRect(&rectStartStaticFV);
    m_ListFV->GetWindowRect(&rectStartListFV);
    GetDlgItem(IDC_STATIC_KK)->GetWindowRect(&rectStaticKK);
    m_ListKK->GetWindowRect(&rectListKK);
    GetDlgItem(IDC_STATIC_BRUTTO)->GetWindowRect(&rectStartStaticBruttoFV);
    GetDlgItem(IDC_STATIC_MWST)->GetWindowRect(&rectStartStaticTaxFV);
    GetDlgItem(IDC_STATIC_NETTO)->GetWindowRect(&rectStartStaticNettoFV);
    GetDlgItem(IDC_EDIT_FV_BRUTTO)->GetWindowRect(&rectStartEditBruttoFV);
    GetDlgItem(IDC_EDIT_FV_TAX)->GetWindowRect(&rectStartEditTaxFV);
    GetDlgItem(IDC_EDIT_FV_NETTO)->GetWindowRect(&rectStartEditNettoFV);

    iAbstandStatic = rectStaticKK.TopLeft().y - rectStartListFV.BottomRight().y;
    iAbstandList = rectStartListFV.TopLeft().y - rectStartStaticFV.BottomRight().y;
    iAbstandBrutto = rectStartListFV.BottomRight().y - rectStartEditBruttoFV.TopLeft().y;
    iAbstandNetto = rectStartListFV.BottomRight().y - rectStartEditNettoFV.TopLeft().y;
    iAbstandTax = rectStartListFV.BottomRight().y - rectStartEditTaxFV.TopLeft().y;
    iHeight = rectStartEditBruttoFV.BottomRight().y - rectStartEditBruttoFV.TopLeft().y;

    iItemHeight = (rectStartListFV.BottomRight().y - rectStartListFV.TopLeft().y) / 14;

    if (iZeilenFV > 0)
    {
        //Listcontrol
        rectListFV.SetRect(rectStartListFV.TopLeft().x,
            rectStartListFV.TopLeft().y,
            rectStartListFV.BottomRight().x,
            (rectStartListFV.TopLeft().y + (iZeilenFV * iItemHeight)));

        rectStaticBruttoFV.SetRect(rectStartStaticBruttoFV.TopLeft().x,
            (rectListFV.BottomRight().y - iAbstandBrutto),
            rectStartStaticBruttoFV.BottomRight().x,
            (rectListFV.BottomRight().y - iAbstandBrutto + iHeight));

        rectStaticTaxFV.SetRect(rectStartStaticTaxFV.TopLeft().x,
            (rectListFV.BottomRight().y - iAbstandTax),
            rectStartStaticTaxFV.BottomRight().x,
            (rectListFV.BottomRight().y - iAbstandTax + iHeight));

        rectStaticNettoFV.SetRect(rectStartStaticNettoFV.TopLeft().x,
            (rectListFV.BottomRight().y - iAbstandNetto),
            rectStartStaticNettoFV.BottomRight().x,
            (rectListFV.BottomRight().y - iAbstandNetto + iHeight));

        rectEditBruttoFV.SetRect(rectStartEditBruttoFV.TopLeft().x,
            (rectListFV.BottomRight().y - iAbstandBrutto),
            rectStartEditBruttoFV.BottomRight().x,
            (rectListFV.BottomRight().y - iAbstandBrutto + iHeight));

        rectEditTaxFV.SetRect(rectStartEditTaxFV.TopLeft().x,
            (rectListFV.BottomRight().y - iAbstandTax),
            rectStartEditTaxFV.BottomRight().x,
            (rectListFV.BottomRight().y - iAbstandTax + iHeight));

        rectEditNettoFV.SetRect(rectStartEditNettoFV.TopLeft().x,
            (rectListFV.BottomRight().y - iAbstandNetto),
            rectStartEditNettoFV.BottomRight().x,
            (rectListFV.BottomRight().y - iAbstandNetto + iHeight));

        rectStartStaticFV.SetRect(rectStartStaticFV.TopLeft().x,
            (rectListFV.BottomRight().y + iAbstandStatic),
            rectStartStaticFV.BottomRight().x,
            (rectListFV.BottomRight().y + iAbstandStatic + iHeight));

        rectStartListFV.SetRect(rectStartListFV.TopLeft().x,
            (rectStartStaticFV.BottomRight().y + iAbstandList),
            rectListFV.BottomRight().x,
            rectListFV.BottomRight().y);
        ScreenToClient(rectListFV);
        m_ListFV->MoveWindow(rectListFV, true);
        ScreenToClient(rectStaticBruttoFV);
        GetDlgItem(IDC_STATIC_BRUTTO)->MoveWindow(rectStaticBruttoFV, true);
        ScreenToClient(rectStaticTaxFV);
        GetDlgItem(IDC_STATIC_MWST)->MoveWindow(rectStaticTaxFV, true);
        ScreenToClient(rectStaticNettoFV);
        GetDlgItem(IDC_STATIC_NETTO)->MoveWindow(rectStaticNettoFV, true);
        ScreenToClient(rectEditBruttoFV);
        GetDlgItem(IDC_EDIT_FV_BRUTTO)->MoveWindow(rectEditBruttoFV, true);
        ScreenToClient(rectEditTaxFV);
        GetDlgItem(IDC_EDIT_FV_TAX)->MoveWindow(rectEditTaxFV, true);
        ScreenToClient(rectEditNettoFV);
        GetDlgItem(IDC_EDIT_FV_NETTO)->MoveWindow(rectEditNettoFV, true);
    }

    if (iZeilenKK > 0)
    {
        //Listcontrol
        rectListKK.SetRect(rectStartListFV.TopLeft().x,
            rectStartListFV.TopLeft().y,
            rectStartListFV.BottomRight().x,
            (rectStartListFV.TopLeft().y + (iZeilenKK * iItemHeight)));

        rectStaticKK.SetRect(rectStartStaticFV.TopLeft().x,
            rectStartStaticFV.TopLeft().y,
            rectStartStaticFV.BottomRight().x,
            rectStartStaticFV.BottomRight().y);

        rectStaticBruttoKK.SetRect(rectStartStaticBruttoFV.TopLeft().x,
            (rectListKK.BottomRight().y - iAbstandBrutto),
            rectStartStaticBruttoFV.BottomRight().x,
            (rectListKK.BottomRight().y - iAbstandBrutto + iHeight));

        rectStaticTaxKK.SetRect(rectStartStaticTaxFV.TopLeft().x,
            (rectListKK.BottomRight().y - iAbstandTax),
            rectStartStaticTaxFV.BottomRight().x,
            (rectListKK.BottomRight().y - iAbstandTax + iHeight));

        rectStaticNettoKK.SetRect(rectStartStaticNettoFV.TopLeft().x,
            (rectListKK.BottomRight().y - iAbstandNetto),
            rectStartStaticNettoFV.BottomRight().x,
            (rectListKK.BottomRight().y - iAbstandNetto + iHeight));

        rectEditBruttoKK.SetRect(rectStartEditBruttoFV.TopLeft().x,
            (rectListKK.BottomRight().y - iAbstandBrutto),
            rectStartEditBruttoFV.BottomRight().x,
            (rectListKK.BottomRight().y - iAbstandBrutto + iHeight));

        rectEditTaxKK.SetRect(rectStartEditTaxFV.TopLeft().x,
            (rectListKK.BottomRight().y - iAbstandTax),
            rectStartEditTaxFV.BottomRight().x,
            (rectListKK.BottomRight().y - iAbstandTax + iHeight));

        rectEditNettoKK.SetRect(rectStartEditNettoFV.TopLeft().x,
            (rectListKK.BottomRight().y - iAbstandNetto),
            rectStartEditNettoFV.BottomRight().x,
            (rectListKK.BottomRight().y - iAbstandNetto + iHeight));

        rectStartStaticFV.SetRect(rectStartStaticFV.TopLeft().x,
            (rectListKK.BottomRight().y + iAbstandStatic),
            rectStartStaticFV.BottomRight().x,
            (rectListKK.BottomRight().y + iAbstandStatic + iHeight));

        rectStartListFV.SetRect(rectStartListFV.TopLeft().x,
            (rectStartStaticFV.BottomRight().y + iAbstandList),
            rectListKK.BottomRight().x,
            rectListKK.BottomRight().y);

        ScreenToClient(rectListKK);
        m_ListKK->MoveWindow(rectListKK, true);
        ScreenToClient(rectStaticKK);
        GetDlgItem(IDC_STATIC_KK)->MoveWindow(rectStaticKK, true);
        ScreenToClient(rectStaticBruttoKK);
        GetDlgItem(IDC_STATIC_BRUTTO_KK)->MoveWindow(rectStaticBruttoKK, true);
        ScreenToClient(rectStaticTaxKK);
        GetDlgItem(IDC_STATIC_MWST_KK)->MoveWindow(rectStaticTaxKK, true);
        ScreenToClient(rectStaticNettoKK);
        GetDlgItem(IDC_STATIC_NETTO_KK)->MoveWindow(rectStaticNettoKK, true);
        ScreenToClient(rectEditBruttoKK);
        GetDlgItem(IDC_EDIT_KK_BRUTTO)->MoveWindow(rectEditBruttoKK, true);
        ScreenToClient(rectEditTaxKK);
        GetDlgItem(IDC_EDIT_KK_TAX)->MoveWindow(rectEditTaxKK, true);
        ScreenToClient(rectEditNettoKK);
        GetDlgItem(IDC_EDIT_KK_NETTO)->MoveWindow(rectEditNettoKK, true);
    }

    if (iZeilenEH > 0)
    {
        //Listcontrol
        rectListEH.SetRect(rectStartListFV.TopLeft().x,
            rectStartListFV.TopLeft().y,
            rectStartListFV.BottomRight().x,
            (rectStartListFV.TopLeft().y + (iZeilenEH * iItemHeight)));

        rectStaticEH.SetRect(rectStartStaticFV.TopLeft().x,
            rectStartStaticFV.TopLeft().y,
            rectStartStaticFV.BottomRight().x,
            rectStartStaticFV.BottomRight().y);

        rectStaticBruttoEH.SetRect(rectStartStaticBruttoFV.TopLeft().x,
            (rectListEH.BottomRight().y - iAbstandBrutto),
            rectStartStaticBruttoFV.BottomRight().x,
            (rectListEH.BottomRight().y - iAbstandBrutto + iHeight));

        rectStaticTaxEH.SetRect(rectStartStaticTaxFV.TopLeft().x,
            (rectListEH.BottomRight().y - iAbstandTax),
            rectStartStaticTaxFV.BottomRight().x,
            (rectListEH.BottomRight().y - iAbstandTax + iHeight));

        rectStaticNettoEH.SetRect(rectStartStaticNettoFV.TopLeft().x,
            (rectListEH.BottomRight().y - iAbstandNetto),
            rectStartStaticNettoFV.BottomRight().x,
            (rectListEH.BottomRight().y - iAbstandNetto + iHeight));

        rectEditBruttoEH.SetRect(rectStartEditBruttoFV.TopLeft().x,
            (rectListEH.BottomRight().y - iAbstandBrutto),
            rectStartEditBruttoFV.BottomRight().x,
            (rectListEH.BottomRight().y - iAbstandBrutto + iHeight));

        rectEditTaxEH.SetRect(rectStartEditTaxFV.TopLeft().x,
            (rectListEH.BottomRight().y - iAbstandTax),
            rectStartEditTaxFV.BottomRight().x,
            (rectListEH.BottomRight().y - iAbstandTax + iHeight));

        rectEditNettoEH.SetRect(rectStartEditNettoFV.TopLeft().x,
            (rectListEH.BottomRight().y - iAbstandNetto),
            rectStartEditNettoFV.BottomRight().x,
            (rectListEH.BottomRight().y - iAbstandNetto + iHeight));
        ScreenToClient(rectListEH);
        m_ListEH->MoveWindow(rectListEH, true);
        ScreenToClient(rectStaticEH);
        GetDlgItem(IDC_STATIC_EH)->MoveWindow(rectStaticEH, true);
        ScreenToClient(rectStaticBruttoEH);
        GetDlgItem(IDC_STATIC_BRUTTO_EH)->MoveWindow(rectStaticBruttoEH, true);
        ScreenToClient(rectStaticTaxEH);
        GetDlgItem(IDC_STATIC_MWST_EH)->MoveWindow(rectStaticTaxEH, true);
        ScreenToClient(rectStaticNettoEH);
        GetDlgItem(IDC_STATIC_NETTO_EH)->MoveWindow(rectStaticNettoEH, true);
        ScreenToClient(rectEditBruttoEH);
        GetDlgItem(IDC_EDIT_EH_BRUTTO)->MoveWindow(rectEditBruttoEH, true);
        ScreenToClient(rectEditTaxEH);
        GetDlgItem(IDC_EDIT_EH_TAX)->MoveWindow(rectEditTaxEH, true);
        ScreenToClient(rectEditNettoEH);
        GetDlgItem(IDC_EDIT_EH_NETTO)->MoveWindow(rectEditNettoEH, true);
    }
}
