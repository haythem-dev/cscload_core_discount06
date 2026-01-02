/**************************************************************************************/
/*                                                                                    */
/*  Programm   : Anzeigen der Lieferscheindaten am Bildschirm an der Enkontrolle      */
/*  Hauptmodul : wepserv.cpp                                                          */
/*  Modul      : welaek.cpp                                                           */
/*  Autor      : Schmidt-Rehschuh                                                     */
/*  Erstellt   : 27.10.1994                                                           */
/*  Geaendert  : 09.06.1997 Anpassung an Phosix                                       */
/*  Aufgabe    : Servermodul; Abfragen der Relationen kdauftrag, kdauftragpos         */
/*                                                                                    */
/**************************************************************************************/

/** INCLUDES (STANDARD) ***************************************************************/

#include "stdafx.h"
#include "welaek.h"
#include <artsel.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

/** IFDEF (STANDARD) ******************************************************************/

/** DEFINES ***************************************************************************/


#define L_BARCODE         15                        /* erste Zeichen ist:-         */
#define L_DATUM            4                        /* Auflösung Barcode: Datum    */
#define L_LSNR             6                        /* Auflösung Barcode: Ls-Nr    */
#define L_SEIT_NR          3                        /* Auflösung Barcode: Seit-Nr  */
#define L_TEXT           100                        /* Länge Textfeld              */
#define L_AUSWAHL          3                        /* Länge 1.Spalte (String)     */
#define L_BLOCK            2                        /* Länge Blockeingabe          */
#define L_MENGE            5                        /* Länge Mengeneingabe         */
#define L_EAN_CODE        13                        /* Länge EAN-Nr                */
#define LEER               0                        /* Eingabenprüfung             */
#define YES                1                        /* Schalterstellung an         */
#define NO                 0                        /* Schalterstellung aus        */
#define OK                 0                        /* in Ordnung                  */
#define FEHLER            -1                        /* Fehler aufgetreten (Pipe)   */
#define WARNUNG           -2                        /* Warnung aufgetreten (Pipe)  */
#define MENGE_ZUVIEL      -3
#define ANZ_SPALTEN        7                        /* gesamtnazahl der Spalten    */
#define ZEILE_SPALTE       0                        /* erste Spalte                */
#define LAGORT_SPALTE      1                        /* zweite Spalte               */
#define MENGE_SPALTE       2                        /* dritte Spalte               */
#define EINH_SPALTE        3                        /* vierte Spalte               */
#define ARTNAME_SPALTE     4                        /* fünfte Spalte               */
#define ARTIKELNR_SPALTE   5                        /* sechste Spalte              */
#define MENGE_SPALTE_HIDE  6                        /* siebte Spalte               */
#define BST_A             65                        /* Ascii-Code für A            */
#define BST_Z             90                        /* Ascii-Code für Z            */
#define ENTER             13                        /* Ascii-Code für Returntaste  */
#define LS_ALT            14                        /* Barcodelänge BS2000         */
#define LS_NEU            16                        /* Barcodelänge WAS            */
#define MAX_STR_LAENGE    50                        /* maximale Laenge einer Zeile */
#define ALT_TASTE        0x80                       /* ALT-Taste                   */
#define STRENDE          '\0'                       /* Neue-Zeile                  */
#define LINEFEED         '\n'                       /* Linefeed(Return)            */
#define BLANC            ' '                        /* Leerzeichen                 */
#define FILLER           "  "                       /* Leer-String                 */
#define ARTIKEL_INFO     "INFO"                     /* Artikelinformation (Server) */
#define BLINKEN          "1"
#define VORWAERTS        0
#define RUECKWAERTS      1
#define STR_ENDE         '\0'
#define M_QUESTION      MB_ICONQUESTION |MB_DEFBUTTON1

enum COLUMNS { P_KST = 0, P_LAGERFACHNR, P_MENGEGELIEFERT, P_EINHEIT, P_ARTIKELNAME, P_ARTIKELNR, P_MENGE };

/*** MACRO ****************************************************************/

#define NUM_COLUMNS(x) sizeof( x ) / ( ( 3 * sizeof( int ) ) + sizeof( char * ) )

/*** STRUCTUR *************************************************************/

struct SELLS
{
    char datum[L_DATUM + 1];
    char ls_nr[L_LSNR + 1];
    char seit_nr_ls[L_SEIT_NR + 1];
};

static int  artikelmenge;
static bool status_block = true;
static char block_von[L_BLOCK + 1];
static char block_bis[L_BLOCK + 1];
static int  g_iSound = IDC_RADIO13;

/** DECLARATION ***********************************************************************/

void SetStringInStruct(struct SELLS*, char*, int);
void SetStaticTextInDialog(class CAUFENDKOPF* d, class CWeLaEk* dlg, char*);
void ChangeLagerort(char*);
void SetzeStrEnde(char*, int);
void SetzePruefziffer(char*);
void SendeSound(LPSTR sound);
static int WertKontr(class CEdit* edit, long max);


/** GLOBALE ***************************************************************************/

LPSTR m_SendeFehler = "ding.wav";
LPSTR m_SendeWarnung = " ";


/** KLASSENDECLARATION: CWELAEKLS******************************************************/

CWeLaEkLs::CWeLaEkLs(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CWeLaEkLs::IDD, pParent)
{
}

/** FUNKTION:DODATAEXCHANGE (Dialog 1) ************************************************/

void CWeLaEkLs::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDITBLOCKBIS, m_cEditBlockbis);
    DDX_Control(pDX, IDC_EDITBLOCKVON, m_cEditBlockvon);
    DDX_Control(pDX, IDC_EDITSEITNR, m_cEditSeitnr);
    DDX_Control(pDX, IDC_EDITRECHNR, m_cEditRechnr);
    DDX_Control(pDX, IDC_EDITBARCODE, m_cEditBarcode);
}

/** BEGIN-MESSAGE-MAP ***************+*************************************************/

BEGIN_MESSAGE_MAP(CWeLaEkLs, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KLANG, OnButtonKlang)
END_MESSAGE_MAP()


/** KLASSENDECLARATION: CWELAEK ****+**************************************************/

