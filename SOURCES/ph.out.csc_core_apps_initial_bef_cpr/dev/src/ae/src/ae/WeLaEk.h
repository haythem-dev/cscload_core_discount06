// welaek.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeLaEk dialog

class CWeLaEk : public CDialogMultiLang
{
// Construction
public:
    int      m_iAnzPositionen;
    CWeLaEk(CWnd* pParent = NULL);   // standard constructor

    void MsgDs( char *, char * );
    int  ReadInListBox( int iCountColumns );
    int  CheckNumberOfArticle( char * );
    int  CheckIdOfSelect( char * );
    void DeleteStringFromListBox( int, int, int );
    int  CallServerLs( class CAUFENDKOPF *, char * );
    int  InsertCountOfArticle( int );
    void CallArtikelInfo( char *, char * );
    void SetLineFeedForString( char * );
    int  PruefeArtikelInLs( char * );
    LRESULT OnHookFkt( WPARAM , LPARAM lpMsg );

    enum { IDD = IDD_LAGER_ENDKONTR };
    CListCtrl m_cListAuftrag;
    CEdit m_cEditArtikelnr;
    CString  m_StaticAdr1;
    CString  m_StaticAdr2;
    CString  m_StaticAdr3;
    CString  m_StaticLsnr;
    CString  m_StaticHausnr;
    CString  m_StaticTournr;
    CString  m_StaticKontnr;
    CString  m_StaticKundnr;
    CString  m_StaticAuftnr;
    CString  m_StaticSeitnr;
    CString  m_StaticAdr4;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnButtonbearbeitet();
    afx_msg void OnDblclkList1(NMHDR* , LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CWeLaEkLs dialog

class CWeLaEkLs : public CDialogMultiLang
{
// Construction
public:
    CWeLaEkLs(CWnd* pParent = NULL); // standard constructor

    enum { IDD = IDD_LAGER_LS_ENDKONTR };
    CEdit m_cEditBlockbis;
    CEdit m_cEditBlockvon;
    CEdit m_cEditSeitnr;
    CEdit m_cEditRechnr;
    CEdit m_cEditBarcode;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnButtonKlang();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CWeLaEkMe dialog

class CWeLaEkMe : public CDialogMultiLang
{
// Construction
public:
    CWeLaEkMe(CWnd* pParent = NULL); // standard constructor

    enum { IDD = IDD_LAGER_ME_ENDKONTR };
    CEdit m_cEditMenge;
    CString  m_StaticArtikelnr;
    CString  m_StaticEinheit;
    CString  m_StaticArtikelname;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CWeLaEkMsg dialog

class CWeLaEkMsg : public CDialogMultiLang
{
// Construction
public:
    CWeLaEkMsg(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_LAGER_ENDKONTR_MSG };
    CStatic  m_cStaticStatus;
    CStatic  m_cStaticBtmHinweis;
    CButton  m_cButtonOk;
    CStatic  m_cStaticMsgbox;
    CString  m_StaticMsg;
    CString  m_cStringText;
    CString  m_cStringStatus;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support
    LRESULT OnHookFkt( WPARAM , LPARAM lpMsg );
    CDC m_dcMem;            // Compatible Memory DC for dialog
    CBitmap m_bmpPicture;   // Bitmap to display
    HBITMAP m_hBmpOld;      // Handle of old bitmap to save
    CPoint  m_pt;           // Position for upper left corner of bitmap
    CSize   m_size;         // Size (width and height) of bitmap
    BOOL    m_bHasPicture;
    void LoadPicture(int);
    bool m_bBlinken;

    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT nIDEvent);
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CWeLaEkKl dialog

class CWeLaEkKl : public CDialogMultiLang
{
// Construction
public:
    CWeLaEkKl(CWnd* pParent = NULL);    // standard constructor

    enum { IDD = IDD_LAGER_ENDKONTR_KLANG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnButtonTest();
    afx_msg void OnRadioAnruf();
    afx_msg void OnRadioKlingel();
    afx_msg void OnRadioSound();
    afx_msg void OnRadioText();
    afx_msg void OnRadioTon();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};
