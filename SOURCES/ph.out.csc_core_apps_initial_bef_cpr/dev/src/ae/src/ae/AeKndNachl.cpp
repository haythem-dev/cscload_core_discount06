// AeKndNachl.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include "DVerbBestaet.h"
#include "DBePosBearb.h"
#include <nachlief.h>
#include <kndsel.h>
#include "DKndInf.h"
#include "DArtDef.h"
#include "AeKndNachl.h"


#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definitionen Buchen
#define BUCHEN_YES      0
#define BUCHEN_NO       1

//Definition der Tabellenbreite und der Ueberschriften
#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "",  75, LVCFMT_RIGHT,
    2,  "",  45, LVCFMT_RIGHT,
    3,  "", 245, LVCFMT_LEFT,
    4,  "",  80, LVCFMT_LEFT,
    -1, "",   0, 0
};


/////////////////////////////////////////////////////////////////////////////
// CAeKndNachl dialog


CAeKndNachl::CAeKndNachl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CAeKndNachl::IDD, pParent), CPageBrowser(0)
{
    m_CPzn = _T("");
    ptrDoc = NULL;   //Zeiger auf das Dokument

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_POS);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_KDKLASSE);
}

void CAeKndNachl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PZN, m_EditPzn);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CPzn);
}

BEGIN_MESSAGE_MAP(CAeKndNachl, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnChangeEditPzn)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
    ON_BN_CLICKED(IDC_BUTTON_SEL, OnButtonSel)
    ON_BN_CLICKED(IDC_BUTTON_ARTIKEL, OnButtonArtikel)
    ON_BN_CLICKED(IDC_BUTTON_BEGRENZT, OnButtonBegrenzt)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAeKndNachl message handlers