CWeLaEk::CWeLaEk(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CWeLaEk::IDD, pParent)
{
    m_StaticAdr1 = "";
    m_StaticAdr2 = "";
    m_StaticAdr3 = "";
    m_StaticLsnr = "";
    m_StaticHausnr = "";
    m_StaticTournr = "";
    m_StaticKontnr = "";
    m_StaticKundnr = "";
    m_StaticAuftnr = "";
    m_StaticSeitnr = "";
    m_StaticAdr4 = "";
    m_iAnzPositionen = 0;
}

/** FUNKTION:DODATAEXCHANGE ***********************************************************/

void CWeLaEk::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_cListAuftrag);
    DDX_Control(pDX, IDC_EDITARTIKELNR, m_cEditArtikelnr);
    DDX_Text(pDX, IDC_STATICADR1, m_StaticAdr1);
    DDX_Text(pDX, IDC_STATICADR2, m_StaticAdr2);
    DDX_Text(pDX, IDC_STATICADR3, m_StaticAdr3);
    DDX_Text(pDX, IDC_STATICLSNR, m_StaticLsnr);
    DDX_Text(pDX, IDC_STATICHAUSNR, m_StaticHausnr);
    DDX_Text(pDX, IDC_STATICTOURNR, m_StaticTournr);
    DDX_Text(pDX, IDC_STATICKONTNR, m_StaticKontnr);
    DDX_Text(pDX, IDC_STATICKUNDNR, m_StaticKundnr);
    DDX_Text(pDX, IDC_STATICAUFTNR, m_StaticAuftnr);
    DDX_Text(pDX, IDC_STATICSEITNR, m_StaticSeitnr);
    DDX_Text(pDX, IDC_STATICADR4, m_StaticAdr4);
}

/** BEGIN-MESSAGE-MAP *****************************************************************/

BEGIN_MESSAGE_MAP(CWeLaEk, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTONBEARBEITET, OnButtonbearbeitet)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/** KLASSENDECLARATION: CWELAEKME *****************************************************/

CWeLaEkMe::CWeLaEkMe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CWeLaEkMe::IDD, pParent)
{
    m_StaticArtikelnr = "";
    m_StaticEinheit = "";
    m_StaticArtikelname = "";
}

/** FUNKTION:DODATAEXCHANGE (CWELAEKME) **********************************************/

void CWeLaEkMe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDITMENGE, m_cEditMenge);
    DDX_Text(pDX, IDC_STATICARTIKELNR, m_StaticArtikelnr);
    DDX_Text(pDX, IDC_STATICEINH, m_StaticEinheit);
    DDX_Text(pDX, IDC_STATICARTNAME, m_StaticArtikelname);
}

/** BEGIN MESSAGE MAP(CWELAEKLS) ******************************************************/

BEGIN_MESSAGE_MAP(CWeLaEkMe, CDialogMultiLang)
END_MESSAGE_MAP()

/** KLASSENDECLARATION: CWELAEK ****+**************************************************/

CWeLaEkMsg::CWeLaEkMsg(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CWeLaEkMsg::IDD, pParent)
{
    m_StaticMsg = "";
    m_cStringText = "";
    m_cStringStatus = "";
}

/** FUNKTION:DODATAEXCHANGE ***********************************************************/

void CWeLaEkMsg::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATICSTATUS, m_cStaticStatus);
    DDX_Control(pDX, IDC_STATIC_BMP_HIN, m_cStaticBtmHinweis);
    DDX_Control(pDX, IDOK, m_cButtonOk);
    DDX_Control(pDX, IDC_STATICMSG, m_cStaticMsgbox);
    DDX_Text(pDX, IDC_STATICMSG, m_StaticMsg);
    DDX_Text(pDX, IDC_STATIC_BMP_HIN, m_cStringText);
    DDX_Text(pDX, IDC_STATICSTATUS, m_cStringStatus);
}

/** BEGIN MESSAGE MAP(CWELAEKMSG) *****************************************************/

BEGIN_MESSAGE_MAP(CWeLaEkMsg, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


/** KLASSENDECLARATION: CWELAEKKL*****************************************************/

CWeLaEkKl::CWeLaEkKl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CWeLaEkKl::IDD, pParent)
{
}

/** FUNKTION:DODATAEXCHANGE (CWELAEKKL) **********************************************/

void CWeLaEkKl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
}

/** BEGIN MESSAGE MAP(CWELAEKKL) *****************************************************/

BEGIN_MESSAGE_MAP(CWeLaEkKl, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
    ON_BN_CLICKED(IDC_RADIO13, OnRadioAnruf)
    ON_BN_CLICKED(IDC_RADIO11, OnRadioKlingel)
    ON_BN_CLICKED(IDC_RADIO12, OnRadioSound)
    ON_BN_CLICKED(IDC_RADIO10, OnRadioText)
    ON_BN_CLICKED(IDC_RADIO14, OnRadioTon)
END_MESSAGE_MAP()

/*************************************************************************************/
/** EIGENE FUNKTIONEN ****************************************************************/
/*************************************************************************************/

/*############# CWELAEKLS ###########################################################*/
/** FUNKTION: ONINITDILOG (Dialog1) **************************************************/

BOOL CWeLaEkLs::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    return TRUE;
}

/** FUNKTION: ONOK (Dialog1 ) ********************************************************/

