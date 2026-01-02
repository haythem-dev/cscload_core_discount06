// DCheckOpenCallOrOrder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDCheckOpenCallOrOrder dialog

class CDCheckOpenCallOrOrder : public CDialogMultiLang
{
// Construction
public:
    CDCheckOpenCallOrOrder(CWnd* pParent = NULL);   // standard constructor
    long GetOrderNr() { return m_OrderNr; }
    long GetCustomerNr() { return m_CustomerNr; }
    short GetVZNr() { return m_VZNr; }

    enum { IDD = IDD_AE_CHECK_OPEN_CALL_OR_ORDER };
    CStatic m_StaticBalken;
    CStatic m_StaticText;
    CString m_CText;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL IsOrder();     //gibt es Auftraege/Rufe zu bearbeiten
    BOOL IsOpenOrder(); //gibt es zurueckgestellte Auftraege
    BOOL IsCallOrder(); //gibt es aktualle Rufe im Rufplan
    BOOL Order();       //Auftraege/Rufe bearbeiten
    BOOL OpenOrder();   //zurueckgestellte Auftraege
    BOOL CallOrder();   //aktualle Rufe im Rufplan
    void SetOrderIsPossible(BOOL bIsPossible = TRUE);

    long m_OrderNr;
    long m_CustomerNr;
    short m_VZNr;
    BOOL m_bCancel;

    virtual void OnCancel();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    DECLARE_MESSAGE_MAP()
};
