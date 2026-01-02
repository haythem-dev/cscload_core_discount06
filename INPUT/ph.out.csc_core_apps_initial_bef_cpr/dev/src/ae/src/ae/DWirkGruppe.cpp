// DWirkGruppe.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include <kndsel.h>
#include "AeDoc.h"
#include "AeFView.h"
#include "DBePosBearb.h"
#include "DArtInf.h"
#include "DKndInf.h"
#include "DWirkGruppe.h"

//Definitionen Buchen
#define BUCHEN_YES  0
#define BUCHEN_NO   1

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB      0
#define COL_BESTAND 1
#define COL_EINHEIT 2
#define COL_NAME    3
#define COL_DAF     4
#define COL_ARTCODE 5
#define COL_AEP     6
#define COL_RABATT  7
#define COL_PZN     8
#define NUM_COLUMNS 9

static COLUMNS_TYPES Columns[] =
{
    COL_KB,      "",  20, LVCFMT_RIGHT,
    COL_BESTAND, "",  70, LVCFMT_RIGHT,
    COL_EINHEIT, "",  70, LVCFMT_LEFT,
    COL_NAME,    "", 170, LVCFMT_LEFT,
    COL_DAF,     "",  40, LVCFMT_LEFT,
    COL_ARTCODE, "",  70, LVCFMT_RIGHT,
    COL_AEP,     "",  70, LVCFMT_RIGHT,
    COL_RABATT,  "",   0, LVCFMT_RIGHT,
    COL_PZN,     "",   0, LVCFMT_RIGHT,
    -1,          "",   0, 0
};


// CDWirkGruppe-Dialogfeld

IMPLEMENT_DYNAMIC(CDWirkGruppe, CDialog)
CDWirkGruppe::CDWirkGruppe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDWirkGruppe::IDD, pParent)
{
    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_KURZ_BESTAND);
    Columns[COL_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_DAF].Columns = CResString::ex().getStrTblText(AETXT_DRF);
    Columns[COL_ARTCODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[COL_AEP].Columns = CResString::ex().getStrTblText(AETXT_AEP);
    Columns[COL_RABATT].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    Columns[COL_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    m_lArtikelNr = 0;
    m_lKndNr = 0;
    m_sVzNr = 0;
    m_ifunktion = 0;
    m_CMenge = _T("");
}

CDWirkGruppe::~CDWirkGruppe()
{
}

void CDWirkGruppe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_COMBO_TYP, m_ComboTyp);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_EditMenge);
}


BEGIN_MESSAGE_MAP(CDWirkGruppe, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnChangeEditMenge)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDWirkGruppe-Meldungshandler

BOOL CDWirkGruppe::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (m_ifunktion == 1)
    {
        this->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDERANGEBOTE));
    }
    else if (m_lArtikelNr == 0)
    {
        CDialogMultiLang::OnCancel();
        return TRUE;
    }

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    s.SetSize(NUM_COLUMNS);
    ppString wirkstoff;

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();

    m_group.SetArtikel_nr(m_lArtikelNr);
    BeginWaitCursor();
    if (m_ifunktion == 1)
    {
        m_List1.SetColumnWidth(COL_RABATT, 70);
        COCCASION occ;
        struct Angebote AB;
        m_pl.clear();
        occ.SetBranchno(m_sVzNr);
        occ.SetCustomerno(m_lKndNr);
        for (;;)
        {
            if (occ.SelList() != SRV_OK)
                break;
            AB.ArtikelNr = occ.GetArticleno();
            AB.dPct = occ.GetDiscountvaluepct();
            m_pl.insert(m_pl.end(), AB);
        }
        if (m_pl.begin() == m_pl.end())
        {
            MsgBoxOK(AETXT_NO_OCCASION);
            CDialogMultiLang::OnCancel();
            EndWaitCursor();
            return TRUE;
        }
        m_group.SetFilialnr(m_sVzNr);
        for (m_it = m_pl.begin(); m_it < m_pl.end(); m_it++)
        {
            m_group.SetArtikel_nr(m_it->ArtikelNr);
            if (m_group.SelArtikel())
                break;
            if (!Fillist())
                return FALSE;
        }
    }
    else
    {
        if (m_group.SelAgent())
        {
            CDialogMultiLang::OnCancel();
            EndWaitCursor();
            return TRUE;
        }
        m_group.GetWirkstoff_nr(wirkstoff);
        CString cWirk = wirkstoff;
        if (cWirk.IsEmpty())
        {
            CDialogMultiLang::OnCancel();
            EndWaitCursor();
            return TRUE;
        }
        m_group.SetFilialnr(m_sVzNr);
        for (;;)
        {
            if (m_group.SelList() != SRV_OK)
                break;
            if (!Fillist())
                return FALSE;
        }
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    if (AeGetApp()->IsBG())
    {
        m_ComboTyp.ResetContent();
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_KRANKENKASSE));
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
        m_ComboTyp.SetCurSel(0);
    }
    else
    {
        GetDlgItem( IDC_COMBO_TYP )->EnableWindow(FALSE);
        GetDlgItem( IDC_COMBO_TYP )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_STATIC_TYP )->EnableWindow(FALSE);
        GetDlgItem( IDC_STATIC_TYP )->ShowWindow(SW_HIDE);
    }
    return TRUE;
}