void CWeLaEkLs::OnOK()
{
    CAUFENDKOPF aufendkopf;
    CWeLaEk dlgWeLaEk;
    struct SELLS sells;
    char barcode[L_BARCODE + 1];
    int laenge;

    if ( !status_block && (GetFocus() == GetDlgItem(IDC_EDITBLOCKVON) ||
         GetFocus() == GetDlgItem(IDC_EDITBLOCKBIS)) )
    {
        GotoDlgCtrl(GetDlgItem(IDC_EDITBARCODE));
        return;
    }

    if (status_block)
    {
        m_cEditBlockvon.GetWindowText(block_von, L_BLOCK + 1);
        m_cEditBlockbis.GetWindowText(block_bis, L_BLOCK + 1);
        if (!atoi(block_von))
            strcpy(block_von, "  ");

        int von;
        int bis;
        if ((von = atoi(block_von)) >= (bis = atoi(block_bis)) && (von != 0 || bis != 0))
        {
            MsgBoxOK(IDS_COMP_START_END_BLOCK);
            GetDlgItem(IDC_EDITBLOCKVON)->SetFocus();
            return;
        }

        if (MsgBoxYesNo(IDS_BLOCK_INPUT, M_QUESTION) == IDNO)
        {
            m_cEditBlockvon.SetWindowText("");
            m_cEditBlockbis.SetWindowText("");
            GetDlgItem(IDC_EDITBLOCKVON)->SetFocus();
            return;
        }

        m_cEditBlockvon.EnableWindow(FALSE);
        m_cEditBlockbis.EnableWindow(FALSE);
        status_block = false;

        GotoDlgCtrl(GetDlgItem(IDC_EDITBARCODE));
        return;
    }

    if ( m_cEditBarcode.GetWindowTextLength() == LEER &&
         m_cEditRechnr.GetWindowTextLength() == LEER &&
         m_cEditSeitnr.GetWindowTextLength() == LEER )
    {
        dlgWeLaEk.MsgDs(
            (char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_NO_BARCODE).GetString() );
        GotoDlgCtrl(GetDlgItem(IDC_EDITRECHNR));
        return;
    }

    if ( GetFocus() == GetDlgItem(IDC_EDITBARCODE) ||
         GetFocus() == GetDlgItem(IDOK) )
    {
        if ((laenge = m_cEditBarcode.GetWindowTextLength()) == LEER)
        {
            dlgWeLaEk.MsgDs(
                (char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(),
                (char*)CResString::ex().getStrTblText(AETXT_NO_BARCODE).GetString() );
            GotoDlgCtrl(GetDlgItem(IDC_EDITRECHNR));
            return;
        }

        m_cEditBarcode.GetWindowText(barcode, L_BARCODE);
        SetStringInStruct(&sells, barcode, laenge);
    }

    if ( GetFocus() == GetDlgItem(IDC_EDITRECHNR) ||
         GetFocus() == GetDlgItem(IDC_EDITSEITNR) ||
         GetFocus() == GetDlgItem(IDOK) )
    {
        if (m_cEditRechnr.GetWindowTextLength() == LEER)
        {
            dlgWeLaEk.MsgDs(
                (char*)CResString::ex().getStrTblText(AETXT_HINWEIS).GetString(),
                (char*)CResString::ex().getStrTblText(AETXT_AUFTRAGNR_EINGEBEN).GetString() );
            GotoDlgCtrl(GetDlgItem(IDC_EDITRECHNR));
            return;
        }
        if (m_cEditSeitnr.GetWindowTextLength() == LEER)
        {
            dlgWeLaEk.MsgDs(
                (char*)CResString::ex().getStrTblText(AETXT_HINWEIS).GetString(),
                (char*)CResString::ex().getStrTblText(AETXT_SEITE_EINGEBEN).GetString() );
            GotoDlgCtrl(GetDlgItem(IDC_EDITSEITNR));
            return;
        }

        m_cEditRechnr.GetWindowText(barcode, L_LSNR + 1);
        sprintf(sells.ls_nr, "%*.*s", L_LSNR, L_LSNR, barcode);
        m_cEditSeitnr.GetWindowText(barcode, L_SEIT_NR);
        sprintf(sells.seit_nr_ls, "%*.*s", L_SEIT_NR, L_SEIT_NR, barcode);
    }

    aufendkopf.s.RECHNUNGNR = atoi(sells.seit_nr_ls);   // notloesung wegen koeinheit!!!!
    if (dlgWeLaEk.CallServerLs(&aufendkopf, sells.ls_nr) == SRV_SQLNOTFOUND)
    {
        dlgWeLaEk.MsgDs(
            (char*)CResString::ex().getStrTblText(IDS_TXT_WARNUNG_DBLPKT).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_KEIN_LIEFERSCHEIN).GetString() );
        GotoDlgCtrl(GetDlgItem(IDC_EDITBARCODE));
        return;
    }

    SetStaticTextInDialog(&aufendkopf, &dlgWeLaEk, sells.seit_nr_ls);

    dlgWeLaEk.DoModal();

    m_cEditBarcode.SetWindowText("");
    m_cEditRechnr.SetWindowText("");
    m_cEditSeitnr.SetWindowText("");

    GotoDlgCtrl(GetDlgItem(IDC_EDITBARCODE));
}

/** FUNKTION: ONCANCEL (Dialog1) *****************************************************/

void CWeLaEkLs::OnCancel()
{
    status_block = true;
    CDialogMultiLang::OnCancel();
}

/** FUNKTION: ONCANCEL (Dialog1) *****************************************************/

void CWeLaEkLs::OnButtonKlang()
{
    CWeLaEkKl dlgWeLaEkKl;
    dlgWeLaEkKl.DoModal();
}

/** FUNKTION: SETSTATICTEXTINDIALOG **************************************************/

void SetStaticTextInDialog(class CAUFENDKOPF* ls, class CWeLaEk* dlg, char* seit_nr_ls)
{

    dlg->m_StaticLsnr.Format("%ld", ls->s.KDAUFTRAGNR);
    dlg->m_StaticSeitnr = seit_nr_ls;
    dlg->m_StaticHausnr.Format("%d", ls->s.FILIALNR);
    dlg->m_StaticAuftnr.Format("%ld", ls->s.RECHNUNGNR);
    dlg->m_StaticTournr = ls->s.TOURID;
    dlg->m_StaticKontnr.Format("%ld", ls->s.IDFNR);
    dlg->m_StaticKundnr.Format("%ld", ls->s.KDNR);
    dlg->m_StaticAdr1 = ls->s.NAMEAPO;
    dlg->m_StaticAdr2 = ls->s.NAMEINHABER;
    dlg->m_StaticAdr3 = ls->s.STRASSE;
    dlg->m_StaticAdr4.Format("%s %s", ls->s.POSTLEITZAHL, ls->s.ORT);
}

/*############# CWELAEK #############################################################*/
/** FUNKTION: ONINITDIALOG ***********************************************************/

