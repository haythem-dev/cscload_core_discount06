// DParKoBehTyp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParKoBehTyp dialog

class CDParKoBehTyp : public CDialogMultiLang
{
// Construction
public:
    CDParKoBehTyp(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_KOBEHTYP };
    CListCtrl m_ListCtl;
    short m_FilialNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(int Filiale,
                      int Typ,
                      long Laenge,
                      long Hoehe,
                      long Breite,
                      long Volumen);

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParKoBehTypUpd dialog

class CDParKoBehTypUpd : public CDialogMultiLang
{
// Construction
public:
    BOOL m_bUpdate;                         // Schalter ob Update oder Insert
    CDParKoBehTypUpd(CWnd* pParent = NULL); // standard constructor

    enum { IDD = IDD_AE_PAR_KOBEHTYP_UPD };
    CEdit m_EditVolumen;
    CEdit m_EditTyp;
    CEdit m_EditLaenge;
    CEdit m_EditHoehe;
    CEdit m_EditFiliale;
    CEdit m_EditBreite;
    long m_lBreite;
    int  m_iFiliale;
    long m_lHoehe;
    long m_lLaenge;
    int  m_iTyp;
    long m_lVolumen;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEditBreite();
    afx_msg void OnChangeEditHoehe();
    afx_msg void OnChangeEditLaenge();
    afx_msg void OnChangeEditTyp();
    afx_msg void OnChangeEditVolumen();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};