void CDWirkGruppe::OnCbnSelchangeComboTyp()
{
    if (m_ComboTyp.GetCurSel() == 1)
    {
        if (!AeGetApp()->IsKndKasse() )
        {
            m_ComboTyp.SetCurSel(0);
            MsgBoxOK(AETXT_NO_KK);
        }
    }
}

void CDWirkGruppe::OnOK()
{
    UpdateData();
    if (m_CMenge.IsEmpty())
    {
        MsgBoxOK(IDP_MENGE_EINGEBEN);
        m_EditMenge.SetFocus();
        return;
    }
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    short sPreistyp = 0;
    if (AeGetApp()->IsBG())
    {
        sPreistyp = static_cast<short>(m_ComboTyp.GetCurSel());
    }
    long MengeBestellt = atol(m_CMenge);
    if (MengeBestellt != 0)
    {
        CAUFPOSBUCH aufposbuch;
        long MengeAbbuchung = MengeBestellt;
        long PosStat        = ITEM_STAT_NORMAL;
        for (;;)
        {
            aufposbuch.s.MENGEBESTELLT     = MengeBestellt;
            aufposbuch.s.MENGEBESTAETIGT   = MengeAbbuchung;
            aufposbuch.s.ARTIKEL_NR        = atol(m_List1.GetItemText(pos, COL_PZN));
            aufposbuch.s.MENGENATRA        = 0;
            aufposbuch.s.STATUS            = PosStat;
            aufposbuch.s.PREIS_TYP         = sPreistyp;
            CString Bemerkung;
            strcpy(aufposbuch.s.BEMERKUNG, (LPCTSTR)Bemerkung);

            //Buchungsversuch
            aufposbuch.Server(AasrvWritepos, PIPE_AE_SRV);
            if (aufposbuch.rc < SRV_OK)                                //Fehler
            {
                return;
            }
            if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE)          //Verfügbare Menge reichte nicht aus
            {
                CDBePosBearb dlgBePosBearb;
                dlgBePosBearb.SetBestMengeStr("%ld", MengeBestellt);
                dlgBePosBearb.m_CArtName        = m_List1.GetItemText(pos, COL_NAME);
                dlgBePosBearb.m_CArtEinh        = m_List1.GetItemText(pos, COL_EINHEIT);
                dlgBePosBearb.SetArtNr(m_List1.GetItemText(pos, COL_PZN));
                dlgBePosBearb.m_CArtCode        = m_List1.GetItemText(pos, COL_ARTCODE);
                dlgBePosBearb.SetBestand("%d", aufposbuch.s.BESTAND);
                dlgBePosBearb.SetVerbMenge(aufposbuch.s.MENGE);
                dlgBePosBearb.SetVerbFiliale(aufposbuch.s.FILIALNR1);
                dlgBePosBearb.m_CDarreichform   = m_List1.GetItemText(pos, COL_DAF);
                dlgBePosBearb.m_LiefMenge       = aufposbuch.s.BESTAND;
                dlgBePosBearb.SetBestMenge(MengeBestellt);
                dlgBePosBearb.m_CBemerkung      = Bemerkung;
                dlgBePosBearb.SetPosStat(ITEM_STAT_NACHLIEFERN);
                dlgBePosBearb.m_KndNr           = m_lKndNr;
                dlgBePosBearb.m_IdfNr           = m_lKndNr;
                if (dlgBePosBearb.DoModal() == IDOK)
                {
                    MengeAbbuchung  = dlgBePosBearb.m_Menge;
                    PosStat         = dlgBePosBearb.GetPosStat();
                    Bemerkung       = dlgBePosBearb.m_CBemerkung;
                    aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
                    continue; //Position erneut buchen
                }
                else
                {
                    return;
                }
            }
            else if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_NICHT_MOEGLICH)
            {
                MsgBoxOK(IDP_AUX_BAD_STATE);
                return;
            }
            break;
        } //Ende der for(;;)

        if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_REICHT_NICHT)   //Verfügbare Verbundmenge reichte nicht aus
        {
            CString Str;
            Str.Format(CResString::ex().getStrTblText(IDS_MENGE_BEST_BEST)
                ,aufposbuch.s.MENGEBESTELLT
                ,aufposbuch.s.MENGEBESTAETIGT
                ,aufposbuch.s.MENGE);
            CString CStr;
            CStr.Format(CResString::ex().getStrTblText(IDP_VB_MENGE_WENIG), Str.GetString());
            MsgBoxOK(CStr);
        }

        ((CAeDoc*)AeGetApp()->m_Doc)->AddPosition(aufposbuch.s);  //Positionsliste erstellen
        ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2);
    }
    m_EditMenge.SetFocus();
    m_EditMenge.SetSel(0, -1, FALSE);
}