BOOL CWeLaEk::OnInitDialog()
{
    COLUMNS_TYPES Columns[] = {
        P_KST,            CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE).GetString(),  20, LVCFMT_LEFT,
        P_LAGERFACHNR,    CResString::ex().getStrTblText(AETXT_LAGERORT).GetString(),       60, LVCFMT_LEFT,
        P_MENGEGELIEFERT, CResString::ex().getStrTblText(AETXT_MENGE).GetString(),          50, LVCFMT_LEFT,
        P_EINHEIT,        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),        60, LVCFMT_CENTER,
        P_ARTIKELNAME,    CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),   204, LVCFMT_LEFT,
        P_ARTIKELNR,      CResString::ex().getStrTblText(AETXT_ARTIKEL_NR).GetString(),     60, LVCFMT_LEFT,
        P_MENGE,          "",                                                                0, LVCFMT_LEFT,
        -1,               "",                                                                0, 0
    };

    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_cListAuftrag))
    {
        return FALSE;
    }

    m_iAnzPositionen = ReadInListBox(NUM_COLUMNS(Columns));
    if (m_iAnzPositionen == LEER)
    {
        MsgDs(
            (char*)CResString::ex().getStrTblText(AETXT_HINWEIS).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_KEINE_POSITIONEN).GetString() );
        OnCancel();
    }
    return TRUE;
}

/** FUNKTION: CALLSERVLS *************************************************************/

int CWeLaEk::CallServerLs(class CAUFENDKOPF* ls, char* ls_nr)
{
    ls->s.KDAUFTRAGNR = atol(ls_nr);

    BeginWaitCursor();
    ls->Server(AaauftSel_end_kopf);     //  ls->s.LS_NR
    EndWaitCursor();

    return ls->rc;
}

/** FUNKTION: SetStringInStruct *******************************************************/

void SetStringInStruct(struct SELLS* sells, char* str, int)
{
    if (str[0] == '-')
        str++;
    strncpy(sells->ls_nr, str + 1, L_LSNR); // erste zeichen immer 9
    sells->ls_nr[L_LSNR] = STRENDE;
    strncpy(sells->seit_nr_ls, str + 1 + L_LSNR, L_SEIT_NR);
    sells->seit_nr_ls[L_SEIT_NR] = STRENDE;
}

/** FUNKTION: MSGDS (MessageBox) *****************************************************/

void CWeLaEk::MsgDs(char* titel, char* msg)
{
    CWeLaEkMsg msgbox;
    CString    filler;

    msgbox.m_cStringStatus = "0";
    if (titel == CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT))
        SendeSound(m_SendeFehler);
    else if (titel == CResString::ex().getStrTblText(IDS_TXT_WARNUNG_DBLPKT))
        SendeSound(m_SendeWarnung);

    msgbox.m_StaticMsg = msg;
    msgbox.m_cStringText = titel;

    msgbox.DoModal();
}

/** FUNKTION: READINLISTBOX **********************************************************/

int CWeLaEk::ReadInListBox(int iCountColumns)
{
    int zaehler = 0;
    CAUFENDPOS lszart;
    char block[3];
    char lagerort[11];
    long artikel_nr = -1;
    long menge = 0;
    CStringArray output;
    char bst = BST_A;

    output.SetSize(iCountColumns);
    lszart.s.FETCH_REL = 1;
    lszart.s.KDAUFTRAGNR = atol(m_StaticLsnr);
    lszart.s.KOBEHAELTNR = atoi(m_StaticSeitnr);

    int von;
    int bis;
    if ((von = atoi(block_von)) == 0 && (bis = atoi(block_bis)) == 0)
    {
        sprintf(lszart.s.LAGERFACHNR, "%*.*s%*.*s", L_BLOCK, L_BLOCK, block_von, L_BLOCK, L_BLOCK, block_bis);
    }
    else
    {
        sprintf(lszart.s.LAGERFACHNR, "%0*d%0*d", L_BLOCK, atoi(block_von), L_BLOCK, atoi(block_bis));
    }
    BeginWaitCursor();
    m_cListAuftrag.DeleteAllItems();
    lszart.Server(AaauftSel_end_pos);
    while (lszart.rc == SRV_OK)
    {
        if (lszart.s.LAGERFACHNR[1] != ' ')   // erste stelle immer leer!
        {
            memcpy(block, lszart.s.LAGERFACHNR + 1, 2);
            block[2] = STRENDE;
        }

        if (lszart.s.LAGERFACHNR[1] == ' ')
            sprintf(lszart.s.LAGERFACHNR, "%s%s", block, lszart.s.LAGERFACHNR + 3);

        if (bst == (BST_Z + 1))
            bst = BST_A;

        if (lszart.s.ARTIKEL_NR != artikel_nr)
        {
            artikel_nr = lszart.s.ARTIKEL_NR;
            menge = lszart.s.MENGEGELIEFERT;
        }
        else
        {
            m_cListAuftrag.DeleteItem(m_cListAuftrag.GetItemCount() - 1);
            lszart.s.MENGEGELIEFERT = lszart.s.MENGEGELIEFERT + menge;
            menge = lszart.s.MENGEGELIEFERT;    // menge zwischenspeichern
        }

        output[P_KST] = bst++;
        strcpy(lagerort, lszart.s.LAGERFACHNR + 1);
        ChangeLagerort(lagerort);
        output[P_LAGERFACHNR].Format("%s", lagerort);
        output[P_MENGEGELIEFERT] = " ";
        output[P_EINHEIT].Format("%s", lszart.s.EINHEIT);
        output[P_ARTIKELNAME].Format("%s", lszart.s.ARTIKEL_NAME);
        output[P_ARTIKELNR].Format("%07ld", lszart.s.ARTIKEL_NR);
        output[P_MENGE].Format("%ld", lszart.s.MENGEGELIEFERT);

        if (!CListCtrlHelper::AppendItem(m_cListAuftrag, iCountColumns, output))
        {
            return FALSE;
        }

        ++zaehler;
        lszart.Server(AaauftSel_end_pos);
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_cListAuftrag, 0);
    lszart.s.FETCH_REL = 0;
    lszart.Server(AaauftSel_end_pos);
    EndWaitCursor();

    return zaehler;
}

/** FUNKTION: ONCANCEL ***************************************************************/

void CWeLaEk::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

/** FUNKTION:OCLKLAUFTRAG( CWELAEK ) *********************************************/

