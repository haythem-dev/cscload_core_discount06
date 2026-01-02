// DParAuftrendzeit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParAuftrendzeit dialog

class CDParAuftrendzeit : public CDialogMultiLang
{
// Construction
public:
    CDParAuftrendzeit(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_AUFTRENDZEIT };
    CListCtrl m_ListCtl;
    short m_FilialNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(int Filiale, long Art, int HFili, int Modus, long Zeit);
    void Art2Char(long Art, CString &CArt);
    void Art2Long(long *Art, CString CArt);
    void Modus2Char(short Modus, CString &CModus);
    void Modus2Int(short *Modus, CString CModus);

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParAuftrendzeitUpd dialog

class CDParAuftrendzeitUpd : public CDialogMultiLang
{
// Construction
public:
    BOOL m_bUpdate;                         // Schalter ob Update oder Insert
    int m_IModus;
    int m_LArt;
    CDParAuftrendzeitUpd(CWnd* pParent = NULL);   // standard constructor
    short m_FilialNr;

    enum { IDD = IDD_AE_PAR_AUFTRENDZEIT_UPD };
    CEdit   m_EditZeit;
    CEdit   m_EditHerkunft;
    CEdit   m_EditFiliale;
    int     m_iFiliale;
    CString m_CHerkunft;
    CString m_CZeit;
    int     m_IRadio11;
    int     m_IRadio31;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditZeit();
    afx_msg void OnChangeEditHerkunft();

    DECLARE_MESSAGE_MAP()
};
