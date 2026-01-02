// daltart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAltArt dialog

class CDAltArt : public CDialogMultiLang
{
public:
    CDAltArt(CWnd* pParent = NULL);     // standard constructor
    bool m_bOrigArt;                    // keinen Alternativartikel auswaehlen
    BOOL m_bNetto;                      // Nettoartikel
    BOOL m_bNatra;                      // Natraartikel
    bool m_bKndSchwerpunk3;             // Arbeitskreis aktuell
    bool m_bKndSchwerpunk5;             // Diabetes
    long m_KundenNr;                    // Kundennummer

    enum { IDD = IDD_AE_ALERN_ART };
    CString m_AltArtBest;
    CString m_AngArtBest;
    CString m_ArtName;
    CString m_ArtEinheit;
    CString m_ArtNr;
    CString m_CDarreichform;
    CString m_CArtNameOrg;
    CString m_CArtEinhOrg;
    CString m_CArtDarrOrg;
    CString m_CArtNrOrg;
    CString m_CArtCodeOrg;
    CString m_CArtCodeAltern;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

    afx_msg void OnOrigArt();
    afx_msg void OnOrigArtinfo();
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()
};