void CWeLaEk::OnDblclkList1(NMHDR*, LRESULT* pResult)
{
    *pResult = 0L;

    int zeile = m_cListAuftrag.GetNextItem(-1, LVNI_SELECTED);
    if (zeile >= 0)
    {
        if (InsertCountOfArticle(zeile) == IDOK)
            DeleteStringFromListBox(zeile, m_cListAuftrag.GetItemCount(), YES);
    }

    GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
}

/** FUNKTION:ONOK ( AUFTRAGBEARBEITUNG ) *********************************************/

void CWeLaEk::OnOK()
{
    CAUFEAN ean;
    char artikel_nr[L_AUFENDPOS_ARTIKEL_NR];
    char text[512];
    int rc;

    if (m_cEditArtikelnr.GetWindowTextLength() == LEER)
    {
        MsgDs(
            (char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_KEINE_ARTIKELNR).GetString() );
        GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
        return;
    }

    int laenge = (int)m_cEditArtikelnr.GetWindowTextLength();
    if (laenge > L_EAN_CODE)
    {
        MsgDs(
            (char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_FALSCHE_PZN).GetString() );
        GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
        return;
    }

    if (laenge == L_EAN_CODE)
    {
        m_cEditArtikelnr.GetWindowText(ean.s.EAN_NR, L_EAN_CODE + 1);
        ean.Server(AaauftSel_ean_uni);
        if (ean.rc == SRV_OK)
            sprintf(artikel_nr, "%ld", ean.s.ARTIKEL_NR);
        else
        {
            MsgDs(
                (char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(),
                (char*)CResString::ex().getStrTblText(AETXT_FALSCHE_EAN).GetString() );
            // früher hat die Serverfunktion mal einen fehler geliefert.
            //  FUNKTION liefert WARNUNG wenn EAN nicht gepflegt!!!!
            GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
            return;
        }
    }
    else
        m_cEditArtikelnr.GetWindowText(artikel_nr, L_AUFENDPOS_ARTIKEL_NR);

    if (CheckNumberOfArticle(artikel_nr) != OK)
    {
        // Pruefen ob Artikel in LS vorhanden, wegen Block-Mechanismus
        rc = PruefeArtikelInLs(artikel_nr);
        if (rc != OK)
        {
            if (rc == MENGE_ZUVIEL)
                sprintf(text, CResString::ex().getStrTblText(IDS_ART_UEBERMENGE), artikel_nr);
            else
                CallArtikelInfo(artikel_nr, text);
            MsgDs((char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(), text);
        }
    }

    m_cEditArtikelnr.SetWindowText("");
    GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
}

/** FUNKTION: ONBUTTONBEARBEITET (CWELAEK) *******************************************/

int CWeLaEk::PruefeArtikelInLs(char* artikel_nr)
{
    CAUFENDPOS lszart;
    int  iBlock;
    char szBlock[3];

    lszart.s.KDAUFTRAGNR = atol(m_StaticLsnr);
    lszart.s.KOBEHAELTNR = atoi(m_StaticSeitnr);
    lszart.s.ARTIKEL_NR = atol(artikel_nr);

    lszart.Server(AaauftSel_art_pos);
    if (lszart.rc == SRV_OK)
    {
        memcpy(szBlock, lszart.s.LAGERFACHNR + 1, 2);
        szBlock[2] = '\0';
        if ((iBlock = atoi(szBlock)) >= atoi(block_von) && iBlock <= atoi(block_bis))
        {
            return MENGE_ZUVIEL;
        }
    }
    return lszart.rc;
}


/** FUNKTION: ONBUTTONBEARBEITET (CWELAEK) *******************************************/

void CWeLaEk::OnButtonbearbeitet()
{
    int zeile;
    CString cSMenge;

    int anzahl = m_cListAuftrag.GetItemCount();
    if (anzahl < m_iAnzPositionen)
    {
        for (zeile = 0; zeile < anzahl; zeile++)
        {
            cSMenge = m_cListAuftrag.GetItemText(zeile, P_MENGE);
            m_cListAuftrag.SetItemText(zeile, P_MENGEGELIEFERT, cSMenge);
        }
    }

    GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
}

/** FUNKTION: CHECKNUMBEROFARTICLE ***************************************************/

int CWeLaEk::CheckNumberOfArticle(char* artikel_nr)
{
    char nummer[L_AUFENDPOS_ARTIKEL_NR];
    int  zeile  = 0;
    int  anzahl = 0;
    int  rc     = FEHLER;

    if (artikel_nr[0] == '-')
        sprintf(artikel_nr, "%s", artikel_nr + 1);

    if (artikel_nr[0] == 'A' || artikel_nr[0] == 'E')
        sprintf(artikel_nr, "%s", artikel_nr + 2);

    SetzeStrEnde(artikel_nr, RUECKWAERTS);
    if (*artikel_nr != '0' && strlen(artikel_nr) == 6)
        SetzePruefziffer(artikel_nr);
    else if (strlen(artikel_nr) < 7)
    {
        sprintf(artikel_nr, "%07ld", atol(artikel_nr));
    }

    anzahl = m_cListAuftrag.GetItemCount();
    for (zeile = 0; zeile < anzahl; zeile++)
    {
        strcpy(nummer, m_cListAuftrag.GetItemText(zeile, P_ARTIKELNR));
        if (!strncmp(nummer, artikel_nr, 7))
        {
            DeleteStringFromListBox(zeile, anzahl, NO);
            rc = OK;
            break;
        }
    }

    return rc;
}

/** FUNKTION: CHECKIDOFSELECT ********************************************************/

int CWeLaEk::CheckIdOfSelect(char* auswahl)
{
    char char_auswahl[3];

    int i      = m_cListAuftrag.GetTopIndex();
    int anzahl = m_cListAuftrag.GetItemCount();

    for (int zeile = i; zeile < anzahl; zeile++)
    {
        strcpy(char_auswahl, m_cListAuftrag.GetItemText(zeile, P_KST));
        if (auswahl[0] == char_auswahl[0])
        {
            m_cListAuftrag.GetNextItem(zeile, LVNI_SELECTED);

            if (InsertCountOfArticle(zeile) == IDCANCEL)
                return FEHLER;

            DeleteStringFromListBox(zeile, m_cListAuftrag.GetItemCount(), YES);
            return OK;
        }
    }

    return FEHLER;
}

/** FUNKTION: CALLARTIKELINFO ********************************************************/

void CWeLaEk::CallArtikelInfo(char* artikel_nr, char* text)
{
    CAUFENDART art;
    char lagerort[10];

    art.s.ARTIKEL_NR = atol(artikel_nr);

    BeginWaitCursor();
    art.Server(AaauftSel_end_art);
    EndWaitCursor();
    if (art.rc != SRV_OK)
        strcpy(text, (char*)CResString::ex().getStrTblText(IDS_ATICLE_NOT_EXISTS).GetString());
    else
    {
        if (atoi(block_von) == 0 && atoi(block_bis) == 0)
            strcpy(lagerort, art.s.LAGERFACHNR);
        else
            sprintf(lagerort, "%0*ld", 7, atol(art.s.LAGERFACHNR));
        ChangeLagerort(lagerort);
        sprintf(text,
            CResString::ex().getStrTblText(IDS_ARTICLE_DATA).GetString(),
            CResString::ex().getStrTblText(IDS_NO_ARTICLE).GetString(),
            art.s.EINHEIT,
            art.s.ARTIKEL_NAME,
            lagerort);
    }
}

/** FUNKTION: DELETESTRINGFROMLISTBOX ************************************************/

void ChangeLagerort(char* lagerort)
{
    char txt[8];

    strcpy(txt, lagerort + 4);
    lagerort[4] = BLANC;
    lagerort[5] = txt[0];
    lagerort[6] = BLANC;
    lagerort[7] = txt[1];
    lagerort[8] = txt[2];
    lagerort[9] = STRENDE;
}

/** FUNKTION: DELETESTRINGFROMLISTBOX ************************************************/

void CWeLaEk::DeleteStringFromListBox(int zeile, int anzahl, int status)
{
    int bst = BST_A;
    int  spalte;
    char str[2];
    int menge;
    char text[L_TEXT];

    CString char_menge = m_cListAuftrag.GetItemText(zeile, P_MENGE);
    if (status)
        menge = atoi(char_menge) - artikelmenge;
    else
        menge = atoi(char_menge) - 1;

    if (menge > 0)
    {
        char_menge.Format("%d", menge);
        // Anzeige hier nur über Buchstabenauswahl
        if (status)
            m_cListAuftrag.SetItemText(zeile, P_MENGEGELIEFERT, char_menge);
        m_cListAuftrag.SetItemText(zeile, P_MENGE, char_menge);
    }
    else
    {
        if (menge < 0)
        {
            sprintf(text, "%d %s", menge * (-1), CResString::ex().getStrTblText(AETXT_ARTIKEL_ZUVIEL).GetString());
            MsgDs((char*)CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(), text);
        }

        m_cListAuftrag.DeleteItem(zeile);
        for (spalte = 0; spalte < (anzahl - 1); spalte++)
        {
            if (bst == (BST_Z + 1))
                bst = BST_A;
            sprintf(str, "%c", bst++);
            m_cListAuftrag.SetItemText(spalte, P_KST, str);
        }
        if ((anzahl - 1) == 0)
        {
            MsgDs(
                (char*)CResString::ex().getStrTblText(AETXT_HINWEIS).GetString(),
                (char*)CResString::ex().getStrTblText(AETXT_VOLLSTAENDIG).GetString() );
            CDialogMultiLang::OnOK();
        }
    }
}

/** FUNKTION: ONHOOKFKT (Tastatureingabe pruefen)*************************************/

LRESULT CWeLaEk::OnHookFkt(WPARAM, LPARAM lpMsg)
{
    int bst = 0;
    char auswahl[L_AUSWAHL] = {0};
    int zeile = 0;

    if ((GetKeyState(VK_MENU) & ALT_TASTE) == ALT_TASTE)   /* ALT abfangen */
        return OK;

    if (GetFocus() == GetDlgItem(IDC_EDITARTIKELNR))
    {
        bst = (int)((LPMSG)lpMsg)->wParam;
        if (bst >= BST_A && bst <= BST_Z)
        {
            sprintf(auswahl, "%c", bst);
            CheckIdOfSelect(auswahl);
            return 1L;
        }
    }

    if (GetFocus() == GetDlgItem(IDC_LAUFTRAG))
    {
        bst = (int)((LPMSG)lpMsg)->wParam;

        if ((bst >= BST_A && bst <= BST_Z) || bst == ENTER)
        {
            if (bst == 13)
            {
                zeile = m_cListAuftrag.GetNextItem(-1, LVNI_SELECTED);
                strcpy(auswahl, m_cListAuftrag.GetItemText(zeile, P_KST));
            }
            if (bst >= BST_A && bst <= BST_Z)
                sprintf(auswahl, "%c", bst);

            CheckIdOfSelect(auswahl);
            GotoDlgCtrl(GetDlgItem(IDC_EDITARTIKELNR));
            return 1L;
        }
    }

    return (long)OK;
}

/** FUNKTION: INSERTCOUNTOFARTIKLE ***************************************************/

int CWeLaEk::InsertCountOfArticle(int pos)
{
    CWeLaEkMe dlgWeLaEkMe;

    dlgWeLaEkMe.m_StaticArtikelnr = m_cListAuftrag.GetItemText(pos, P_ARTIKELNR);
    dlgWeLaEkMe.m_StaticArtikelname = m_cListAuftrag.GetItemText(pos, P_ARTIKELNAME);
    dlgWeLaEkMe.m_StaticEinheit = m_cListAuftrag.GetItemText(pos, P_EINHEIT);

    return (int)dlgWeLaEkMe.DoModal();
}

/*############# CWELAEKME ###########################################################*/
/** FUNKTION: ONINITDIALOG (CWELAEKME) ***********************************************/

BOOL CWeLaEkMe::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    return TRUE;
}

/** FUNKTION: ONOK (CWELAEKME) *******************************************************/

void CWeLaEkMe::OnOK()
{
    CWeLaEk dlgWeLaEk;
    char char_menge[L_MENGE];

    if (m_cEditMenge.GetWindowTextLength() == LEER)
    {
        dlgWeLaEk.MsgDs(
            (char*)CResString::ex().getStrTblText(IDS_TXT_WARNUNG_DBLPKT).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_MENGENEINGABE).GetString() );
        GotoDlgCtrl(GetDlgItem(IDC_EDITMENGE));
        return;
    }

    m_cEditMenge.GetWindowText(char_menge, L_MENGE);

    artikelmenge = atoi(char_menge);
    if (artikelmenge == 0)
    {
        dlgWeLaEk.MsgDs(
            (char*)CResString::ex().getStrTblText(IDS_TXT_WARNUNG_DBLPKT).GetString(),
            (char*)CResString::ex().getStrTblText(AETXT_MENGENEINGABE).GetString() );
        GotoDlgCtrl(GetDlgItem(IDC_EDITMENGE));
        return;
    }

    CDialogMultiLang::OnOK();
}