BOOL CAeKndNachl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    m_funktion = AaauftSel_kndnl;
    GetDlgItem(IDC_BUTTON_BEGRENZT)->EnableWindow(FALSE);
    startpos = NULL;

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_YES);
    idResources.push_back(IDI_ICON_NOT);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CAeKndNachl::GetPage(const int /*nKzUpDown=NEXT_PG*/)
{
    //Variablen
    CNACHLIEF nachlief;
    NACHLIEF sNachlief;
    int gefunden;
    int max;
    CStringArray s;
    CString CStr;
    s.SetSize(NUM_COLUMNS);
    struct nachladr *newpos;
    struct nachladr *oldpos;
    struct nachladr *idfpos;
    struct satzadr *actpos;
    struct satzadr *merkpos;
    struct satzadr *inspos;

    //Anfangsinitialisierung durchfuehren
    UpdateData();
    nachlief.s.FETCH_REL = 1;          //normaler Fetch
    nachlief.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    CARTAESEL code;
    BeginWaitCursor();
    strcpy(code.s.ARTICLE_CODE,m_CPzn);
    code.Server( AatartSel_NoByCode );
    EndWaitCursor();
    nachlief.s.ARTIKEL_NR = code.s.ARTIKEL_NR;
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    nachlief.Server(m_funktion);
    m_bCursorOpen = true;       //Datenbankcurser offen
    if (nachlief.rc == SRV_SQLNOTFOUND)
    {
        CloseCursor();
        EndWaitCursor();
        MsgBoxOK(IDP_KEIN_AUFTRAG);
        return false;
    }
    m_bFirstDataset = false;
    sNachlief.IDFNR = nachlief.s.IDFNR;
    strcpy(sNachlief.MATCHCODE, nachlief.s.MATCHCODE);
    strcpy(sNachlief.KZKDKLASSE, nachlief.s.KZKDKLASSE);
    sNachlief.POSNR = 1;          //Anzahl Positionen
    newpos = (struct nachladr *)malloc(sizeof(struct nachladr));
    startpos = newpos;
    newpos->idfnr = nachlief.s.IDFNR;
    newpos->folgpos = NULL;
    actpos = (struct satzadr *)malloc(sizeof(struct satzadr));
    newpos->satzpos = actpos;
    actpos->kdauftragnr = nachlief.s.KDAUFTRAGNR;
    actpos->posnr = nachlief.s.POSNR;
    actpos->datum = nachlief.s.DATUM;
    actpos->postyp = nachlief.s.POSTYP;
    actpos->nextpos = NULL;
    CLetterMan kb;
    for (int i = 0; ; i++)
    {
        nachlief.Server(m_funktion);
        nachlief.s.FETCH_REL = 1;          //normaler Fetch
        if (nachlief.rc == SRV_OK)
        {
            if (sNachlief.IDFNR == nachlief.s.IDFNR)
            {
                merkpos = actpos;
                actpos = (struct satzadr*)malloc(sizeof(struct satzadr));
                actpos->kdauftragnr = nachlief.s.KDAUFTRAGNR;
                actpos->posnr = nachlief.s.POSNR;
                actpos->datum = nachlief.s.DATUM;
                actpos->postyp = nachlief.s.POSTYP;
                actpos->nextpos = NULL;
                merkpos->nextpos = actpos;
                sNachlief.POSNR++;
                continue;
            }
            else
            {
                gefunden = 0;
                for (idfpos = startpos; ;)
                {
                    if (idfpos->idfnr == nachlief.s.IDFNR)
                    {
                        for (inspos = idfpos->satzpos; inspos->nextpos != NULL; inspos = inspos->nextpos);
                        merkpos = inspos;
                        inspos = (struct satzadr*)malloc(sizeof(struct satzadr));
                        inspos->kdauftragnr = nachlief.s.KDAUFTRAGNR;
                        inspos->posnr = nachlief.s.POSNR;
                        inspos->datum = nachlief.s.DATUM;
                        inspos->postyp = nachlief.s.POSTYP;
                        inspos->nextpos = NULL;
                        merkpos->nextpos = inspos;
                        max = m_ListCtl.GetItemCount();
                        for (int pos = 0; pos < max; pos++)
                        {
                            if (nachlief.s.IDFNR == atol(m_ListCtl.GetItemText(pos, 1)))
                            {
                                int anzpos = atol(m_ListCtl.GetItemText(pos, 2));
                                CStr.Format("%d", ++anzpos);
                                m_ListCtl.SetItemText(pos, 2, CStr);
                            }
                        }
                        gefunden = 1;
                        break;
                    }
                    if ((idfpos = idfpos->folgpos) == NULL) break;
                }
                if (gefunden == 1) continue;
                oldpos = newpos;
                newpos = (struct nachladr*)malloc(sizeof(struct nachladr));
                oldpos->folgpos = newpos;
                newpos->idfnr = nachlief.s.IDFNR;
                newpos->folgpos = NULL;
                actpos = (struct satzadr*)malloc(sizeof(struct satzadr));
                newpos->satzpos = actpos;
                actpos->kdauftragnr = nachlief.s.KDAUFTRAGNR;
                actpos->posnr = nachlief.s.POSNR;
                actpos->datum = nachlief.s.DATUM;
                actpos->postyp = nachlief.s.POSTYP;
                actpos->nextpos = NULL;
            }
        }
        if (nachlief.rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        m_bFirstDataset = false;
        InsList(kb.Next(), &sNachlief, s);
        sNachlief.IDFNR = nachlief.s.IDFNR;
        strcpy(sNachlief.MATCHCODE, nachlief.s.MATCHCODE);
        strcpy(sNachlief.KZKDKLASSE, nachlief.s.KZKDKLASSE);
        sNachlief.POSNR = 1;          //Anzahl Positionen
    } //Ende der for()-Schleife
    InsList(kb.Next(), &sNachlief, s);
    selectpos = 0;
    CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

BOOL CAeKndNachl::InsList(char* kb, struct NACHLIEF* nachlief, class CStringArray& s)
{
    CString CStr;
    //Ausgabe in die Listbox
    s[0] = kb;
    CStr.Format("%ld", nachlief->IDFNR);
    s[1] = CStr;
    CStr.Format("%d", nachlief->POSNR);
    s[2] = CStr;
    s[3] = nachlief->MATCHCODE;
    s[4] = nachlief->KZKDKLASSE;

    if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, BUCHEN_YES))
    {
        EndWaitCursor();
        return FALSE;
    }
    return TRUE;
}

void CAeKndNachl::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
    struct nachladr *newpos;
    struct nachladr *actpos;
    struct satzadr *freepos;
    struct satzadr *merkpos;
    if (startpos == NULL)
        return;
    for (actpos = startpos;;)
    {
        newpos = actpos->folgpos;
        for (freepos = actpos->satzpos;;)
        {
            merkpos = freepos->nextpos;
            free(freepos);
            if (merkpos == NULL)
                break;
            freepos = merkpos;
        }
        free(actpos);
        if (newpos == NULL)
            break;
        actpos = newpos;
    }
}

void CAeKndNachl::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CNACHLIEF nachlief;
    nachlief.s.FETCH_REL = 0;
    BeginWaitCursor();
    nachlief.Server(m_funktion);
    EndWaitCursor();
    ResetCursor();
}