void CDWirkGruppe::OnChangeEditMenge()
{
    CString str;

    m_EditMenge.GetWindowText(str);
    if (str.IsEmpty())                              //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (isdigit((int)chN))
    {
        AllgWertKontr(&m_EditMenge, MAXIMUM_BUCH_MENGE);
        return;
    }
    str = str.Left(str.GetLength() -1);             //letztes Zeichen löschen
    m_EditMenge.SetWindowText(str);                 //String zurückschreiben
    if (CLetterMan::InRange(chN, m_List1.GetItemCount()))
    {
        int pos = chN - AeGetApp()->Letter_A();
        CListCtrlHelper::SetFocusSelectedFocused(m_List1, pos);
    }
}

void CDWirkGruppe::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();
    *pResult = 0L;
}

BOOL CDWirkGruppe::Fillist()
{
    //Variablen
    s[COL_KB] = m_kb.Next();
    s[COL_BESTAND].Format("%d", m_group.GetBestand());
    ppString einheit;
    m_group.GetEinheit(einheit);
    s[COL_EINHEIT] = einheit;
    CARTAESEL code;
    code.s.ARTIKEL_NR = m_group.GetArtikel_nr();
    code.Server(AatartSel_Preferred);
    AllgEntfSpaces(code.s.ARTICLE_CODE);
    s[COL_ARTCODE] = code.s.ARTICLE_CODE;
    ppString name;
    m_group.GetArtikel_name(name);
    s[COL_NAME] = name;
    ppString drf;
    m_group.GetDarreichform(drf);
    s[COL_DAF] = drf;
    s[COL_PZN].Format("%d", m_group.GetArtikel_nr());
    s[COL_AEP].Format("%0.2lf", m_group.GetPreisekapo());
    if (m_ifunktion == 1)
    {
        s[COL_RABATT].Format("%0.2lf", m_it->dPct);
    }
    else
    {
        s[COL_RABATT].Empty();
    }

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
    {
        EndWaitCursor();
        return FALSE;
    }
    return TRUE;
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDWirkGruppe::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
            return 0;
        CDArtInf dlgArtInf(atol(m_List1.GetItemText(pos, COL_PZN)));
        dlgArtInf.DoModal();
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(m_lKndNr);
        dlgKndInf.SetKndNr(m_lKndNr);
        dlgKndInf.SetKndVz(m_sVzNr);
        dlgKndInf.DoModal();
        return 1L;
    }
    return 0L;
}