/** FUNKTION: ONINITDIALOG ***********************************************************/

BOOL CWeLaEkMsg::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CRect msgrect;
    CRect drawrect;
    CDC* pdc = GetDC();
    int str_hoehe;
    int hoehe;
    char status[3];

    m_cStaticStatus.GetWindowText(status, 2);

    m_bBlinken = (strcmp(status, BLINKEN) == 0) ? true : false;
    if (m_bBlinken)
        SetTimer(1, 500, NULL);
    SetWindowText(m_cStringText);
    m_cStaticBtmHinweis.SetWindowText(" ");
    m_cStaticMsgbox.GetClientRect(msgrect);
    m_cStaticMsgbox.ClientToScreen(msgrect);
    ScreenToClient(msgrect);

    /*** Static verschieben *******************/
    m_cStaticMsgbox.GetClientRect(msgrect);
    m_cStaticMsgbox.ClientToScreen(msgrect);
    ScreenToClient(msgrect);

    // Tabulator wird erweitert
    pdc->DrawText(m_StaticMsg, (-1), drawrect, DT_EXPANDTABS | DT_CALCRECT);

    msgrect.right = msgrect.left + drawrect.Width();
    msgrect.bottom = msgrect.top + drawrect.Height();
    str_hoehe = msgrect.top;
    hoehe     = drawrect.Height();
    m_cStaticMsgbox.MoveWindow(msgrect);

    /*** Button verschieben ******************/
    m_cButtonOk.GetClientRect(drawrect);
    m_cButtonOk.ClientToScreen(drawrect);
    ScreenToClient(drawrect);
    drawrect.OffsetRect( ((msgrect.right - drawrect.Width() + 15) / 2) -
                         drawrect.left, 15 + max(msgrect.bottom, 50) -
                         drawrect.top );

    m_cButtonOk.MoveWindow(drawrect);
    msgrect.bottom = drawrect.bottom;

    /*** Dialog ausrichten *******************/
    GetWindowRect(drawrect);

    drawrect.left   = drawrect.left - 27;
    drawrect.right  = drawrect.left + msgrect.right + 27;
    drawrect.bottom = drawrect.top  + msgrect.bottom + str_hoehe + 25;
    MoveWindow(drawrect);

    /*** Bitmap anzeigen *********************/
    LoadPicture(hoehe);

    ReleaseDC(pdc);
    if (m_bBlinken)
        ShowWindow(SW_SHOWMAXIMIZED);
    return TRUE;
}