void CAeKndNachl::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
    }
}

void CAeKndNachl::SelectEintrag()
{
    /*int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    CDNACHLIEFAEN nachliefaen;
    if (pos >= 0)
    {
        nachliefaen.m_CBestand = m_ListCtl.GetItemText(pos, 8);
        nachliefaen.m_CPzn = m_ListCtl.GetItemText(pos, 1);
        nachliefaen.m_CName = m_ListCtl.GetItemText(pos, 6);
        nachliefaen.m_CEinheit = m_ListCtl.GetItemText(pos, 5);
        nachliefaen.m_CDarr = m_ListCtl.GetItemText(pos, 7);
        nachliefaen.m_CMenge = m_ListCtl.GetItemText(pos, 2);
        nachliefaen.m_CMengeAlt = m_ListCtl.GetItemText(pos, 3);
        if (nachliefaen.DoModal() == IDCANCEL) return;
        CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, BUCHEN_YES);
        m_ListCtl.SetItemText(pos, 2, nachliefaen.m_CMenge);
    }*/
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CAeKndNachl::OnHookFkt( WPARAM /*wParam*/, LPARAM /*lpMsg*/ )
{
    return 0;
}

void CAeKndNachl::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CAeKndNachl::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, false, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        MarkListPosChar((int)(pLVKeyDow->wVKey));
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == ' ')
    {
        UpdBearbkz(m_ListCtl.GetNextItem(-1, LVNI_SELECTED));
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        long KndNr=0;
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr;
            CStr  = m_ListCtl.GetItemText(pos, 1);
            KndNr = atol (CStr);
        }
        if (KndNr != 0)
        {
            dlgKndInf.SetIdfNr(KndNr);
            //nase VZ muß noch über select korrekt versorgt werden
            dlgKndInf.SetKndVz( AeGetApp()->VzNr() );
        }
        dlgKndInf.DoModal();
        return;
    }
    *pResult = 0L;
}

void CAeKndNachl::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCtl, Letter, pos))
    {
        if (pos == m_ListCtl.GetNextItem(-1, LVNI_SELECTED))
        {
            UpdBearbkz(pos);
        }
        else
        {
            MarkListPos(pos);
        }
    }
}

void CAeKndNachl::MarkListPos(int pos)
{
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos);
    selectpos = pos;
}

void CAeKndNachl::OnClickList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos == selectpos)
        UpdBearbkz(pos);
    selectpos = pos;
    *pResult = 0L;
}

//Aktualisierung der Bestandsinformation nach einer Buchung
void CAeKndNachl::UpdBearbkz(int pos)
{
    int kz = (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES) ? BUCHEN_NO : BUCHEN_YES;
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, kz);
}

void CAeKndNachl::OnButtonUpd()
{
    int max = m_ListCtl.GetItemCount();
    nachladr* actpos = startpos;
    BeginWaitCursor();
    for (int pos = 0; pos < max; pos++, actpos = actpos->folgpos)
    {
        if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES)
        {
            long KndNr = atol(m_ListCtl.GetItemText(pos, 1));
            CAUFTRAG auftrag;
            auftrag.s.IDFNR = KndNr;
            auftrag.s.KUNDENNR = KndNr;
            //nase VZ muß noch über select korrekt versorgt werden
            auftrag.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
            auftrag.Server(AasrvNeworder, PIPE_AE_SRV);
            auftrag.s.STATUS = ORD_ZURUECKGEST_DAFUE;
            auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
        }
    }
    EndWaitCursor();
    CDialogMultiLang::OnCancel();
}

void CAeKndNachl::OnChangeEditPzn()
{
    CString CPzn;
    m_EditPzn.GetWindowText(CPzn);
    if (CPzn.IsEmpty())
        GetDlgItem(IDC_BUTTON_BEGRENZT)->EnableWindow(FALSE);
    else
        GetDlgItem(IDC_BUTTON_BEGRENZT)->EnableWindow();
}

void CAeKndNachl::OnButtonSel()
{
    m_funktion = AaauftSel_kndnl;
    GetPage();
}

void CAeKndNachl::OnButtonArtikel()
{
    //Definition Artikel
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() == IDOK)
    {
        m_CPzn = dlgArtDef.GetArticleCode();
        UpdateData(FALSE);
    }
}

void CAeKndNachl::OnButtonBegrenzt()
{
    m_funktion = AaauftSel_kndnlprio;
    GetPage();
}
