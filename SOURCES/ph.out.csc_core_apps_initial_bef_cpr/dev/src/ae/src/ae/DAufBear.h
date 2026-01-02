// daufbear.h : header file
//
#include "AIListctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDAufBear dialog
class CAIListCtrl;

class CDAufBear : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDAufBear(CWnd* pParent = NULL);    // standard constructor
    virtual ~CDAufBear();
    CAeDoc *ptrDoc;                     // Zeiger auf das Dokument
    CImageList  m_ImageSmall;
    BOOL        m_bDefektAnzeige;       // Schalter fuer Defektanzeige
    int         m_iDefNachPos;          // aktuelle Position in der Defektnachbearbeitungsliste
    BOOL        m_bDefSelVerbund;       // Defektanzeige Auswahlschalter Verbundartikel
    BOOL        m_bDefSelDfDef;         // Defektanzeige Auswahlschalter
    BOOL        m_bDefSelPhonDef;       // Defektanzeige Auswahlschalter
    BOOL        m_bDefSelDfFrText;      // Defektanzeige Auswahlschalter
    BOOL        m_bDefSelPhonFrText;    // Defektanzeige Auswahlschalter
    BOOL        m_bArtAnschreiben;      // Uebergebenen Artikel anschreiben
    BOOL        m_bArtUebernehmen;      // Artikel uebernehmen, aber nicht anschreiben
    bool        m_bKndSchwerpunk3;      // Arbeitskreis aktuell
    bool        m_bKndSchwerpunk5;      // Diabetes
    CString     m_CArtName;             // Fuer DAFUE-Nachbearbeitung
    CString     m_CArtEinh;             // Fuer DAFUE-Nachbearbeitung
    CString     m_CArtDarr;             // Fuer DAFUE-Nachbearbeitung
    CString     m_VerbundZeitenKnd;     // Verbundzeiten des Kunden
    long        m_lMenge;               // Fuer DAFUE-Nachbearbeitung
    long        m_lKndNr;               // aktuelle Kundennr
    long        m_IdfNr;                // aktuelle IDF-nr
    short       m_VzNr;                 // aktuelle VZ-nr
    short       m_OrgFilNr;             // orginal VZ des Kunden
    long        m_lAuftrNr;             // aktuelle Auftragnr
    bool        m_bDafueKz;             // Kennz. Dafue-defekte abarbeiten
    bool        m_bMengWarn;            // Kennz. Große Menge als Warnung ausgeben
    bool        m_bKndMussKopfBem;      // Auftragskopfbemerkung erzwingen
    CString     m_CAufArt;              // Auftragsart
    CString     m_CPreis;               // Preis
    CString     m_CCharge;              // Charge
    bool        m_bNatraDefs;           // Kennz. Natra-defekte abarbeiten
    CTM         zeit;
    bool        m_bKz_Kunde_Verbund;    // Kennz. Kunde kann Verbund
    CString     m_CArticleCode;         // Artikel-Code
    long        m_lDeliveryDate;        // Lieferdatum
    CString     m_Tour;                 // Tour des Auftrags

    // Dialog Data
    enum { IDD = IDD_AE_AUF_BEARB };
    CButton m_CBVerbund;
    CButton m_CBFtPhon;
    CButton m_CBFtDafue;
    CButton m_CBDefPhon;
    CButton m_CBDefDafue;
    CEdit   m_EditSuchBez;
    CEdit   m_EditPosNr;
    CAIListCtrl *m_ListCtl;
//  CListCtrl   m_ListCtl;
    CString m_CTelNr;
    CString m_CKurzWahl;


// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    void    ChangePos();                                        //Aendern einer Position (Dialog)
    void    AlterPosition(  AUFPOSBUCH *ptrPos,
                            int posNr,
                            int menge,
                            int buchmenge,
                            CString bemerkung,
                            int buchStat,
                            CString natRabMenge,
                            CString preis,
                            int preisTyp,
                            CString pctMan,
                            CString charge,
                            BOOL fixCharge
                         ); //Aendern einer Position (Buchung)
    long    SelListPos();
    long    SelListPos(long* Menge, CString& ArtName, CString& ArtEinh, CString& ArtDarr);     // ArtikelNr des ausgewählten Art. best.
    void    MarkListPosChar(int Letter);                        // Markiert Pos. nach Eingabe Kennbuchstaben
    void    MarkListPos(int pos);                               // Markiert eine  Position
    void    SetMarked(int pos);                                 // Markiert einen Listeintrag als bearbeitet
    void    SelPosNr();                                         // Markiert entspr. Auftr.-Pos.-Nr
    void    SelSuchBez();                                       // Markiert ersten Eintrag mit entspr. Suchbez.
    void    SelArtNo();                                         // Markiert die entspr. Articleno.
    void    FillList();                                         // Füllt Listbox
    void    FillPosList();
    void    UpdateListPos(int pos, long OrdPos);                // Schreibt einen eintrag in der Listbox                // Änd. ListPos entspr. Speicherliste
    int     GetMaxAufPos();                                     // Liefert die max. Auf. Pos im Auftrag
    long    GetAufPos(int pos);                                 // giebt Auftragsposition zurück
    CString m_ArtName;
    CString m_ArtEinh;
    CString m_ArtNr;
    void    SetColumnWidthUser(CListCtrl* lc, char* name, char* keypath, int anz);
    void    WriteColumnWidthUser(CListCtrl* lc, char* name, char* keypath, int anz);
    void    CheckLinkPos(int linkpos);                          // Nachlesen verlinkte Position

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnKeydownListAuftrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkListAuftrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnChangeEditPosition();
    afx_msg void OnChangeEditSuchbez();
    virtual void OnCancel();
    afx_msg void OnCheckDefDafue();
    afx_msg void OnCheckDefPhon();
    afx_msg void OnCheckFtDafue();
    afx_msg void OnCheckFtPhon();
    afx_msg void OnButtonDruck();
    afx_msg void OnButtonAllPos();
    afx_msg void OnCheckVerbund();
    afx_msg void OnDestroy();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()

private:
    void RunArtInfDlg(long lArtikelNr);
    CString ToString(long lValue);
};