/** FUNKTION: ONHOOKFKT ( CWELAEKMSG ) ***********************************************/

LRESULT CWeLaEkMsg::OnHookFkt(WPARAM, LPARAM lpMsg)
{
    int  bst = 0;
    static int zaehler = 0;

    if ((GetKeyState(VK_MENU) & ALT_TASTE) == ALT_TASTE)   /* ALT abfangen */
        return (long)OK;

    bst = (int)((LPMSG)lpMsg)->wParam;
    if (bst == ENTER && zaehler == 0)
    {
        CDialogMultiLang::OnOK();
        return 1L;
    }

    ++zaehler;
    if (bst == ENTER && zaehler > 0)
        zaehler = 0;

    return 1L;
}

/** FUNKTION: LOAD-PICTURE ( CWELAEKMSG ) ********************************************/

void CWeLaEkMsg::LoadPicture(int hoehe)
{
    CBitmap* pBmpOld;
    //RECT rectStaticClient;
    CRect rectStaticClient;
    BITMAP bmInfo;

    VERIFY(m_bmpPicture.LoadBitmap(IDB_HINWEIS));

    // Größe aus Bitmap holen
    m_bmpPicture.GetObject(sizeof(BITMAP), &bmInfo);
    m_size.cx = bmInfo.bmWidth;
    m_size.cy = bmInfo.bmHeight;

    // Position aus Control holen
    m_cStaticBtmHinweis.GetClientRect(rectStaticClient);
    m_cStaticBtmHinweis.ClientToScreen(rectStaticClient); // Convert to Dialog coordinates
    ScreenToClient(rectStaticClient);

    m_pt.x = rectStaticClient.left;
    m_pt.y = rectStaticClient.top + (hoehe / 3);

    m_cStaticBtmHinweis.ShowWindow(SW_SHOWNA);
    m_cStaticBtmHinweis.MoveWindow(m_pt.x, m_pt.y, m_size.cx + 10, m_size.cy + 10); // +10 für einrücken
    m_pt.x += 5;
    m_pt.y += 5;      // 5 Pixel eingerückt
    // Get temporary DC for dialog - Will be released in dc destructor

    CClientDC dc(this);

    VERIFY(m_dcMem.CreateCompatibleDC(&dc));        // DC erzeugen
    pBmpOld = m_dcMem.SelectObject(&m_bmpPicture);  // Bitmap hineinselektieren
    VERIFY(pBmpOld);
    m_hBmpOld = (HBITMAP)pBmpOld->GetSafeHandle();
    VERIFY(m_hBmpOld);  // altes Bitmap-Handle sichern
    m_bHasPicture = TRUE;
}

/** FUNKTION: ONDESTROY ( CWELAEKMSG ) ***********************************************/

void CWeLaEkMsg::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    // Ressourcen freigeben
    if (m_bHasPicture)
    {
        ASSERT(m_hBmpOld);
        VERIFY(m_dcMem.SelectObject(CBitmap::FromHandle(m_hBmpOld)));
        // Need to DeleteObject() the bitmap which was loaded.
        m_bmpPicture.DeleteObject();
        if (m_bBlinken)
            KillTimer(1);
    }
}

/** FUNKTION: ONPAINT ( CWELAEKMSG ) *************************************************/

void CWeLaEkMsg::OnPaint()
{
    CPaintDC dc(this);

    if (m_bHasPicture)
        dc.BitBlt(m_pt.x, m_pt.y, m_size.cx, m_size.cy, &m_dcMem, 0, 0, SRCCOPY);
}

/** FUNKTION: ONTIMER ( CWELAEKMSG ) *************************************************/

void CWeLaEkMsg::OnTimer(UINT nIDEvent)
{
    static bool normal = true;

    if (!m_bBlinken)
        return;

    if (normal)
    {
        ShowWindow(SW_SHOWNORMAL);
        normal = false;
    }
    else
    {
        ShowWindow(SW_SHOWMAXIMIZED);
        normal = true;
    }

    Invalidate(FALSE);
    CDialogMultiLang::OnTimer(nIDEvent);
}

/** FUNKTION: SETLINEFEEDFORSTRING ***************************************************/

void CWeLaEk::SetLineFeedForString(char* str)
{
    int i;
    int anz_char = 1;
    int z;
    int anz;

    if (strlen(str) > MAX_STR_LAENGE)
    {
        for (i = 0; i < (int)strlen(str); i++)
        {
            if (str[i] == BLANC)
            {
                anz = 1;
                for (z = (i + 1); (str[z] != STRENDE && str[z] != BLANC); z++)
                    ++anz;
                if ((MAX_STR_LAENGE - (anz + anz_char)) < 0)
                {
                    str[i] = LINEFEED;
                    anz_char = 0;
                }
            }
            ++anz_char;
        }
    }
}

/** FUNKTION: CWE-LA-EK-KL ONINIT-DIALOG *********************************************/

BOOL CWeLaEkKl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    switch (g_iSound)
    {
    case IDC_RADIO10:
        CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO10);
        break;
    case IDC_RADIO11:
        CheckRadioButton( IDC_RADIO10,IDC_RADIO14,IDC_RADIO11 );
        break;
    case IDC_RADIO13:
        CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO13);
        break;
    case IDC_RADIO12:
        CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO12);
        break;
    case IDC_RADIO14:
        CheckRadioButton(IDC_RADIO10, IDC_RADIO14, IDC_RADIO14);
        break;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

/** FUNKTION: ONBUTTONTEST ( CWELAEKKL ) *********************************************/

void CWeLaEkKl::OnButtonTest()
{
    SendeSound(m_SendeFehler);
}

/** FUNKTION: ONRADIOANRUF ( CWELAEKKL ) *********************************************/

void CWeLaEkKl::OnRadioAnruf()
{
    g_iSound = IDC_RADIO13;
    m_SendeFehler = "ringout.wav";
}

/** FUNKTION: ONRADIOKLINGEL ( CWELAEKKL ) *******************************************/

void CWeLaEkKl::OnRadioKlingel()
{
    g_iSound = IDC_RADIO11;
    m_SendeFehler = "chimes.wav";
}

/** FUNKTION: ONRADIOSOUND ( CWELAEKKL ) *********************************************/

void CWeLaEkKl::OnRadioSound()
{
    g_iSound = IDC_RADIO12;
    m_SendeFehler = "tada.wav";
}

/** FUNKTION: ONRADIOTEXT ( CWELAEKKL ) **********************************************/

void CWeLaEkKl::OnRadioText()
{
    g_iSound = IDC_RADIO10;
    m_SendeFehler = "ansag.wav";
}

/** FUNKTION: ONRADIOTON ( CWELAEKKL ) ***********************************************/

void CWeLaEkKl::OnRadioTon()
{
    g_iSound = IDC_RADIO14;
    m_SendeFehler = "ding.wav";
}

/********** SETZTESTRENDE ***************************************************/

void SetzeStrEnde(char* str, int anweisung)
{
    int i;

    if (anweisung == VORWAERTS)
    {
        for (i = 0; i < (int)strlen(str); i++)
        {
            if (str[i] == BLANC)
            {
                str[i] = STR_ENDE;
                break;
            }
        }
    }
    if (anweisung == RUECKWAERTS)
    {
        for (i = ((int)strlen(str) - 1); i >= 0; i--)
        {
            if (str[i] != BLANC && str[i] != STR_ENDE)
            {
                str[i + 1] = STR_ENDE;
                break;
            }
        }
        if (i == -1)
            str[0] = STR_ENDE;
    }
}

/********** SETZTPRUEFZIFFER ************************************************/

void SetzePruefziffer(char* nr)
{
    char artikel_nr[8];

    sprintf(artikel_nr, "%06ld", atol(nr));
    artikel_nr[6] = (( 2 * ( artikel_nr[0] - 48 ) +
                       3 * ( artikel_nr[1] - 48 ) +
                       4 * ( artikel_nr[2] - 48 ) +
                       5 * ( artikel_nr[3] - 48 ) +
                       6 * ( artikel_nr[4] - 48 ) +
                       7 * ( artikel_nr[5] - 48 )) % 11 ) + 48;
    if (artikel_nr[6] == ':')               /* Modul ergibt 10 - ascii :    */
        artikel_nr[6] = '0';
    artikel_nr[7] = '\0';
    strcpy(nr, artikel_nr);
}


/********** SENDE_SOUND *****************************************************/

void SendeSound(LPSTR sound)
{
    UINT Flags = SND_ASYNC;

    sndPlaySound((LPSTR)sound, Flags);
}

/********** WertKontrolle ***************************************************/

static int WertKontr(class CEdit* edit, long max)
{
    char buf[22], error_msg[81];
    long erg;

    edit->GetWindowText(buf, 20);
    if (buf[0] == '\0')
        return -1;
    if (AllgReadLong(buf, &erg, 0L, max, error_msg) < 0)
    {
        FehlerBehandlung(-2, error_msg);
        edit->SetWindowText("");
        edit->SetFocus();
        return -1;
    }
    return 0;
}
